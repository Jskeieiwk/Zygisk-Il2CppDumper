// gl_hook.cpp — хук eglSwapBuffers у libil2cpp.so / libunity.so / libmain.so, и там рендерим.
#include "gl_hook.h"
#include "plt_hook.h"
#include "renderer.h"
#include "game.h"
#include "aim.h"
#include "state.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <atomic>

#define LOGK(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-hook", fmt, ##__VA_ARGS__)

namespace vanta {

using eglSwapBuffers_t = EGLBoolean (*)(EGLDisplay, EGLSurface);
static eglSwapBuffers_t orig_eglSwapBuffers = nullptr;
static std::atomic<int> g_refresh_counter{0};

static EGLBoolean my_eglSwapBuffers(EGLDisplay dpy, EGLSurface sfc) {
    EGLint w = 0, h = 0;
    eglQuerySurface(dpy, sfc, EGL_WIDTH, &w);
    eglQuerySurface(dpy, sfc, EGL_HEIGHT, &h);

    if (w > 0 && h > 0) {
        if (renderer_init_if_needed(w, h)) {
            // раз в 2 кадра обновляем snapshot игроков — чтобы не кушать CPU каждым кадром
            if ((g_refresh_counter.fetch_add(1) & 1) == 0) {
                game_refresh();
            }
            renderer_new_frame(w, h);
            aim_tick_and_update();
            renderer_draw();
        }
    }
    if (orig_eglSwapBuffers) return orig_eglSwapBuffers(dpy, sfc);
    return EGL_FALSE;
}

bool hook_egl_swap() {
    // хукаем во всех .so, которые могут содержать импорт eglSwapBuffers — на всякий.
    static const char* targets[] = {
        "libil2cpp.so", "libunity.so", "libmain.so", "libgame.so", nullptr
    };
    void* any_prev = nullptr;
    for (int i = 0; targets[i]; ++i) {
        void* prev = plt_hook(targets[i], "eglSwapBuffers", (void*)my_eglSwapBuffers);
        if (prev) {
            any_prev = prev;
            orig_eglSwapBuffers = reinterpret_cast<eglSwapBuffers_t>(prev);
            LOGK("hooked eglSwapBuffers in %s", targets[i]);
        }
    }
    if (!orig_eglSwapBuffers) {
        orig_eglSwapBuffers = (eglSwapBuffers_t)eglSwapBuffers; // прямой вызов как fallback
    }
    return any_prev != nullptr;
}

void unhook_egl_swap() {
    // no-op — Linux loader уже удаляет наш .so; GOT не восстанавливаем.
}

} // namespace vanta
