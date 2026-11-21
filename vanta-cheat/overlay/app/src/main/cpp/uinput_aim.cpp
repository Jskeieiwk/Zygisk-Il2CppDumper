// uinput_aim.cpp — мульти-тач эмуляция через /dev/uinput.
// подаём свайпы в правой части экрана (зона обзора), смещая prцел к цели.
#include "uinput_aim.h"

#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <atomic>
#include <mutex>
#include <android/log.h>

#define LOGA(fmt, ...) __android_log_print(ANDROID_LOG_INFO,  "vanta-aim", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-aim", fmt, ##__VA_ARGS__)

namespace vanta {

static int g_fd = -1;
static std::mutex g_mu;
static AimConfig g_cfg{};
static bool g_touch_down = false;
static int  g_touch_x = 0;
static int  g_touch_y = 0;

bool aim_init() {
    std::lock_guard<std::mutex> lk(g_mu);
    if (g_fd >= 0) return true;
    g_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (g_fd < 0) { LOGE("open /dev/uinput: %d", errno); return false; }

    ioctl(g_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(g_fd, UI_SET_KEYBIT, BTN_TOUCH);
    ioctl(g_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_POSITION_X);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_POSITION_Y);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_TRACKING_ID);
    ioctl(g_fd, UI_SET_ABSBIT, ABS_MT_TOUCH_MAJOR);
    ioctl(g_fd, UI_SET_PROPBIT, INPUT_PROP_DIRECT);

    uinput_user_dev dev{};
    strncpy(dev.name, "vanta-touch", UINPUT_MAX_NAME_SIZE - 1);
    dev.id.bustype = BUS_VIRTUAL;
    dev.id.vendor  = 0x1234;
    dev.id.product = 0x5678;
    dev.id.version = 1;
    dev.absmin[ABS_MT_POSITION_X] = 0;    dev.absmax[ABS_MT_POSITION_X] = 32767;
    dev.absmin[ABS_MT_POSITION_Y] = 0;    dev.absmax[ABS_MT_POSITION_Y] = 32767;
    dev.absmin[ABS_MT_TRACKING_ID] = 0;   dev.absmax[ABS_MT_TRACKING_ID] = 65535;
    dev.absmin[ABS_MT_TOUCH_MAJOR] = 0;   dev.absmax[ABS_MT_TOUCH_MAJOR] = 255;
    write(g_fd, &dev, sizeof(dev));
    if (ioctl(g_fd, UI_DEV_CREATE) < 0) {
        LOGE("UI_DEV_CREATE: %d", errno); close(g_fd); g_fd = -1; return false;
    }
    LOGA("uinput touch created");
    return true;
}

static void emit(int type, int code, int val) {
    input_event e{};
    e.type = type; e.code = code; e.value = val;
    write(g_fd, &e, sizeof(e));
}

void aim_set_config(const AimConfig& c) {
    std::lock_guard<std::mutex> lk(g_mu);
    g_cfg = c;
}

static void touch_begin(int x, int y) {
    emit(EV_ABS, ABS_MT_TRACKING_ID, 1);
    emit(EV_ABS, ABS_MT_POSITION_X, x);
    emit(EV_ABS, ABS_MT_POSITION_Y, y);
    emit(EV_ABS, ABS_MT_TOUCH_MAJOR, 20);
    emit(EV_KEY, BTN_TOUCH, 1);
    emit(EV_SYN, SYN_REPORT, 0);
    g_touch_down = true;
}
static void touch_move(int x, int y) {
    emit(EV_ABS, ABS_MT_POSITION_X, x);
    emit(EV_ABS, ABS_MT_POSITION_Y, y);
    emit(EV_SYN, SYN_REPORT, 0);
}
static void touch_end() {
    emit(EV_ABS, ABS_MT_TRACKING_ID, -1);
    emit(EV_KEY, BTN_TOUCH, 0);
    emit(EV_SYN, SYN_REPORT, 0);
    g_touch_down = false;
}

// активируем только когда aim engaged; смещаем от центра экрана по направлению к цели
void aim_update(int cx, int cy, int tx, int ty, bool active) {
    std::lock_guard<std::mutex> lk(g_mu);
    if (g_fd < 0) return;

    if (!active) {
        if (g_touch_down) touch_end();
        return;
    }

    float dx = (float)(tx - cx);
    float dy = (float)(ty - cy);
    float dist = sqrtf(dx*dx + dy*dy);
    if (dist > g_cfg.fov_px) {
        if (g_touch_down) touch_end();
        return;
    }
    if (dist < g_cfg.deadzone_px) {
        if (g_touch_down) touch_end();
        return;
    }

    // игровой look-зона обычно справа; базовая точка — 0.75 ширины, 0.5 высоты
    // игра маппит абсолютные координаты tochdevice'а через свои коэффициенты screen_w/screen_h.
    // мы работаем в абсолютных 0..32767.
    const int base_x = (int)(32767 * 0.75f);
    const int base_y = (int)(32767 * 0.50f);
    // шаг: сдвиг пропорциональный delta * smooth
    float step = fminf(1.0f, g_cfg.smooth * 1.5f);
    int nx = base_x + (int)(dx * step * 20.f);
    int ny = base_y + (int)(dy * step * 20.f);

    if (!g_touch_down) {
        touch_begin(base_x, base_y);
        g_touch_x = base_x; g_touch_y = base_y;
    }
    if (nx != g_touch_x || ny != g_touch_y) {
        touch_move(nx, ny);
        g_touch_x = nx; g_touch_y = ny;
    }
}

void aim_shutdown() {
    std::lock_guard<std::mutex> lk(g_mu);
    if (g_fd < 0) return;
    if (g_touch_down) touch_end();
    ioctl(g_fd, UI_DEV_DESTROY);
    close(g_fd);
    g_fd = -1;
}

} // namespace vanta
