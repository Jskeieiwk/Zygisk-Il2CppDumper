#include "inline_hook.h"
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <android/log.h>

#define LOGH(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-ihook", fmt, ##__VA_ARGS__)

namespace vanta {

static bool is_pc_relative(uint32_t insn) {
    // ADR/ADRP: 0x1F000000 mask, 0x10000000 value
    if ((insn & 0x1F000000u) == 0x10000000u) return true;
    // B/BL: 0x7C000000 mask, 0x14000000 (B) / 0x94000000 (BL)
    if ((insn & 0x7C000000u) == 0x14000000u) return true;
    // B.cond: 0xFF000010 mask == 0x54000000
    if ((insn & 0xFF000010u) == 0x54000000u) return true;
    // CBZ/CBNZ/TBZ/TBNZ
    if ((insn & 0x7E000000u) == 0x34000000u) return true;  // CBZ/CBNZ
    if ((insn & 0x7E000000u) == 0x36000000u) return true;  // TBZ/TBNZ
    // LDR (literal)
    if ((insn & 0x3B000000u) == 0x18000000u) return true;
    return false;
}

bool inline_hook(void* target, void* new_fn, void** orig_trampoline) {
    if (!target || !new_fn || !orig_trampoline) return false;
    uint32_t* code = reinterpret_cast<uint32_t*>(target);
    for (int i = 0; i < 4; ++i) {
        if (is_pc_relative(code[i])) {
            LOGH("target %p insn[%d]=0x%08x is PC-relative — abort", target, i, code[i]);
            return false;
        }
    }

    size_t ps = sysconf(_SC_PAGESIZE);
    // trampoline: original 16 bytes + jump back
    void* tramp = mmap(nullptr, ps, PROT_READ | PROT_WRITE | PROT_EXEC,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (tramp == MAP_FAILED) { LOGH("mmap trampoline fail"); return false; }
    memcpy(tramp, target, 16);
    uint32_t back[] = { 0x58000051u /* LDR X17,#8 */, 0xD61F0220u /* BR X17 */ };
    memcpy((uint8_t*)tramp + 16, back, sizeof(back));
    *reinterpret_cast<void**>((uint8_t*)tramp + 24) = (uint8_t*)target + 16;
    __builtin___clear_cache((char*)tramp, (char*)tramp + 32);

    // overwrite target: LDR X17,#8 ; BR X17 ; <new_fn>
    uintptr_t page = reinterpret_cast<uintptr_t>(target) & ~(ps - 1);
    if (mprotect((void*)page, ps, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
        LOGH("mprotect W fail"); return false;
    }
    uint32_t jmp[] = { 0x58000051u, 0xD61F0220u };
    memcpy(target, jmp, sizeof(jmp));
    *reinterpret_cast<void**>((uint8_t*)target + 8) = new_fn;
    __builtin___clear_cache((char*)target, (char*)target + 16);
    mprotect((void*)page, ps, PROT_READ | PROT_EXEC);

    *orig_trampoline = tramp;
    LOGH("inline hook %p -> %p (orig via trampoline %p)", target, new_fn, tramp);
    return true;
}

} // namespace vanta
