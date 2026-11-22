// inject.cpp — standalone aarch64 ptrace-инжектор (отдельный исполняемый файл)
// usage: ./inject <pid> <abs path to .so> <entry symbol>
// запускать от root; возвращает 0 при успехе, иначе код ошибки.
#include <dirent.h>
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/elf.h>
#include <linux/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#if !defined(__aarch64__)
    #error "inject-arm64 требует aarch64"
#endif

using regs_t = user_regs_struct;

static bool get_regs(pid_t pid, regs_t* r) {
    iovec iov{r, sizeof(*r)};
    return ptrace(PTRACE_GETREGSET, pid, (void*)NT_PRSTATUS, &iov) == 0;
}
static bool set_regs(pid_t pid, regs_t* r) {
    iovec iov{r, sizeof(*r)};
    return ptrace(PTRACE_SETREGSET, pid, (void*)NT_PRSTATUS, &iov) == 0;
}

static uintptr_t find_module_base(pid_t pid, const char* soname) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    FILE* f = fopen(path, "r");
    if (!f) return 0;
    char line[512];
    uintptr_t base = 0;
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, soname)) continue;
        if (sscanf(line, "%lx", (unsigned long*)&base) == 1) break;
    }
    fclose(f);
    return base;
}

static uintptr_t remote_sym(pid_t pid, const char* lib, const char* sym) {
    void* h = dlopen(lib, RTLD_LAZY | RTLD_GLOBAL);
    if (!h) { fprintf(stderr, "[vanta] dlopen(%s) fail: %s\n", lib, dlerror()); return 0; }
    void* local = dlsym(h, sym);
    if (!local) { dlclose(h); return 0; }
    uintptr_t our = find_module_base(getpid(), lib);
    if (!our) { dlclose(h); return 0; }
    uintptr_t their = find_module_base(pid, lib);
    dlclose(h);
    if (!their) return 0;
    return their + ((uintptr_t)local - our);
}

static bool poke_mem(pid_t pid, uintptr_t addr, const void* src, size_t n) {
    char path[64]; snprintf(path, sizeof(path), "/proc/%d/mem", pid);
    int fd = open(path, O_RDWR);
    if (fd < 0) return false;
    bool ok = lseek(fd, (off_t)addr, SEEK_SET) == (off_t)addr && write(fd, src, n) == (ssize_t)n;
    close(fd);
    return ok;
}

static bool wait_signal(pid_t pid, int* out_sig) {
    int st;
    if (waitpid(pid, &st, __WALL) < 0) return false;
    if (WIFSTOPPED(st) && out_sig) *out_sig = WSTOPSIG(st);
    return WIFSTOPPED(st);
}

// ждём именно SIGSEGV/SIGBUS/SIGILL (от прыжка в trap-LR).
// любой другой сигнал (SIGPROF/SIGCHLD/SIGALRM от Unity) пробрасываем обратно.
static bool wait_for_trap(pid_t pid) {
    for (int i = 0; i < 400; ++i) {
        int st;
        if (waitpid(pid, &st, __WALL) < 0) return false;
        if (!WIFSTOPPED(st)) return false;
        int sig = WSTOPSIG(st);
        if (sig == SIGSEGV || sig == SIGBUS || sig == SIGILL) return true;
        // пробрасываем сигнал обратно
        if (ptrace(PTRACE_CONT, pid, nullptr, (void*)(long)sig) != 0) return false;
    }
    return false;
}

