#pragma once
// External memory access for an Android game process.
//
// Design: never attach via ptrace, never inject a .so. Reads and writes use
// process_vm_readv / process_vm_writev, invoked through raw syscalls so even a
// libc-level hook on those functions by the game's in-process anti-cheat
// cannot see our activity — we're a separate process; the anti-cheat lives in
// the game's address space and only knows about its own.
//
// Requires CAP_SYS_PTRACE (automatic for root) OR same uid as the target plus
// matching dumpable flag. Launched via `su 0 /data/local/tmp/<name>`.

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace ext {

/// Locates the process id of a package by scanning /proc/*/cmdline. Returns 0
/// if none found. Throws nothing; the caller gets 0 and retries.
pid_t find_pid(const char* package);

struct Mapping {
    uintptr_t start, end, offset;
    int perms;     // bitmask: 1 r, 2 w, 4 x
    std::string path;
};

/// Reads /proc/<pid>/maps into a vector. Throws std::runtime_error on failure.
std::vector<Mapping> read_maps(pid_t pid);

/// Returns the base virtual address of a module whose basename matches
/// `module` ("libil2cpp.so"), or 0 if absent.
uintptr_t module_base(pid_t pid, const char* module);

/// Raw memory read through the process_vm_readv syscall. Returns false on any
/// short read or EFAULT. All callers must tolerate failure.
bool read_bytes(pid_t pid, uintptr_t addr, void* out, size_t len);
bool write_bytes(pid_t pid, uintptr_t addr, const void* in, size_t len);

template<class T>
bool read(pid_t pid, uintptr_t addr, T& out) {
    return read_bytes(pid, addr, &out, sizeof(T));
}

template<class T>
T read_or(pid_t pid, uintptr_t addr, T fallback = T{}) {
    T value{};
    return read_bytes(pid, addr, &value, sizeof(T)) ? value : fallback;
}

template<class T>
bool write(pid_t pid, uintptr_t addr, const T& value) {
    return write_bytes(pid, addr, &value, sizeof(T));
}

/// Walks a pointer chain: starting from base, read pointer; add offsets[i];
/// repeat. Returns the final pointer value, or 0 on any failed read.
uintptr_t chain(pid_t pid, uintptr_t base, std::initializer_list<ptrdiff_t> offsets);

/// Reads an IL2CPP string object (System.String) and decodes UTF-16 to UTF-8.
/// Returns an empty string on any failure.
std::string read_il2cpp_string(pid_t pid, uintptr_t string_object);

} // namespace ext
