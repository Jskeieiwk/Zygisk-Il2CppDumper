// game.h — il2cpp reader. читает позиции/HP активных игроков.
#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>

namespace vanta {

struct Vec3 { float x, y, z; };

struct PlayerSnap {
    uint32_t id;
    Vec3 pos;
    Vec3 head;
    float hp;
    float max_hp;
    float distance;
    bool  local;
    bool  alive;
    bool  teammate;
    char  nick[32];
};

struct CamSnap {
    Vec3 pos;
    Vec3 forward;
    float fov;
    int   screen_w, screen_h;
};

bool game_init();                 // резолвит классы/методы; false если il2cpp ещё не готов
void game_refresh();              // пересчитать snapshot (вызывается из render thread раз в N кадров)
const CamSnap& game_camera();
void game_copy_players(std::vector<PlayerSnap>& out);  // копия под мьютексом

} // namespace vanta
