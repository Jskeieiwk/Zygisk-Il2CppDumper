// Cloud Crack 67 — root ptrace injector (arm64 only).
// Usage: cloud_injector <pid> <absolute path to .so>
// Must run as root; attaches to pid, forces it to dlopen() the .so,
// detaches.  Works by locating libdl & libc in the target's /proc/<pid>/maps,
// resolving the offsets of __loader_dlopen / mmap / free via the local
// copies of those libraries, then rewriting the remote registers to call
// the target function with x30 = a known sentinel address.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <elf.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <sys/user.h>

#ifndef NT_PRSTATUS
#define NT_PRSTATUS 1
#endif

#define die(fmt, ...) do { fprintf(stderr, "[inj] " fmt "\n", ##__VA_ARGS__); return 1; } while(0)
#define say(fmt, ...)    fprintf(stderr, "[inj] " fmt "\n", ##__VA_ARGS__)

struct user_pt_regs_a64 {
    unsigned long long regs[31];
    unsigned long long sp;
    unsigned long long pc;
    unsigned long long pstate;
};

static long rptrace(int req, pid_t pid, void *addr, void *data) {
    return ptrace(req, pid, addr, data);
}

static int get_regs(pid_t pid, user_pt_regs_a64 *r) {
    iovec io{r, sizeof(*r)};
    return rptrace(PTRACE_GETREGSET, pid, (void*)NT_PRSTATUS, &io);
}
static int set_regs(pid_t pid, user_pt_regs_a64 *r) {
    iovec io{r, sizeof(*r)};
    return rptrace(PTRACE_SETREGSET, pid, (void*)NT_PRSTATUS, &io);
}

// PEEKDATA/POKEDATA do 8-byte on arm64.
static int read_mem(pid_t pid, uint64_t addr, void *buf, size_t len) {
    size_t i = 0;
    while (i < len) {
        errno = 0;
        long w = rptrace(PTRACE_PEEKDATA, pid, (void*)(uintptr_t)(addr + i), nullptr);
        if (errno) return -1;
        size_t n = len - i < 8 ? len - i : 8;
        memcpy((uint8_t*)buf + i, &w, n);
        i += n;
    }
    return 0;
}
static int write_mem(pid_t pid, uint64_t addr, const void *buf, size_t len) {
    size_t i = 0;
    while (i < len) {
        long w = 0;
        size_t n = len - i < 8 ? len - i : 8;
        if (n < 8) {
            errno = 0;
            w = rptrace(PTRACE_PEEKDATA, pid, (void*)(uintptr_t)(addr + i), nullptr);
            if (errno) return -1;
        }
        memcpy(&w, (const uint8_t*)buf + i, n);
        if (rptrace(PTRACE_POKEDATA, pid, (void*)(uintptr_t)(addr + i), (void*)(uintptr_t)w) != 0)
            return -1;
        i += n;
    }
    return 0;
}

// Walk /proc/<pid>/maps and either:
//   - find the exact mapping path that contains `addr`     (containing_path_out)
//   - compute the lowest mapped address for a given `path` (base_for_path)
// Returns true on success.
static bool scan_maps(pid_t pid, uint64_t addr, char *containing_path_out, size_t out_sz,
                      const char *path_wanted, uint64_t *base_for_path) {
    char mp[64];
    snprintf(mp, sizeof(mp), "/proc/%d/maps", pid);
    FILE *fp = fopen(mp, "re");
    if (!fp) return false;
    char line[1024];
    bool found_container = false;
    uint64_t lo = 0;
    while (fgets(line, sizeof(line), fp)) {
        uint64_t a = 0, b = 0;
        unsigned off = 0, dev_major = 0, dev_minor = 0;
        char perms[8] = {0};
        unsigned long ino = 0;
        int consumed = 0;
        if (sscanf(line, "%lx-%lx %7s %x %x:%x %lu %n",
                   &a, &b, perms, &off, &dev_major, &dev_minor, &ino, &consumed) < 7) continue;
        const char *path = line + consumed;
        // trim leading spaces and the trailing newline
        while (*path == ' ') ++path;
        char *nl = strpbrk((char*)path, "\r\n");
        if (nl) *nl = 0;
        if (*path == 0 || *path == '[') continue;  // skip anon / [heap] / [stack]
        if (addr && addr >= a && addr < b && !found_container) {
            if (containing_path_out && out_sz) {
                strncpy(containing_path_out, path, out_sz - 1);
                containing_path_out[out_sz - 1] = 0;
            }
            found_container = true;
        }
        if (path_wanted && strcmp(path, path_wanted) == 0) {
            if (lo == 0 || a < lo) lo = a;
        }
    }
    fclose(fp);
    if (base_for_path) *base_for_path = lo;
    return addr ? found_container : (lo != 0);
}

// Resolve a symbol into the target process by:
//   1) dlopen + dlsym locally to get the actual address of the function body
//   2) look up which file-backed mapping that address lives in LOCALLY
//   3) find that same file-backed mapping in the TARGET process
//   4) return remote_base + (local_sym_addr - local_base_of_containing_module)
//
// This handles the common Android quirk where libdl.so symbols like
// __loader_dlopen are actually trampolines whose bodies live in the
// dynamic linker (linker64), not in libdl.so.
static uint64_t remote_sym(pid_t pid, const char *lib, const char *sym) {
    void *h = dlopen(lib, RTLD_NOW | RTLD_NOLOAD);
    if (!h) h = dlopen(lib, RTLD_NOW);
    if (!h) { say("dlopen(%s) failed: %s", lib, dlerror()); return 0; }
    void *addr = dlsym(h, sym);
    if (!addr) { say("dlsym(%s) failed in %s: %s", sym, lib, dlerror()); return 0; }

    char container[256] = {0};
    if (!scan_maps(getpid(), (uint64_t)addr, container, sizeof(container), nullptr, nullptr)
        || !container[0]) {
        say("could not find containing map for %s/%s @%p", lib, sym, addr);
        return 0;
    }
    uint64_t lb = 0, rb = 0;
    scan_maps(getpid(), 0, nullptr, 0, container, &lb);
    scan_maps(pid,       0, nullptr, 0, container, &rb);
    if (!lb || !rb) {
        say("base lookup failed for %s (local=%lx remote=%lx)", container, lb, rb);
        return 0;
    }
    uint64_t off = (uint64_t)addr - lb;
    uint64_t ra = rb + off;
    say("%s/%s via %s local=%p(base %lx) remote=%lx(base %lx) off=%lx",
        lib, sym, container, addr, lb, ra, rb, off);
    return ra;
}

