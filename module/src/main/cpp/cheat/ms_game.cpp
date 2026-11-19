#include "ms_game.h"

#include "ms_log.h"

namespace ms::game {

Refs refs;

namespace {

constexpr const char *kGameImage = "Assembly-CSharp.dll";

struct Checker {
    bool ok = true;
    void need(const void *p, const char *what) {
        if (!p) {
            MS_LOGE("missing: %s", what);
            ok = false;
        }
    }
    void need(bool b, const char *what) {
        if (!b) {
            MS_LOGE("missing: %s", what);
            ok = false;
        }
    }
};

}  // namespace

bool resolve() {
    using namespace il2cpp;
    Refs r;
    Checker c;

    r.ally_class = find_class(kGameImage, "", "C_Battle_AllyUnit");
    r.enemy_class = find_class(kGameImage, "", "C_Battle_EnemyUnit");
    r.manager_class = find_class(kGameImage, "", "C_Battle_Manager");
    r.ability_class = find_class(kGameImage, "", "V_Ability_Manager");
    r.object_class = find_class(nullptr, "UnityEngine", "Object");
    void *mono_behaviour = find_class(nullptr, "UnityEngine", "MonoBehaviour");
    void *transform = find_class(nullptr, "UnityEngine", "Transform");
    void *time = find_class(nullptr, "UnityEngine", "Time");
    void *screen = find_class(nullptr, "UnityEngine", "Screen");
    void *input = find_class(nullptr, "UnityEngine", "Input");
    r.event_system_class = find_class(nullptr, "UnityEngine.EventSystems", "EventSystem");

    c.need(r.ally_class, "C_Battle_AllyUnit");
    c.need(r.enemy_class, "C_Battle_EnemyUnit");
    c.need(r.manager_class, "C_Battle_Manager");
    c.need(r.ability_class, "V_Ability_Manager");
    c.need(r.object_class, "UnityEngine.Object");
    c.need(mono_behaviour, "UnityEngine.MonoBehaviour");
    c.need(transform, "UnityEngine.Transform");
    c.need(time, "UnityEngine.Time");
    c.need(screen, "UnityEngine.Screen");
    c.need(input, "UnityEngine.Input");
    if (!c.ok) return false;

    static const char *const kAllyDamage[] = {"System.Single", "System.Single", "System.Int32"};
    static const char *const kOneType[] = {"System.Type"};
    static const char *const kOneString[] = {"System.String"};
    static const char *const kOneVector3[] = {"UnityEngine.Vector3"};
    static const char *const kOneInt[] = {"System.Int32"};
    static const char *const kOneFloat[] = {"System.Single"};

    r.ally_unit_damage = find_method(r.ally_class, "Unit_Damage", 3, kAllyDamage);
    r.enemy_unit_damage = find_method(r.enemy_class, "Unit_Damage", 10);
    r.mana_gain = find_method(r.ability_class, "ManaGain", 1, kOneFloat);
    r.manager_update = find_method(r.manager_class, "Update", 0);
    r.time_get_scale = find_method(time, "get_timeScale", 0);
    r.time_set_scale = find_method(time, "set_timeScale", 1, kOneFloat);
    r.enemy_unit_death = find_method(r.enemy_class, "Unit_Death", 0);
    r.ally_game_clear = find_method(r.ally_class, "Game_ClearON", 0);
    r.find_objects_of_type = find_method(r.object_class, "FindObjectsOfType", 1, kOneType);
    r.start_coroutine_str = find_method(mono_behaviour, "StartCoroutine", 1, kOneString);
    r.transform_get_scale = find_method(transform, "get_localScale", 0);
    r.transform_set_scale = find_method(transform, "set_localScale", 1, kOneVector3);
    r.input_touch_count = find_method(input, "get_touchCount", 0);
    r.input_get_touch = find_method(input, "GetTouch", 1, kOneInt);
    r.screen_width = find_method(screen, "get_width", 0);
    r.screen_height = find_method(screen, "get_height", 0);

    c.need(r.ally_unit_damage, "C_Battle_AllyUnit.Unit_Damage");
    c.need(r.enemy_unit_damage, "C_Battle_EnemyUnit.Unit_Damage");
    c.need(r.mana_gain, "V_Ability_Manager.ManaGain");
    c.need(r.manager_update, "C_Battle_Manager.Update");
    c.need(r.time_get_scale, "Time.get_timeScale");
    c.need(r.time_set_scale, "Time.set_timeScale");
    c.need(r.enemy_unit_death, "C_Battle_EnemyUnit.Unit_Death");
    c.need(r.ally_game_clear, "C_Battle_AllyUnit.Game_ClearON");
    c.need(r.find_objects_of_type, "Object.FindObjectsOfType(Type)");
    c.need(r.start_coroutine_str, "MonoBehaviour.StartCoroutine(string)");
    c.need(r.transform_get_scale, "Transform.get_localScale");
    c.need(r.transform_set_scale, "Transform.set_localScale");
    c.need(r.input_touch_count, "Input.get_touchCount");
    c.need(r.input_get_touch, "Input.GetTouch");
    c.need(r.screen_width, "Screen.get_width");
    c.need(r.screen_height, "Screen.get_height");

    c.need(find_field(r.object_class, "m_CachedPtr", kIntPtr, false, r.object_cached_ptr), "Object.m_CachedPtr");
    c.need(find_field(r.ally_class, "Unit_Hp", kR4, true, r.ally_hp), "Ally.Unit_Hp");
    c.need(find_field(r.ally_class, "UnitApply_HpMax", kR4, true, r.ally_hp_max), "Ally.UnitApply_HpMax");
    c.need(find_field(r.ally_class, "Unit_IsLive", kBoolean, true, r.ally_is_live), "Ally.Unit_IsLive");
    c.need(find_field(r.ally_class, "Transform_ObjItemObtainArea", kClass, false, r.ally_pickup_area),
           "Ally.Transform_ObjItemObtainArea");
    c.need(find_field(r.enemy_class, "Unit_Hp", kR4, false, r.enemy_hp), "Enemy.Unit_Hp");
    c.need(find_field(r.enemy_class, "Unit_IsLive", kBoolean, false, r.enemy_is_live), "Enemy.Unit_IsLive");
    c.need(find_field(r.manager_class, "Battle_IsPlay", kBoolean, true, r.battle_is_play), "Manager.Battle_IsPlay");
    c.need(find_field(r.manager_class, "Battle_ClearON", kI4, true, r.battle_clear_on), "Manager.Battle_ClearON");

    // Optional: universal per-frame tick for menu input outside of battle.
    if (r.event_system_class) {
        r.event_system_update = find_method(r.event_system_class, "Update", 0);
    }
    r.event_system_ok = r.event_system_update != nullptr;
    if (!r.event_system_ok) {
        MS_LOGW("EventSystem.Update unavailable: menu input only works in battle");
    }

    if (!c.ok) return false;
    refs = r;
    return true;
}

}  // namespace ms::game
