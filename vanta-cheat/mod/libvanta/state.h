// state.h — глобальное состояние libvanta (все тогглы меню, конфиг ESP/aim).
#pragma once

#include <atomic>
#include <stdint.h>

namespace vanta {

struct State {
    // жизненный цикл
    std::atomic<bool> loaded{false};
    std::atomic<bool> menu_open{false};
    std::atomic<bool> esp_initialized{false};

    // UI окно
    float menu_x = 0.15f;      // в единицах экрана (ratio)
    float menu_y = 0.15f;
    float menu_w = 0.60f;
    float menu_h = 0.70f;

    // watermark плавающая кнопка — координаты и видимость
    float wm_x = 0.72f;
    float wm_y = 0.04f;

    // активная вкладка
    int tab_main = 0;    // 0=Combat 1=Visuals 2=Utility 3=Player 4=Skins 5=Misc
    int tab_sub  = 0;

    // --- Combat / Aimbot ---
    bool  aim_enabled    = false;
    bool  aim_fire_only  = true;
    bool  aim_head       = true;
    bool  aim_visible    = true;
    bool  aim_ignore_team = true;
    float aim_fov        = 180.0f;   // px
    float aim_smooth     = 0.35f;
    float aim_dead       = 4.0f;

    // --- Visuals / ESP ---
    bool  esp_box     = true;
    bool  esp_line    = false;
    bool  esp_name    = true;
    bool  esp_hp      = true;
    bool  esp_dist    = true;
    bool  esp_skeleton = false;
    float esp_max_distance = 300.0f;
    uint32_t color_enemy = 0xFFFF2E2E;
    uint32_t color_team  = 0xFF00E676;
    uint32_t color_text  = 0xFFFFFFFF;

    // --- Utility ---
    bool  util_no_recoil = false;
    bool  util_no_spread = false;
    bool  util_fast_loot = false;
    bool  util_auto_heal = false;

    // --- Player ---
    bool  player_speed  = false;
    float player_speed_mul = 1.0f;
    bool  player_god    = false;
    bool  player_fly    = false;

    // --- Misc ---
    bool  show_fps = true;
};

extern State g;

} // namespace vanta
