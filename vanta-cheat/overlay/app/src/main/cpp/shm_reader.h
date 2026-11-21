// shm_reader.h — чтение shared-memory от helper.so
#pragma once
#include "shm_proto.h"
#include <atomic>

namespace vanta {

struct ShmReader {
    int fd = -1;
    VantaShmHeader* ptr = nullptr;
    bool open();
    void close();
    // snap — скопировать когерентный снапшот (двойное чтение seq)
    bool snap(VantaShmHeader* dst);
};

} // namespace vanta
