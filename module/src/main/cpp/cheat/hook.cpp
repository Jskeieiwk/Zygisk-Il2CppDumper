#include "hook.h"
#include "il2cpp_api.h"
#include "../log.h"

#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

#if __has_include("dobby.h")
  #include "dobby.h"
  #define HAVE_DOBBY 1
#else
  #define HAVE_DOBBY 0
#endif

void *resolve_rva(uint64_t rva) {
    auto base = il2cpp_base();
    if (!base) return nullptr;
    return (void*)(base + rva);
}

static void unprotect(void *addr, size_t len) {
    uintptr_t page = sysconf(_SC_PAGESIZE);
    uintptr_t start = (uintptr_t)addr & ~(page - 1);
    uintptr_t end   = ((uintptr_t)addr + len + page - 1) & ~(page - 1);
    mprotect((void*)start, end - start, PROT_READ | PROT_WRITE | PROT_EXEC);
}

static void flush_cache(void *addr, size_t len) {
    __builtin___clear_cache((char*)addr, (char*)addr + len);
}

void patch_bytes(void *addr, const void *bytes, size_t len) {
    if (!addr) return;
    unprotect(addr, len);
    memcpy(addr, bytes, len);
    flush_cache(addr, len);
}

void patch_u32(void *addr, uint32_t v) {
    patch_bytes(addr, &v, sizeof(v));
}

#if HAVE_DOBBY

bool inline_hook(void *target, void *hook, void **trampoline_out) {
    if (!target || !hook) return false;
    int r = DobbyHook(target, (dobby_dummy_func_t)hook, (dobby_dummy_func_t*)trampoline_out);
    LOGI("[Cloud] DobbyHook %p -> %p = %d", target, hook, r);
    return r == 0;
}

#else

// Minimal fallback inline hook for ARM64. Steals 16 bytes (4 instructions).
// Rejects targets whose first 4 instructions include PC-relative ones
// (ADR, ADRP, LDR literal, B, BL, B.cond, CBZ, CBNZ, TBZ, TBNZ).
// Good enough for simple setters like Camera.set_fieldOfView; refuses
// hooks that need relocation (e.g. Transform.set_rotation_Injected at +8
// has an ADRP — use Dobby for that).

static bool is_pc_relative(uint32_t ins) {
    if ((ins & 0x1f000000) == 0x10000000) return true;         // ADR / ADRP
    if ((ins & 0xff000000) == 0x58000000) return true;         // LDR literal (64-bit)
    if ((ins & 0xff000000) == 0x18000000) return true;         // LDR literal (32-bit)
    if ((ins & 0xff000000) == 0x9c000000) return true;         // LDR literal (vec)
    if ((ins & 0x7c000000) == 0x14000000) return true;         // B / BL
    if ((ins & 0xff000010) == 0x54000000) return true;         // B.cond
    if ((ins & 0x7e000000) == 0x34000000) return true;         // CBZ / CBNZ
    if ((ins & 0x7e000000) == 0x36000000) return true;         // TBZ / TBNZ
    return false;
}

bool inline_hook(void *target, void *hook, void **trampoline_out) {
    if (!target || !hook) return false;
    uint32_t *t = (uint32_t*)target;
    for (int i = 0; i < 4; ++i) {
        if (is_pc_relative(t[i])) {
            LOGE("[Cloud] inline_hook refusing %p — PC-rel ins at +%d", target, i*4);
            return false;
        }
    }

    size_t tramp_size = 16 /* original */ + 16 /* abs jump back */;
    void *tramp = mmap(nullptr, 4096, PROT_READ | PROT_WRITE | PROT_EXEC,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (tramp == MAP_FAILED) return false;

    uint32_t *tp = (uint32_t*)tramp;
    // original 4 instructions
    for (int i = 0; i < 4; ++i) tp[i] = t[i];
    // then: LDR X17, #8 ; BR X17 ; <absolute 8-byte return address>
    tp[4] = 0x58000051;  // LDR X17, [PC, #8]
    tp[5] = 0xd61f0220;  // BR  X17
    uint64_t back = (uint64_t)target + 16;
    memcpy(&tp[6], &back, 8);
    flush_cache(tramp, tramp_size);

    // overwrite target with: LDR X17, #8 ; BR X17 ; <absolute hook>
    uint32_t patch[4];
    patch[0] = 0x58000051;
    patch[1] = 0xd61f0220;
    uint64_t hv = (uint64_t)hook;
    memcpy(&patch[2], &hv, 8);
    patch_bytes(target, patch, sizeof(patch));

    if (trampoline_out) *trampoline_out = tramp;
    LOGI("[Cloud] inline_hook (mini) %p -> %p (tramp %p)", target, hook, tramp);
    return true;
}

#endif
