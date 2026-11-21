#include "maps_util.h"

#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

namespace vanta {

pid_t find_pid_by_package(const char* package_name) {
    if (!package_name || !*package_name) return -1;
    DIR* proc = opendir("/proc");
    if (!proc) return -1;
    pid_t found = -1;
    dirent* e;
    while ((e = readdir(proc))) {
        if (e->d_type != DT_DIR) continue;
        if (e->d_name[0] < '0' || e->d_name[0] > '9') continue;
        char path[256];
        snprintf(path, sizeof(path), "/proc/%s/cmdline", e->d_name);
        int fd = open(path, O_RDONLY | O_CLOEXEC);
        if (fd < 0) continue;
        char buf[256] = {0};
        read(fd, buf, sizeof(buf) - 1);
        close(fd);
        if (strcmp(buf, package_name) == 0) {
            found = atoi(e->d_name);
            break;
        }
    }
    closedir(proc);
    return found;
}

uintptr_t find_module_base(pid_t pid, const char* soname) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    FILE* f = fopen(path, "r");
    if (!f) return 0;
    char line[512];
    uintptr_t base = 0;
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, soname)) continue;
        // формат: 7f1234000-7f5678000 r-xp 00000000 fc:00 12345  /path/to/lib.so
        uintptr_t s;
        if (sscanf(line, "%lx", (long unsigned*)&s) == 1) {
            base = s;
            break;
        }
    }
    fclose(f);
    return base;
}

uintptr_t get_remote_symbol(pid_t pid, const char* lib, const char* sym) {
    void* h = dlopen(lib, RTLD_LAZY);
    if (!h) return 0;
    void* local_sym = dlsym(h, sym);
    if (!local_sym) { dlclose(h); return 0; }
    // определяем где libc лежит у нас
    uintptr_t our_base = find_module_base(getpid(), lib);
    if (!our_base) { dlclose(h); return 0; }
    uintptr_t offset = (uintptr_t)local_sym - our_base;
    uintptr_t their_base = find_module_base(pid, lib);
    dlclose(h);
    if (!their_base) return 0;
    return their_base + offset;
}

} // namespace vanta
