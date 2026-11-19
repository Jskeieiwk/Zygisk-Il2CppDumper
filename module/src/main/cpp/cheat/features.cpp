#include "features.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>

#include "ms_game.h"
#include "ms_log.h"
#include "ms_state.h"
#include "overlay.h"

namespace ms {
Settings g_settings;
Status g_status;
}  // namespace ms

namespace ms::features {

namespace {

using il2cpp::api;
using game::refs;

std::atomic<bool> g_ready{false};

// ---- typed calls into il2cpp-compiled code: (this?, args..., const MethodInfo*) ----

template<class R, class... A>
R invoke(const void *method, A... args) {
    using Fn = R (*)(A..., const void *);
    return reinterpret_cast<Fn>(il2cpp::method_pointer(method))(args..., method);
}

template<class T>
T &field(void *obj, const il2cpp::Field &f) {
    return *reinterpret_cast<T *>(static_cast<uint8_t *>(obj) + f.offset);
}

template<class T>
T static_get(const il2cpp::Field &f) {
    T v{};
    api.field_static_get_value(f.info, &v);
    return v;
}

template<class T>
void static_set(const il2cpp::Field &f, T v) {
    api.field_static_set_value(f.info, &v);
}

int64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// Unity object that has not been destroyed on the native side.
bool alive(void *obj) {
    if (!obj || (reinterpret_cast<uintptr_t>(obj) & 7u) != 0) return false;
    return field<void *>(obj, refs.object_cached_ptr) != nullptr;
}

bool finite_in(float v, float lo, float hi) { return std::isfinite(v) && v >= lo && v <= hi; }

int clamp_mul(int v, int hi) { return std::clamp(v, kMulMin, hi); }

// Returns the managed Object[] for a class, or nullptr. Main thread only.
void *find_objects(void *klass) {
    void *type_obj = api.type_get_object(api.class_get_type(klass));
    if (!type_obj) return nullptr;
    return invoke<void *>(refs.find_objects_of_type, type_obj);
}

template<class Fn>
int for_each_object(void *array, int limit, Fn &&fn) {
    if (!array) return 0;
    const uint32_t len = api.array_length(array);
    const int n = static_cast<int>(std::min<uint32_t>(len, static_cast<uint32_t>(limit)));
    auto **items = reinterpret_cast<void **>(static_cast<uint8_t *>(array) + il2cpp::kArrayDataOffset);
    int visited = 0;
    for (int i = 0; i < n; ++i) {
        if (alive(items[i])) {
            fn(items[i]);
            ++visited;
        }
    }
    return visited;
}

// ---- main-thread state ----

int64_t s_manager_seen_ms = 0;
bool s_ally_class_inited = false;
void *s_ally = nullptr;
int s_ally_search_cooldown = 0;

float s_time_applied = 1.0f;     // multiplier currently baked into Time.timeScale

void *s_pickup_transform = nullptr;
float s_pickup_applied = 1.0f;
game::Vector3 s_pickup_written{};

int64_t s_last_input_poll_ms = 0;

bool battle_active() {
    if (s_manager_seen_ms == 0 || now_ms() - s_manager_seen_ms > 500) return false;
    return static_get<bool>(refs.battle_is_play);
}

void *current_ally() {
    if (s_ally && alive(s_ally)) return s_ally;
    s_ally = nullptr;
    if (s_ally_search_cooldown > 0) {
        --s_ally_search_cooldown;
        return nullptr;
    }
    s_ally_search_cooldown = 30;
    for_each_object(find_objects(refs.ally_class), 8, [](void *o) {
        if (!s_ally) s_ally = o;
    });
    if (s_ally && !s_ally_class_inited) {
        api.runtime_class_init(refs.ally_class);
        s_ally_class_inited = true;
    }
    return s_ally;
}

// ---- hooks ----

using AllyDamageFn = void (*)(void *, float, float, int, const void *);
using EnemyDamageFn = void (*)(void *, int, float, int, float, float, float, float, float, float, float,
                               const void *);
using ManaGainFn = void (*)(void *, float, const void *);
using UpdateFn = void (*)(void *, const void *);
using GetScaleFn = float (*)(const void *);
using SetScaleFn = void (*)(float, const void *);

AllyDamageFn o_ally_damage = nullptr;
EnemyDamageFn o_enemy_damage = nullptr;
ManaGainFn o_mana_gain = nullptr;
UpdateFn o_manager_update = nullptr;
UpdateFn o_event_system_update = nullptr;
GetScaleFn o_get_time_scale = nullptr;
SetScaleFn o_set_time_scale = nullptr;

void hk_ally_damage(void *self, float damage, float special, int damage_type, const void *mi) {
    if (g_ready.load(std::memory_order_acquire) && g_settings.god_mode.load()) return;
    if (auto o = o_ally_damage) o(self, damage, special, damage_type, mi);
}

void hk_enemy_damage(void *self, int magic_id, float damage, int cri_ran, float cri_mul, float s1, float s2,
                     float s3, float s4, float stun, float freeze, const void *mi) {
    if (g_ready.load(std::memory_order_acquire)) {
        const int mul = clamp_mul(g_settings.attack_mul.load(), kMulMax);
        if (mul > 1 && finite_in(damage, 0.0f, 1e30f)) {
            damage = std::min(damage * static_cast<float>(mul), 1e30f);
        }
    }
    if (auto o = o_enemy_damage) o(self, magic_id, damage, cri_ran, cri_mul, s1, s2, s3, s4, stun, freeze, mi);
}

void hk_mana_gain(void *self, float mana, const void *mi) {
    if (g_ready.load(std::memory_order_acquire)) {
        const int mul = clamp_mul(g_settings.mana_gain_mul.load(), kMulMax);
        if (mul > 1 && finite_in(mana, 0.0f, 1e9f)) mana *= static_cast<float>(mul);
    }
    if (auto o = o_mana_gain) o(self, mana, mi);
}

// The game sees an unmultiplied time scale, so its own save/restore of timeScale never compounds.
float hk_get_time_scale(const void *mi) {
    auto o = o_get_time_scale;
    if (!o) return 1.0f;
    const float v = o(mi);
    if (g_ready.load(std::memory_order_acquire) && s_time_applied > 1.0f && std::isfinite(v)) {
        return v / s_time_applied;
    }
    return v;
}

void hk_set_time_scale(float v, const void *mi) {
    auto o = o_set_time_scale;
    if (!o) return;
    if (g_ready.load(std::memory_order_acquire) && s_time_applied > 1.0f && finite_in(v, 0.0f, 25.0f)) {
        v *= s_time_applied;
    }
    o(v, mi);
}

void time_tick(bool in_battle) {
    const float desired = in_battle ? static_cast<float>(clamp_mul(g_settings.time_mul.load(), kTimeMulMax)) : 1.0f;
    if (desired == s_time_applied) return;
    const float real = o_get_time_scale(refs.time_get_scale);
    if (!std::isfinite(real) || real < 0.0f) return;
    const float base = real / s_time_applied;
    s_time_applied = desired;
    if (real > 0.0f) o_set_time_scale(base * desired, refs.time_set_scale);
    // real == 0: game is paused; its next set_timeScale goes through the hook with the new multiplier.
}

void poll_input() {
    const int64_t t = now_ms();
    if (t - s_last_input_poll_ms < 3) return;  // several EventSystems may tick in one frame
    s_last_input_poll_ms = t;

    int count = invoke<int>(refs.input_touch_count);
    if (count <= 0) return;
    count = std::min(count, 10);
    const float sw = static_cast<float>(invoke<int>(refs.screen_width));
    const float sh = static_cast<float>(invoke<int>(refs.screen_height));
    if (!(sw > 0 && sh > 0)) return;

    overlay::TouchEvent events[10];
    int n = 0;
    for (int i = 0; i < count; ++i) {
        const game::Touch touch = invoke<game::Touch>(refs.input_get_touch, i);
        overlay::TouchKind kind;
        switch (touch.phase) {
            case 0: kind = overlay::TouchKind::Down; break;
            case 1: kind = overlay::TouchKind::Move; break;
            case 3:
            case 4: kind = overlay::TouchKind::Up; break;
            default: continue;  // Stationary
        }
        if (!finite_in(touch.pos_x, -sw, 2 * sw) || !finite_in(touch.pos_y, -sh, 2 * sh)) continue;
        events[n++] = {kind, touch.finger_id, touch.pos_x, sh - touch.pos_y, sw, sh, t};
    }
    if (n > 0) overlay::push_touches(events, n);
}

void pickup_radius_tick(void *ally) {
    void *tr = field<void *>(ally, refs.ally_pickup_area);
    if (!alive(tr)) return;
    if (tr != s_pickup_transform) {
        s_pickup_transform = tr;
        s_pickup_applied = 1.0f;
    }
    const float desired = static_cast<float>(clamp_mul(g_settings.pickup_radius_mul.load(), kMulMax));
    game::Vector3 cur = invoke<game::Vector3>(refs.transform_get_scale, tr);
    if (!finite_in(cur.x, 1e-4f, 1e6f) || !finite_in(cur.y, 1e-4f, 1e6f)) return;

    // C_Battle_AllyUnit.Unit_StatBuff rewrites this scale (x, y = base + UnitApply_ItemObtainArea).
    // If the scale is no longer what we wrote, the game reset it to its own base value.
    const auto same = [](float a, float b) { return std::fabs(a - b) <= 1e-4f * std::max(1.0f, std::fabs(b)); };
    if (s_pickup_applied != 1.0f && !(same(cur.x, s_pickup_written.x) && same(cur.y, s_pickup_written.y))) {
        s_pickup_applied = 1.0f;
    }
    if (desired == s_pickup_applied) return;
    game::Vector3 next = cur;
    next.x = cur.x / s_pickup_applied * desired;
    next.y = cur.y / s_pickup_applied * desired;
    invoke<void>(refs.transform_set_scale, tr, next);
    s_pickup_applied = desired;
    s_pickup_written = next;
}

void set_result(ActionResult r) { g_status.last_action.store(static_cast<int>(r)); }

void battle_tick() {
    const bool in_battle = battle_active();
    g_status.in_battle.store(in_battle);

    const bool want_collect = g_settings.req_collect_mana.exchange(false);
    const bool want_kill = g_settings.req_kill_all.exchange(false);
    const bool want_clear = g_settings.req_clear_stage.exchange(false);

    if (!in_battle) {
        if (want_collect || want_kill || want_clear) set_result(ActionResult::NotInBattle);
        return;
    }
    void *ally = current_ally();
    const bool ally_live = ally && s_ally_class_inited && static_get<bool>(refs.ally_is_live);
    if (!ally_live) {
        if (want_collect || want_kill || want_clear) set_result(ActionResult::NotInBattle);
        return;
    }

    if (g_settings.infinite_hp.load()) {
        const float max_hp = static_get<float>(refs.ally_hp_max);
        const float hp = static_get<float>(refs.ally_hp);
        if (finite_in(max_hp, 1.0f, 1e9f) && (!std::isfinite(hp) || hp < max_hp)) {
            static_set<float>(refs.ally_hp, max_hp);
        }
    }

    pickup_radius_tick(ally);

    if (want_collect) {
        // Same routine as the game's own "collect all mana" rune: enables Obj_AllObtain_ManaBall for 0.05 s.
        void *name = api.string_new("Play_Rune_Obtain_AllManaBall");
        if (name) {
            invoke<void *>(refs.start_coroutine_str, ally, name);
            set_result(ActionResult::Done);
        } else {
            set_result(ActionResult::Failed);
        }
    }

    if (want_kill) {
        // Unit_Death only acts when Unit_Hp <= 0 and Unit_IsLive; this is the path Unit_Damage takes
        // on a lethal hit, so drops, kill counters and boss-clear logic run as usual.
        int killed = 0;
        for_each_object(find_objects(refs.enemy_class), 4096, [&](void *enemy) {
            if (!field<bool>(enemy, refs.enemy_is_live)) return;
            field<float>(enemy, refs.enemy_hp) = 0.0f;
            invoke<void>(refs.enemy_unit_death, enemy);
            ++killed;
        });
        g_status.last_kill_count.store(killed);
        set_result(ActionResult::Done);
    }

    if (want_clear) {
        // Game_ClearON is what the final boss's death coroutine calls to win the stage.
        if (static_get<int>(refs.battle_clear_on) == 0) {
            invoke<void>(refs.ally_game_clear, ally);
        }
        set_result(ActionResult::Done);
    }
}

void hk_manager_update(void *self, const void *mi) {
    if (g_ready.load(std::memory_order_acquire)) {
        if (s_manager_seen_ms == 0) api.runtime_class_init(refs.manager_class);
        s_manager_seen_ms = now_ms();
        if (!refs.event_system_ok) poll_input();
        battle_tick();
        time_tick(g_status.in_battle.load());
    }
    if (auto o = o_manager_update) o(self, mi);
}

void hk_event_system_update(void *self, const void *mi) {
    if (g_ready.load(std::memory_order_acquire)) {
        poll_input();
        const bool in_battle = battle_active();
        if (!in_battle) g_status.in_battle.store(false);
        time_tick(in_battle);
    }
    if (auto o = o_event_system_update) o(self, mi);
}

}  // namespace

size_t fill_hook_specs(hook::Spec *out, size_t capacity) {
    using il2cpp::method_pointer;
    const hook::Spec specs[] = {
        {"C_Battle_AllyUnit.Unit_Damage", method_pointer(refs.ally_unit_damage),
         reinterpret_cast<void *>(hk_ally_damage), reinterpret_cast<void **>(&o_ally_damage)},
        {"C_Battle_EnemyUnit.Unit_Damage", method_pointer(refs.enemy_unit_damage),
         reinterpret_cast<void *>(hk_enemy_damage), reinterpret_cast<void **>(&o_enemy_damage)},
        {"V_Ability_Manager.ManaGain", method_pointer(refs.mana_gain),
         reinterpret_cast<void *>(hk_mana_gain), reinterpret_cast<void **>(&o_mana_gain)},
        {"C_Battle_Manager.Update", method_pointer(refs.manager_update),
         reinterpret_cast<void *>(hk_manager_update), reinterpret_cast<void **>(&o_manager_update)},
        {"Time.get_timeScale", method_pointer(refs.time_get_scale),
         reinterpret_cast<void *>(hk_get_time_scale), reinterpret_cast<void **>(&o_get_time_scale)},
        {"Time.set_timeScale", method_pointer(refs.time_set_scale),
         reinterpret_cast<void *>(hk_set_time_scale), reinterpret_cast<void **>(&o_set_time_scale)},
        {"EventSystem.Update", method_pointer(refs.event_system_update),
         reinterpret_cast<void *>(hk_event_system_update), reinterpret_cast<void **>(&o_event_system_update)},
    };
    size_t n = 0;
    for (const auto &s : specs) {
        if (!s.target) continue;  // only EventSystem.Update is optional; resolve() guarantees the rest
        if (n == capacity) return 0;
        out[n++] = s;
    }
    return n;
}

void set_ready() { g_ready.store(true, std::memory_order_release); }

}  // namespace ms::features
