// entry.cpp — главный entry point, вызываемый инжектором после dlopen.
#include "state.h"
#include "gl_hook.h"
#include "input.h"
#include "aim.h"
#include "game.h"

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <android/log.h>

#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-main", fmt, ##__VA_ARGS__)

namespace vanta {

static bool read_overlay_flag() {
    FILE* f = fopen("/data/local/tmp/vanta.flag", "r");
    if (!f) return true;
    int c = fgetc(f);
    fclose(f);
    return c != '0';
}

static void* init_thread(void*) {
    bool overlay_on = read_overlay_flag();
    LOGE("vanta: overlay=%d, ждём EGL context", overlay_on ? 1 : 0);

    // даём игре время загрузить il2cpp и libEGL
    for (int i = 0; i < 100 && !g.loaded.load(); ++i) {
        if (hook_egl_swap()) {
            LOGE("EGL swap hooked");
            break;
        }
        usleep(200000);
    }

    // il2cpp
    for (int i = 0; i < 300; ++i) {
        if (game_init()) break;
        usleep(100000);
    }

    input_start();
    aim_start();
    g.menu_open = overlay_on;
    g.loaded = true;
    LOGE("vanta ready");
    return nullptr;
}

} // namespace vanta

extern "C" __attribute__((visibility("default")))
int vanta_start() {
    pthread_t t;
    pthread_create(&t, nullptr, vanta::init_thread, nullptr);
    pthread_detach(t);
    return 0;
}

extern "C" __attribute__((visibility("default")))
int vanta_stop() {
    vanta::aim_stop();
    vanta::input_stop();
    vanta::unhook_egl_swap();
    return 0;
}
