// Root-only, same-ABI ptrace/dlopen loader. Does not alter SELinux or anti-cheat.
#include "brand.h"
#include <sys/ptrace.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#if defined(__aarch64__)
#include <asm/ptrace.h>
#ifndef NT_ARM_SYSTEM_CALL
#define NT_ARM_SYSTEM_CALL 0x404
#endif
using Registers = user_pt_regs;
static uintptr_t pc(const Registers& r) { return r.pc; }
static uintptr_t result(const Registers& r) { return r.regs[0]; }
#elif defined(__x86_64__)
#include <sys/user.h>
using Registers = user_regs_struct;
static uintptr_t pc(const Registers& r) { return r.rip; }
static uintptr_t result(const Registers& r) { return r.rax; }
#else
#error "This helper supports ARM64 and x86_64 only"
#endif

static void require(bool ok, const std::string& message) {
    if(!ok) throw std::runtime_error(message + ": " + std::strerror(errno));
}
static int waitStop(pid_t pid, int seconds) {
    auto end=std::chrono::steady_clock::now()+std::chrono::seconds(seconds);
    while(std::chrono::steady_clock::now()<end) {
        int status=0; pid_t got=waitpid(pid,&status,__WALL|WNOHANG);
        if(got==pid) return status;
        if(got<0 && errno!=EINTR) throw std::runtime_error("waitpid failed");
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    throw std::runtime_error("Remote call timeout; target is being stopped to avoid resuming with corrupted registers");
}
static Registers getRegs(pid_t pid) {
    Registers r{}; iovec v{&r,sizeof(r)};
    require(ptrace(PTRACE_GETREGSET,pid,reinterpret_cast<void*>(NT_PRSTATUS),&v)==0,"GETREGSET");
    if(v.iov_len!=sizeof(r)) throw std::runtime_error("Target ABI differs from loader ABI");
    return r;
}
static void setRegs(pid_t pid,const Registers& r) {
    iovec v{const_cast<Registers*>(&r),sizeof(r)};
    require(ptrace(PTRACE_SETREGSET,pid,reinterpret_cast<void*>(NT_PRSTATUS),&v)==0,"SETREGSET");
}
static std::vector<unsigned char> readMemory(pid_t pid,uintptr_t at,size_t size) {
    std::vector<unsigned char> out(size);
    for(size_t i=0;i<size;i+=sizeof(long)) {
        errno=0; long word=ptrace(PTRACE_PEEKDATA,pid,reinterpret_cast<void*>(at+i),nullptr);
        require(!(word==-1 && errno),"PTRACE_PEEKDATA");
        std::memcpy(out.data()+i,&word,std::min(sizeof(word),size-i));
    }
    return out;
}
static void writeMemory(pid_t pid,uintptr_t at,const void* data,size_t size) {
    const auto* bytes=static_cast<const unsigned char*>(data);
    for(size_t i=0;i<size;i+=sizeof(long)) {
        long word=0; size_t count=std::min(sizeof(word),size-i);
        if(count!=sizeof(word)) { auto previous=readMemory(pid,at+i,sizeof(word)); std::memcpy(&word,previous.data(),sizeof(word)); }
        std::memcpy(&word,bytes+i,count);
        require(ptrace(PTRACE_POKEDATA,pid,reinterpret_cast<void*>(at+i),reinterpret_cast<void*>(word))==0,"PTRACE_POKEDATA");
    }
}
struct Mapping { uintptr_t start,end,offset; std::string perms,path; };
static std::vector<Mapping> maps(pid_t pid) {
    std::ifstream f("/proc/"+std::to_string(pid)+"/maps");
    if(!f) throw std::runtime_error("Cannot read process maps");
    std::vector<Mapping> out; std::string line;
    while(std::getline(f,line)) {
        unsigned long a,b,o; char perms[8]; int used=0;
        if(std::sscanf(line.c_str(),"%lx-%lx %7s %lx %*s %*s %n",&a,&b,perms,&o,&used)!=4) continue;
        std::string path=line.substr(used); while(!path.empty() && path.front()==' ') path.erase(0,1);
        out.push_back({a,b,o,perms,path});
    }
    return out;
}
static uintptr_t remoteSymbol(pid_t pid,const char* name) {
    void* sym=dlsym(RTLD_DEFAULT,name);
    if(!sym) throw std::runtime_error(std::string("Missing local symbol: ")+name);
    uintptr_t addr=reinterpret_cast<uintptr_t>(sym);
    auto own=maps(getpid()); auto remote=maps(pid);
    for(const auto& m:own) if(addr>=m.start && addr<m.end) {
        uintptr_t fileOffset=addr-m.start+m.offset;
        for(const auto& r:remote) if(r.path==m.path && r.perms.find('x')!=std::string::npos && fileOffset>=r.offset && fileOffset<r.offset+r.end-r.start)
            return r.start+(fileOffset-r.offset);
        throw std::runtime_error(std::string("Matching runtime mapping not found for ")+name+" (namespace/ABI mismatch)");
    }
    throw std::runtime_error(std::string("Cannot resolve mapping for ")+name);
}

class Trace {
    pid_t pid_; bool attached_=false, stopped_=false, safe_=true;
    Registers original_{};
#if defined(__aarch64__)
    int originalSyscall_=-1;
    void setSyscall(int nr) {
        iovec v{&nr,sizeof(nr)};
        require(ptrace(PTRACE_SETREGSET,pid_,reinterpret_cast<void*>(NT_ARM_SYSTEM_CALL),&v)==0,"SETREGSET syscall number");
    }
#endif
    uintptr_t scratch_=0; std::vector<unsigned char> stack_;
public:
    explicit Trace(pid_t pid):pid_(pid) {
        require(ptrace(PTRACE_ATTACH,pid_,nullptr,nullptr)==0,"PTRACE_ATTACH (check root/SELinux)"); attached_=true;
        try {
            int s=waitStop(pid_,5);
            if(!WIFSTOPPED(s)) throw std::runtime_error("Process exited during attach");
            stopped_=true; original_=getRegs(pid_);
#if defined(__aarch64__)
            iovec syscallInfo{&originalSyscall_,sizeof(originalSyscall_)};
            require(ptrace(PTRACE_GETREGSET,pid_,reinterpret_cast<void*>(NT_ARM_SYSTEM_CALL),&syscallInfo)==0,"GETREGSET syscall number");
            scratch_=(original_.sp-4096)&~uintptr_t(15);
#else
            scratch_=(original_.rsp-4096)&~uintptr_t(15);
#endif
            // Preserve a private slice of the existing stack for every remote call.
            stack_=readMemory(pid_,scratch_-16384,4096+16384);
        } catch(...) { if(stopped_) ptrace(PTRACE_DETACH,pid_,nullptr,nullptr); else { kill(pid_,SIGSTOP); ptrace(PTRACE_DETACH,pid_,nullptr,reinterpret_cast<void*>(SIGSTOP)); } throw; }
    }
    ~Trace() {
        if(!attached_) return;
        if(stopped_) {
            if(safe_) {
                try {
                    if(!stack_.empty()) writeMemory(pid_,scratch_-16384,stack_.data(),stack_.size());
                    setRegs(pid_,original_);
#if defined(__aarch64__)
                    setSyscall(originalSyscall_);
#endif
                }
                catch(...) { safe_=false; }
            }
            ptrace(PTRACE_DETACH,pid_,nullptr,reinterpret_cast<void*>(safe_?0:SIGSTOP));
        }
    }
    uintptr_t call(uintptr_t fn,std::initializer_list<uintptr_t> args) {
        if(args.size()>6) throw std::runtime_error("Too many remote-call arguments");
        Registers r=original_; size_t i=0;
#if defined(__aarch64__)
        for(auto a:args) r.regs[i++]=a;
        r.pc=fn; r.sp=scratch_; r.regs[30]=0;
#else
        decltype(r.rdi)* slots[]={&r.rdi,&r.rsi,&r.rdx,&r.rcx,&r.r8,&r.r9};
        for(auto a:args) *slots[i++]=a;
        uintptr_t zero=0; r.rsp=scratch_-8; writeMemory(pid_,r.rsp,&zero,sizeof(zero)); r.rip=fn; r.rax=0; r.orig_rax=~0UL;
#endif
        setRegs(pid_,r);
#if defined(__aarch64__)
        // Cancel a suspended syscall restart while running the injected call.
        setSyscall(-1);
#endif
        require(ptrace(PTRACE_CONT,pid_,nullptr,nullptr)==0,"PTRACE_CONT"); stopped_=false; safe_=false;
        int status;
        try { status=waitStop(pid_,15); }
        catch(...) {
            kill(pid_,SIGSTOP);
            try { int s=waitStop(pid_,3); stopped_=WIFSTOPPED(s); } catch(...) {}
            throw;
        }
        if(!WIFSTOPPED(status)) { attached_=false; throw std::runtime_error("Target exited during remote call"); }
        stopped_=true;
        Registers done=getRegs(pid_);
        if(WSTOPSIG(status)!=SIGSEGV || pc(done)!=0)
            throw std::runtime_error("Unexpected stop during remote call; target left stopped. Restart the game.");
        safe_=true;
        return result(done);
    }
};

static pid_t findProcess(const std::string& package) {
    DIR* dir=opendir("/proc"); require(dir!=nullptr,"opendir /proc");
    pid_t found=0; dirent* entry;
    while((entry=readdir(dir))) {
        char* end; long n=std::strtol(entry->d_name,&end,10); if(*end || n<=0) continue;
        std::ifstream f(std::string("/proc/")+entry->d_name+"/cmdline"); std::string cmd; std::getline(f,cmd,'\0');
        if(cmd==package) { if(found) { closedir(dir); throw std::runtime_error("Several users run this package; close the duplicate game instance"); } found=static_cast<pid_t>(n); }
    }
    closedir(dir);
    if(!found) throw std::runtime_error("Game is not running: "+package);
    return found;
}
static void validateElf(const std::string& path) {
    std::ifstream file(path,std::ios::binary); Elf64_Ehdr h{}; file.read(reinterpret_cast<char*>(&h),sizeof(h));
#if defined(__aarch64__)
    constexpr int machine=EM_AARCH64;
#else
    constexpr int machine=EM_X86_64;
#endif
    if(!file || std::memcmp(h.e_ident,ELFMAG,SELFMAG) || h.e_ident[EI_CLASS]!=ELFCLASS64 || h.e_ident[EI_DATA]!=ELFDATA2LSB || h.e_machine!=machine || h.e_type!=ET_DYN)
        throw std::runtime_error("Not a matching 64-bit ELF shared library: "+path);
}
struct Staged {
    std::string path;
    ~Staged() { if(!path.empty()) unlink(path.c_str()); }
};
static void stageLibrary(pid_t pid,const std::string& pkg,const std::string& source,Staged& staged,const char* extension=".so") {
    struct stat proc{}; require(stat(("/proc/"+std::to_string(pid)).c_str(),&proc)==0,"stat process");
    std::string data="/data/user/"+std::to_string(proc.st_uid/100000)+"/"+pkg;
    struct stat home{}; require(stat(data.c_str(),&home)==0,"stat target app directory");
    if(home.st_uid!=proc.st_uid) throw std::runtime_error("Target UID does not match application data directory");
    std::string cache=data+"/code_cache";
    if(mkdir(cache.c_str(),0700)==0) require(chown(cache.c_str(),home.st_uid,home.st_gid)==0,"chown code_cache");
    else require(errno==EEXIST,"mkdir code_cache");
    staged.path=cache+"/" BRAND_LIB_PREFIX+std::to_string(getpid())+extension;
    int in=open(source.c_str(),O_RDONLY|O_CLOEXEC); require(in>=0,"open source library");
    int out=open(staged.path.c_str(),O_WRONLY|O_CREAT|O_EXCL|O_NOFOLLOW|O_CLOEXEC,0600);
    if(out<0) { close(in); require(false,"create target library"); }
    bool ok=true; char bytes[32768]; ssize_t n;
    while((n=read(in,bytes,sizeof(bytes)))>0) {
        ssize_t done=0;
        while(done<n) { ssize_t w=write(out,bytes+done,n-done); if(w<=0) { ok=false; break; } done+=w; }
        if(!ok) break;
    }
    ok=ok && n==0 && fchown(out,home.st_uid,home.st_gid)==0 && fchmod(out,0400)==0;
    close(in); close(out); require(ok,"copy target library");
    // Restore the normal app-data label; never disable or relax SELinux.
    pid_t child=fork(); require(child>=0,"fork restorecon");
    if(child==0) { execl("/system/bin/restorecon","restorecon",cache.c_str(),staged.path.c_str(),nullptr); _exit(127); }
    int status=0; while(waitpid(child,&status,0)<0 && errno==EINTR) {}
    if(!WIFEXITED(status) || WEXITSTATUS(status)!=0) throw std::runtime_error("restorecon failed; refusing to load an incorrectly labelled library");
}
int main(int argc,char** argv) {
    try {
        if(geteuid()!=0) throw std::runtime_error("Root required");
        if((argc!=4&&argc!=5&&argc!=6) || std::string(argv[1])!="--package") throw std::runtime_error("Usage: loader --package com.example.game /absolute/library.so [internal-ui.dex] [headshot.ogg]");
        std::string package=argv[2];
        if(package.empty() || package.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.")!=std::string::npos || package.find("..")!=std::string::npos)
            throw std::runtime_error("Invalid package name");
        validateElf(argv[3]); pid_t pid=findProcess(package);
        validateElf("/proc/"+std::to_string(pid)+"/exe");
        for(const auto& mapping:maps(pid))
            if(mapping.path.find("/code_cache/" BRAND_LIB_PREFIX)!=std::string::npos)
                throw std::runtime_error("already loaded; restart");
        uintptr_t mmapFn=remoteSymbol(pid,"mmap"), dlopenFn=remoteSymbol(pid,"dlopen"), munmapFn=remoteSymbol(pid,"munmap"), errorFn=remoteSymbol(pid,"dlerror");
        Staged staged,dex,audio;
        if(argc>=5) stageLibrary(pid,package,argv[4],dex,".dex");
        if(argc==6) stageLibrary(pid,package,argv[5],audio,".ogg");
        stageLibrary(pid,package,argv[3],staged);
        uintptr_t handle=0;
        {
            Trace trace(pid);
            size_t len=staged.path.size()+1;
            uintptr_t remote=trace.call(mmapFn,{0,len,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,~uintptr_t(0),0});
            if(remote==~uintptr_t(0) || remote==0) throw std::runtime_error("rm");
            writeMemory(pid,remote,staged.path.c_str(),len);
            handle=trace.call(dlopenFn,{remote,RTLD_NOW|RTLD_LOCAL});
            std::string error;
            if(!handle) {
                uintptr_t ptr=trace.call(errorFn,{});
                if(ptr) { for(size_t i=0;i<2048;i++) { char ch=static_cast<char>(readMemory(pid,ptr+i,1)[0]); if(!ch) break; error+=ch; } }
            }
            trace.call(munmapFn,{remote,len});
            if(!handle) throw std::runtime_error("dl:"+error);
        }
        // Remove the on-disk file now that dlopen holds a mapping; keeps the name out of file scans.
        unlink(staged.path.c_str());
        // The game thread confirms that its Android view was attached.
        if(argc>=5) {
            const std::string marker=staged.path+".r";
            const std::string progress=staged.path+".p";
            bool ready=false;
            std::string lastStage;
            for(int attempt=0;attempt<1000;attempt++) {
                std::ifstream file(marker);
                std::string value;
                if(file>>value && value=="ready") {ready=true;break;}
                std::ifstream status(progress);
                std::string current;
                if(std::getline(status,current) && current!=lastStage) lastStage=current;
                if(lastStage.rfind("FAILED:",0)==0)break;
                if(kill(pid,0)!=0)break;
                usleep(100000);
            }
            unlink(marker.c_str());
            unlink(progress.c_str());
            if(!ready)throw std::runtime_error("st:"+(lastStage.empty()?std::string("x"):lastStage));
        }
        // Keep DEX and audio on disk under randomised names for lazy classloading and SoundPool.
        if(!dex.path.empty()) dex.path.clear();
        if(!audio.path.empty()) audio.path.clear();
        (void)handle;
        return 0;
    } catch(const std::exception& e) { std::fprintf(stderr,"err:%s\n",e.what()); return 1; }
}
