#include "ms_main.h"

#include <unistd.h>

#include "features.h"
#include "hook.h"
#include "il2cpp_rt.h"
#include "ms_game.h"
#include "ms_log.h"
#include "ms_state.h"
#include "overlay.h"

namespace ms {

void start(void *il2cpp_handle) {
    using il2cpp::api;
    if (!il2cpp::load_api(il2cpp_handle)) return;
    if (!il2cpp::init_module_range(reinterpret_cast<void *>(api.domain_get))) return;

    int waited = 0;
    while (!api.is_vm_thread(nullptr)) {
        if (++waited > 300) {
            MS_LOGE("il2cpp_init did not finish in 300 s");
            return;
        }
        sleep(1);
    }

    void *thread = api.thread_attach(api.domain_get());
    bool resolved = false;
    for (int attempt = 0; attempt < 10 && !resolved; ++attempt) {
        resolved = game::resolve();
        if (!resolved) sleep(2);
    }
    if (thread) api.thread_detach(thread);
    if (!resolved) {
        MS_LOGE("game symbols not resolved; this build of Magic Survival is not supported");
        return;
    }

    hook::Spec specs[16];
    size_t n = features::fill_hook_specs(specs, 16);
    if (n == 0) {
        MS_LOGE("game hook table empty");
        return;
    }
    const size_t n_overlay = overlay::fill_hook_specs(specs + n, 16 - n);
    if (n_overlay == 0) {
        MS_LOGE("eglSwapBuffers not resolved; menu cannot be drawn");
        return;
    }
    n += n_overlay;

    if (!hook::install_all(specs, n)) {
        MS_LOGE("hook installation failed, everything rolled back");
        return;
    }
    features::set_ready();
    overlay::set_ready();
    g_status.hooks_ready.store(true);
    MS_LOGI("ready: %zu hooks, double-tap the screen to open the menu", n);
}

}  // namespace ms
