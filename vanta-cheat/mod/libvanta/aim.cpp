// aim.cpp — aim через /dev/uinput: виртуальный тач, свайп в look-зоне.
#include "aim.h"
#include "state.h"
#include "game.h"
#include "imgui.h"

#include <vector>
#include <errno.h>

#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <atomic>
#include <mutex>
#include <android/log.h>

#define LOGA(fmt, ...) __android_log_print(ANDROID_LOG_INFO,  "vanta-aim", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-aim", fmt, ##__VA_ARGS__)

namespace vanta {

static int g_fd = -1;
static bool g_down = false;
static int g_cur_x = 0, g_cur_y = 0;

void aim_start() {
    if (g_fd >= 0) return;
    g_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (g_fd < 0) { LOGE("uinput open: %d", errno); return; }
    ioctl(g_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(g_fd, UI_SET_KEYBIT, BTN_TOUCH);
    ioctl(g_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_POSITION_X);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_POSITION_Y);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_TRACKING_ID);
    ioctl(g_fd, UI_SET_PROPBIT, INPUT_PROP_DIRECT);
    uinput_user_dev dev{};
    strncpy(dev.name, "vanta-aim", UINPUT_MAX_NAME_SIZE - 1);
    dev.id.bustype = BUS_VIRTUAL; dev.id.vendor = 0x1234; dev.id.product = 0x5678;
    dev.absmin[ABS_MT_POSITION_X] = 0; dev.absmax[ABS_MT_POSITION_X] = 32767;
    dev.absmin[ABS_MT_POSITION_Y] = 0; dev.absmax[ABS_MT_POSITION_Y] = 32767;
    dev.absmin[ABS_MT_TRACKING_ID] = 0; dev.absmax[ABS_MT_TRACKING_ID] = 65535;
    write(g_fd, &dev, sizeof(dev));
    if (ioctl(g_fd, UI_DEV_CREATE) < 0) {
        LOGE("UI_DEV_CREATE %d", errno); close(g_fd); g_fd = -1; return;
    }
    LOGA("aim uinput ready");
}

void aim_stop() {
    if (g_fd < 0) return;
    if (g_down) {
        input_event e{};
        e.type = EV_ABS; e.code = ABS_MT_TRACKING_ID; e.value = -1; write(g_fd, &e, sizeof(e));
        e.type = EV_KEY; e.code = BTN_TOUCH;          e.value = 0; write(g_fd, &e, sizeof(e));
        e.type = EV_SYN; e.code = SYN_REPORT;         e.value = 0; write(g_fd, &e, sizeof(e));
    }
    ioctl(g_fd, UI_DEV_DESTROY);
    close(g_fd); g_fd = -1;
}

static void emit(int type, int code, int val) {
    if (g_fd < 0) return;
    input_event e{}; e.type = type; e.code = code; e.value = val;
    write(g_fd, &e, sizeof(e));
}
static void touch_begin(int x, int y) {
    emit(EV_ABS, ABS_MT_TRACKING_ID, 1);
    emit(EV_ABS, ABS_MT_POSITION_X, x);
    emit(EV_ABS, ABS_MT_POSITION_Y, y);
    emit(EV_KEY, BTN_TOUCH, 1);
    emit(EV_SYN, SYN_REPORT, 0);
    g_down = true; g_cur_x = x; g_cur_y = y;
}
static void touch_move(int x, int y) {
    emit(EV_ABS, ABS_MT_POSITION_X, x);
    emit(EV_ABS, ABS_MT_POSITION_Y, y);
    emit(EV_SYN, SYN_REPORT, 0);
    g_cur_x = x; g_cur_y = y;
}
static void touch_end() {
    emit(EV_ABS, ABS_MT_TRACKING_ID, -1);
    emit(EV_KEY, BTN_TOUCH, 0);
    emit(EV_SYN, SYN_REPORT, 0);
    g_down = false;
}

