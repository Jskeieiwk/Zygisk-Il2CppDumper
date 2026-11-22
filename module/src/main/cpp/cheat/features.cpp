#include "features.h"
#include "cheat.h"
#include "il2cpp_api.h"
#include "hook.h"
#include "../log.h"
#include "../game.h"

#include <chrono>
#include <thread>
#include <cstring>
#include <vector>

// =========================================================================
//   Game type cache — resolved once, read every tick.
// =========================================================================
struct GameTypes {
    Il2CppClass *Camera           = nullptr;
    Il2CppClass *Transform        = nullptr;
    Il2CppClass *Object           = nullptr;      // UnityEngine.Object
    Il2CppClass *PlayerController = nullptr;
    Il2CppClass *SurvivalStats    = nullptr;
    Il2CppClass *WeaponController = nullptr;

    const MethodInfo *Camera_get_main       = nullptr;
    const MethodInfo *Camera_set_fov        = nullptr;
    const MethodInfo *Object_FindObjectsOfType = nullptr;

    // PlayerController SyncVar offsets — from playercontroller_fields.txt.
    int off_PC_flightGrantSync = -1;   // 0xF8
    int off_PC_laserGrantSync  = -1;   // 0x100
    int off_PC_flyingSync      = -1;   // 0x108
    int off_PC_laserBeamSync   = -1;   // 0x118
    int off_PC_laserDpsSync    = -1;   // 0x120
    int off_PC_laserRangeSync  = -1;   // 0x128
    int off_PC_flightSpeedSync = -1;   // 0x130
    int off_PC_adminGhostSync  = -1;   // 0x168
    int off_PC_adminGodSync    = -1;   // 0x170

    // WeaponController fields of interest for no-recoil / no-spread.
    int off_WC_recoilMul       = -1;
    int off_WC_recoilRandomMul = -1;
    int off_WC_spreadMul       = -1;
    int off_WC_spreadFloor     = -1;
};
static GameTypes T;

// A FishNet SyncVar<T> value field sits inside the struct at a known inner
// offset.  On the builds we've seen, the backing `Value` is the first word
// after the SyncVar header: +0x8 for bool, which matches read patterns in
// dump.cs.  For simplicity we write at that inner offset directly.
static constexpr int kSyncVarValueInnerOffset = 0x18;

template <typename T>
static void write_syncvar(void *instance, int outer_offset, T value) {
    if (!instance || outer_offset < 0) return;
    auto base = (uint8_t*)instance + outer_offset + kSyncVarValueInnerOffset;
    *(T*)base = value;
}

// =========================================================================
//   Resolve
// =========================================================================
static void try_resolve_pc_offsets() {
    if (!T.PlayerController) return;
#define OFF(var, name) do {                                                  \
        auto f = find_field(T.PlayerController, name);                       \
        T.var = get_field_offset(f);                                         \
        LOGI("[Cloud] PC.%s offset = 0x%x", name, T.var);                    \
    } while(0)
    OFF(off_PC_flightGrantSync, "_flightGrantSync");
    OFF(off_PC_laserGrantSync,  "_laserGrantSync");
    OFF(off_PC_flyingSync,      "_flyingSync");
    OFF(off_PC_laserBeamSync,   "_laserBeamSync");
    OFF(off_PC_laserDpsSync,    "_laserDpsSync");
    OFF(off_PC_laserRangeSync,  "_laserRangeSync");
    OFF(off_PC_flightSpeedSync, "_flightSpeedSync");
    OFF(off_PC_adminGhostSync,  "_adminGhostSync");
    OFF(off_PC_adminGodSync,    "_adminGodSync");
#undef OFF
}

static void try_resolve_wc_offsets() {
    if (!T.WeaponController) return;
#define OFF(var, name) do {                                                  \
        auto f = find_field(T.WeaponController, name);                       \
        T.var = get_field_offset(f);                                         \
        if (T.var > 0) LOGI("[Cloud] WC.%s offset = 0x%x", name, T.var);     \
    } while(0)
    OFF(off_WC_recoilMul,       "_RecoilMul");
    OFF(off_WC_recoilRandomMul, "_RecoilRandomMul");
    OFF(off_WC_spreadMul,       "_SpreadMul");
    OFF(off_WC_spreadFloor,     "_SpreadFloorDeg");
#undef OFF
}

