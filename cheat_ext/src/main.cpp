// Phase-1 external probe for Oxide Survival Island.
//
// Objective: prove the architecture change — a separate PIE binary that reads
// the game's memory from outside the process is invisible to libng (which
// lives inside the game and only inspects its own address space). Reads
// libil2cpp.so base + Build ID + two anchor instruction words via
// process_vm_readv, prints the result, then keeps re-reading for 60 s so dj
// can play and observe whether the architecture itself gets flagged.
//
// Run with: su 0 /data/local/tmp/<name>
#include "mem.hpp"

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <vector>

namespace {

constexpr const char* kPackage = "com.catsbit.oxidesurvivalisland";
constexpr size_t kLateUpdateRva = 0x7818ED8;
constexpr uint32_t kLateUpdateWord = 0xf81e0ffe;
constexpr size_t kUpdateRva = 0x78198A4;
constexpr uint32_t kUpdateWord = 0xd10203ff;
constexpr uint8_t kBuildId[20] = {
    0x76, 0xe4, 0x7a, 0x1a, 0xdd, 0xbd, 0x7a, 0xee, 0x36, 0x59,
    0x5c, 0x8d, 0xc2, 0xbb, 0x2f, 0x7e, 0xac, 0x1f, 0xfc, 0x5e,
};

// Read ELF header + phdr table from the mapped game module, find the PT_NOTE
// containing the GNU Build ID, extract its 20-byte descriptor.
bool read_build_id(pid_t pid, uintptr_t base, uint8_t out[20]) {
    struct Ehdr {
        uint8_t pad[0x20];
        uint16_t e_type, e_machine;
        uint32_t e_version;
        uint64_t e_entry, e_phoff, e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize, e_phentsize, e_phnum;
    } eh{};
    if (!ext::read_bytes(pid, base, &eh, sizeof(eh))) return false;
    std::vector<uint8_t> phdrs(static_cast<size_t>(eh.e_phentsize) * eh.e_phnum);
    if (!ext::read_bytes(pid, base + eh.e_phoff, phdrs.data(), phdrs.size())) return false;
    for (int i = 0; i < eh.e_phnum; i++) {
        struct Phdr {
            uint32_t p_type, p_flags;
            uint64_t p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_align;
        };
        auto* p = reinterpret_cast<Phdr*>(phdrs.data() + i * eh.e_phentsize);
        if (p->p_type != 4 /* PT_NOTE */ || p->p_memsz > 4096) continue;
        std::vector<uint8_t> notes(p->p_memsz);
        if (!ext::read_bytes(pid, base + p->p_vaddr, notes.data(), notes.size())) continue;
        size_t at = 0;
        while (at + 12 <= notes.size()) {
            uint32_t n_namesz = 0, n_descsz = 0, n_type = 0;
            std::memcpy(&n_namesz, notes.data() + at, 4);
            std::memcpy(&n_descsz, notes.data() + at + 4, 4);
            std::memcpy(&n_type, notes.data() + at + 8, 4);
            size_t name_pad = (n_namesz + 3) & ~3u;
            size_t desc_pad = (n_descsz + 3) & ~3u;
            size_t step = 12 + name_pad + desc_pad;
            if (step == 0 || at + step > notes.size()) break;
            if (n_type == 3 /* NT_GNU_BUILD_ID */ && n_descsz == 20 &&
                n_namesz >= 4 && std::memcmp(notes.data() + at + 12, "GNU", 4) == 0) {
                std::memcpy(out, notes.data() + at + 12 + name_pad, 20);
                return true;
            }
            at += step;
        }
    }
    return false;
}

} // namespace

int main() {
    std::printf("[ext] probing %s\n", kPackage);
    pid_t pid = 0;
    for (int i = 0; i < 60 && !pid; i++) {
        pid = ext::find_pid(kPackage);
        if (!pid) std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if (!pid) {
        std::fprintf(stderr, "[ext] game not running after 60 s\n");
        return 1;
    }
    std::printf("[ext] found pid=%d\n", pid);

    uintptr_t base = 0;
    for (int i = 0; i < 30 && !base; i++) {
        try {
            base = ext::module_base(pid, "libil2cpp.so");
        } catch (const std::exception& e) {
            std::fprintf(stderr, "[ext] maps: %s\n", e.what());
            return 2;
        }
        if (!base) std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if (!base) {
        std::fprintf(stderr, "[ext] libil2cpp.so not mapped in game yet\n");
        return 3;
    }
    std::printf("[ext] libil2cpp.so base=0x%lx\n", static_cast<unsigned long>(base));

    uint8_t id[20] = {};
    if (!read_build_id(pid, base, id)) {
        std::fprintf(stderr, "[ext] cannot read Build ID\n");
        return 4;
    }
    std::printf("[ext] build id=");
    for (int i = 0; i < 20; i++) std::printf("%02x", id[i]);
    std::printf("\n");
    bool id_ok = std::memcmp(id, kBuildId, 20) == 0;
    std::printf("[ext] build id match=%d\n", id_ok ? 1 : 0);

    uint32_t anchor_a = 0, anchor_b = 0;
    bool a_ok = ext::read(pid, base + kLateUpdateRva, anchor_a);
    bool b_ok = ext::read(pid, base + kUpdateRva, anchor_b);
    std::printf("[ext] LateUpdate@+0x%lx: read=%d word=0x%08x expected=0x%08x match=%d\n",
                static_cast<unsigned long>(kLateUpdateRva), a_ok ? 1 : 0,
                anchor_a, kLateUpdateWord, anchor_a == kLateUpdateWord ? 1 : 0);
    std::printf("[ext] Update@+0x%lx:     read=%d word=0x%08x expected=0x%08x match=%d\n",
                static_cast<unsigned long>(kUpdateRva), b_ok ? 1 : 0,
                anchor_b, kUpdateWord, anchor_b == kUpdateWord ? 1 : 0);

    // Hold for 60 s while dj plays — any ban in this window means the
    // architecture itself (external process_vm_readv against the game) is
    // flagged, not any in-process cheat code. That is the whole point of
    // Phase 1.
    std::printf("[ext] idle-reading game memory for 60 s; play now and watch for ban\n");
    for (int i = 0; i < 60; i++) {
        uint32_t probe = 0;
        ext::read(pid, base + kLateUpdateRva, probe);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::printf("[ext] 60 s elapsed, exit clean\n");
    return 0;
}
