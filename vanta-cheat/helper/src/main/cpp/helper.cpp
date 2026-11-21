// helper.cpp — загружается в процесс игры через ptrace-инжектор.
// задача: 60 раз в секунду итерировать PlayerManager.clientPlayerList, считывать
// позиции/здоровье/скорости и писать в shared memory. Никаких записей в память игры.
#include "il2cpp_api.h"
#include "offsets.h"
#include "shm_proto.h"

#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/system_properties.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <atomic>

#include <android/log.h>
#define LOGH(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-helper", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-helper", fmt, ##__VA_ARGS__)

using namespace OxideOffsets;

namespace {

std::atomic<bool> g_stop{false};
pthread_t g_thread{};

VantaShmHeader* g_shm = nullptr;
int g_shm_fd = -1;

Il2CppClass* g_cls_player_mgr = nullptr;
Il2CppClass* g_cls_mouselook  = nullptr;
Il2CppClass* g_cls_component  = nullptr;
Il2CppClass* g_cls_transform  = nullptr;
Il2CppClass* g_cls_camera     = nullptr;
Il2CppClass* g_cls_screen     = nullptr;

FieldInfo* g_fld_client_list  = nullptr;  // static List<PlayerManager> PlayerManager.clientPlayerList

const MethodInfo* g_m_list_get_count = nullptr; // List<PlayerManager>::get_Count
const MethodInfo* g_m_list_get_item  = nullptr; // List<PlayerManager>::get_Item(int)
const MethodInfo* g_m_component_get_transform = nullptr;
const MethodInfo* g_m_transform_get_position  = nullptr;
const MethodInfo* g_m_transform_get_forward   = nullptr;
const MethodInfo* g_m_transform_get_right     = nullptr;
const MethodInfo* g_m_camera_get_main         = nullptr;  // static Camera.main
const MethodInfo* g_m_camera_get_fov          = nullptr;
const MethodInfo* g_m_camera_world_to_screen  = nullptr;
const MethodInfo* g_m_screen_get_width        = nullptr;
const MethodInfo* g_m_screen_get_height       = nullptr;

uint64_t now_ns() {
    timespec t{};
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (uint64_t)t.tv_sec * 1'000'000'000ull + (uint64_t)t.tv_nsec;
}

bool open_shm() {
    // ashmem через /dev/ashmem давно deprecated; используем memfd + bind-mount
    // но проще: tmpfs файл в /data/local/tmp — rw для оверлея тоже рутового.
    const char* path = "/data/local/tmp/" VANTA_SHM_NAME;
    g_shm_fd = open(path, O_RDWR | O_CREAT, 0666);
    if (g_shm_fd < 0) { LOGE("shm open: %s", strerror(errno)); return false; }
    if (ftruncate(g_shm_fd, sizeof(VantaShmHeader)) < 0) {
        LOGE("ftruncate: %s", strerror(errno)); return false;
    }
    void* p = mmap(nullptr, sizeof(VantaShmHeader), PROT_READ | PROT_WRITE,
                   MAP_SHARED, g_shm_fd, 0);
    if (p == MAP_FAILED) { LOGE("mmap: %s", strerror(errno)); return false; }
    g_shm = reinterpret_cast<VantaShmHeader*>(p);
    memset(g_shm, 0, sizeof(*g_shm));
    g_shm->magic = VANTA_SHM_MAGIC;
    g_shm->version = VANTA_SHM_VERSION;
    g_shm->game_pid = getpid();
    chmod(path, 0666);
    LOGH("shm mapped at %p, pid=%d", g_shm, getpid());
    return true;
}

// найти Assembly-CSharp image, затем классы и методы
bool bind_runtime() {
    auto dom = g_il2cpp.domain_get();
    if (!dom) { LOGE("domain null"); return false; }
    size_t nasm = 0;
    auto asms = g_il2cpp.domain_get_assemblies(dom, &nasm);

    const Il2CppImage* img_csharp = nullptr;
    const Il2CppImage* img_unity_core = nullptr;
    const Il2CppImage* img_unity_screen = nullptr;

    for (size_t i = 0; i < nasm; ++i) {
        auto im = g_il2cpp.assembly_get_image(asms[i]);
        if (!im) continue;
        // находим PlayerManager
        auto cls = g_il2cpp.class_from_name(im, "Oxide", "PlayerManager");
        if (cls && !img_csharp) img_csharp = im;
        cls = g_il2cpp.class_from_name(im, "UnityEngine", "Transform");
        if (cls && !img_unity_core) img_unity_core = im;
        cls = g_il2cpp.class_from_name(im, "UnityEngine", "Screen");
        if (cls && !img_unity_screen) img_unity_screen = im;
    }

    if (!img_csharp) { LOGE("Assembly-CSharp не найден"); return false; }
    if (!img_unity_core) { LOGE("UnityEngine.CoreModule не найден"); return false; }

    g_cls_player_mgr = g_il2cpp.class_from_name(img_csharp, "Oxide", "PlayerManager");
    g_cls_mouselook  = g_il2cpp.class_from_name(img_csharp, "Oxide", "MouseLook");
    g_cls_component  = g_il2cpp.class_from_name(img_unity_core, "UnityEngine", "Component");
    g_cls_transform  = g_il2cpp.class_from_name(img_unity_core, "UnityEngine", "Transform");
    g_cls_camera     = g_il2cpp.class_from_name(img_unity_core, "UnityEngine", "Camera");
    g_cls_screen     = g_il2cpp.class_from_name(img_unity_screen ? img_unity_screen : img_unity_core,
                                                "UnityEngine", "Screen");

    if (!g_cls_player_mgr || !g_cls_component || !g_cls_transform || !g_cls_camera) {
        LOGE("базовые классы не резолвятся"); return false;
    }
    g_il2cpp.runtime_class_init(g_cls_player_mgr);

    g_fld_client_list = g_il2cpp.class_get_field_from_name(g_cls_player_mgr, "clientPlayerList");
    if (!g_fld_client_list) { LOGE("clientPlayerList не найден"); return false; }

    // List<PlayerManager> — generic, но методы get_Count/get_Item разделяют одну MethodInfo
    // можно читать через конкретный инстанс: получим List object и достанем его klass → методы
    // отложим это на первую итерацию loop'а.

    g_m_component_get_transform = g_il2cpp.class_get_method_from_name(g_cls_component, "get_transform", 0);
    g_m_transform_get_position  = g_il2cpp.class_get_method_from_name(g_cls_transform, "get_position", 0);
    g_m_transform_get_forward   = g_il2cpp.class_get_method_from_name(g_cls_transform, "get_forward", 0);
    g_m_transform_get_right     = g_il2cpp.class_get_method_from_name(g_cls_transform, "get_right", 0);
    g_m_camera_get_main         = g_il2cpp.class_get_method_from_name(g_cls_camera, "get_main", 0);
    g_m_camera_get_fov          = g_il2cpp.class_get_method_from_name(g_cls_camera, "get_fieldOfView", 0);
    g_m_camera_world_to_screen  = g_il2cpp.class_get_method_from_name(g_cls_camera, "WorldToScreenPoint", 1);

    if (g_cls_screen) {
        g_m_screen_get_width  = g_il2cpp.class_get_method_from_name(g_cls_screen, "get_width", 0);
        g_m_screen_get_height = g_il2cpp.class_get_method_from_name(g_cls_screen, "get_height", 0);
    }

    LOGH("runtime bind OK");
    return true;
}

// Transform.get_position → Vector3 (возврат по регистрам / через obj — вызываем runtime_invoke)
Il2CppVector3 transform_position(Il2CppObject* t) {
    if (!t || !g_m_transform_get_position) return {0,0,0};
    Il2CppException* exc = nullptr;
    Il2CppObject* boxed = g_il2cpp.runtime_invoke(g_m_transform_get_position, t, nullptr, &exc);
    // Vector3 — struct, runtime_invoke возвращает boxed → object header 0x10 + data
    if (!boxed) return {0,0,0};
    auto p = reinterpret_cast<const uint8_t*>(boxed) + 0x10;
    return *reinterpret_cast<const Il2CppVector3*>(p);
}

Il2CppVector3 transform_forward(Il2CppObject* t) {
    if (!t || !g_m_transform_get_forward) return {0,0,1};
    Il2CppException* exc = nullptr;
    auto b = g_il2cpp.runtime_invoke(g_m_transform_get_forward, t, nullptr, &exc);
    if (!b) return {0,0,1};
    return *reinterpret_cast<const Il2CppVector3*>(reinterpret_cast<const uint8_t*>(b) + 0x10);
}

Il2CppObject* component_transform(Il2CppObject* c) {
    if (!c || !g_m_component_get_transform) return nullptr;
    Il2CppException* exc = nullptr;
    return g_il2cpp.runtime_invoke(g_m_component_get_transform, c, nullptr, &exc);
}

// возвращает Camera.main; кешируется, но обновляется если null
Il2CppObject* camera_main_cached = nullptr;
Il2CppObject* get_camera_main() {
    if (camera_main_cached) return camera_main_cached;
    if (!g_m_camera_get_main) return nullptr;
    Il2CppException* exc = nullptr;
    camera_main_cached = g_il2cpp.runtime_invoke(g_m_camera_get_main, nullptr, nullptr, &exc);
    return camera_main_cached;
}

int screen_width()  {
    if (!g_m_screen_get_width) return 0;
    Il2CppException* exc = nullptr;
    auto b = g_il2cpp.runtime_invoke(g_m_screen_get_width, nullptr, nullptr, &exc);
    if (!b) return 0;
    return *reinterpret_cast<const int32_t*>(reinterpret_cast<const uint8_t*>(b) + 0x10);
}
int screen_height() {
    if (!g_m_screen_get_height) return 0;
    Il2CppException* exc = nullptr;
    auto b = g_il2cpp.runtime_invoke(g_m_screen_get_height, nullptr, nullptr, &exc);
    if (!b) return 0;
    return *reinterpret_cast<const int32_t*>(reinterpret_cast<const uint8_t*>(b) + 0x10);
}

// утилиты чтения managed-полей по офсету
template<typename T> inline T read_at(const void* obj, uintptr_t off) {
    return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(obj) + off);
}

