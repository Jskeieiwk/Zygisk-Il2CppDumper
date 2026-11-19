#include "metadata_dump.h"
#include "log.h"
#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/uio.h>
#include <unistd.h>
#include <vector>

namespace {

struct Region {
    uint64_t start, end;
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

// Readable regions that are not backed by a file: heap, malloc arenas, [anon:...].
std::vector<Region> AnonymousReadableRegions() {
    std::vector<Region> regions;
    FILE *f = fopen("/proc/self/maps", "r");
    if (!f) return regions;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        unsigned long long start, end;
        char perms[8];
        int consumed = 0;
        if (sscanf(line, "%llx-%llx %7s %*s %*s %*s %n", &start, &end, perms, &consumed) < 3) continue;
        if (perms[0] != 'r') continue;
        const char *path = line + consumed;
        while (*path == ' ') path++;
        if (*path == '/' || std::strncmp(path, "[stack", 6) == 0) continue;
        if (end <= start) continue;
        regions.push_back({start, end});
    }
    fclose(f);
    return regions;
}

// Candidate metadata image found at `addr`; `limit` is the end of its mapping.
bool ReadCandidate(uint64_t addr, uint64_t limit, std::vector<uint8_t> &out) {
    uint8_t header[kMetadataProbeSize];
    size_t probe = (size_t) std::min<uint64_t>(sizeof(header), limit - addr);
    if (!SafeRead(addr, header, probe) || !MetadataHeaderPlausible(header, probe)) return false;
    size_t total = MetadataV31TotalSize(header, probe);
    if (total) {
        if (addr + total > limit) return false;
        LOGI("metadata: v31 image at %llx, exact size %zu", (unsigned long long) addr, total);
    } else {
        // Other versions: layout not verified here, so bound by the mapping and say so.
        total = (size_t) std::min<uint64_t>(limit - addr, kMetadataMaxSize);
        LOGW("metadata: header at %llx has version != 31, size taken from the mapping (%zu), unverified",
             (unsigned long long) addr, total);
    }
    out.resize(total);
    return SafeRead(addr, out.data(), total);
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
    // The image's own header bytes AF 1B B1 FA, scanned on 4-byte boundaries.
    const uint8_t magic[4] = {0xAF, 0x1B, 0xB1, 0xFA};
    std::vector<std::vector<uint8_t>> found;
    for (int round = 0; round < kScanRounds && found.empty(); round++) {
        if (round) sleep(3);
        std::vector<uint8_t> chunk(kChunk + 4);
        for (const Region &r: AnonymousReadableRegions()) {
            for (uint64_t pos = r.start; pos < r.end; pos += kChunk) {
                size_t n = (size_t) std::min<uint64_t>(kChunk + 3, r.end - pos);
                if (n < 4 || !SafeRead(pos, chunk.data(), n)) continue;
                for (size_t i = 0; i + 4 <= n; i += 4) {
                    if (std::memcmp(&chunk[i], magic, 4) != 0) continue;
                    uint64_t hit = pos + i;
                    uint64_t self = (uint64_t) chunk.data();
                    if (hit >= self && hit < self + chunk.size()) continue;  // our own read buffer
                    std::vector<uint8_t> image;
                    if (!ReadCandidate(hit, r.end, image)) continue;
                    bool duplicate = false;
                    for (const auto &g: found) duplicate = duplicate || g == image;
                    if (!duplicate && (int) found.size() < kMaxFiles) found.push_back(std::move(image));
                }
            }
        }
        if (found.empty()) LOGW("metadata: no decrypted image in memory yet (round %d)", round + 1);
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
