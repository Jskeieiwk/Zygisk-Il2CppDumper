#include "hook.h"

#include <cerrno>
#include <cstdint>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

#include "ms_log.h"
#include "And64InlineHook.hpp"

namespace ms::hook {

namespace {

// And64InlineHook overwrites at most 5 instructions (20 bytes).
constexpr size_t kPatchBytes = 24;
constexpr size_t kMaxHooks = 32;

struct Saved {
    void *target;
    uint8_t bytes[kPatchBytes];
};

bool make_writable(void *addr, size_t len, bool writable) {
    const auto page = static_cast<uintptr_t>(sysconf(_SC_PAGESIZE));
    const auto a = reinterpret_cast<uintptr_t>(addr);
    const uintptr_t start = a & ~(page - 1);
    const uintptr_t end = (a + len + page - 1) & ~(page - 1);
    const int prot = writable ? (PROT_READ | PROT_WRITE | PROT_EXEC) : (PROT_READ | PROT_EXEC);
    if (mprotect(reinterpret_cast<void *>(start), end - start, prot) != 0) {
        MS_LOGE("mprotect(%p) failed: %d", reinterpret_cast<void *>(start), errno);
        return false;
    }
    return true;
}

void restore(const Saved &s) {
    if (!make_writable(s.target, kPatchBytes, true)) return;
    std::memcpy(s.target, s.bytes, kPatchBytes);
    __builtin___clear_cache(static_cast<char *>(s.target), static_cast<char *>(s.target) + kPatchBytes);
    make_writable(s.target, kPatchBytes, false);
}

}  // namespace

bool install_all(Spec *specs, size_t count) {
    if (count > kMaxHooks) return false;
    for (size_t i = 0; i < count; ++i) {
        if (!specs[i].target || !specs[i].replacement || !specs[i].original) {
            MS_LOGE("hook %s: unresolved", specs[i].name);
            return false;
        }
    }

    Saved saved[kMaxHooks];
    size_t done = 0;
    bool ok = true;
    for (; done < count; ++done) {
        Spec &s = specs[done];
        saved[done].target = s.target;
        std::memcpy(saved[done].bytes, s.target, kPatchBytes);
        *s.original = nullptr;
        A64HookFunction(s.target, s.replacement, s.original);
        if (*s.original == nullptr) {
            MS_LOGE("hook %s at %p failed", s.name, s.target);
            restore(saved[done]);  // may be partially written
            ok = false;
            break;
        }
        MS_LOGI("hook %s at %p installed", s.name, s.target);
    }

    if (!ok) {
        for (size_t i = 0; i < done; ++i) {
            restore(saved[i]);
            *specs[i].original = nullptr;
        }
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        make_writable(specs[i].target, kPatchBytes, false);
    }
    return true;
}

}  // namespace ms::hook
