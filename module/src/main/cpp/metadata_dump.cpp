#include "metadata_dump.h"
#include "log.h"
#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <vector>

namespace {

struct Region {
    uint64_t start, end;
    std::string path;
};

constexpr size_t kChunk = 4u << 20;
constexpr int kMaxFiles = 4;
constexpr int kScanRounds = 5;

// Copies memory of this process without risking SIGSEGV on an unreadable address.
bool SafeRead(uint64_t from, void *to, size_t size) {
    size_t done = 0;
    while (done < size) {
        iovec local{(uint8_t *) to + done, size - done};
        iovec remote{(void *) (from + done), size - done};
        ssize_t n = process_vm_readv(getpid(), &local, 1, &remote, 1, 0);
        if (n <= 0) return false;
        done += (size_t) n;
    }
    return true;
}

// True for mappings that are static code/resources and cannot hold a freshly decrypted buffer.
bool IsStaticFileMapping(const std::string &path) {
    static const char *prefixes[] = {"/system", "/apex", "/vendor", "/product", "/odm", "/data/app",
                                     "/data/dalvik-cache", "/dev/__properties__", "/proc"};
    static const char *contains[] = {".so", ".apk", ".odex", ".vdex", ".oat", ".art", ".jar", ".dex",
                                     ".ttf", ".otf", ".obb", ".pak"};
    for (const char *p: prefixes)
        if (path.rfind(p, 0) == 0) return true;
    for (const char *c: contains)
        if (path.find(c) != std::string::npos) return true;
    return false;
}

// Readable regions that can hold runtime data: heap, malloc arenas, [anon:...], memfd, ashmem and
// other mappings that are not static libraries or resources.
std::vector<Region> ScannableRegions() {
    std::vector<Region> regions;
    FILE *f = fopen("/proc/self/maps", "r");
    if (!f) return regions;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        unsigned long long start, end;
        char perms[8];
        int consumed = 0;
        if (sscanf(line, "%llx-%llx %7s %*s %*s %*s %n", &start, &end, perms, &consumed) < 3) continue;
        if (perms[0] != 'r' || end <= start) continue;
        const char *p = line + consumed;
        while (*p == ' ') p++;
        std::string path(p);
        while (!path.empty() && (path.back() == '\n' || path.back() == ' ')) path.pop_back();
        if (path.rfind("[stack", 0) == 0 || path == "[vvar]" || path == "[vsyscall]") continue;
        if (!path.empty() && path[0] == '/' && IsStaticFileMapping(path)) continue;
        regions.push_back({start, end, path});
    }
    fclose(f);
    return regions;
}

// Candidate metadata image found at `addr`; `limit` is the end of its mapping. `by_structure` means
// the first word is not the standard magic: the image is accepted from its header layout alone and
// the magic is restored in the output.
bool ReadCandidate(uint64_t addr, uint64_t limit, bool by_structure, std::vector<uint8_t> &out) {
    uint8_t header[kMetadataProbeSize];
    size_t probe = (size_t) std::min<uint64_t>(sizeof(header), limit - addr);
    if (!SafeRead(addr, header, probe)) return false;
    size_t total = 0;
    if (by_structure) {
        total = MetadataStructureSize(header, probe);
        if (!total) return false;
        uint32_t first_word;
        std::memcpy(&first_word, header, 4);
        LOGI("metadata: structural match at %llx, first word %08x, size %zu",
             (unsigned long long) addr, first_word, total);
    } else {
        if (!MetadataHeaderPlausible(header, probe)) {
            static int rejected_logged = 0;
            if (rejected_logged++ < 8) {
                int32_t version;
                uint32_t first;
                std::memcpy(&version, header + 4, 4);
                std::memcpy(&first, header + 8, 4);
                LOGW("metadata: magic at %llx rejected: version=%d firstSection=0x%x",
                     (unsigned long long) addr, version, first);
            }
            return false;
        }
        total = MetadataV31TotalSize(header, probe);
        if (total) {
            LOGI("metadata: v31 image at %llx, exact size %zu", (unsigned long long) addr, total);
        } else {
            total = MetadataStructureSize(header, probe);
            if (total) {
                LOGI("metadata: image at %llx, size from header %zu", (unsigned long long) addr, total);
            } else {
                // Other versions: layout not verified here, so bound by the mapping and say so.
                total = (size_t) std::min<uint64_t>(limit - addr, kMetadataMaxSize);
                LOGW("metadata: header at %llx has an unverified layout, size taken from the mapping (%zu)",
                     (unsigned long long) addr, total);
            }
        }
    }
    if (addr + total > limit) {
        LOGW("metadata: header at %llx needs %zu bytes but its mapping has %llu", (unsigned long long) addr,
             total, (unsigned long long) (limit - addr));
        return false;
    }
    out.resize(total);
    if (!SafeRead(addr, out.data(), total)) return false;
    if (by_structure) {
        const uint8_t magic[4] = {0xAF, 0x1B, 0xB1, 0xFA};
        std::memcpy(out.data(), magic, 4);
    }
    return true;
}

