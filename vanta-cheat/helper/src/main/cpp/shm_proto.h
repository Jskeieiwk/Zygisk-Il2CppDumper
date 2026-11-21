// shm_proto.h — протокол shared-memory между helper (внутри игры) и overlay (наш процесс)
// обе стороны видят одну и ту же структуру. helper только пишет, overlay только читает.
#pragma once

#include <stdint.h>

#define VANTA_SHM_NAME      "vanta_oxide_shm"
#define VANTA_SHM_MAGIC     0x56414E54u   // 'VANT'
#define VANTA_SHM_VERSION   1u
#define VANTA_MAX_PLAYERS   128
#define VANTA_NICK_LEN      32

enum VantaFlags : uint32_t {
    VF_ALIVE    = 1u << 0,
    VF_LOCAL    = 1u << 1,  // это сам игрок — рисовать не надо
    VF_TEAMMATE = 1u << 2,
    VF_VISIBLE  = 1u << 3,  // не окклюжен (raycast прошёл) — если helper смог посчитать
    VF_BOT      = 1u << 4,
};

struct VantaVec3 { float x, y, z; };
struct VantaVec2 { float x, y; };
struct VantaMat4 { float m[16]; };

struct VantaPlayer {
    uint32_t net_id;           // netId из Mirror — стабильный ID
    uint32_t flags;            // VantaFlags
    VantaVec3 pos;             // world position (центр груди)
    VantaVec3 head;            // head bone position
    VantaVec3 velocity;        // текущая скорость
    float     health;          // 0..max
    float     max_health;      // 100 обычно
    float     distance;        // от локалки до этого игрока, метров
    uint32_t  team_id;
    char      nick[VANTA_NICK_LEN];
};

struct VantaCamera {
    VantaVec3 pos;             // мировая позиция камеры
    VantaVec3 forward;         // forward вектор
    VantaMat4 view_proj;        // view*projection матрица для World→Screen
    float     fov;
    int32_t   screen_w;
    int32_t   screen_h;
};

// основная структура в shm; обновляется helper'ом каждые N мс
struct VantaShmHeader {
    uint32_t magic;
    uint32_t version;
    uint64_t seq;              // ++ каждый фрейм — overlay читает дважды и сверяет
    uint64_t timestamp_ns;     // CLOCK_MONOTONIC
    uint32_t game_pid;
    uint32_t local_player_idx; // индекс локалки в players[]
    uint32_t player_count;
    uint32_t _pad;
    VantaCamera camera;
    VantaPlayer players[VANTA_MAX_PLAYERS];
};
static_assert(sizeof(VantaShmHeader) < 128 * 1024, "shm fits in one ashmem page cluster");

// команды overlay → helper (обратный канал), небольшая отдельная структура
struct VantaControl {
    uint32_t magic;
    uint32_t seq;
    uint32_t kill_switch;      // 1 → helper выгружается
    uint32_t enable_hitbox_scan;  // 1 → helper пытается резолвить head-bone по иерархии
};