// простейшая логика — ищем ближайшую цель по экрану (ESP уже спроецировал каждого).
// т.к. ESP считает проекцию каждый кадр, здесь тоже пройдём список.
void aim_tick_and_update() {
    if (!g.aim_enabled || g_fd < 0) { if (g_down) touch_end(); return; }

    const CamSnap& cam = game_camera();
    std::vector<PlayerSnap> pls; game_copy_players(pls);
    ImGuiIO& io = ImGui::GetIO();
    int sw = cam.screen_w > 0 ? cam.screen_w : (int)io.DisplaySize.x;
    int sh = cam.screen_h > 0 ? cam.screen_h : (int)io.DisplaySize.y;
    float cx = io.DisplaySize.x * 0.5f, cy = io.DisplaySize.y * 0.5f;

    float best = 1e9f;
    float tx = 0, ty = 0;
    bool any = false;

    // та же World2Screen что в esp.cpp (упрощённая)
    auto w2s = [&](const Vec3& w, float& X, float& Y) {
        float dx = w.x - cam.pos.x, dy = w.y - cam.pos.y, dz = w.z - cam.pos.z;
        float fl = sqrtf(cam.forward.x * cam.forward.x + cam.forward.y * cam.forward.y + cam.forward.z * cam.forward.z);
        if (fl < 1e-5f) return false;
        float fx = cam.forward.x / fl, fy = cam.forward.y / fl, fz = cam.forward.z / fl;
        float rx = fz, ry = 0, rz = -fx;
        float rl = sqrtf(rx*rx + rz*rz); if (rl < 1e-5f) return false;
        rx /= rl; rz /= rl;
        float ux = ry*fz - rz*fy, uy = rz*fx - rx*fz, uz = rx*fy - ry*fx;
        float dF = dx*fx + dy*fy + dz*fz; if (dF < 0.1f) return false;
        float dR = dx*rx + dy*ry + dz*rz;
        float dU = dx*ux + dy*uy + dz*uz;
        float fovR = cam.fov > 1 ? cam.fov * 3.14159265f / 180.f : 60.f * 3.14159265f / 180.f;
        float tH = tanf(fovR * 0.5f);
        float asp = (float)sw / (sh > 0 ? sh : 1);
        X = ((dR / (dF * tH * asp)) * 0.5f + 0.5f) * sw;
        Y = (1.f - ((dU / (dF * tH)) * 0.5f + 0.5f)) * sh;
        return true;
    };

    for (const auto& p : pls) {
        if (!p.alive || p.local) continue;
        if (g.aim_ignore_team && p.teammate) continue;
        Vec3 target = g.aim_head ? p.head : Vec3{ (p.pos.x + p.head.x)*0.5f, (p.pos.y + p.head.y)*0.5f, (p.pos.z + p.head.z)*0.5f };
        float X, Y;
        if (!w2s(target, X, Y)) continue;
        float ddx = X - cx, ddy = Y - cy;
        float dd = sqrtf(ddx*ddx + ddy*ddy);
        if (dd > g.aim_fov) continue;
        if (dd < best) { best = dd; tx = X; ty = Y; any = true; }
    }

    if (!any) { if (g_down) touch_end(); return; }
    float ddx = tx - cx, ddy = ty - cy;
    float dd = sqrtf(ddx*ddx + ddy*ddy);
    if (dd < g.aim_dead) { if (g_down) touch_end(); return; }

    // мапим на виртуальный тач. зона look — правые 60% экрана.
    const int base_x = (int)(32767 * 0.75f);
    const int base_y = (int)(32767 * 0.50f);
    float step = fminf(1.f, g.aim_smooth * 1.5f);
    int nx = base_x + (int)(ddx * step * 20.f);
    int ny = base_y + (int)(ddy * step * 20.f);
    if (!g_down) touch_begin(base_x, base_y);
    if (nx != g_cur_x || ny != g_cur_y) touch_move(nx, ny);
}

} // namespace vanta
