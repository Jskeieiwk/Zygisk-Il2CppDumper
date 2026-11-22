#include "cheat.h"
#include "il2cpp_api.h"
#include "features.h"
#include "overlay.h"
#include "antiguard.h"
#include "hook.h"
#include "../log.h"
#include "../game.h"

#include <thread>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <mutex>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

// =========================================================================
//   File logger — mirrors to /sdcard/cloud_cheat.log so dj can see how far
//   we got even when the game crashes before he can grab logcat.
// =========================================================================
static std::mutex s_log_mu;
void cheat_log(const char *fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n < 0) return;

    LOGI("%s", buf);

    std::lock_guard<std::mutex> lk(s_log_mu);
    // Try the game's private files dir first (always writable by this uid),
    // fall back to /sdcard if that fails.
    FILE *fp = fopen("/data/data/" GamePackageName "/files/cloud_cheat.log", "ae");
    if (!fp) fp = fopen("/sdcard/cloud_cheat.log", "ae");
    if (!fp) return;
    time_t t = time(nullptr);
    struct tm lt{};
    localtime_r(&t, &lt);
    fprintf(fp, "[%02d:%02d:%02d] %s\n", lt.tm_hour, lt.tm_min, lt.tm_sec, buf);
    fclose(fp);
}

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
        SET_B("god",           enabled_god);
        SET_B("ghost",         enabled_ghost);
        SET_B("laser",         enabled_laser);
        SET_F("laser_dps",     laser_dps);
        SET_F("laser_range",   laser_range);
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

    cheat_log("=================================================");
    cheat_log("  %s  — Berda %s (pid=%d)", CheatWatermark, CheatVersion, getpid());
    cheat_log("  data dir: %s", game_data_dir ? game_data_dir : "(null)");
    cheat_log("=================================================");

    cheat_config_load();
    cheat_log("config: overlay=%d watermark=%d fov_lock=%d no_recoil=%d antiguard=%d",
              g_cfg.enabled_overlay, g_cfg.enabled_watermark,
              g_cfg.enabled_fov_lock, g_cfg.enabled_no_recoil, g_cfg.enabled_antiguard);
    std::thread(cheat_config_watch_thread).detach();

    std::thread([game_data_dir]() {
        cheat_log("warm-up: sleeping 6s before any hook / patch ...");
        std::this_thread::sleep_for(std::chrono::seconds(6));
        cheat_log("warm-up done");

        if (g_cfg.enabled_antiguard) {
            cheat_log("installing antiguard ...");
            antiguard_install();
            cheat_log("antiguard done");
        } else {
            cheat_log("antiguard SKIPPED (config)");
        }

        if (g_cfg.enabled_overlay) {
            cheat_log("installing overlay ...");
            overlay_install();
            cheat_log("overlay done");
        } else {
            cheat_log("overlay SKIPPED (config)");
        }

        cheat_log("waiting for il2cpp runtime ...");
        wait_for_il2cpp_runtime();
        cheat_log("il2cpp up — resolving types");
        features_resolve_types();
        cheat_log("types resolved — installing feature hooks");
        features_install_hooks();
        cheat_log("entering feature tick loop");
        features_tick_loop();
    }).detach();
}
