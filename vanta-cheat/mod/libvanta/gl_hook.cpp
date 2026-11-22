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
    static std::atomic<int> once{0};
    if (once.fetch_add(1) < 2) {
        LOGK("my_eglSwapBuffers CALLED #%d dpy=%p sfc=%p", once.load(), dpy, sfc);
    }
    EGLint w = 0, h = 0;
    eglQuerySurface(dpy, sfc, EGL_WIDTH, &w);
    eglQuerySurface(dpy, sfc, EGL_HEIGHT, &h);
    if (w <= 0 || h <= 0) {
        // fallback: через GL_VIEWPORT
        GLint vp[4] = {0};
        glGetIntegerv(GL_VIEWPORT, vp);
        if (vp[2] > 0 && vp[3] > 0) { w = vp[2]; h = vp[3]; }
    }
    if (once.load() < 4) LOGK("swap wh=%dx%d", w, h);

    if (w > 0 && h > 0) {
        if (renderer_init_if_needed(w, h)) {
            if ((g_refresh_counter.fetch_add(1) & 1) == 0) {
                game_refresh();
            }
            renderer_new_frame(w, h);
            aim_tick_and_update();
            renderer_draw();
        } else {
            if (once.load() < 10) LOGK("renderer_init_if_needed returned false");
        }
    }
    if (orig_eglSwapBuffers) return orig_eglSwapBuffers(dpy, sfc);
    return EGL_FALSE;
}

bool hook_egl_swap() {
    // хукаем во ВСЕХ .so процесса — игра может звать eglSwapBuffers откуда угодно.
    int total = 0;
    FILE* f = fopen("/proc/self/maps", "r");
    if (f) {
        char line[1024];
        static char seen[64][128] = {{0}};
        int seen_n = 0;
        while (fgets(line, sizeof(line), f)) {
            // ищем r-xp маппинги .so
            if (!strstr(line, ".so")) continue;
            if (!strstr(line, "r-xp")) continue;
            char path[512] = {0};
            if (sscanf(line, "%*s %*s %*s %*s %*s %511s", path) != 1) continue;
            const char* slash = strrchr(path, '/');
            const char* name = slash ? slash + 1 : path;
            // фильтруем системные
            if (strstr(path, "/system/") || strstr(path, "/apex/")) {
                if (!strstr(path, "libunity") && !strstr(path, "libil2cpp") &&
                    !strstr(path, "libmain")  && !strstr(path, "libgame")) continue;
            }
            // пропускаем дубликаты
            bool dup = false;
            for (int i = 0; i < seen_n; ++i) if (!strcmp(seen[i], name)) { dup = true; break; }
            if (dup) continue;
            if (seen_n < 64) { strncpy(seen[seen_n], name, 127); ++seen_n; }

            void* prev = plt_hook(name, "eglSwapBuffers", (void*)my_eglSwapBuffers);
            if (prev) {
                if (!orig_eglSwapBuffers)
                    orig_eglSwapBuffers = reinterpret_cast<eglSwapBuffers_t>(prev);
                LOGK("hooked eglSwapBuffers in %s", name);
                ++total;
            }
        }
        fclose(f);
    }
    if (!orig_eglSwapBuffers) {
        orig_eglSwapBuffers = (eglSwapBuffers_t)eglSwapBuffers;
    }
    LOGK("hook_egl_swap: %d .so hooked", total);
    return total > 0;
}

void unhook_egl_swap() {
    // no-op — Linux loader уже удаляет наш .so; GOT не восстанавливаем.
}

} // namespace vanta
