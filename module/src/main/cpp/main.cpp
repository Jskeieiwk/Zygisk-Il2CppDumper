#include <cstring>
#include <cstdio>
#include <string>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <jni.h>

#include "hack.h"
#include "game.h"
#include "log.h"

// Payload entry: fires when the injector dlopen()s this .so inside the game
// process.  We read our own cmdline (= target app's) and start the hack
// pipeline in a detached thread so the injector can resume its loader
// stub without waiting on us.

static std::string my_cmdline() {
    char buf[256]{};
    int fd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
    if (fd < 0) return {};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (n <= 0) return {};
    return std::string(buf);  // cmdline is NUL-separated; first token is enough
}

static std::string data_dir_for(const std::string &pkg) {
    char path[256];
    snprintf(path, sizeof(path), "/data/data/%s/files", pkg.c_str());
    mkdir(path, 0755);
    return path;
}

__attribute__((constructor))
static void cloud_cheat_init() {
    auto pkg = my_cmdline();
    LOGI("[Cloud] dlopen'd into pid=%d cmdline=%s", getpid(), pkg.c_str());

    if (pkg != GamePackageName) {
        LOGW("[Cloud] not the target process (%s != %s) — bailing", pkg.c_str(), GamePackageName);
        return;
    }

    std::string dd = data_dir_for(pkg);
    char *cd = new char[dd.size() + 1];
    strcpy(cd, dd.c_str());

    std::thread(hack_start, cd).detach();
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    (void)vm; (void)reserved;
    // Second entry — for injectors that explicitly call JNI_OnLoad after dlopen.
    // The constructor above has already fired; this is a safe no-op.
    return JNI_VERSION_1_6;
}
