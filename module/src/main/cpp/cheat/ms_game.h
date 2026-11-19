#pragma once

// Every Magic Survival symbol the cheat uses, resolved by name.
// Source: dump.cs of com.vkslrzm.Zombie 0.9941 (Unity 2022.3.62f3, metadata v31).
// Semantics confirmed by disassembling that build's libil2cpp.so (size 40523040).

#include "il2cpp_rt.h"

namespace ms::game {

struct Vector3 {
    float x, y, z;
};

// UnityEngine.Touch, 0x44 bytes in this build.
struct Touch {
    int finger_id;
    float pos_x, pos_y;
    float raw_x, raw_y;
    float delta_x, delta_y;
    float time_delta;
    int tap_count;
    int phase;          // 0 Began, 1 Moved, 2 Stationary, 3 Ended, 4 Canceled
    int type;
    float pressure, max_pressure, radius, radius_variance, altitude, azimuth;
};
static_assert(sizeof(Touch) == 0x44, "UnityEngine.Touch layout");

struct Refs {
    // Classes
    void *ally_class = nullptr;       // C_Battle_AllyUnit
    void *enemy_class = nullptr;      // C_Battle_EnemyUnit
    void *manager_class = nullptr;    // C_Battle_Manager
    void *ability_class = nullptr;    // V_Ability_Manager
    void *event_system_class = nullptr;
    void *object_class = nullptr;     // UnityEngine.Object

    // Hook targets
    const void *ally_unit_damage = nullptr;     // void Unit_Damage(float, float, int)
    const void *enemy_unit_damage = nullptr;    // void Unit_Damage(int, float, int, float x7)
    const void *mana_gain = nullptr;            // void ManaGain(float)
    const void *manager_update = nullptr;       // void Update()
    const void *event_system_update = nullptr;  // void Update()
    const void *time_get_scale = nullptr;       // static float get_timeScale()
    const void *time_set_scale = nullptr;       // static void set_timeScale(float)

    // Called
    const void *enemy_unit_death = nullptr;     // void Unit_Death()
    const void *ally_game_clear = nullptr;      // void Game_ClearON()
    const void *find_objects_of_type = nullptr; // static Object[] FindObjectsOfType(Type)
    const void *start_coroutine_str = nullptr;  // Coroutine StartCoroutine(string)
    const void *transform_get_scale = nullptr;  // Vector3 get_localScale()
    const void *transform_set_scale = nullptr;  // void set_localScale(Vector3)
    const void *input_touch_count = nullptr;    // static int get_touchCount()
    const void *input_get_touch = nullptr;      // static Touch GetTouch(int)
    const void *screen_width = nullptr;         // static int get_width()
    const void *screen_height = nullptr;        // static int get_height()

    // Fields
    il2cpp::Field object_cached_ptr;      // UnityEngine.Object.m_CachedPtr (IntPtr)
    il2cpp::Field ally_hp;                // static float Unit_Hp
    il2cpp::Field ally_hp_max;            // static float UnitApply_HpMax
    il2cpp::Field ally_is_live;           // static bool Unit_IsLive
    il2cpp::Field ally_pickup_area;       // Transform Transform_ObjItemObtainArea
    il2cpp::Field enemy_hp;               // float Unit_Hp
    il2cpp::Field enemy_is_live;          // bool Unit_IsLive
    il2cpp::Field battle_is_play;         // static bool C_Battle_Manager.Battle_IsPlay
    il2cpp::Field battle_clear_on;        // static int C_Battle_Manager.Battle_ClearON

    bool event_system_ok = false;         // optional: input falls back to the battle tick
};

extern Refs refs;

// Resolves everything. Returns false (and logs each miss) if a required symbol is absent.
bool resolve();

}  // namespace ms::game