void features_resolve_types() {
    LOGI("[Cloud] resolving game types ...");

    T.Camera    = find_class("UnityEngine.CoreModule.dll", "UnityEngine", "Camera");
    T.Transform = find_class("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
    T.Object    = find_class("UnityEngine.CoreModule.dll", "UnityEngine", "Object");

    T.PlayerController = find_class("Assembly-CSharp.dll", "", "PlayerController");
    T.SurvivalStats    = find_class("Assembly-CSharp.dll", "", "SurvivalStats");
    T.WeaponController = find_class("Assembly-CSharp.dll", "", "WeaponController");

    LOGI("[Cloud] Camera=%p PC=%p SS=%p WC=%p",
         T.Camera, T.PlayerController, T.SurvivalStats, T.WeaponController);

    if (T.Camera) {
        T.Camera_get_main = find_method(T.Camera, "get_main",        0);
        T.Camera_set_fov  = find_method(T.Camera, "set_fieldOfView", 1);
    }
    if (T.Object) {
        T.Object_FindObjectsOfType = find_method(T.Object, "FindObjectsOfType", 1);
    }

    try_resolve_pc_offsets();
    try_resolve_wc_offsets();
}

void features_install_hooks() {
    LOGI("[Cloud] no inline code hooks installed — pure data-plane tick");
}

// =========================================================================
//   Helpers for il2cpp invokes
// =========================================================================
static void *invoke0(const MethodInfo *m) {
    if (!m || !il2cpp_runtime_invoke) return nullptr;
    return il2cpp_runtime_invoke(m, nullptr, nullptr, nullptr);
}
static void invoke1f(const MethodInfo *m, void *inst, float v) {
    if (!m || !il2cpp_runtime_invoke) return;
    void *args[1] = { &v };
    il2cpp_runtime_invoke(m, inst, args, nullptr);
}
static void *invoke_static1ptr(const MethodInfo *m, void *arg) {
    if (!m || !il2cpp_runtime_invoke) return nullptr;
    void *args[1] = { &arg };
    return il2cpp_runtime_invoke(m, nullptr, args, nullptr);
}

// Call UnityEngine.Object.FindObjectsOfType(typeof(T)) for a resolved class.
struct Il2CppArray {
    void   *klass;
    void   *monitor;
    void   *bounds;
    size_t  max_length;
    void   *vector[1];
};

static Il2CppArray *find_instances(Il2CppClass *klass) {
    if (!klass || !T.Object_FindObjectsOfType || !il2cpp_type_get_object || !il2cpp_class_get_type)
        return nullptr;
    auto type_obj = il2cpp_type_get_object(il2cpp_class_get_type(klass));
    if (!type_obj) return nullptr;
    auto result = invoke_static1ptr(T.Object_FindObjectsOfType, type_obj);
    return (Il2CppArray*)result;
}

template <typename Fn>
static void for_each_instance(Il2CppClass *klass, Fn fn) {
    auto arr = find_instances(klass);
    if (!arr) return;
    auto base = (void**)arr->vector;
    for (size_t i = 0; i < arr->max_length; ++i) {
        void *inst = base[i];
        if (inst) fn(inst);
    }
}

// =========================================================================
//   Features
// =========================================================================
static void apply_fov_lock() {
    if (!g_cfg.enabled_fov_lock) return;
    auto cam = invoke0(T.Camera_get_main);
    if (!cam) return;
    invoke1f(T.Camera_set_fov, cam, g_cfg.fov_value);
}

static void apply_player_toggles() {
    if (!T.PlayerController) return;

    for_each_instance(T.PlayerController, [&](void *pc) {
        // Flight grant + flying state.
        write_syncvar<bool>(pc, T.off_PC_flightGrantSync, g_cfg.enabled_fly);
        write_syncvar<bool>(pc, T.off_PC_flyingSync,      g_cfg.enabled_fly);
        if (g_cfg.enabled_fly && T.off_PC_flightSpeedSync > 0) {
            float base = 8.0f;
            write_syncvar<float>(pc, T.off_PC_flightSpeedSync,
                                 g_cfg.enabled_speed ? base * g_cfg.speed_multiplier : base);
        }

        // Admin tier bits.
        write_syncvar<bool>(pc, T.off_PC_adminGodSync,   g_cfg.enabled_god);
        write_syncvar<bool>(pc, T.off_PC_adminGhostSync, g_cfg.enabled_ghost);

        // Laser beam of doom.
        write_syncvar<bool>(pc, T.off_PC_laserGrantSync, g_cfg.enabled_laser);
        write_syncvar<bool>(pc, T.off_PC_laserBeamSync,  g_cfg.enabled_laser);
        if (g_cfg.enabled_laser) {
            write_syncvar<float>(pc, T.off_PC_laserDpsSync,   g_cfg.laser_dps);
            write_syncvar<float>(pc, T.off_PC_laserRangeSync, g_cfg.laser_range);
        }
    });
}

static void apply_no_recoil() {
    if (!T.WeaponController) return;
    if (!g_cfg.enabled_no_recoil && !g_cfg.enabled_no_spread) return;

    for_each_instance(T.WeaponController, [](void *wc) {
        if (g_cfg.enabled_no_recoil) {
            if (T.off_WC_recoilMul       > 0) *(float*)((uint8_t*)wc + T.off_WC_recoilMul)       = 0.0f;
            if (T.off_WC_recoilRandomMul > 0) *(float*)((uint8_t*)wc + T.off_WC_recoilRandomMul) = 0.0f;
        }
        if (g_cfg.enabled_no_spread) {
            if (T.off_WC_spreadMul   > 0) *(float*)((uint8_t*)wc + T.off_WC_spreadMul)   = 0.0f;
            if (T.off_WC_spreadFloor > 0) *(float*)((uint8_t*)wc + T.off_WC_spreadFloor) = 0.0f;
        }
    });
}

void features_tick_loop() {
    LOGI("[Cloud] feature tick loop running");
    using namespace std::chrono_literals;
    int since_warmup = 0;
    while (true) {
        apply_fov_lock();
        apply_player_toggles();
        apply_no_recoil();

        // Re-resolve offsets periodically for the first minute in case some
        // types weren't registered yet during the first pass.
        if (++since_warmup < 60 && (T.off_PC_flyingSync < 0 || T.off_WC_recoilMul < 0)) {
            try_resolve_pc_offsets();
            try_resolve_wc_offsets();
        }

        std::this_thread::sleep_for(100ms);
    }
}
