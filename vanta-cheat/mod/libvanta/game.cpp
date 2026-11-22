// game.cpp — il2cpp reader
#include "game.h"
#include "../../helper/src/main/cpp/il2cpp_api.h"
#include "../../helper/src/main/cpp/offsets.h"

#include <dlfcn.h>
#include <string.h>
#include <math.h>
#include <android/log.h>

#define LOGG(fmt, ...) __android_log_print(ANDROID_LOG_INFO,  "vanta-game", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-game", fmt, ##__VA_ARGS__)

using namespace OxideOffsets;

namespace vanta {

namespace {
Il2CppClass* cls_pm = nullptr;
Il2CppClass* cls_mouselook = nullptr;
Il2CppClass* cls_component = nullptr;
Il2CppClass* cls_transform = nullptr;
Il2CppClass* cls_camera = nullptr;
Il2CppClass* cls_screen = nullptr;

FieldInfo* fld_client_list = nullptr;
const MethodInfo* m_list_get_count = nullptr;
const MethodInfo* m_list_get_item  = nullptr;
const MethodInfo* m_component_transform = nullptr;
const MethodInfo* m_transform_position  = nullptr;
const MethodInfo* m_transform_forward   = nullptr;
const MethodInfo* m_camera_get_main     = nullptr;
const MethodInfo* m_camera_get_fov      = nullptr;
const MethodInfo* m_screen_get_width    = nullptr;
const MethodInfo* m_screen_get_height   = nullptr;

Il2CppObject* camera_main_cached = nullptr;

CamSnap cam_snap{};
std::vector<PlayerSnap> players_snap;
std::mutex snap_mu;

bool game_thread_attached = false;

template<typename T> inline T R(const void* obj, uintptr_t off) {
    return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(obj) + off);
}

Il2CppObject* invoke0(const MethodInfo* m, void* self) {
    if (!m) return nullptr;
    Il2CppException* e = nullptr;
    return g_il2cpp.runtime_invoke(m, self, nullptr, &e);
}
Vec3 unbox_vec3(Il2CppObject* b) {
    if (!b) return {0,0,0};
    auto p = reinterpret_cast<const uint8_t*>(b) + 0x10;
    return *reinterpret_cast<const Vec3*>(p);
}
int32_t unbox_i32(Il2CppObject* b) {
    if (!b) return 0;
    return *reinterpret_cast<const int32_t*>(reinterpret_cast<const uint8_t*>(b) + 0x10);
}
float unbox_f32(Il2CppObject* b) {
    if (!b) return 0.f;
    return *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(b) + 0x10);
}

} // anon

bool game_init() {
    if (g_il2cpp.loaded && cls_pm) return true;
    // il2cpp API может сидеть в разных .so: libil2cpp.so (стандарт),
    // libunity.so (встроенный), libmain.so, или сам процесс.
    static const char* candidates[] = {
        "libil2cpp.so", "libunity.so", "libmain.so", "libil2cpp.dylib",
        nullptr
    };
    void* h = nullptr;
    for (int i = 0; candidates[i] && !h; ++i) {
        h = dlopen(candidates[i], RTLD_NOW | RTLD_GLOBAL | RTLD_NOLOAD);
        if (!h) h = dlopen(candidates[i], RTLD_NOW | RTLD_GLOBAL);
        if (h) {
            if (!dlsym(h, "il2cpp_domain_get")) {
                dlclose(h); h = nullptr; continue;
            }
            LOGG("il2cpp найден в %s", candidates[i]);
            break;
        }
    }
    if (!h) {
        // last resort: dlopen(NULL) — main ELF, иногда там всё
        h = dlopen(nullptr, RTLD_NOW);
        if (!h || !dlsym(h, "il2cpp_domain_get")) {
            LOGE("il2cpp API ни в одной .so не найден"); return false;
        }
        LOGG("il2cpp найден в main executable");
    }
    if (!il2cpp_api_load(h)) return false;
    auto dom = g_il2cpp.domain_get();
    if (!dom) return false;
    if (!game_thread_attached) {
        g_il2cpp.thread_attach(dom);
        game_thread_attached = true;
    }

    size_t nasm = 0;
    auto asms = g_il2cpp.domain_get_assemblies(dom, &nasm);
    const Il2CppImage* img_csharp = nullptr;
    const Il2CppImage* img_unity = nullptr;
    const Il2CppImage* img_screen = nullptr;
    for (size_t i = 0; i < nasm; ++i) {
        auto im = g_il2cpp.assembly_get_image(asms[i]);
        if (!im) continue;
        if (!img_csharp && g_il2cpp.class_from_name(im, "Oxide", "PlayerManager"))
            img_csharp = im;
        if (!img_unity && g_il2cpp.class_from_name(im, "UnityEngine", "Transform"))
            img_unity = im;
        if (!img_screen && g_il2cpp.class_from_name(im, "UnityEngine", "Screen"))
            img_screen = im;
    }
    if (!img_csharp || !img_unity) {
        LOGE("csharp=%p unity=%p", img_csharp, img_unity);
        return false;
    }

    cls_pm        = g_il2cpp.class_from_name(img_csharp, "Oxide", "PlayerManager");
    cls_mouselook = g_il2cpp.class_from_name(img_csharp, "Oxide", "MouseLook");
    cls_component = g_il2cpp.class_from_name(img_unity, "UnityEngine", "Component");
    cls_transform = g_il2cpp.class_from_name(img_unity, "UnityEngine", "Transform");
    cls_camera    = g_il2cpp.class_from_name(img_unity, "UnityEngine", "Camera");
    cls_screen    = g_il2cpp.class_from_name(img_screen ? img_screen : img_unity, "UnityEngine", "Screen");
    if (!cls_pm || !cls_component || !cls_transform || !cls_camera) {
        LOGE("классы не резолвятся"); return false;
    }
    g_il2cpp.runtime_class_init(cls_pm);

    fld_client_list = g_il2cpp.class_get_field_from_name(cls_pm, "clientPlayerList");
    if (!fld_client_list) { LOGE("clientPlayerList miss"); return false; }

    m_component_transform = g_il2cpp.class_get_method_from_name(cls_component, "get_transform", 0);
    m_transform_position  = g_il2cpp.class_get_method_from_name(cls_transform, "get_position", 0);
    m_transform_forward   = g_il2cpp.class_get_method_from_name(cls_transform, "get_forward",  0);
    m_camera_get_main     = g_il2cpp.class_get_method_from_name(cls_camera,    "get_main",     0);
    m_camera_get_fov      = g_il2cpp.class_get_method_from_name(cls_camera,    "get_fieldOfView", 0);
    if (cls_screen) {
        m_screen_get_width  = g_il2cpp.class_get_method_from_name(cls_screen, "get_width",  0);
        m_screen_get_height = g_il2cpp.class_get_method_from_name(cls_screen, "get_height", 0);
    }

    LOGG("il2cpp runtime bound");
    return true;
}

