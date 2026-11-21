// uinput_aim.h — создаёт виртуальный touch-device через /dev/uinput и стримит движения прицела.
// требует root. движения эмулируют свайпы вокруг центра экрана, что движет prоцел в игре.
#pragma once

#include <stdint.h>
#include <atomic>

namespace vanta {

struct AimConfig {
    float fov_px      = 180.f;  // радиус в экранных пикселях — цели только внутри
    float smooth      = 0.25f;  // 0..1, больше — плавнее
    float deadzone_px = 4.f;
    bool  prefer_head = true;
    bool  lock_only_while_firing = true;  // активен пока жмётся кнопка огонь (через key_hold)
};

bool aim_init();
void aim_set_config(const AimConfig& c);
void aim_update(int screen_cx, int screen_cy, int target_sx, int target_sy, bool active);
void aim_shutdown();

} // namespace vanta
