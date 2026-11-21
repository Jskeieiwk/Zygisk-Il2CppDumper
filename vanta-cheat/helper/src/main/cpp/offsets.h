// offsets.h — офсеты из dump.cs Oxide Survival Island
// пакет: com.catsbit.oxidesurvivalisland, версия 1.20.12034
// источник: dump3 release 2026-11-21, dump.cs @ TypeDefIndex комментарии приведены ниже
#pragma once

#include <stdint.h>

namespace OxideOffsets {

// === PlayerManager : NetworkBehaviour (Namespace: Oxide, TypeDefIndex 11031) ===
// основной класс управляемого игрока. все офсеты от начала managed object.
namespace PlayerManager {
    constexpr uintptr_t worldCameraRoot      = 0xA8;  // Transform
    constexpr uintptr_t mouseLook            = 0xB0;  // MouseLook
    constexpr uintptr_t playerEventHandler   = 0xB8;
    constexpr uintptr_t raycastManager       = 0xC8;  // RaycastManager
    constexpr uintptr_t fpManager            = 0xD0;  // FPManager
    constexpr uintptr_t inventory            = 0xD8;  // PlayerInventory
    constexpr uintptr_t playerMap            = 0xE0;
    constexpr uintptr_t vitals               = 0x108; // PlayerVitals
    constexpr uintptr_t stats                = 0x110;
    constexpr uintptr_t team                 = 0x160;
    constexpr uintptr_t nicklabel            = 0x170;
    constexpr uintptr_t characterModel       = 0x190; // GameObject
    constexpr uintptr_t animator             = 0x1F0; // Animator
    constexpr uintptr_t weapons              = 0x1F8; // FPWeaponBase[]
    constexpr uintptr_t lookAngle            = 0x208; // float
    constexpr uintptr_t isInAir              = 0x218; // bool
    constexpr uintptr_t isOnPlayer           = 0x219;
    constexpr uintptr_t violationLevel       = 0x21C;
    constexpr uintptr_t lastTickPosition     = 0x228; // Vector3 — последняя синхронизированная позиция
    constexpr uintptr_t lastSavedPosition    = 0x234; // Vector3
    constexpr uintptr_t playerFlags          = 0x2C0;
}

// === PlayerVitals : EntityVitals : GenericVitals : atj : NetworkBehaviour ===
namespace Vitals {
    // из GenericVitals (10744) — унаследовано
    constexpr uintptr_t maxHealth            = 0x88;  // float
    constexpr uintptr_t hitboxes             = 0xA8;  // HitBox[]
    constexpr uintptr_t damageMultipliers    = 0xB0;  // float[]
    // из atj (10762)
    constexpr uintptr_t entity               = 0x68;  // aoN — внутри неё Health
    // PlayerVitals (10755): Player на 0x100
    constexpr uintptr_t playerBack           = 0x100; // PlayerManager
}

// === aoN (EntityBase) : atj — через PlayerVitals.entity ===
namespace Entity {
    constexpr uintptr_t displayName          = 0x88;  // string
    constexpr uintptr_t killExp              = 0x90;  // int
    constexpr uintptr_t health               = 0x98;  // aog<float,...> — ObservableValue, см. ниже
    constexpr uintptr_t changeHealth         = 0xA0;
    constexpr uintptr_t isGrounded           = 0xA8;  // aov<bool>
    constexpr uintptr_t velocity             = 0xB0;  // aov<Vector3>
    constexpr uintptr_t land                 = 0xB8;
    constexpr uintptr_t death                = 0xC0;
    constexpr uintptr_t respawn              = 0xC8;
}

// === aog<float, T> ObservableValue — float value хранится в dvR (первое generic-поле) ===
// в dump обозначено как 0x0 (generic). для аллокации managed-объекта layout:
// [0..0x18] = managed header + action/filter поля, generic value после них.
// практический офсет для aog<float, T>: 0x18 (после Action<T> и Filter)
// дальше — через il2cpp_class_value_size instance class.
namespace ObservableFloat {
    constexpr uintptr_t value                = 0x18;  // эмпирический — уточнить в рантайме
}

// === aov<N> ObservableValue — для Vector3 velocity ===
namespace ObservableVec3 {
    constexpr uintptr_t value                = 0x18;  // три float по этому адресу
}

// === MouseLook (TypeDefIndex 10733) — через PlayerManager.mouseLook ===
namespace MouseLook {
    constexpr uintptr_t eventHandler         = 0x20;
    constexpr uintptr_t lookRoot             = 0x28;  // Transform — реальная камера первого лица
    constexpr uintptr_t invert               = 0x30;
    constexpr uintptr_t sensitivity          = 0x34;  // float
    constexpr uintptr_t defaultLookLimits    = 0x38;
    constexpr uintptr_t currentLook          = 0x98;  // Vector2 <dKB>k__BackingField — yaw/pitch
}

// === static поля PlayerManager (резолвим через il2cpp_class_get_field_from_name) ===
// имена полей как в dump:
//   static JO<PlayerManager>        sleepingPlayerList    (offset 0x0)
//   static JO<PlayerManager>        activePlayerList      (offset 0x8)
//   static readonly List<PlayerManager> clientPlayerList  (offset 0x10)  ← самое ценное для нас
//   static string                   serverName            (offset 0x18)
//   static string                   serverBuildNumber     (offset 0x20)

// === UnityEngine.Component / Behaviour / Transform ===
// managed Transform наследует Component. cached_ptr Unity нативной Transform лежит в
// managed-объекте UnityEngine.Object на офсете 0x10.
namespace UnityObject {
    constexpr uintptr_t cachedPtr            = 0x10;  // void* нативного Unity-объекта
}

// === для Unity Transform мы НЕ парсим native layout — используем il2cpp_runtime_invoke
// на get_position / get_rotation / get_forward (icall). см. helper.cpp ===

// === имена классов для il2cpp_class_from_name ===
namespace Names {
    constexpr const char* NS_OXIDE          = "Oxide";
    constexpr const char* CLS_PLAYER_MGR    = "PlayerManager";
    constexpr const char* CLS_PLAYER_VITALS = "PlayerVitals";
    constexpr const char* CLS_MOUSELOOK     = "MouseLook";

    constexpr const char* NS_UNITY          = "UnityEngine";
    constexpr const char* CLS_COMPONENT     = "Component";
    constexpr const char* CLS_TRANSFORM     = "Transform";
    constexpr const char* CLS_CAMERA        = "Camera";
    constexpr const char* CLS_GAMEOBJECT    = "GameObject";
    constexpr const char* CLS_SCREEN        = "Screen";
}

} // namespace OxideOffsets
