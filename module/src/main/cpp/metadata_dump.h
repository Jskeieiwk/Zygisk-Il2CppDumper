#ifndef ZYGISK_IL2CPPDUMPER_METADATA_DUMP_H
#define ZYGISK_IL2CPPDUMPER_METADATA_DUMP_H

#include <cstddef>
#include <cstdint>
#include <cstring>

// Pure helpers, no Android dependencies, so they can be checked on a host compiler.

constexpr uint32_t kMetadataSanity = 0xFAB11BAF;
constexpr size_t kMetadataHeaderSize = 0x100;
// Unity 2022 (metadata version 31): sanity, version, then 31 (offset, size) pairs = 0x100 bytes.
constexpr int32_t kMetadataVersion31 = 31;
constexpr size_t kMetadataV31PairCount = 31;
constexpr size_t kMetadataMaxSize = 0x20000000;

// Returns the total size of a plaintext v31 global-metadata.dat described by its 0x100-byte header
// (largest offset+size over all sections), or 0 if the header is not a plausible v31 header.
inline size_t MetadataTotalSize(const uint8_t *header, size_t available) {
    if (available < kMetadataHeaderSize) return 0;
    uint32_t sanity;
    int32_t version;
    std::memcpy(&sanity, header, 4);
    std::memcpy(&version, header + 4, 4);
    if (sanity != kMetadataSanity || version != kMetadataVersion31) return 0;
    uint64_t end = kMetadataHeaderSize;
    for (size_t i = 0; i < kMetadataV31PairCount; i++) {
        int32_t offset, size;
        std::memcpy(&offset, header + 8 + i * 8, 4);
        std::memcpy(&size, header + 12 + i * 8, 4);
        if (offset < 0 || size < 0) return 0;
        uint64_t section_end = (uint64_t) (uint32_t) offset + (uint32_t) size;
        if (section_end > kMetadataMaxSize) return 0;
        if (section_end > end) end = section_end;
    }
    return (size_t) end;
}

// Per-build constants, measured from libil2cpp.so (aarch64) of the dumped game build.
// Build ID e5f46eb0e88ed1bd53ba133780db868d3076f729 (NT_GNU_BUILD_ID of the analysed file).
// kSlotRva is a module-relative virtual address (not a file offset): the .bss pointer that
// il2cpp::vm::MetadataLoader keeps to the decrypted global-metadata buffer. Measured as the
// store at 0x2b97ea8 (`str x0, [x23, #0x4b0]`, x23 = page 0x645e000) after the loader call at
// 0x2b97ea0; the failure path reads it at 0x2b98144 and clears it at 0x2b9814c.
struct MetadataBuildConfig {
    const char *name;
    uint8_t build_id[20];
    uint64_t slot_rva;
};

constexpr MetadataBuildConfig kMetadataBuilds[] = {
        {"libil2cpp.so dump3 release (Unity 2022.3.60f1, metadata v31)",
         {0xe5, 0xf4, 0x6e, 0xb0, 0xe8, 0x8e, 0xd1, 0xbd, 0x53, 0xba,
          0x13, 0x37, 0x80, 0xdb, 0x86, 0x8d, 0x30, 0x76, 0xf7, 0x29},
         0x645e4b0},
};

bool dump_decrypted_metadata(void *il2cpp_handle, const char *outDir);

#endif //ZYGISK_IL2CPPDUMPER_METADATA_DUMP_H