// возвращает X0 после удара в trap-LR. Пробрасываем сигналы Unity (SIGPROF и т.п.).
// печатает диагностику чтобы понять что происходит.
static uintptr_t remote_call(pid_t pid, uintptr_t func, const uintptr_t* args, int nargs, uintptr_t trap) {
    regs_t r{};
    if (!get_regs(pid, &r)) return 0;
    regs_t backup = r;
    for (int i = 0; i < nargs && i < 8; ++i) r.regs[i] = args[i];
    r.pc = func;
    r.sp &= ~0xFULL;
    r.regs[30] = trap;
    if (!set_regs(pid, &r)) return 0;

    // verify set
    regs_t check{};
    get_regs(pid, &check);
    if (check.pc != func) {
        fprintf(stderr, "[vanta] set_regs: pc не записался (хотел 0x%lx, получил 0x%lx)\n",
                (unsigned long)func, (unsigned long)check.pc);
    }

    if (ptrace(PTRACE_CONT, pid, nullptr, nullptr) != 0) {
        fprintf(stderr, "[vanta] PTRACE_CONT: %s\n", strerror(errno));
        set_regs(pid, &backup);
        return 0;
    }

    // ждём SIGSEGV/SIGBUS/SIGILL. остальные пробрасываем.
    int got_sig = 0;
    for (int i = 0; i < 1000; ++i) {
        int st;
        if (waitpid(pid, &st, __WALL) < 0) {
            fprintf(stderr, "[vanta] waitpid err: %s\n", strerror(errno));
            break;
        }
        if (!WIFSTOPPED(st)) {
            fprintf(stderr, "[vanta] child not stopped st=0x%x\n", st);
            break;
        }
        int sig = WSTOPSIG(st);
        if (sig == SIGSEGV || sig == SIGBUS || sig == SIGILL || sig == SIGTRAP) {
            got_sig = sig;
            break;
        }
        // не наш сигнал — пробрасываем
        ptrace(PTRACE_CONT, pid, nullptr, (void*)(long)sig);
    }

    regs_t after{};
    get_regs(pid, &after);
    fprintf(stderr, "[vanta] call: pc_before=0x%lx -> pc_after=0x%lx x0=0x%lx sig=%d\n",
            (unsigned long)func, (unsigned long)after.pc, (unsigned long)after.regs[0], got_sig);
    uintptr_t ret = after.regs[0];
    set_regs(pid, &backup);
    return ret;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: %s <pid> <abs_so_path> <entry_symbol>\n", argv[0]);
        return 2;
    }
    pid_t pid_arg = (pid_t)atoi(argv[1]);
    const char* so = argv[2];
    const char* en = argv[3];

    // ищем ноушающий поток (State: R) — ptrace на нём не висит в чужом syscall
    pid_t pid = pid_arg;
    {
        char dir[64]; snprintf(dir, sizeof(dir), "/proc/%d/task", pid_arg);
        DIR* d = opendir(dir);
        if (d) {
            dirent* e;
            pid_t best = pid_arg;
            while ((e = readdir(d))) {
                if (e->d_name[0] < '0' || e->d_name[0] > '9') continue;
                pid_t tid = (pid_t)atoi(e->d_name);
                char status[128];
                snprintf(status, sizeof(status), "/proc/%d/task/%d/status", pid_arg, tid);
                FILE* f = fopen(status, "r");
                if (!f) continue;
                char line[256];
                while (fgets(line, sizeof(line), f)) {
                    if (strncmp(line, "State:", 6) == 0) {
                        if (line[7] == 'R') { best = tid; }
                        break;
                    }
                }
                fclose(f);
                if (best != pid_arg) break;
            }
            closedir(d);
            if (best != pid_arg) {
                fprintf(stderr, "[vanta] использую активный тред %d вместо %d\n", best, pid_arg);
                pid = best;
            }
        }
    }

    fprintf(stderr, "[vanta] attach %d\n", pid);
    if (ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) < 0) {
        fprintf(stderr, "[vanta] PTRACE_ATTACH %d: %s\n", pid, strerror(errno));
        return 3;
    }
    if (!wait_signal(pid, nullptr)) {
        fprintf(stderr, "[vanta] wait after attach failed\n");
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        return 4;
    }

    uintptr_t r_mmap        = remote_sym(pid, "libc.so",  "mmap");
    // __loader_dlopen / __loader_dlsym требуют caller_addr → надёжнее на Android 7+
    uintptr_t r_ldr_dlopen  = remote_sym(pid, "libdl.so", "__loader_dlopen");
    uintptr_t r_ldr_dlsym   = remote_sym(pid, "libdl.so", "__loader_dlsym");
    uintptr_t r_pub_dlopen  = remote_sym(pid, "libdl.so", "dlopen");
    uintptr_t r_pub_dlsym   = remote_sym(pid, "libdl.so", "dlsym");
    bool loader = r_ldr_dlopen != 0 && r_ldr_dlsym != 0;
    uintptr_t r_dlopen = loader ? r_ldr_dlopen : r_pub_dlopen;
    uintptr_t r_dlsym  = loader ? r_ldr_dlsym  : r_pub_dlsym;
    if (!r_mmap || !r_dlopen || !r_dlsym) {
        fprintf(stderr, "[vanta] remote symbols not resolved (mmap=%p dlopen=%p dlsym=%p)\n",
                (void*)r_mmap, (void*)r_dlopen, (void*)r_dlsym);
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        return 5;
    }
    fprintf(stderr, "[vanta] dlopen variant: %s\n", loader ? "__loader_dlopen" : "dlopen");

    // LR = заведомо невалидный addr (kernel-space для userspace процесса) → гарантированный SIGSEGV
    const uintptr_t TRAP = 0xDEADBEEFDEADBEEFULL;

    fprintf(stderr, "[vanta] remote_mmap RWX...\n");
    uintptr_t mm_args[6] = {
        0, 0x2000,
        (uintptr_t)(PROT_READ | PROT_WRITE | PROT_EXEC),
        (uintptr_t)(MAP_PRIVATE | MAP_ANONYMOUS),
        (uintptr_t)-1, 0
    };
    uintptr_t buf = remote_call(pid, r_mmap, mm_args, 6, TRAP);
    if (!buf || (intptr_t)buf == -1) {
        fprintf(stderr, "[vanta] remote mmap failed\n");
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        return 6;
    }

    // layout buf (2 страницы 0x2000):
    //   0x0000..0x0400 — путь к .so (или имя символа)
    //   0x0400..0x0408 — шеллкод (blr x8; brk #0)
    //   0x1FF0         — свой выровненный стек (растёт вниз)
    const uintptr_t str_addr   = buf;
    const uintptr_t shell_addr = buf + 0x400;
    const uintptr_t stack_addr = buf + 0x1FF0;   // свой стек, dlopen'у есть куда расти
    uint32_t shellcode[2] = { 0xD63F0100u /* blr x8 */, 0xD4200000u /* brk #0 */ };
    if (!poke_mem(pid, shell_addr, shellcode, sizeof(shellcode))) {
        fprintf(stderr, "[vanta] poke shellcode fail\n");
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        return 7;
    }

    size_t plen = strlen(so) + 1;
    if (!poke_mem(pid, str_addr, so, plen)) {
        fprintf(stderr, "[vanta] poke path fail\n");
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        return 7;
    }

    // remote_call_sh: pc=shell_addr, x8=func, x0..=args; SIGTRAP от brk.
    // используем свой стек (stack_addr) — активный тред может иметь почти-полный стек
    auto remote_call_sh = [&](uintptr_t func, const uintptr_t* a, int n) -> uintptr_t {
        regs_t r{}; if (!get_regs(pid, &r)) return 0;
        regs_t backup = r;
        for (int i = 0; i < n && i < 8; ++i) r.regs[i] = a[i];
        r.regs[8] = func;
        r.pc = shell_addr;
        r.sp = stack_addr & ~0xFULL;
        r.regs[30] = TRAP;
        if (!set_regs(pid, &r)) return 0;
        if (ptrace(PTRACE_CONT, pid, nullptr, nullptr) != 0) return 0;
        int got = 0;
        for (int i = 0; i < 1000; ++i) {
            int st;
            if (waitpid(pid, &st, __WALL) < 0) break;
            if (!WIFSTOPPED(st)) break;
            int sig = WSTOPSIG(st);
            if (sig == SIGTRAP || sig == SIGSEGV || sig == SIGBUS || sig == SIGILL) { got = sig; break; }
            ptrace(PTRACE_CONT, pid, nullptr, (void*)(long)sig);
        }
        regs_t af{}; get_regs(pid, &af);
        fprintf(stderr, "[vanta] sh-call func=0x%lx pc_after=0x%lx x0=0x%lx sig=%d\n",
                (unsigned long)func, (unsigned long)af.pc, (unsigned long)af.regs[0], got);
        set_regs(pid, &backup);
        return af.regs[0];
    };

    fprintf(stderr, "[vanta] remote_dlopen path=0x%lx shell=0x%lx stack=0x%lx\n",
            (unsigned long)str_addr, (unsigned long)shell_addr, (unsigned long)stack_addr);
    // сначала пробуем публичный dlopen(path, flags) — 2 аргумента, без caller.
    // если не вернул handle — пробуем __loader_dlopen(path, flags, 0).
    uintptr_t handle = 0;
    if (r_pub_dlopen) {
        uintptr_t a2[2] = { str_addr, (uintptr_t)(RTLD_NOW | RTLD_GLOBAL) };
        handle = remote_call_sh(r_pub_dlopen, a2, 2);
        if (handle) fprintf(stderr, "[vanta] публичный dlopen: 0x%lx\n", (unsigned long)handle);
    }
    if (!handle && r_ldr_dlopen) {
        uintptr_t a3[3] = { str_addr, (uintptr_t)(RTLD_NOW | RTLD_GLOBAL), 0 };
        handle = remote_call_sh(r_ldr_dlopen, a3, 3);
        if (handle) fprintf(stderr, "[vanta] __loader_dlopen(caller=0): 0x%lx\n", (unsigned long)handle);
    }
    if (!handle) {
        fprintf(stderr, "[vanta] remote dlopen failed\n");
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        return 8;
    }
    fprintf(stderr, "[vanta] dlopen → 0x%lx\n", (unsigned long)handle);

    fprintf(stderr, "[vanta] remote_dlsym...\n");
    poke_mem(pid, str_addr, en, strlen(en) + 1);
    uintptr_t sym = 0;
    if (r_pub_dlsym) {
        uintptr_t a2[2] = { handle, str_addr };
        sym = remote_call_sh(r_pub_dlsym, a2, 2);
    }
    if (!sym && r_ldr_dlsym) {
        uintptr_t a3[3] = { handle, str_addr, 0 };
        sym = remote_call_sh(r_ldr_dlsym, a3, 3);
    }
    fprintf(stderr, "[vanta] dlsym %s → 0x%lx\n", en, (unsigned long)sym);
    if (sym) {
        fprintf(stderr, "[vanta] remote_entry...\n");
        uintptr_t none[1] = {0};
        remote_call_sh(sym, none, 0);
    }

    ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
    return sym ? 0 : 9;
}
