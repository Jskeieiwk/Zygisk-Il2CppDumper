#pragma once

#include <atomic>

namespace ms {

constexpr int kMulMin = 1;
constexpr int kMulMax = 50;
constexpr int kTimeMulMax = 4;

// Written by the menu, read by the game hooks. All game-side work happens on Unity's main thread.
struct Settings {
    std::atomic<bool> god_mode{false};
    std::atomic<bool> infinite_hp{false};
    std::atomic<int> attack_mul{1};       // damage dealt to enemies
    std::atomic<int> pickup_radius_mul{1};
    std::atomic<int> mana_gain_mul{1};    // mana per pickup
    std::atomic<int> time_mul{1};         // 1..4

    // One-shot actions, consumed by the main thread.
    std::atomic<bool> req_collect_mana{false};
    std::atomic<bool> req_kill_all{false};
    std::atomic<bool> req_clear_stage{false};
};

enum class ActionResult : int { None = 0, Done, NotInBattle, Failed };

struct Status {
    std::atomic<bool> hooks_ready{false};
    std::atomic<bool> in_battle{false};
    std::atomic<int> last_action{static_cast<int>(ActionResult::None)};
    std::atomic<int> last_kill_count{0};
};

extern Settings g_settings;
extern Status g_status;

}  // namespace ms
