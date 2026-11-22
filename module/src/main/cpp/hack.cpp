#include "hack.h"
#include "cheat/cheat.h"
#include "cheat/il2cpp_api.h"
#include "log.h"
#include "xdl.h"
#include <cstdarg>

#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <dlfcn.h>

void hack_start(const char *game_data_dir) {
    cheat_log("hack_start: tid=%d data=%s", gettid(), game_data_dir);
    for (int i = 0; i < 60; ++i) {
        void *handle = xdl_open("libil2cpp.so", 0);
        if (handle) {
            cheat_log("hack_start: libil2cpp.so opened after %ds", i);
            il2cpp_api_init(handle);
            cheat_log("hack_start: il2cpp api bound");
            xdl_info_t info{};
            xdl_info(handle, XDL_DI_DLINFO, &info);
            il2cpp_set_base((uintptr_t)info.dli_fbase);
            cheat_log("hack_start: libil2cpp base=%p", info.dli_fbase);
            cheat_start(game_data_dir);
            return;
        }
        sleep(1);
    }
    cheat_log("hack_start: libil2cpp.so never appeared after 60s");
}
