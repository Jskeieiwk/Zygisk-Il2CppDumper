// plt_hook.cpp — минималистичный PLT hook для aarch64 ELF
#include "plt_hook.h"

#include <elf.h>
#include <fcntl.h>
#include <link.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdio>
#include <cstdint>
#include <dlfcn.h>
#include <android/log.h>

#define LOGP(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-plt", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-plt", fmt, ##__VA_ARGS__)

namespace vanta {

struct SoInfo {
    uintptr_t base;      // load bias (first mapped page)
    const char* path;    // текстовая строка карт
};

static bool find_so(const char* so_name, uintptr_t* out_base, char* path_buf, size_t path_cap) {
    FILE* f = fopen("/proc/self/maps", "r");
    if (!f) return false;
    char line[1024];
    *out_base = 0;
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, so_name)) continue;
        if (!strstr(line, "r")) continue;  // интересует r-- или r-x маппинг с file backing
        uintptr_t s;
        char perms[8]; char path[512] = {0};
        if (sscanf(line, "%lx-%*lx %5s %*lx %*s %*lu %511s", &s, perms, path) >= 2) {
            if (perms[0] != 'r') continue;
            if (!*out_base) {
                *out_base = s;
                if (path_buf && path_cap && path[0]) {
                    strncpy(path_buf, path, path_cap - 1);
                    path_buf[path_cap - 1] = 0;
                }
                break;
            }
        }
    }
    fclose(f);
    return *out_base != 0;
}

static void protect_rw(void* addr) {
    uintptr_t page = (uintptr_t)addr & ~(uintptr_t)(sysconf(_SC_PAGESIZE) - 1);
    mprotect((void*)page, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE);
}
static void protect_r(void* addr) {
    uintptr_t page = (uintptr_t)addr & ~(uintptr_t)(sysconf(_SC_PAGESIZE) - 1);
    mprotect((void*)page, sysconf(_SC_PAGESIZE), PROT_READ);
}

// ищем нужный програмный заголовок PT_DYNAMIC через ELF header в памяти процесса
void* plt_hook(const char* so_name, const char* sym_name, void* new_fn) {
    uintptr_t base = 0;
    if (!find_so(so_name, &base, nullptr, 0)) {
        LOGE("so not found: %s", so_name);
        return nullptr;
    }
    auto* eh = reinterpret_cast<const ElfW(Ehdr)*>(base);
    if (memcmp(eh->e_ident, ELFMAG, SELFMAG) != 0) {
        LOGE("not ELF at base %p (%s)", (void*)base, so_name);
        return nullptr;
    }
    auto ph = reinterpret_cast<const ElfW(Phdr)*>(base + eh->e_phoff);
    const ElfW(Dyn)* dyn = nullptr;
    uintptr_t dyn_vaddr = 0;
    for (int i = 0; i < eh->e_phnum; ++i) {
        if (ph[i].p_type == PT_DYNAMIC) {
            dyn_vaddr = ph[i].p_vaddr;
            dyn = reinterpret_cast<const ElfW(Dyn)*>(base + dyn_vaddr);
            break;
        }
    }
    if (!dyn) { LOGE("no PT_DYNAMIC in %s", so_name); return nullptr; }

    const ElfW(Sym)* symtab = nullptr;
    const char* strtab = nullptr;
    const ElfW(Rela)* rela_plt = nullptr;   size_t rela_plt_sz = 0;
    const ElfW(Rela)* rela_dyn = nullptr;   size_t rela_dyn_sz = 0;
    for (const ElfW(Dyn)* d = dyn; d->d_tag != DT_NULL; ++d) {
        switch (d->d_tag) {
            case DT_SYMTAB:   symtab   = reinterpret_cast<const ElfW(Sym)*>(base + d->d_un.d_ptr); break;
            case DT_STRTAB:   strtab   = reinterpret_cast<const char*>(base + d->d_un.d_ptr); break;
            case DT_JMPREL:   rela_plt = reinterpret_cast<const ElfW(Rela)*>(base + d->d_un.d_ptr); break;
            case DT_PLTRELSZ: rela_plt_sz = d->d_un.d_val; break;
            case DT_RELA:     rela_dyn = reinterpret_cast<const ElfW(Rela)*>(base + d->d_un.d_ptr); break;
            case DT_RELASZ:   rela_dyn_sz = d->d_un.d_val; break;
            default: break;
        }
    }
    if (!symtab || !strtab) { LOGE("no symtab/strtab"); return nullptr; }

    auto scan = [&](const ElfW(Rela)* rel, size_t sz) -> void* {
        if (!rel || !sz) return nullptr;
        size_t n = sz / sizeof(ElfW(Rela));
        for (size_t i = 0; i < n; ++i) {
            uint32_t type = ELF64_R_TYPE(rel[i].r_info);
            if (type != R_AARCH64_JUMP_SLOT && type != R_AARCH64_GLOB_DAT) continue;
            uint32_t s = ELF64_R_SYM(rel[i].r_info);
            const char* name = strtab + symtab[s].st_name;
            if (strcmp(name, sym_name) != 0) continue;
            void** slot = reinterpret_cast<void**>(base + rel[i].r_offset);
            protect_rw(slot);
            void* prev = *slot;
            *slot = new_fn;
            protect_r(slot);
            __builtin___clear_cache((char*)slot, (char*)slot + sizeof(void*));
            LOGP("hooked %s in %s: %p -> %p (prev=%p)", sym_name, so_name, slot, new_fn, prev);
            return prev;
        }
        return nullptr;
    };
    void* prev = scan(rela_plt, rela_plt_sz);
    if (!prev) prev = scan(rela_dyn, rela_dyn_sz);
    if (!prev) LOGE("symbol %s not found in %s relocs", sym_name, so_name);
    return prev;
}

} // namespace vanta
