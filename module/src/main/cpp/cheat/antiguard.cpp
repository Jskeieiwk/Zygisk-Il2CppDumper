// Neutralises Berda's libguard.so.
//
// libguard exports exactly two symbols the game polls — guard_status (20
// bytes) and guard_verify (16 bytes) — and does its scanning on a worker
// thread spawned from init_array.  The game reads those return values, so
// a flat "return 0" rewrite of both functions ends the whole detection.
//
// We also silence any residual constructor scan on Adreno/Mali by simply
// not touching the worker — it can run forever and find whatever it
// wants; the game never sees the result once the getters lie.

#include "antiguard.h"
#include "hook.h"
#include "../log.h"

#include <dlfcn.h>
#include <cstdint>
#include <cstring>

static const uint32_t kClean[2] = {
    0xd2800000,   // movz x0, #0
    0xd65f03c0,   // ret
};

static bool patch_export(void *handle, const char *name) {
    void *p = dlsym(handle, name);
    if (!p) {
        LOGW("[antiguard] symbol %s missing", name);
        return false;
    }
    patch_bytes(p, kClean, sizeof(kClean));
    LOGI("[antiguard] patched %s @ %p -> return 0", name, p);
    return true;
}

void antiguard_install() {
    void *g = dlopen("libguard.so", RTLD_NOW);
    if (!g) {
        LOGI("[antiguard] libguard.so not loaded — nothing to patch");
        return;
    }
    bool ok1 = patch_export(g, "guard_status");
    bool ok2 = patch_export(g, "guard_verify");
    if (ok1 && ok2) LOGI("[antiguard] libguard neutralised");
    else            LOGW("[antiguard] partial neutralisation — one symbol missing");
}
