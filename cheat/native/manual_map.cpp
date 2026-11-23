#include "manual_map.h"

#include <sys/uio.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

namespace {

[[noreturn]] void fail(const char* where) {
    throw std::runtime_error(std::string("mm:") + where + ":" + std::strerror(errno));
}

// ---------- host-side ELF helpers ----------

std::vector<uint8_t> readFile(const std::string& path) {
    std::ifstream f(path, std::ios::binary | std::ios::ate);
    if (!f) throw std::runtime_error("open " + path);
    std::streamsize n = f.tellg();
    f.seekg(0);
    std::vector<uint8_t> buf(static_cast<size_t>(n));
    if (!f.read(reinterpret_cast<char*>(buf.data()), n)) throw std::runtime_error("read " + path);
    return buf;
}

const Elf64_Phdr* phdrs(const std::vector<uint8_t>& bytes, size_t& count) {
    const auto* eh = reinterpret_cast<const Elf64_Ehdr*>(bytes.data());
    count = eh->e_phnum;
    return reinterpret_cast<const Elf64_Phdr*>(bytes.data() + eh->e_phoff);
}

// Map a virtual address inside the image to a file offset.
size_t vaddrToOffset(const Elf64_Phdr* ph, size_t n, Elf64_Addr vaddr) {
    for (size_t i = 0; i < n; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (vaddr >= ph[i].p_vaddr && vaddr < ph[i].p_vaddr + ph[i].p_filesz)
            return ph[i].p_offset + (vaddr - ph[i].p_vaddr);
    }
    throw std::runtime_error("vaddrToOffset: 0x" + std::to_string(vaddr));
}

const Elf64_Dyn* dynamicStart(const std::vector<uint8_t>& bytes,
                              const Elf64_Phdr* ph, size_t n) {
    for (size_t i = 0; i < n; i++)
        if (ph[i].p_type == PT_DYNAMIC)
            return reinterpret_cast<const Elf64_Dyn*>(bytes.data() + ph[i].p_offset);
    throw std::runtime_error("no PT_DYNAMIC");
}

// ---------- remote process memory IO ----------

void writeRemoteBulk(pid_t pid, uintptr_t dst, const void* src, size_t n) {
    iovec local{const_cast<void*>(src), n};
    iovec remote{reinterpret_cast<void*>(dst), n};
    size_t left = n;
    while (left) {
        iovec li{static_cast<char*>(local.iov_base) + (n - left), left};
        iovec ri{reinterpret_cast<char*>(remote.iov_base) + (n - left), left};
        ssize_t w = process_vm_writev(pid, &li, 1, &ri, 1, 0);
        if (w < 0) {
            if (errno == EINTR) continue;
            fail("process_vm_writev");
        }
        if (w == 0) throw std::runtime_error("mm:write=0");
        left -= static_cast<size_t>(w);
    }
}

// ---------- extern symbol resolver (loader-local dlsym translated to remote) ----------

struct Mapping { uintptr_t start, end, offset; std::string perms, path; };

std::vector<Mapping> readMaps(pid_t pid) {
    std::ifstream f("/proc/" + std::to_string(pid) + "/maps");
    if (!f) throw std::runtime_error("maps " + std::to_string(pid));
    std::vector<Mapping> out; std::string line;
    while (std::getline(f, line)) {
        unsigned long a, b, o; char perms[8]; int used = 0;
        if (std::sscanf(line.c_str(), "%lx-%lx %7s %lx %*s %*s %n",
                        &a, &b, perms, &o, &used) != 4) continue;
        std::string path = line.substr(used);
        while (!path.empty() && path.front() == ' ') path.erase(0, 1);
        out.push_back({a, b, o, perms, path});
    }
    return out;
}

class Resolver {
public:
    Resolver(pid_t pid) : own_(readMaps(getpid())), remote_(readMaps(pid)) {}