float vlen(const Il2CppVector3& a, const Il2CppVector3& b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return sqrtf(dx*dx + dy*dy + dz*dz);
}

// основной цикл — вызывается в своём треде, attached к il2cpp runtime
void* worker(void*) {
    // приаттачить к домену — обязательно для вызова runtime_invoke из чужого треда
    g_il2cpp.thread_attach(g_il2cpp.domain_get());

    bool list_methods_bound = false;

    while (!g_stop.load(std::memory_order_relaxed)) {
        // достаём managed list
        Il2CppObject* list_obj = nullptr;
        g_il2cpp.field_static_get_value(g_fld_client_list, &list_obj);
        if (!list_obj) { usleep(50'000); continue; }

        if (!list_methods_bound) {
            auto klass = *reinterpret_cast<Il2CppClass**>(list_obj);
            g_m_list_get_count = g_il2cpp.class_get_method_from_name(klass, "get_Count", 0);
            g_m_list_get_item  = g_il2cpp.class_get_method_from_name(klass, "get_Item", 1);
            if (!g_m_list_get_count || !g_m_list_get_item) {
                LOGE("list_methods bind failed, retry");
                usleep(250'000);
                continue;
            }
            list_methods_bound = true;
            LOGH("list methods bound");
        }

        Il2CppException* exc = nullptr;
        auto boxed_count = g_il2cpp.runtime_invoke(g_m_list_get_count, list_obj, nullptr, &exc);
        int32_t count = boxed_count
            ? *reinterpret_cast<const int32_t*>(reinterpret_cast<const uint8_t*>(boxed_count) + 0x10)
            : 0;
        if (count < 0) count = 0;
        if (count > VANTA_MAX_PLAYERS) count = VANTA_MAX_PLAYERS;

        // камера и экран
        auto cam = get_camera_main();
        Il2CppObject* cam_tr = component_transform(cam);
        auto cam_pos = cam_tr ? transform_position(cam_tr) : Il2CppVector3{0,0,0};
        auto cam_fwd = cam_tr ? transform_forward(cam_tr) : Il2CppVector3{0,0,1};
        float cam_fov = 60.f;
        if (cam && g_m_camera_get_fov) {
            auto b = g_il2cpp.runtime_invoke(g_m_camera_get_fov, cam, nullptr, &exc);
            if (b) cam_fov = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(b) + 0x10);
        }
        int sw = screen_width();
        int sh = screen_height();

        // ищем локалку по PlayerManager.mouseLook != null (у чужих игроков его нет / зануляется)
        int local_idx = -1;
        int written = 0;

        for (int i = 0; i < count; ++i) {
            void* params[1] = { &i };
            auto boxed_item = g_il2cpp.runtime_invoke(g_m_list_get_item, list_obj, params, &exc);
            if (!boxed_item) continue;
            // List<T> get_Item возвращает T; для ref-типа — сам объект через runtime_invoke
            // возвращается boxed на object; данные — сам Il2CppObject*
            Il2CppObject* pm = boxed_item; // для reference type тут и есть объект

            auto& dst = g_shm->players[written];
            memset(&dst, 0, sizeof(dst));
            dst.net_id = read_at<uint32_t>(pm, 0x58); // netId у NetworkBehaviour — проверим в рантайме
            dst.flags = 0;

            // Transform самого игрока
            Il2CppObject* tr = component_transform(pm);
            Il2CppVector3 pos = transform_position(tr);
            dst.pos = { pos.x, pos.y, pos.z };

            // голова: worldCameraRoot (0xA8) → transform
            Il2CppObject* head_tr = read_at<Il2CppObject*>(pm, PlayerManager::worldCameraRoot);
            auto head = head_tr ? transform_position(head_tr) : pos;
            dst.head = { head.x, head.y + 1.6f, head.z };

            // vitals / HP
            Il2CppObject* vit = read_at<Il2CppObject*>(pm, PlayerManager::vitals);
            float max_hp = 100.f, cur_hp = 100.f;
            if (vit) {
                max_hp = read_at<float>(vit, Vitals::maxHealth);
                Il2CppObject* entity = read_at<Il2CppObject*>(vit, Vitals::entity);
                if (entity) {
                    Il2CppObject* hp_obs = read_at<Il2CppObject*>(entity, Entity::health);
                    if (hp_obs) {
                        cur_hp = read_at<float>(hp_obs, ObservableFloat::value);
                    }
                }
            }
            dst.health = cur_hp;
            dst.max_health = max_hp > 0.f ? max_hp : 100.f;
            if (cur_hp > 0.1f) dst.flags |= VF_ALIVE;

            // локалка — есть mouseLook
            Il2CppObject* ml = read_at<Il2CppObject*>(pm, PlayerManager::mouseLook);
            if (ml) {
                dst.flags |= VF_LOCAL;
                local_idx = written;
            }

            dst.distance = vlen(cam_pos, dst.pos);

            // DisplayName из entity
            if (vit) {
                Il2CppObject* entity = read_at<Il2CppObject*>(vit, Vitals::entity);
                if (entity) {
                    auto str = read_at<Il2CppString*>(entity, Entity::displayName);
                    if (str) il2cpp_string_to_cstr(str, dst.nick, VANTA_NICK_LEN);
                }
            }

            ++written;
        }

        // пишем камеру
        g_shm->camera.pos = { cam_pos.x, cam_pos.y, cam_pos.z };
        g_shm->camera.forward = { cam_fwd.x, cam_fwd.y, cam_fwd.z };
        g_shm->camera.fov = cam_fov;
        g_shm->camera.screen_w = sw;
        g_shm->camera.screen_h = sh;
        // view_proj не строим — overlay считает World2Screen сам, либо дёргает helper (TODO)

        g_shm->player_count = written;
        g_shm->local_player_idx = (local_idx >= 0) ? local_idx : 0xFFFFFFFFu;
        g_shm->timestamp_ns = now_ns();
        __sync_add_and_fetch(&g_shm->seq, 1);

        // ~60 FPS — 16 мс
        usleep(16'000);
    }

    g_il2cpp.thread_detach(nullptr);
    LOGH("worker stopped");
    return nullptr;
}

} // namespace

// entry — вызывается из dlopen-инжектора после полной загрузки libil2cpp.so игрой
extern "C" __attribute__((visibility("default")))
int vanta_helper_start() {
    LOGH("helper start pid=%d", getpid());

    void* h = dlopen("libil2cpp.so", RTLD_NOW | RTLD_GLOBAL);
    if (!h) { LOGE("dlopen libil2cpp.so: %s", dlerror()); return -1; }
    if (!il2cpp_api_load(h)) return -2;

    // Il2CppDomain может быть ещё не инициализирован. ждём до 30 секунд.
    for (int i = 0; i < 300; ++i) {
        if (g_il2cpp.domain_get() && g_il2cpp.domain_get()) {
            if (bind_runtime()) break;
        }
        usleep(100'000);
    }
    if (!g_cls_player_mgr) { LOGE("bind_runtime timeout"); return -3; }

    if (!open_shm()) return -4;

    pthread_create(&g_thread, nullptr, worker, nullptr);
    LOGH("helper installed");
    return 0;
}

extern "C" __attribute__((visibility("default")))
void vanta_helper_stop() {
    g_stop = true;
    if (g_thread) pthread_join(g_thread, nullptr);
    if (g_shm) munmap(g_shm, sizeof(*g_shm));
    if (g_shm_fd >= 0) close(g_shm_fd);
}