bool WriteFile(const std::string &path, const std::vector<uint8_t> &data) {
    FILE *f = fopen(path.c_str(), "wb");
    if (!f) {
        LOGE("metadata: cannot open %s (errno %d)", path.c_str(), errno);
        return false;
    }
    bool ok = fwrite(data.data(), 1, data.size(), f) == data.size();
    ok = (fclose(f) == 0) && ok;
    LOGI("metadata: wrote %zu bytes to %s ok=%d", data.size(), path.c_str(), (int) ok);
    return ok;
}

}  // namespace

int dump_decrypted_metadata(const char *outDir) {
    // <outDir>/files may not exist yet in the game's data directory; il2cpp_dump writes there too.
    std::string files_dir = std::string(outDir).append("/files");
    if (mkdir(files_dir.c_str(), 0771) != 0 && errno != EEXIST)
        LOGE("metadata: mkdir %s failed (errno %d)", files_dir.c_str(), errno);
    // Two detectors on 4-byte boundaries: the standard magic word, and a magic-independent one
    // (version word followed by a plausible header size) for builds whose protector changed the magic.
    const uint8_t magic[4] = {0xAF, 0x1B, 0xB1, 0xFA};
    constexpr size_t kOverlap = 12;
    std::vector<std::vector<uint8_t>> found;
    for (int round = 0; round < kScanRounds && found.empty(); round++) {
        if (round) sleep(3);
        std::vector<uint8_t> chunk(kChunk + kOverlap);
        for (const Region &r: ScannableRegions()) {
            for (uint64_t pos = r.start; pos < r.end; pos += kChunk) {
                size_t n = (size_t) std::min<uint64_t>(kChunk + kOverlap, r.end - pos);
                if (n < 12 || !SafeRead(pos, chunk.data(), n)) continue;
                for (size_t i = 0; i + 12 <= n; i += 4) {
                    uint32_t w1, w2;
                    std::memcpy(&w1, &chunk[i + 4], 4);
                    std::memcpy(&w2, &chunk[i + 8], 4);
                    bool by_magic = std::memcmp(&chunk[i], magic, 4) == 0;
                    bool by_structure = !by_magic && w1 >= 24 && w1 <= 40 && w2 >= 0xC0 && w2 <= 0x400 &&
                                        (w2 & 7) == 0;
                    if (!by_magic && !by_structure) continue;
                    uint64_t hit = pos + i;
                    uint64_t self = (uint64_t) chunk.data();
                    if (hit >= self && hit < self + chunk.size()) continue;  // our own read buffer
                    std::vector<uint8_t> image;
                    if (!ReadCandidate(hit, r.end, by_structure, image)) continue;
                    bool duplicate = false;
                    for (const auto &g: found) duplicate = duplicate || g == image;
                    if (!duplicate && (int) found.size() < kMaxFiles) found.push_back(std::move(image));
                }
            }
        }
        if (found.empty()) {
            size_t regions = 0;
            uint64_t bytes = 0;
            for (const Region &r: ScannableRegions()) {
                regions++;
                bytes += r.end - r.start;
            }
            LOGW("metadata: no decrypted image in memory yet (round %d, scanned %zu regions, %llu MB)",
                 round + 1, regions, (unsigned long long) (bytes >> 20));
        }
    }
    int written = 0;
    for (size_t i = 0; i < found.size(); i++) {
        std::string path = std::string(outDir).append("/files/global-metadata.dec");
        if (i) path.append(std::to_string(i + 1));
        path.append(".dat");
        if (WriteFile(path, found[i])) written++;
    }
    if (!written) LOGE("metadata: nothing written");
    return written;
}
