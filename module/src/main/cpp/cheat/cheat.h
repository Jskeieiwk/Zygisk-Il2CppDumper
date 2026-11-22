#ifndef CLOUD_CHEAT_H
#define CLOUD_CHEAT_H

#include <cstdint>

void cheat_start(const char *game_data_dir);

struct CheatConfig {
    bool  enabled_overlay      = true;
    bool  enabled_watermark    = true;

    bool  enabled_fov_lock     = false;
    float fov_value            = 90.0f;

    bool  enabled_fly          = false;
    bool  enabled_speed        = false;
    float speed_multiplier     = 2.5f;

    bool  enabled_god          = false;
    bool  enabled_ghost        = false;
    bool  enabled_laser        = false;
    float laser_dps            = 9999.0f;
    float laser_range          = 500.0f;

    bool  enabled_no_recoil    = false;
    bool  enabled_no_spread    = false;

    bool  enabled_esp_box      = false;
    bool  enabled_esp_name     = false;
    bool  enabled_esp_distance = false;
    bool  enabled_esp_line     = false;
    float esp_max_distance     = 400.0f;

    bool  enabled_aim_visual   = false;
    float aim_fov              = 10.0f;
    bool  aim_target_bone_head = true;

    bool  enabled_chams        = false;

    bool  enabled_antiguard    = true;
};

extern CheatConfig g_cfg;

void cheat_config_load();
void cheat_config_watch_thread();

#endif
