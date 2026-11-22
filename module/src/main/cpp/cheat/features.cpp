#include "features.h"
#include "cheat.h"
#include "il2cpp_api.h"
#include "hook.h"
#include "../log.h"
#include "../game.h"

#include <chrono>
#include <thread>
#include <cstring>

struct GameTypes {
    Il2CppClass *Camera = nullptr;
    Il2CppClass *Transform = nullptr;
    Il2CppClass *Vector3 = nullptr;
    Il2CppClass *PlayerController = nullptr;
    Il2CppClass *SurvivalStats = nullptr;
    Il2CppClass *WeaponController = nullptr;
    Il2CppClass *NameplateOverlay = nullptr;

    const MethodInfo *Camera_get_main = nullptr;
    const MethodInfo *Camera_set_fov  = nullptr;
    const MethodInfo *Camera_get_fov  = nullptr;

    int off_PC_flyingSync       = -1;   // _flyingSync      0x108
    int off_PC_flightGrantSync  = -1;   // _flightGrantSync 0xF8
    int off_PC_adminGhostSync   = -1;   // 0x168
    int off_PC_adminGodSync     = -1;   // 0x170
    int off_PC_flightSpeedSync  = -1;   // 0x130
    int off_PC_laserGrantSync   = -1;   // 0x100
    int off_PC_laserBeamSync    = -1;   // 0x118
    int off_PC_laserDpsSync     = -1;   // 0x120
    int off_PC_laserRangeSync   = -1;   // 0x128
};

static GameTypes T;

static void try_resolve_pc_offsets() {
    if (!T.PlayerController) return;
#define OFF(var, name) do {                                                    \
        auto f = find_field(T.PlayerController, name);                         \
        T.var = get_field_offset(f);                                           \
        LOGI("[Cloud] PC.%s offset = 0x%x", name, T.var);                      \
    } while(0)
    OFF(off_PC_flyingSync,       "_flyingSync");
    OFF(off_PC_flightGrantSync,  "_flightGrantSync");
    OFF(off_PC_adminGhostSync,   "_adminGhostSync");
    OFF(off_PC_adminGodSync,     "_adminGodSync");
    OFF(off_PC_flightSpeedSync,  "_flightSpeedSync");
    OFF(off_PC_laserGrantSync,   "_laserGrantSync");
    OFF(off_PC_laserBeamSync,    "_laserBeamSync");
    OFF(off_PC_laserDpsSync,     "_laserDpsSync");
    OFF(off_PC_laserRangeSync,   "_laserRangeSync");
#undef OFF
}

void features_resolve_types() {
    LOGI("[Cloud] resolving game types ...");

    T.Camera   = find_class("UnityEngine.CoreModule.dll", "UnityEngine", "Camera");
    T.Transform= find_class("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
    T.Vector3  = find_class("UnityEngine.CoreModule.dll", "UnityEngine", "Vector3");

    T.PlayerController = find_class("Assembly-CSharp.dll", "", "PlayerController");
    T.SurvivalStats    = find_class("Assembly-CSharp.dll", "", "SurvivalStats");
    T.WeaponController = find_class("Assembly-CSharp.dll", "", "WeaponController");
    T.NameplateOverlay = find_class("Assembly-CSharp.dll", "", "NameplateOverlay");

    LOGI("[Cloud] Camera=%p Transform=%p PlayerController=%p SurvivalStats=%p WeaponController=%p",
         T.Camera, T.Transform, T.PlayerController, T.SurvivalStats, T.WeaponController);

    if (T.Camera) {
        T.Camera_get_main = find_method(T.Camera, "get_main",       0);
        T.Camera_set_fov  = find_method(T.Camera, "set_fieldOfView",1);
        T.Camera_get_fov  = find_method(T.Camera, "get_fieldOfView",0);
        LOGI("[Cloud] Camera.get_main=%p set_fov=%p get_fov=%p",
             T.Camera_get_main, T.Camera_set_fov, T.Camera_get_fov);
    }

    try_resolve_pc_offsets();
}

// -------------------------------------------------------------------------
//   Hooks: for stage 1 we keep hooks minimal and all-field based.
//   FOV lock is applied by *calling* the setter each tick, not hooking.
//   This avoids patching libil2cpp code pages that trip integrity scans.
// -------------------------------------------------------------------------
void features_install_hooks() {
    LOGI("[Cloud] stage 1 build — field-based features only, no code patches");
}

// -------------------------------------------------------------------------

static void *invoke0(const MethodInfo *m) {
    if (!m || !il2cpp_runtime_invoke) return nullptr;
    return il2cpp_runtime_invoke(m, nullptr, nullptr, nullptr);
}

static void invoke1f(const MethodInfo *m, void *inst, float v) {
    if (!m || !il2cpp_runtime_invoke) return;
    void *args[1] = { &v };
    il2cpp_runtime_invoke(m, inst, args, nullptr);
}

static float invoke_get_f(const MethodInfo *m, void *inst) {
    if (!m || !il2cpp_runtime_invoke) return 0.0f;
    void *boxed = il2cpp_runtime_invoke(m, inst, nullptr, nullptr);
    if (!boxed) return 0.0f;
    // unbox: value sits right after the Il2CppObject header (16 bytes on arm64)
    return *(float*)((uint8_t*)boxed + 0x10);
}

static void apply_fov_lock() {
    if (!g_cfg.enabled_fov_lock) return;
    if (!T.Camera_get_main || !T.Camera_set_fov) return;
    auto cam = invoke0(T.Camera_get_main);
    if (!cam) return;
    invoke1f(T.Camera_set_fov, cam, g_cfg.fov_value);
}

void features_tick_loop() {
    LOGI("[Cloud] feature tick loop running");
    using namespace std::chrono_literals;
    while (true) {
        apply_fov_lock();
        std::this_thread::sleep_for(100ms);
    }
}
