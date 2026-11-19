#include "metadata_dump.h"
#include "log.h"
#include "xdl.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <elf.h>
#include <link.h>
#include <string>
#include <sys/uio.h>
#include <unistd.h>
#include <vector>

// Copies memory of this process without risking SIGSEGV on a bad pointer.
static bool SafeRead(const void *from, void *to, size_t size) {
    size_t done = 0;
    while (done < size) {
        iovec local{(uint8_t *) to + done, size - done};
        iovec remote{(void *) ((const uint8_t *) from + done), size - done};
        ssize_t n = process_vm_readv(getpid(), &local, 1, &remote, 1, 0);
        if (n <= 0) return false;
        done += (size_t) n;
    }
    return true;
}

static bool ReadBuildId(const xdl_info_t &info, uint8_t out[20]) {
    for (size_t i = 0; i < info.dlpi_phnum; i++) {
        const ElfW(Phdr) &ph = info.dlpi_phdr[i];
        if (ph.p_type != PT_NOTE || ph.p_memsz < sizeof(ElfW(Nhdr)) || ph.p_memsz > 0x1000) continue;
        std::vector<uint8_t> notes(ph.p_memsz);
        if (!SafeRead((const uint8_t *) info.dli_fbase + ph.p_vaddr, notes.data(), notes.size()))
            continue;
        size_t pos = 0;
        while (pos + sizeof(ElfW(Nhdr)) <= notes.size()) {
            ElfW(Nhdr) nh;
            std::memcpy(&nh, &notes[pos], sizeof(nh));
            size_t name_off = pos + sizeof(nh);
            size_t desc_off = name_off + ((nh.n_namesz + 3) & ~3u);
            size_t next = desc_off + ((nh.n_descsz + 3) & ~3u);
            if (next > notes.size()) break;
            if (nh.n_type == NT_GNU_BUILD_ID && nh.n_descsz == 20) {
                std::memcpy(out, &notes[desc_off], 20);
                return true;
            }
            pos = next;
        }
    }
    return false;
}

// Writes the decrypted global-metadata that libil2cpp.so holds in memory to
// <outDir>/files/global-metadata.dec.dat. Returns true only when the written file passed the
// v31 header validation. Does nothing (and says why in the log) on an unknown libil2cpp build.
bool dump_decrypted_metadata(void *il2cpp_handle, const char *outDir) {
    xdl_info_t info{};
    if (xdl_info(il2cpp_handle, XDL_DI_DLINFO, &info) == -1 || !info.dli_fbase) {
        LOGE("metadata: xdl_info failed for libil2cpp.so");
        return false;
    }
    uint8_t build_id[20];
    if (!ReadBuildId(info, build_id)) {
        LOGE("metadata: no GNU build id in libil2cpp.so, refusing to use a hard-coded slot");
        return false;
    }
    const MetadataBuildConfig *cfg = nullptr;
    for (const auto &b: kMetadataBuilds) {
        if (std::memcmp(b.build_id, build_id, 20) == 0) cfg = &b;
    }
    if (!cfg) {
        char hex[41];
        for (int i = 0; i < 20; i++) snprintf(hex + i * 2, 3, "%02x", build_id[i]);
        LOGE("metadata: libil2cpp.so build id %s is not in kMetadataBuilds; slot RVA unknown for this build", hex);
        return false;
    }
    LOGI("metadata: matched build config '%s'", cfg->name);

    const auto *slot = (const uint8_t *) info.dli_fbase + cfg->slot_rva;
    // The slot is filled when il2cpp initialises; wait for it.
    for (int attempt = 0; attempt < 120; attempt++) {
        uint64_t ptr = 0;
        if (SafeRead(slot, &ptr, sizeof(ptr)) && ptr) {
            uint8_t header[kMetadataHeaderSize];
            if (SafeRead((void *) ptr, header, sizeof(header))) {
                size_t total = MetadataTotalSize(header, sizeof(header));
                if (total) {
                    std::vector<uint8_t> buf(total);
                    if (!SafeRead((void *) ptr, buf.data(), total)) {
                        LOGE("metadata: reading %zu bytes at %p failed", total, (void *) ptr);
                        return false;
                    }
                    std::string path = std::string(outDir).append("/files/global-metadata.dec.dat");
                    FILE *f = fopen(path.c_str(), "wb");
                    if (!f) {
                        LOGE("metadata: cannot open %s (errno %d)", path.c_str(), errno);
                        return false;
                    }
                    bool ok = fwrite(buf.data(), 1, buf.size(), f) == buf.size();
                    ok = (fclose(f) == 0) && ok;
                    LOGI("metadata: wrote %zu bytes to %s ok=%d", total, path.c_str(), (int) ok);
                    return ok;
                }
                LOGW("metadata: slot holds %p but its header is not a v31 header yet", (void *) ptr);
            }
        }
        sleep(1);
    }
    LOGE("metadata: slot never held a valid v31 header");
    return false;
}
