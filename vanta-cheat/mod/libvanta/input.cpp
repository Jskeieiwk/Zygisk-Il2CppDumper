// input.cpp — простейший тач-ридер через /dev/input/eventN (нужен root).
// находит touchscreen device, читает Multi-Touch Protocol B, кормит ImGui.
#include "input.h"
#include "imgui.h"
#include "state.h"

#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <atomic>
#include <mutex>
#include <android/log.h>

#define LOGI(fmt, ...) __android_log_print(ANDROID_LOG_INFO,  "vanta-input", fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "vanta-input", fmt, ##__VA_ARGS__)

namespace vanta {

namespace {
struct Touch {
    int tracking = -1;
    int x = 0, y = 0;
    bool down = false;
};
Touch g_t;                 // одно главное касание (ImGui умеет только "мышь")
int   g_abs_min_x = 0, g_abs_max_x = 32767;
int   g_abs_min_y = 0, g_abs_max_y = 32767;
std::atomic<bool> g_stop{false};
pthread_t g_thr{};
std::mutex g_mu;
std::atomic<bool> g_have_event{false};

bool device_is_touch(int fd) {
    unsigned long abs_bits[(ABS_MAX + 7) / 8] = {};
    if (ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(abs_bits)), abs_bits) < 0) return false;
    bool has_mt_x = (abs_bits[ABS_MT_POSITION_X / 8] >> (ABS_MT_POSITION_X & 7)) & 1;
    bool has_mt_y = (abs_bits[ABS_MT_POSITION_Y / 8] >> (ABS_MT_POSITION_Y & 7)) & 1;
    return has_mt_x && has_mt_y;
}

int open_touchscreen() {
    DIR* d = opendir("/dev/input");
    if (!d) return -1;
    dirent* e;
    int best = -1;
    while ((e = readdir(d))) {
        if (strncmp(e->d_name, "event", 5) != 0) continue;
        char path[64]; snprintf(path, sizeof(path), "/dev/input/%s", e->d_name);
        int fd = open(path, O_RDONLY | O_NONBLOCK);
        if (fd < 0) continue;
        if (device_is_touch(fd)) {
            input_absinfo ai{};
            if (ioctl(fd, EVIOCGABS(ABS_MT_POSITION_X), &ai) >= 0) {
                g_abs_min_x = ai.minimum; g_abs_max_x = ai.maximum;
            }
            if (ioctl(fd, EVIOCGABS(ABS_MT_POSITION_Y), &ai) >= 0) {
                g_abs_min_y = ai.minimum; g_abs_max_y = ai.maximum;
            }
            LOGI("touch device: %s  [%d..%d x %d..%d]", path,
                 g_abs_min_x, g_abs_max_x, g_abs_min_y, g_abs_max_y);
            best = fd;
            break;
        }
        close(fd);
    }
    closedir(d);
    return best;
}

void* reader_thread(void*) {
    int fd = open_touchscreen();
    if (fd < 0) { LOGE("no touch device"); return nullptr; }
    int cur_x = 0, cur_y = 0;
    int slot = 0; (void)slot;
    bool down = false;
    while (!g_stop.load()) {
        input_event ev;
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n != (ssize_t)sizeof(ev)) { usleep(2000); continue; }
        if (ev.type == EV_ABS) {
            switch (ev.code) {
                case ABS_MT_TRACKING_ID:
                    if (ev.value < 0) down = false; else down = true;
                    break;
                case ABS_MT_POSITION_X: cur_x = ev.value; break;
                case ABS_MT_POSITION_Y: cur_y = ev.value; break;
            }
        } else if (ev.type == EV_KEY) {
            if (ev.code == BTN_TOUCH) down = ev.value != 0;
        } else if (ev.type == EV_SYN && ev.code == SYN_REPORT) {
            std::lock_guard<std::mutex> lk(g_mu);
            g_t.down = down;
            g_t.x = cur_x;
            g_t.y = cur_y;
            g_have_event = true;
        }
    }
    close(fd);
    return nullptr;
}

} // anon

bool input_start() {
    g_stop = false;
    if (pthread_create(&g_thr, nullptr, reader_thread, nullptr) != 0) {
        LOGE("thread create fail"); return false;
    }
    return true;
}

void input_stop() {
    g_stop = true;
    if (g_thr) pthread_join(g_thr, nullptr);
}

void input_new_frame(int fb_w, int fb_h) {
    ImGuiIO& io = ImGui::GetIO();
    Touch t;
    bool have;
    {
        std::lock_guard<std::mutex> lk(g_mu);
        t = g_t;
        have = g_have_event.load();
    }
    if (!have) {
        io.AddMouseButtonEvent(0, t.down);
        return;
    }
    float sx = (float)(t.x - g_abs_min_x) / (float)(g_abs_max_x - g_abs_min_x) * fb_w;
    float sy = (float)(t.y - g_abs_min_y) / (float)(g_abs_max_y - g_abs_min_y) * fb_h;
    io.AddMousePosEvent(sx, sy);
    io.AddMouseButtonEvent(0, t.down);
}

} // namespace vanta
