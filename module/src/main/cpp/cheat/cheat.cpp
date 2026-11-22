#include "cheat.h"
#include "il2cpp_api.h"
#include "features.h"
#include "overlay.h"
#include "hook.h"
#include "../log.h"
#include "../game.h"

#include <thread>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

CheatConfig g_cfg;
static std::atomic<bool> s_started{false};

static const char *kConfigPath = "/sdcard/cloud_cheat.ini";

static void parse_bool(const char *v, bool &out) {
    if (!v) return;
    while (*v == ' ' || *v == '\t') ++v;
    out = (*v == '1' || *v == 't' || *v == 'T' || *v == 'y' || *v == 'Y' || *v == 'o' || *v == 'O');
}
static void parse_float(const char *v, float &out) {
    if (!v) return;
    float f = (float)atof(v);
    if (f == f) out = f;
}

void cheat_config_load() {
    FILE *fp = fopen(kConfigPath, "re");
    if (!fp) {
        LOGI("[Cloud] no config at %s, using defaults", kConfigPath);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char *eq = strchr(line, '=');
        if (!eq) continue;
        *eq = 0;
        const char *k = line;
        const char *v = eq + 1;
        char *nl = strpbrk((char*)v, "\r\n");
        if (nl) *nl = 0;
#define SET_B(name, field) if (strcmp(k, name) == 0) { parse_bool(v, g_cfg.field); continue; }
#define SET_F(name, field) if (strcmp(k, name) == 0) { parse_float(v, g_cfg.field); continue; }
        SET_B("overlay",       enabled_overlay);
        SET_B("watermark",     enabled_watermark);
        SET_B("fov_lock",      enabled_fov_lock);
        SET_F("fov",           fov_value);
        SET_B("fly",           enabled_fly);
        SET_B("speed",         enabled_speed);
        SET_F("speed_mult",    speed_multiplier);
        SET_B("no_recoil",     enabled_no_recoil);
        SET_B("no_spread",     enabled_no_spread);
        SET_B("esp_box",       enabled_esp_box);
        SET_B("esp_name",      enabled_esp_name);
        SET_B("esp_distance",  enabled_esp_distance);
        SET_B("esp_line",      enabled_esp_line);
        SET_F("esp_max_dist",  esp_max_distance);
        SET_B("aim_visual",    enabled_aim_visual);
        SET_F("aim_fov",       aim_fov);
        SET_B("chams",         enabled_chams);
        SET_B("antiguard",     enabled_antiguard);
#undef SET_B
#undef SET_F
    }
    fclose(fp);
    LOGI("[Cloud] config loaded");
}

void cheat_config_watch_thread() {
    time_t last = 0;
    while (true) {
        struct stat st{};
        if (stat(kConfigPath, &st) == 0 && st.st_mtime != last) {
            last = st.st_mtime;
            cheat_config_load();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

static void wait_for_il2cpp_runtime() {
    for (int i = 0; i < 120; ++i) {
        if (il2cpp_domain_get && il2cpp_domain_get() != nullptr) {
            auto t = il2cpp_thread_attach(il2cpp_domain_get());
            (void)t;
            LOGI("[Cloud] il2cpp runtime up (try %d)", i);
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    LOGE("[Cloud] il2cpp runtime never came up");
}

void cheat_start(const char *game_data_dir) {
    bool expected = false;
    if (!s_started.compare_exchange_strong(expected, true)) {
        LOGW("[Cloud] cheat_start re-entered, ignoring");
        return;
    }

    LOGI("================================================================");
    LOGI("  %s  — Berda Survival cheat %s", CheatWatermark, CheatVersion);
    LOGI("  data dir: %s", game_data_dir ? game_data_dir : "(null)");
    LOGI("================================================================");

    cheat_config_load();
    std::thread(cheat_config_watch_thread).detach();

    if (g_cfg.enabled_overlay) {
        overlay_install();
    }

    std::thread([game_data_dir]() {
        wait_for_il2cpp_runtime();
        features_resolve_types();
        features_install_hooks();
        features_tick_loop();
    }).detach();
}