void game_refresh() {
    if (!cls_pm || !fld_client_list) { if (!game_init()) return; }

    Il2CppObject* list = nullptr;
    g_il2cpp.field_static_get_value(fld_client_list, &list);
    if (!list) return;

    if (!m_list_get_count) {
        auto klass = *reinterpret_cast<Il2CppClass**>(list);
        m_list_get_count = g_il2cpp.class_get_method_from_name(klass, "get_Count", 0);
        m_list_get_item  = g_il2cpp.class_get_method_from_name(klass, "get_Item", 1);
        if (!m_list_get_count || !m_list_get_item) return;
    }

    int32_t count = unbox_i32(invoke0(m_list_get_count, list));
    if (count < 0) count = 0;
    if (count > 128) count = 128;

    // камера
    if (m_camera_get_main) camera_main_cached = invoke0(m_camera_get_main, nullptr);
    Il2CppObject* cam_tr = camera_main_cached
        ? invoke0(m_component_transform, camera_main_cached) : nullptr;
    Vec3 cp = cam_tr ? unbox_vec3(invoke0(m_transform_position, cam_tr)) : Vec3{0,0,0};
    Vec3 cf = cam_tr ? unbox_vec3(invoke0(m_transform_forward,  cam_tr)) : Vec3{0,0,1};
    float fov = 60.f;
    if (camera_main_cached && m_camera_get_fov)
        fov = unbox_f32(invoke0(m_camera_get_fov, camera_main_cached));
    int sw = m_screen_get_width  ? unbox_i32(invoke0(m_screen_get_width,  nullptr)) : 0;
    int sh = m_screen_get_height ? unbox_i32(invoke0(m_screen_get_height, nullptr)) : 0;

    std::vector<PlayerSnap> next;
    next.reserve(count);

    for (int i = 0; i < count; ++i) {
        void* args[1] = { &i };
        Il2CppException* e = nullptr;
        Il2CppObject* pm = g_il2cpp.runtime_invoke(m_list_get_item, list, args, &e);
        if (!pm) continue;

        PlayerSnap p{};
        p.id = (uint32_t)i;

        Il2CppObject* tr = invoke0(m_component_transform, pm);
        Vec3 pos = tr ? unbox_vec3(invoke0(m_transform_position, tr)) : Vec3{0,0,0};
        p.pos = pos;

        Il2CppObject* cam_root = R<Il2CppObject*>(pm, PlayerManager::worldCameraRoot);
        p.head = cam_root ? unbox_vec3(invoke0(m_transform_position, cam_root))
                          : Vec3{ pos.x, pos.y + 1.6f, pos.z };

        float max_hp = 100.f, cur_hp = 100.f;
        Il2CppObject* vit = R<Il2CppObject*>(pm, PlayerManager::vitals);
        if (vit) {
            max_hp = R<float>(vit, Vitals::maxHealth);
            Il2CppObject* entity = R<Il2CppObject*>(vit, Vitals::entity);
            if (entity) {
                Il2CppObject* hobs = R<Il2CppObject*>(entity, Entity::health);
                if (hobs) cur_hp = R<float>(hobs, ObservableFloat::value);
            }
        }
        p.hp = cur_hp;
        p.max_hp = max_hp > 0 ? max_hp : 100.f;
        p.alive = cur_hp > 0.1f;

        Il2CppObject* ml = R<Il2CppObject*>(pm, PlayerManager::mouseLook);
        p.local = ml != nullptr;

        float dx = p.pos.x - cp.x, dy = p.pos.y - cp.y, dz = p.pos.z - cp.z;
        p.distance = sqrtf(dx*dx + dy*dy + dz*dz);

        if (vit) {
            Il2CppObject* entity = R<Il2CppObject*>(vit, Vitals::entity);
            if (entity) {
                Il2CppString* s = R<Il2CppString*>(entity, Entity::displayName);
                if (s) il2cpp_string_to_cstr(s, p.nick, sizeof(p.nick));
            }
        }
        next.push_back(p);
    }

    {
        std::lock_guard<std::mutex> lk(snap_mu);
        cam_snap.pos = cp;
        cam_snap.forward = cf;
        cam_snap.fov = fov;
        cam_snap.screen_w = sw;
        cam_snap.screen_h = sh;
        players_snap.swap(next);
    }
}

const CamSnap& game_camera() { return cam_snap; }
void game_copy_players(std::vector<PlayerSnap>& out) {
    std::lock_guard<std::mutex> lk(snap_mu);
    out = players_snap;
}

} // namespace vanta