    // Returns the remote address of `name`, or 0 if unresolved. `name` must be a
    // plain symbol name (e.g. "mmap", "_ZdlPv").
    uintptr_t resolve(const char* name) {
        auto it = cache_.find(name);
        if (it != cache_.end()) return it->second;

        void* local = dlsym(RTLD_DEFAULT, name);
        uintptr_t r = 0;
        if (local) r = translate(reinterpret_cast<uintptr_t>(local));
        cache_.emplace(name, r);
        return r;
    }

private:
    uintptr_t translate(uintptr_t local_addr) {
        for (const auto& m : own_) {
            if (local_addr < m.start || local_addr >= m.end) continue;
            uintptr_t file_off = local_addr - m.start + m.offset;
            for (const auto& r : remote_) {
                if (r.path != m.path) continue;
                if (r.perms.find('x') == std::string::npos) continue;
                if (file_off < r.offset || file_off >= r.offset + (r.end - r.start)) continue;
                return r.start + (file_off - r.offset);
            }
            return 0;
        }
        return 0;
    }
    std::vector<Mapping> own_, remote_;
    std::unordered_map<std::string, uintptr_t> cache_;
};

} // namespace

namespace manual_map {

uintptr_t load(pid_t pid, const RemoteCaller& caller, const std::string& so_path) {
    auto bytes = readFile(so_path);
    if (bytes.size() < sizeof(Elf64_Ehdr) ||
        std::memcmp(bytes.data(), ELFMAG, SELFMAG) != 0)
        throw std::runtime_error("mm:not ELF");

    size_t nph = 0;
    const Elf64_Phdr* ph = phdrs(bytes, nph);

    // Virtual image span (max p_vaddr+p_memsz over PT_LOAD, rounded up to page).
    uint64_t image_end = 0;
    for (size_t i = 0; i < nph; i++)
        if (ph[i].p_type == PT_LOAD) {
            uint64_t e = ph[i].p_vaddr + ph[i].p_memsz;
            if (e > image_end) image_end = e;
        }
    const uint64_t page = 0x1000;
    image_end = (image_end + page - 1) & ~(page - 1);

    // Resolve the remote libc helpers we need before any work.
    Resolver resolver(pid);
    auto need = [&](const char* n) {
        uintptr_t v = resolver.resolve(n);
        if (!v) throw std::runtime_error(std::string("mm:missing:") + n);
        return v;
    };
    uintptr_t mmap_fn = need("mmap");
    uintptr_t mprotect_fn = need("mprotect");

    // Remote-allocate the whole image as RW; we'll flip to the final PT_LOAD
    // permissions after relocations are applied.
    uintptr_t base = caller(mmap_fn,
        {0, image_end, PROT_READ | PROT_WRITE,
         MAP_PRIVATE | MAP_ANONYMOUS, ~uintptr_t(0), 0});
    if (base == 0 || base == ~uintptr_t(0))
        throw std::runtime_error("mm:mmap failed");

    // 1. Write PT_LOAD contents.
    for (size_t i = 0; i < nph; i++) {
        if (ph[i].p_type != PT_LOAD || ph[i].p_filesz == 0) continue;
        writeRemoteBulk(pid, base + ph[i].p_vaddr,
                        bytes.data() + ph[i].p_offset, ph[i].p_filesz);
        // p_memsz > p_filesz (bss) is already zero from MAP_ANONYMOUS.
    }

    // 2. Parse DYNAMIC.
    const Elf64_Dyn* dyn = dynamicStart(bytes, ph, nph);
    uint64_t rela = 0, rela_sz = 0, rela_ent = sizeof(Elf64_Rela);
    uint64_t jmprel = 0, pltrel_sz = 0;
    uint64_t symtab = 0, strtab = 0;
    uint64_t init_array = 0, init_array_sz = 0;
    for (; dyn->d_tag != DT_NULL; dyn++) {
        switch (dyn->d_tag) {
            case DT_RELA:         rela = dyn->d_un.d_ptr; break;
            case DT_RELASZ:       rela_sz = dyn->d_un.d_val; break;
            case DT_RELAENT:      rela_ent = dyn->d_un.d_val; break;
            case DT_JMPREL:       jmprel = dyn->d_un.d_ptr; break;
            case DT_PLTRELSZ:     pltrel_sz = dyn->d_un.d_val; break;
            case DT_SYMTAB:       symtab = dyn->d_un.d_ptr; break;
            case DT_STRTAB:       strtab = dyn->d_un.d_ptr; break;
            case DT_INIT_ARRAY:   init_array = dyn->d_un.d_ptr; break;
            case DT_INIT_ARRAYSZ: init_array_sz = dyn->d_un.d_val; break;
        }
    }
    if (!symtab || !strtab) throw std::runtime_error("mm:no symtab");

    const Elf64_Sym* syms = reinterpret_cast<const Elf64_Sym*>(
        bytes.data() + vaddrToOffset(ph, nph, symtab));
    const char* strs = reinterpret_cast<const char*>(
        bytes.data() + vaddrToOffset(ph, nph, strtab));

    // 3. Apply relocations.
    auto applyRela = [&](uint64_t off, uint64_t sz) {
        if (!off || !sz) return;
        const auto* r = reinterpret_cast<const Elf64_Rela*>(
            bytes.data() + vaddrToOffset(ph, nph, off));
        size_t n = sz / rela_ent;
        for (size_t i = 0; i < n; i++) {
            uint32_t type = ELF64_R_TYPE(r[i].r_info);
            uint32_t s = ELF64_R_SYM(r[i].r_info);
            uintptr_t at = base + r[i].r_offset;
            uintptr_t value = 0;
            switch (type) {
                case R_AARCH64_RELATIVE:
                    value = base + r[i].r_addend;
                    break;
                case R_AARCH64_GLOB_DAT:
                case R_AARCH64_JUMP_SLOT:
                case R_AARCH64_ABS64: {
                    const char* name = strs + syms[s].st_name;
                    // A defined symbol inside this image: compute locally.
                    if (syms[s].st_shndx != SHN_UNDEF)
                        value = base + syms[s].st_value;
                    else
                        value = resolver.resolve(name);
                    if (!value) throw std::runtime_error(std::string("mm:unres:") + name);
                    value += r[i].r_addend;
                    break;
                }
                case R_AARCH64_IRELATIVE:
                    // ifunc resolver — would need a remote call into the resolver
                    // function at (base + r_addend). None in our payload; reject.
                    throw std::runtime_error("mm:IRELATIVE");
                case R_AARCH64_TLSDESC:
                case R_AARCH64_TLS_TPREL64:
                case R_AARCH64_TLS_DTPREL64:
                case R_AARCH64_TLS_DTPMOD64:
                    throw std::runtime_error("mm:TLS unsupported");
                case R_AARCH64_COPY:
                case R_AARCH64_NONE:
                    continue;
                default:
                    throw std::runtime_error("mm:reloc " + std::to_string(type));
            }
            writeRemoteBulk(pid, at, &value, sizeof(value));
        }
    };
    applyRela(rela, rela_sz);
    applyRela(jmprel, pltrel_sz);

    // 4. mprotect each PT_LOAD to its final permissions.
    for (size_t i = 0; i < nph; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        int prot = 0;
        if (ph[i].p_flags & PF_R) prot |= PROT_READ;
        if (ph[i].p_flags & PF_W) prot |= PROT_WRITE;
        if (ph[i].p_flags & PF_X) prot |= PROT_EXEC;
        uintptr_t seg_base = (base + ph[i].p_vaddr) & ~(page - 1);
        uintptr_t seg_end  = (base + ph[i].p_vaddr + ph[i].p_memsz + page - 1) & ~(page - 1);
        caller(mprotect_fn, {seg_base, seg_end - seg_base, static_cast<uintptr_t>(prot)});
    }

    // 5. Call init_array entries. After RELATIVE relocations their remote values
    // are already (base + original_rva), but we read the file-time values from
    // our local copy and add base ourselves — the RELATIVE fix is a no-op for us.
    if (init_array && init_array_sz) {
        size_t n = init_array_sz / sizeof(uint64_t);
        const uint64_t* arr = reinterpret_cast<const uint64_t*>(
            bytes.data() + vaddrToOffset(ph, nph, init_array));
        for (size_t i = 0; i < n; i++) {
            uint64_t v = arr[i];
            if (!v || v == ~uint64_t(0)) continue;
            caller(base + v, {});
        }
    }

    return base;
}

} // namespace manual_map
