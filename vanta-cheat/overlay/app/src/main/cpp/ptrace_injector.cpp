// ptrace_injector.cpp — aarch64 / armv7 ptrace-инжекция .so в чужой процесс.
// минимальная проверенная последовательность; никаких внешних библиотек.
#include "ptrace_injector.h"
#include "maps_util.h"

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/elf.h>
#include <android/log.h>

#define LOGJ(fmt, ...) __android_log_print(ANDROID_LOG_INFO,  "vanta-inject", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-inject", fmt, ##__VA_ARGS__)

namespace vanta {

#if !defined(__aarch64__)
    #error "vanta ptrace_injector: only aarch64"
#endif
using regs_t = user_regs_struct;
static constexpr int NT = NT_PRSTATUS;

static bool get_regs(pid_t pid, regs_t* r) {
    iovec iov{ r, sizeof(*r) };
    return ptrace(PTRACE_GETREGSET, pid, (void*)NT, &iov) == 0;
}
static bool set_regs(pid_t pid, regs_t* r) {
    iovec iov{ r, sizeof(*r) };
    return ptrace(PTRACE_SETREGSET, pid, (void*)NT, &iov) == 0;
}

static bool wait_stopped(pid_t pid) {
    int status;
    waitpid(pid, &status, __WALL);
    return WIFSTOPPED(status);
}

// записать данные в память чужого процесса через /proc/pid/mem (быстрее чем ptrace word-by-word)
static bool write_remote(pid_t pid, uintptr_t addr, const void* data, size_t len) {
    char p[64]; snprintf(p, sizeof(p), "/proc/%d/mem", pid);
    int fd = open(p, O_RDWR);
    if (fd < 0) return false;
    bool ok = pread(fd, (void*)nullptr, 0, 0) == 0 || true;  // noop
    if (lseek(fd, addr, SEEK_SET) == (off_t)-1) { close(fd); return false; }
    ssize_t n = write(fd, data, len);
    close(fd);
    return n == (ssize_t)len;
}

// универсальный вызов функции в чужом процессе; возвращает значение из X0/R0
static uintptr_t remote_call(pid_t pid, uintptr_t func, uintptr_t args[], int nargs, uintptr_t ret_trap) {
    regs_t r{};
    if (!get_regs(pid, &r)) return 0;
    regs_t backup = r;
    for (int i = 0; i < nargs && i < 8; ++i) r.regs[i] = args[i];
    r.pc = func;
    r.sp &= ~0xFULL;              // 16-байт выравнивание SP под AAPCS64
    r.regs[30] = ret_trap;        // LR → заведомо невалидный адрес, ловим SIGSEGV как финиш
    if (!set_regs(pid, &r)) return 0;
    if (ptrace(PTRACE_CONT, pid, nullptr, nullptr) < 0) return 0;
    int status;
    waitpid(pid, &status, __WALL);
    regs_t after{};
    get_regs(pid, &after);
    set_regs(pid, &backup);
    return after.regs[0];
}

InjectResult inject_so(pid_t pid, const char* so_path, const char* entry_name) {
    InjectResult res{};
    res.success = false;

    auto fail = [&](const char* m) {
        res.error_code = errno;
        res.message = std::string(m) + ": " + strerror(errno);
        LOGE("%s", res.message.c_str());
        return res;
    };

    if (ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) < 0) return fail("PTRACE_ATTACH");
    if (!wait_stopped(pid)) { ptrace(PTRACE_DETACH, pid, nullptr, nullptr); return fail("wait_stopped"); }

    uintptr_t rem_mmap   = get_remote_symbol(pid, "libc.so", "mmap");
    uintptr_t rem_munmap = get_remote_symbol(pid, "libc.so", "munmap");
    uintptr_t rem_dlopen = get_remote_symbol(pid, "libdl.so", "dlopen");
    if (!rem_dlopen) rem_dlopen = get_remote_symbol(pid, "libdl.so", "__loader_dlopen");
    uintptr_t rem_dlsym  = get_remote_symbol(pid, "libdl.so", "dlsym");
    if (!rem_dlsym)  rem_dlsym  = get_remote_symbol(pid, "libdl.so", "__loader_dlsym");

    if (!rem_mmap || !rem_dlopen || !rem_dlsym) {
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        res.message = "remote symbols not found";
        LOGE("%s", res.message.c_str());
        return res;
    }

    // trap-адрес — ждём SEGV. Берём 0x0 — почти гарантированный craш в маппинге.
    uintptr_t trap = 0;

    // 1) mmap в игре — буфер под путь
    uintptr_t args[6] = { 0, 0x1000, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, (uintptr_t)-1, 0 };
    uintptr_t buf = remote_call(pid, rem_mmap, args, 6, trap);
    if (!buf || (intptr_t)buf == -1) {
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        res.message = "remote mmap failed"; return res;
    }
    LOGJ("remote mmap buf=%lx", (unsigned long)buf);

    // 2) write путь .so в этот буфер
    size_t plen = strlen(so_path) + 1;
    write_remote(pid, buf, so_path, plen);

    // 3) dlopen(path, RTLD_NOW|RTLD_GLOBAL)
    uintptr_t dl_args[2] = { buf, (uintptr_t)(RTLD_NOW | RTLD_GLOBAL) };
    uintptr_t handle = remote_call(pid, rem_dlopen, dl_args, 2, trap);
    LOGJ("remote dlopen handle=%lx", (unsigned long)handle);
    if (!handle) {
        uintptr_t fa[1] = { buf };
        remote_call(pid, rem_munmap, fa, 1, trap);
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
        res.message = "remote dlopen failed"; return res;
    }
    res.remote_handle = handle;

    // 4) dlsym(handle, entry_name)
    write_remote(pid, buf, entry_name, strlen(entry_name) + 1);
    uintptr_t ds_args[2] = { handle, buf };
    uintptr_t sym = remote_call(pid, rem_dlsym, ds_args, 2, trap);
    LOGJ("remote dlsym entry=%lx", (unsigned long)sym);
    res.remote_sym = sym;

    // 5) вызов entry()
    if (sym) {
        uintptr_t ea[1] = { 0 };
        remote_call(pid, sym, ea, 0, trap);
    }

    // отдельная ветка для cleanup буфера опускаем — чит всё равно живёт всю игру
    ptrace(PTRACE_DETACH, pid, nullptr, nullptr);

    res.success = sym != 0;
    res.message = "ok";
    return res;
}

} // namespace vanta