// Perform a function call in the remote process.
// x0..x7 = args, x30 = 0 so a return raises SIGSEGV we catch cleanly.
static int remote_call(pid_t pid, user_pt_regs_a64 *saved,
                       uint64_t fn, uint64_t args[], int nargs, uint64_t *ret) {
    user_pt_regs_a64 r = *saved;
    for (int i = 0; i < nargs && i < 8; ++i) r.regs[i] = args[i];
    r.regs[30] = 0;   // lr -> cause SIGSEGV on return
    r.sp &= ~0xFULL;  // keep SP 16-byte aligned
    r.pc = fn;

    if (set_regs(pid, &r) != 0)  { say("set_regs: %s", strerror(errno)); return -1; }
    if (rptrace(PTRACE_CONT, pid, 0, 0) != 0) { say("CONT: %s", strerror(errno)); return -1; }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) { say("waitpid: %s", strerror(errno)); return -1; }
    if (!WIFSTOPPED(status)) {
        say("not stopped status=%x", status);
        return -1;
    }
    int sig = WSTOPSIG(status);
    if (sig != SIGSEGV && sig != SIGILL && sig != SIGBUS) {
        say("unexpected stop sig=%d", sig);
        // step through anyway
    }
    if (get_regs(pid, &r) != 0) { say("get_regs after call: %s", strerror(errno)); return -1; }
    *ret = r.regs[0];
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) die("usage: %s <pid> <abs path to .so>", argv[0]);
    pid_t pid = (pid_t)atoi(argv[1]);
    const char *so_path = argv[2];
    size_t pathlen = strlen(so_path) + 1;

    if (pid <= 0) die("bad pid");
    say("attaching pid=%d so=%s", pid, so_path);

    if (rptrace(PTRACE_ATTACH, pid, 0, 0) != 0) die("ATTACH: %s", strerror(errno));
    int st = 0;
    if (waitpid(pid, &st, 0) < 0) die("initial wait: %s", strerror(errno));

    user_pt_regs_a64 saved{};
    if (get_regs(pid, &saved) != 0) die("initial get_regs: %s", strerror(errno));

    // Resolve remote mmap/munmap/dlopen.
    uint64_t r_mmap = remote_sym(pid, "libc.so", "mmap");
    if (!r_mmap) r_mmap = remote_sym(pid, "libc.so", "mmap64");
    if (!r_mmap) { rptrace(PTRACE_DETACH, pid, 0, 0); die("resolve mmap failed"); }

    // Try the loader's privileged entry points first; fall back to plain dlopen.
    uint64_t r_dlopen = remote_sym(pid, "libdl.so", "__loader_dlopen");
    if (!r_dlopen) r_dlopen = remote_sym(pid, "libdl.so", "dlopen");
    if (!r_dlopen) r_dlopen = remote_sym(pid, "libc.so", "dlopen");
    if (!r_dlopen) { rptrace(PTRACE_DETACH, pid, 0, 0); die("resolve dlopen failed"); }

    // mmap a page in the target for our path string.
    uint64_t args[6] = {
        0,                                          // addr
        0x1000,                                     // length
        PROT_READ | PROT_WRITE,                     // prot
        MAP_PRIVATE | MAP_ANONYMOUS,                // flags
        (uint64_t)-1,                               // fd
        0                                           // offset
    };
    uint64_t page = 0;
    if (remote_call(pid, &saved, r_mmap, args, 6, &page) != 0 || (int64_t)page == -1) {
        rptrace(PTRACE_DETACH, pid, 0, 0);
        die("remote mmap failed = %lx", page);
    }
    say("remote page = %lx", page);

    if (write_mem(pid, page, so_path, pathlen) != 0) {
        rptrace(PTRACE_DETACH, pid, 0, 0);
        die("write path to remote");
    }

    // Call dlopen(path, RTLD_NOW).  For __loader_dlopen a 3rd arg (caller) is
    // accepted: we hand it back the page we just mmap'd (anywhere executable
    // works too; caller only gates namespace lookup).
    uint64_t a2[3] = { page, (uint64_t)RTLD_NOW, page };
    uint64_t handle = 0;
    if (remote_call(pid, &saved, r_dlopen, a2, 3, &handle) != 0) {
        rptrace(PTRACE_DETACH, pid, 0, 0);
        die("remote dlopen failed");
    }
    say("remote dlopen returned handle = %lx", handle);
    if (handle == 0) {
        say("WARN: dlopen returned 0 — check SELinux domain and that the .so is readable to the target uid");
    }

    // Restore target registers and detach.
    if (set_regs(pid, &saved) != 0) say("WARN: set_regs restore: %s", strerror(errno));
    if (rptrace(PTRACE_DETACH, pid, 0, 0) != 0) say("WARN: DETACH: %s", strerror(errno));

    say("done");
    return (handle == 0) ? 2 : 0;
}
