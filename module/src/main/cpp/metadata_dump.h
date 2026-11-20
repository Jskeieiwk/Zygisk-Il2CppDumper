#ifndef ZYGISK_IL2CPPDUMPER_METADATA_DUMP_H
#define ZYGISK_IL2CPPDUMPER_METADATA_DUMP_H

#include <cstddef>
#include <cstdint>
#include <cstring>

// Pure helpers, no Android dependencies, so they can be checked on a host compiler.

constexpr uint32_t kMetadataSanity = 0xFAB11BAF;
constexpr size_t kMetadataProbeSize = 0x200;
constexpr size_t kMetadataMaxSize = 0x20000000;

// Metadata version 31 (Unity 2022.x): sanity, version, then 31 (offset, size) int pairs; the first
// offset equals the header size 0x100. Layout confirmed by the loader check in a Unity 2022 libil2cpp.so
// (header size 0x100, version compared against 0x1f).
constexpr int32_t kMetadataVersion31 = 31;
constexpr size_t kMetadataV31HeaderSize = 0x100;
constexpr size_t kMetadataV31PairCount = 31;

// True when the first bytes look like the header of a plaintext global-metadata.dat of any version
// that starts with sanity, version, firstSectionOffset (versions 16..40, header size 0x80..0x400).
inline bool MetadataHeaderPlausible(const uint8_t *p, size_t available) {
    if (available < 12) return false;
    uint32_t sanity, first;
    int32_t version;
    std::memcpy(&sanity, p, 4);
    std::memcpy(&version, p + 4, 4);
    std::memcpy(&first, p + 8, 4);
    return sanity == kMetadataSanity && version >= 16 && version <= 40 && first >= 0x80 && first <= 0x400;
}

// Exact total size of a v31 metadata image from its 0x100-byte header (largest offset+size over all
// sections), or 0 when the header is not a consistent v31 header.
inline size_t MetadataV31TotalSize(const uint8_t *header, size_t available) {
    if (available < kMetadataV31HeaderSize || !MetadataHeaderPlausible(header, available)) return 0;
    int32_t version;
    uint32_t first;
    std::memcpy(&version, header + 4, 4);
    std::memcpy(&first, header + 8, 4);
    if (version != kMetadataVersion31 || first != kMetadataV31HeaderSize) return 0;
    uint64_t end = kMetadataV31HeaderSize;
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


// Magic-independent detector for metadata versions 24..40, whose header is: magic, version,
// then (offset, size) int pairs with the first offset equal to the header size (8 + 8 * pairs).
// A protector may replace the magic word, so the first word is ignored here. Returns the total size
// (largest offset+size) when the pairs are non-negative, offsets never decrease, every offset is
// at least the header size and most sections are non-empty; otherwise 0.
inline size_t MetadataStructureSize(const uint8_t *header, size_t available) {
    if (available < 12) return 0;
    int32_t version;
    uint32_t first;
    std::memcpy(&version, header + 4, 4);
    std::memcpy(&first, header + 8, 4);
    if (version < 24 || version > 40 || first < 0xC0 || first > 0x400 || (first & 7) != 0) return 0;
    if (available < first) return 0;
    size_t pairs = (first - 8) / 8;
    uint64_t end = first;
    uint32_t prev_offset = first;
    size_t non_empty = 0;
    for (size_t i = 0; i < pairs; i++) {
        int32_t offset, size;
        std::memcpy(&offset, header + 8 + i * 8, 4);
        std::memcpy(&size, header + 12 + i * 8, 4);
        if (offset < 0 || size < 0 || (uint32_t) offset < prev_offset || (uint32_t) offset < first) return 0;
        prev_offset = (uint32_t) offset;
        uint64_t section_end = (uint64_t) (uint32_t) offset + (uint32_t) size;
        if (section_end > kMetadataMaxSize) return 0;
        if (section_end > end) end = section_end;
        if (size > 0) non_empty++;
    }
    if (non_empty * 3 < pairs * 2) return 0;
    return (size_t) end;
}

// Scans this process's readable runtime memory for a decrypted global-metadata image, found either
// by its magic word or by the structure of its header, and writes each distinct one (at most 4) to <outDir>/files/global-metadata.dec.dat, .dec2.dat, ...
// Returns the number of files written. Needs no per-build offsets.
int dump_decrypted_metadata(const char *outDir);

// Appends one line to <outDir>/files/module_status.txt so a run is visible without logcat.
void write_status(const char *outDir, const char *line);

#endif //ZYGISK_IL2CPPDUMPER_METADATA_DUMP_H
