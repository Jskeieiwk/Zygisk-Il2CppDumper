#include "shm_reader.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <android/log.h>

#define LOGR(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-shm", fmt, ##__VA_ARGS__)

namespace vanta {

bool ShmReader::open() {
    const char* path = "/data/local/tmp/" VANTA_SHM_NAME;
    fd = ::open(path, O_RDONLY);
    if (fd < 0) { LOGR("open shm fail"); return false; }
    void* p = mmap(nullptr, sizeof(VantaShmHeader), PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) { ::close(fd); fd = -1; return false; }
    ptr = reinterpret_cast<VantaShmHeader*>(p);
    if (ptr->magic != VANTA_SHM_MAGIC) { LOGR("bad magic"); close(); return false; }
    return true;
}

void ShmReader::close() {
    if (ptr) munmap(ptr, sizeof(VantaShmHeader));
    if (fd >= 0) ::close(fd);
    ptr = nullptr; fd = -1;
}

bool ShmReader::snap(VantaShmHeader* dst) {
    if (!ptr || !dst) return false;
    for (int tries = 0; tries < 4; ++tries) {
        uint64_t s1 = ptr->seq;
        memcpy(dst, ptr, sizeof(*dst));
        uint64_t s2 = ptr->seq;
        if (s1 == s2 && s1 != 0) return true;
    }
    return false;
}

} // namespace vanta
