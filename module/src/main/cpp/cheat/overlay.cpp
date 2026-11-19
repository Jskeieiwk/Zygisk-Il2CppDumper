#include "overlay.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <dlfcn.h>
#include <mutex>
#include <unistd.h>

#include <EGL/egl.h>

#include "gles3_renderer.h"
#include "imgui.h"
#include "ms_log.h"
#include "ms_state.h"
#include "xdl.h"

namespace ms::overlay {

namespace {

std::atomic<bool> g_ready{false};

// ---------------------------------------------------------------- input queue (main thread -> swap thread)

std::mutex g_queue_mutex;
std::deque<TouchEvent> g_queue;
constexpr size_t kQueueMax = 256;

void drain(std::deque<TouchEvent> &out) {
    std::lock_guard<std::mutex> lock(g_queue_mutex);
    out.swap(g_queue);
    g_queue.clear();
}

int64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// ---------------------------------------------------------------- theme

namespace col {
constexpr ImU32 kBackdrop = IM_COL32(0, 0, 0, 110);
constexpr ImVec4 kWindow{0.035f, 0.035f, 0.047f, 0.97f};
constexpr ImU32 kCard = IM_COL32(20, 20, 27, 255);
constexpr ImU32 kCardBorder = IM_COL32(38, 38, 50, 255);
constexpr ImVec4 kBorder{0.16f, 0.16f, 0.21f, 1.0f};
constexpr ImVec4 kText{0.93f, 0.93f, 0.95f, 1.0f};
constexpr ImVec4 kTextDim{0.54f, 0.54f, 0.62f, 1.0f};
constexpr ImVec4 kAccent{0.55f, 0.36f, 0.96f, 1.0f};
constexpr ImVec4 kAccentHover{0.65f, 0.50f, 0.98f, 1.0f};
constexpr ImVec4 kAccentActive{0.45f, 0.28f, 0.85f, 1.0f};
constexpr ImVec4 kFrame{0.09f, 0.09f, 0.12f, 1.0f};
constexpr ImVec4 kFrameHover{0.12f, 0.12f, 0.16f, 1.0f};
constexpr ImVec4 kDanger{0.86f, 0.24f, 0.27f, 1.0f};
constexpr ImVec4 kDangerHover{0.93f, 0.33f, 0.36f, 1.0f};
constexpr ImVec4 kGood{0.20f, 0.77f, 0.45f, 1.0f};
constexpr ImU32 kSwitchOff = IM_COL32(48, 48, 62, 255);
constexpr ImU32 kKnob = IM_COL32(245, 245, 250, 255);
}  // namespace col

// ---------------------------------------------------------------- overlay state (swap thread only)

ImFont *g_font = nullptr;
ImFont *g_font_title = nullptr;
bool g_imgui_ready = false;
EGLContext g_gl_context = EGL_NO_CONTEXT;
bool g_gl_ok = false;

bool g_menu_open = false;
float g_menu_alpha = 0.0f;
ImVec2 g_menu_min{0, 0}, g_menu_max{0, 0};
int g_tracked_finger = -1;   // finger currently driving ImGui
int g_swallow_finger = -1;   // finger whose remaining events are ignored
int64_t g_last_tap_ms = 0;
ImVec2 g_last_tap_pos{0, 0};
int64_t g_last_frame_ms = 0;

constexpr int64_t kDoubleTapMs = 350;

bool load_fonts(float px) {
    ImGuiIO &io = ImGui::GetIO();
    static const char *const kFonts[] = {
        "/system/fonts/Roboto-Regular.ttf",
        "/system/fonts/NotoSans-Regular.ttf",
        "/system/fonts/DroidSans.ttf",
        "/system/fonts/MiSansVF.ttf",
    };
    const ImWchar *ranges = io.Fonts->GetGlyphRangesCyrillic();
    ImFontConfig cfg;
    cfg.OversampleH = 2;
    cfg.OversampleV = 2;
    for (const char *path : kFonts) {
        if (access(path, R_OK) != 0) continue;
        g_font = io.Fonts->AddFontFromFileTTF(path, px, &cfg, ranges);
        if (!g_font) continue;
        g_font_title = io.Fonts->AddFontFromFileTTF(path, px * 1.35f, &cfg, ranges);
        MS_LOGI("menu font: %s %.0fpx", path, px);
        break;
    }
    if (!g_font) {
        MS_LOGW("no system font with Cyrillic found, falling back to the built-in font");
        ImFontConfig def;
        def.SizePixels = px;
        g_font = io.Fonts->AddFontDefault(&def);
    }
    if (!g_font_title) g_font_title = g_font;
    return g_font != nullptr;
}

void apply_style(float scale) {
    ImGuiStyle &s = ImGui::GetStyle();
    s = ImGuiStyle();
    s.WindowPadding = ImVec2(18, 18);
    s.FramePadding = ImVec2(12, 9);
    s.ItemSpacing = ImVec2(10, 10);
    s.ItemInnerSpacing = ImVec2(8, 6);
    s.WindowRounding = 18;
    s.FrameRounding = 10;
    s.GrabRounding = 10;
    s.GrabMinSize = 22;
    s.WindowBorderSize = 1;
    s.FrameBorderSize = 0;
    s.ScrollbarSize = 0;
    s.TouchExtraPadding = ImVec2(4, 4);
    s.ScaleAllSizes(scale);

    ImVec4 *c = s.Colors;
    c[ImGuiCol_Text] = col::kText;
    c[ImGuiCol_TextDisabled] = col::kTextDim;
    c[ImGuiCol_WindowBg] = col::kWindow;
    c[ImGuiCol_Border] = col::kBorder;
    c[ImGuiCol_FrameBg] = col::kFrame;
    c[ImGuiCol_FrameBgHovered] = col::kFrameHover;
    c[ImGuiCol_FrameBgActive] = col::kFrameHover;
    c[ImGuiCol_SliderGrab] = col::kAccent;
    c[ImGuiCol_SliderGrabActive] = col::kAccentHover;
    c[ImGuiCol_Button] = col::kFrame;
    c[ImGuiCol_ButtonHovered] = col::kFrameHover;
    c[ImGuiCol_ButtonActive] = col::kAccentActive;
    c[ImGuiCol_Separator] = col::kBorder;
}

bool init_imgui(int w, int h) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.BackendRendererName = "ms_gles3";
    io.BackendPlatformName = "ms_unity_touch";
    io.DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));

    const float px = std::clamp(static_cast<float>(std::min(w, h)) * 0.034f, 18.0f, 64.0f);
    if (!load_fonts(px)) return false;
    apply_style(px / 16.0f);
    return true;
}

// ---------------------------------------------------------------- touch -> menu / ImGui

bool inside_menu(ImVec2 p) {
    if (g_menu_max.x <= g_menu_min.x || g_menu_max.y <= g_menu_min.y) return true;  // not laid out yet
    return p.x >= g_menu_min.x && p.x <= g_menu_max.x && p.y >= g_menu_min.y && p.y <= g_menu_max.y;
}

void release_imgui_pointer() {
    ImGuiIO &io = ImGui::GetIO();
    if (g_tracked_finger != -1) io.AddMouseButtonEvent(0, false);
    io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
    g_tracked_finger = -1;
}

void close_menu() {
    release_imgui_pointer();
    g_menu_open = false;
}

void process_touches(float fb_w, float fb_h) {
    std::deque<TouchEvent> events;
    drain(events);
    ImGuiIO &io = ImGui::GetIO();
    const float near_px = std::min(fb_w, fb_h) * 0.07f;

    for (const TouchEvent &e : events) {
        const ImVec2 p(e.x * fb_w / e.screen_w, e.y * fb_h / e.screen_h);

        if (e.finger == g_swallow_finger) {
            if (e.kind == TouchKind::Up) g_swallow_finger = -1;
            continue;
        }

        if (!g_menu_open) {
            if (e.kind != TouchKind::Down) continue;
            const float dx = p.x - g_last_tap_pos.x, dy = p.y - g_last_tap_pos.y;
            if (g_last_tap_ms != 0 && e.time_ms - g_last_tap_ms <= kDoubleTapMs &&
                dx * dx + dy * dy <= near_px * near_px) {
                g_menu_open = true;
                g_menu_min = g_menu_max = ImVec2(0, 0);
                g_swallow_finger = e.finger;
                g_last_tap_ms = 0;
            } else {
                g_last_tap_ms = e.time_ms;
                g_last_tap_pos = p;
            }
            continue;
        }

        switch (e.kind) {
            case TouchKind::Down:
                if (g_tracked_finger != -1) break;  // ignore extra fingers
                if (!inside_menu(p)) {
                    close_menu();
                    g_swallow_finger = e.finger;
                    break;
                }
                g_tracked_finger = e.finger;
                io.AddMouseSourceEvent(ImGuiMouseSource_TouchScreen);
                io.AddMousePosEvent(p.x, p.y);
                io.AddMouseButtonEvent(0, true);
                break;
            case TouchKind::Move:
                if (e.finger == g_tracked_finger) {
                    io.AddMouseSourceEvent(ImGuiMouseSource_TouchScreen);
                    io.AddMousePosEvent(p.x, p.y);
                }
                break;
            case TouchKind::Up:
                if (e.finger == g_tracked_finger) {
                    io.AddMouseSourceEvent(ImGuiMouseSource_TouchScreen);
                    io.AddMousePosEvent(p.x, p.y);
                    io.AddMouseButtonEvent(0, false);
                    io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
                    g_tracked_finger = -1;
                }
                break;
        }
    }
}

// ---------------------------------------------------------------- widgets

ImU32 u32(const ImVec4 &c, float alpha_mul = 1.0f) {
    return ImGui::GetColorU32(ImVec4(c.x, c.y, c.z, c.w * alpha_mul));
}

struct Card {
    ImDrawList *dl;
    float pad;
    float top;
};

Card begin_card(const char *title) {
    Card card{ImGui::GetWindowDrawList(), ImGui::GetStyle().WindowPadding.x * 0.8f, 0.0f};
    ImGui::PushStyleColor(ImGuiCol_Text, col::kTextDim);
    ImGui::TextUnformatted(title);
    ImGui::PopStyleColor();
    card.top = ImGui::GetCursorScreenPos().y;
    card.dl->ChannelsSplit(2);
    card.dl->ChannelsSetCurrent(1);
    ImGui::Dummy(ImVec2(0, card.pad * 0.5f));
    ImGui::Indent(card.pad);
    ImGui::BeginGroup();
    return card;
}

void end_card(const Card &card) {
    ImGui::EndGroup();
    ImGui::Unindent(card.pad);
    ImGui::Dummy(ImVec2(0, card.pad * 0.5f));
    const float x0 = ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x;
    const float x1 = ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x;
    const float y1 = ImGui::GetCursorScreenPos().y - ImGui::GetStyle().ItemSpacing.y;
    card.dl->ChannelsSetCurrent(0);
    const float rounding = ImGui::GetStyle().FrameRounding * 1.4f;
    card.dl->AddRectFilled(ImVec2(x0, card.top), ImVec2(x1, y1), ImGui::GetColorU32(col::kCard), rounding);
    card.dl->AddRect(ImVec2(x0, card.top), ImVec2(x1, y1), ImGui::GetColorU32(col::kCardBorder), rounding);
    card.dl->ChannelsMerge();
    ImGui::Dummy(ImVec2(0, ImGui::GetStyle().ItemSpacing.y * 0.5f));
}

float content_width(const Card &card) { return ImGui::GetContentRegionAvail().x - card.pad; }

void toggle_row(const Card &card, const char *id, const char *label, std::atomic<bool> &value) {
    const float w = content_width(card);
    const float h = ImGui::GetFrameHeight() * 1.2f;
    const ImVec2 p = ImGui::GetCursorScreenPos();
    if (ImGui::InvisibleButton(id, ImVec2(w, h))) value.store(!value.load());
    const bool on = value.load();

    ImGuiStorage *st = ImGui::GetStateStorage();
    float *anim = st->GetFloatRef(ImGui::GetID(id), on ? 1.0f : 0.0f);
    const float target = on ? 1.0f : 0.0f;
    *anim += (target - *anim) * std::min(1.0f, ImGui::GetIO().DeltaTime * 14.0f);

    ImDrawList *dl = ImGui::GetWindowDrawList();
    const float fs = ImGui::GetFontSize();
    dl->AddText(ImVec2(p.x, p.y + (h - fs) * 0.5f), u32(col::kText), label);

    const float sh = h * 0.72f, sw = sh * 1.8f;
    const ImVec2 a(p.x + w - sw, p.y + (h - sh) * 0.5f), b(a.x + sw, a.y + sh);
    const ImVec4 off = ImGui::ColorConvertU32ToFloat4(col::kSwitchOff);
    const ImVec4 mix(off.x + (col::kAccent.x - off.x) * *anim, off.y + (col::kAccent.y - off.y) * *anim,
                     off.z + (col::kAccent.z - off.z) * *anim, 1.0f);
    dl->AddRectFilled(a, b, ImGui::GetColorU32(mix), sh * 0.5f);
    const float r = sh * 0.5f - sh * 0.12f;
    const float cx = a.x + sh * 0.5f + (sw - sh) * *anim;
    dl->AddCircleFilled(ImVec2(cx, a.y + sh * 0.5f), r, ImGui::GetColorU32(col::kKnob), 32);
}

void multiplier_row(const Card &card, const char *id, const char *label, std::atomic<int> &value, int hi) {
    int v = std::clamp(value.load(), kMulMin, hi);
    const float w = content_width(card);
    ImGui::PushID(id);

    const ImVec2 p = ImGui::GetCursorScreenPos();
    char buf[16];
    std::snprintf(buf, sizeof(buf), "x%d", v);
    ImGui::TextUnformatted(label);
    const float tw = ImGui::CalcTextSize(buf).x;
    ImGui::GetWindowDrawList()->AddText(ImVec2(p.x + w - tw, p.y),
                                        u32(v > 1 ? col::kAccentHover : col::kTextDim), buf);

    const float bs = ImGui::GetFrameHeight() * 1.15f;
    const float sp = ImGui::GetStyle().ItemSpacing.x;
    if (ImGui::Button("-", ImVec2(bs, bs))) --v;
    ImGui::SameLine(0, sp);
    ImGui::SetNextItemWidth(w - 2 * bs - 2 * sp);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(ImGui::GetStyle().FramePadding.x, (bs - ImGui::GetFontSize()) * 0.5f));
    ImGui::SliderInt("##v", &v, kMulMin, hi, "", ImGuiSliderFlags_AlwaysClamp);
    ImGui::PopStyleVar();
    ImGui::SameLine(0, sp);
    if (ImGui::Button("+", ImVec2(bs, bs))) ++v;

    value.store(std::clamp(v, kMulMin, hi));
    ImGui::PopID();
}

void time_row(const Card &card) {
    const float w = content_width(card);
    const float sp = ImGui::GetStyle().ItemSpacing.x;
    const float bw = (w - 3 * sp) / 4.0f;
    const float bh = ImGui::GetFrameHeight() * 1.2f;
    const int cur = g_settings.time_mul.load();
    static const char *const kLabels[] = {"x1", "x2", "x3", "x4"};
    for (int i = 0; i < 4; ++i) {
        const bool sel = cur == i + 1;
        if (sel) {
            ImGui::PushStyleColor(ImGuiCol_Button, col::kAccent);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, col::kAccentHover);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, col::kAccentActive);
        }
        if (ImGui::Button(kLabels[i], ImVec2(bw, bh))) g_settings.time_mul.store(i + 1);
        if (sel) ImGui::PopStyleColor(3);
        if (i < 3) ImGui::SameLine(0, sp);
    }
}

bool action_button(const Card &card, const char *label, const ImVec4 &c, const ImVec4 &hover, bool enabled) {
    const float w = content_width(card);
    const float h = ImGui::GetFrameHeight() * 1.35f;
    ImGui::PushStyleColor(ImGuiCol_Button, enabled ? c : col::kFrame);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, enabled ? hover : col::kFrame);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, enabled ? col::kAccentActive : col::kFrame);
    ImGui::PushStyleColor(ImGuiCol_Text, enabled ? col::kText : col::kTextDim);
    const bool pressed = ImGui::Button(label, ImVec2(w, h));
    ImGui::PopStyleColor(4);
    return pressed && enabled;
}

void status_chip(const char *text, const ImVec4 &c, float right_x, float center_y) {
    ImDrawList *dl = ImGui::GetWindowDrawList();
    const ImVec2 ts = ImGui::CalcTextSize(text);
    const float px = ts.y * 0.6f, py = ts.y * 0.25f;
    const ImVec2 a(right_x - ts.x - 2 * px, center_y - ts.y * 0.5f - py);
    const ImVec2 b(right_x, center_y + ts.y * 0.5f + py);
    dl->AddRectFilled(a, b, u32(c, 0.18f), (b.y - a.y) * 0.5f);
    dl->AddText(ImVec2(a.x + px, a.y + py), u32(c), text);
}

// ---------------------------------------------------------------- menu

void draw_menu(float fb_w, float fb_h) {
    const float dt = ImGui::GetIO().DeltaTime;
    g_menu_alpha = std::clamp(g_menu_alpha + (g_menu_open ? dt : -dt) * 7.0f, 0.0f, 1.0f);
    if (g_menu_alpha <= 0.0f) return;

    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(fb_w, fb_h),
                                                  ImGui::GetColorU32(col::kBackdrop, g_menu_alpha));

    const float width = std::min(fb_w, fb_h) * 0.88f;
    ImGui::SetNextWindowPos(ImVec2(fb_w * 0.5f, fb_h * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(width, 0), ImVec2(width, fb_h * 0.96f));
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, g_menu_alpha);
    const ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                   ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize |
                                   ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    ImGui::Begin("##ms_menu", nullptr, flags);
    ImGui::PushFont(g_font);

    // Header
    const bool ready = g_status.hooks_ready.load();
    const bool in_battle = g_status.in_battle.load();
    ImGui::PushFont(g_font_title);
    const ImVec2 hp = ImGui::GetCursorScreenPos();
    ImGui::TextUnformatted("Magic Survival");
    const float title_h = ImGui::GetItemRectSize().y;
    ImGui::PopFont();
    const float right = ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x;
    if (!ready) {
        status_chip("загрузка", col::kTextDim, right, hp.y + title_h * 0.5f);
    } else if (in_battle) {
        status_chip("в бою", col::kGood, right, hp.y + title_h * 0.5f);
    } else {
        status_chip("не в бою", col::kTextDim, right, hp.y + title_h * 0.5f);
    }
    ImGui::Dummy(ImVec2(0, ImGui::GetStyle().ItemSpacing.y * 0.3f));

    {
        Card c = begin_card("ВЫЖИВАНИЕ");
        toggle_row(c, "##god", "Год мод", g_settings.god_mode);
        toggle_row(c, "##infhp", "Бесконечное HP", g_settings.infinite_hp);
        end_card(c);
    }
    {
        Card c = begin_card("МНОЖИТЕЛИ");
        multiplier_row(c, "atk", "Сила атаки", g_settings.attack_mul, kMulMax);
        multiplier_row(c, "pick", "Радиус подбора маны", g_settings.pickup_radius_mul, kMulMax);
        multiplier_row(c, "mana", "Мана за подбор", g_settings.mana_gain_mul, kMulMax);
        end_card(c);
    }
    {
        Card c = begin_card("СКОРОСТЬ ВРЕМЕНИ");
        time_row(c);
        end_card(c);
    }
    {
        Card c = begin_card("ДЕЙСТВИЯ");
        const bool can = ready && in_battle;
        if (action_button(c, "Собрать всю ману", col::kAccent, col::kAccentHover, can)) {
            g_settings.req_collect_mana.store(true);
        }
        if (action_button(c, "Убить всех (и боссов)", col::kDanger, col::kDangerHover, can)) {
            g_settings.req_kill_all.store(true);
        }
        if (action_button(c, "Пройти локацию", col::kGood, col::kGood, can)) {
            g_settings.req_clear_stage.store(true);
        }
        const auto result = static_cast<ActionResult>(g_status.last_action.load());
        char line[64] = "";
        switch (result) {
            case ActionResult::Done:
                std::snprintf(line, sizeof(line), "Готово. Убито за последний раз: %d",
                              g_status.last_kill_count.load());
                break;
            case ActionResult::NotInBattle:
                std::snprintf(line, sizeof(line), "Действия работают только в бою");
                break;
            case ActionResult::Failed:
                std::snprintf(line, sizeof(line), "Не получилось, смотри logcat MSCheat");
                break;
            case ActionResult::None:
                break;
        }
        if (line[0]) {
            ImGui::PushStyleColor(ImGuiCol_Text, col::kTextDim);
            ImGui::TextWrapped("%s", line);
            ImGui::PopStyleColor();
        }
        end_card(c);
    }

    ImGui::PushStyleColor(ImGuiCol_Text, col::kTextDim);
    const char *hint = "Нажми вне меню, чтобы закрыть";
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(hint).x) * 0.5f);
    ImGui::TextUnformatted(hint);
    ImGui::PopStyleColor();

    ImGui::PopFont();
    g_menu_min = ImGui::GetWindowPos();
    g_menu_max = ImVec2(g_menu_min.x + ImGui::GetWindowWidth(), g_menu_min.y + ImGui::GetWindowHeight());
    ImGui::End();
    ImGui::PopStyleVar();
}

// ---------------------------------------------------------------- frame

void draw_frame(EGLDisplay display, EGLSurface surface) {
    if (!g_ready.load(std::memory_order_acquire)) return;
    const EGLContext ctx = eglGetCurrentContext();
    if (ctx == EGL_NO_CONTEXT || eglGetCurrentSurface(EGL_DRAW) != surface) return;
    EGLint w = 0, h = 0;
    if (!eglQuerySurface(display, surface, EGL_WIDTH, &w) || !eglQuerySurface(display, surface, EGL_HEIGHT, &h)) return;
    if (w <= 0 || h <= 0 || w > 16384 || h > 16384) return;

    if (!g_imgui_ready) {
        if (!init_imgui(w, h)) return;
        g_imgui_ready = true;
    }
    if (ctx != g_gl_context) {
        if (g_gl_context != EGL_NO_CONTEXT) {
            MS_LOGW("GL context changed, recreating renderer objects");
            gles3::abandon();
        }
        g_gl_context = ctx;
        g_gl_ok = gles3::create();
        if (!g_gl_ok) MS_LOGE("renderer init failed for this context");
    }
    if (!g_gl_ok) return;

    const float fw = static_cast<float>(w), fh = static_cast<float>(h);
    process_touches(fw, fh);
    if (!g_menu_open && g_menu_alpha <= 0.0f) {
        g_last_frame_ms = 0;
        return;
    }

    ImGuiIO &io = ImGui::GetIO();
    const int64_t t = now_ms();
    io.DeltaTime = g_last_frame_ms ? std::clamp(static_cast<float>(t - g_last_frame_ms) / 1000.0f, 0.001f, 0.1f)
                                   : 1.0f / 60.0f;
    g_last_frame_ms = t;
    io.DisplaySize = ImVec2(fw, fh);
    io.DisplayFramebufferScale = ImVec2(1, 1);

    ImGui::NewFrame();
    draw_menu(fw, fh);
    ImGui::Render();
    gles3::render(ImGui::GetDrawData(), w, h);
}

// ---------------------------------------------------------------- EGL hooks

using SwapFn = EGLBoolean (*)(EGLDisplay, EGLSurface);
using SwapDamageFn = EGLBoolean (*)(EGLDisplay, EGLSurface, EGLint *, EGLint);

SwapFn o_swap = nullptr;
SwapDamageFn o_swap_damage = nullptr;
thread_local bool t_in_swap = false;

EGLBoolean hk_swap(EGLDisplay d, EGLSurface s) {
    auto o = o_swap;
    if (!o) return EGL_FALSE;
    if (t_in_swap) return o(d, s);
    t_in_swap = true;
    draw_frame(d, s);
    const EGLBoolean r = o(d, s);
    t_in_swap = false;
    return r;
}

EGLBoolean hk_swap_damage(EGLDisplay d, EGLSurface s, EGLint *rects, EGLint n) {
    auto o = o_swap_damage;
    if (!o) return EGL_FALSE;
    if (t_in_swap) return o(d, s, rects, n);
    t_in_swap = true;
    draw_frame(d, s);
    const EGLBoolean r = o(d, s, rects, n);
    t_in_swap = false;
    return r;
}

void *egl_symbol(void *handle, const char *name) {
    void *p = xdl_sym(handle, name, nullptr);
    if (!p) return nullptr;
    Dl_info info{};
    if (!dladdr(p, &info) || !info.dli_fname || !std::strstr(info.dli_fname, "libEGL")) {
        MS_LOGE("%s resolved outside libEGL", name);
        return nullptr;
    }
    return p;
}

}  // namespace

void push_touches(const TouchEvent *events, int count) {
    std::lock_guard<std::mutex> lock(g_queue_mutex);
    for (int i = 0; i < count; ++i) {
        if (g_queue.size() >= kQueueMax) g_queue.pop_front();
        g_queue.push_back(events[i]);
    }
}

size_t fill_hook_specs(hook::Spec *out, size_t capacity) {
    void *egl = xdl_open("libEGL.so", XDL_DEFAULT);
    if (!egl) {
        MS_LOGE("libEGL.so not loaded");
        return 0;
    }
    void *swap = egl_symbol(egl, "eglSwapBuffers");
    void *swap_damage = egl_symbol(egl, "eglSwapBuffersWithDamageKHR");
    xdl_close(egl);
    if (!swap || capacity < 2) return 0;

    size_t n = 0;
    out[n++] = {"eglSwapBuffers", swap, reinterpret_cast<void *>(hk_swap), reinterpret_cast<void **>(&o_swap)};
    if (swap_damage) {
        out[n++] = {"eglSwapBuffersWithDamageKHR", swap_damage, reinterpret_cast<void *>(hk_swap_damage),
                    reinterpret_cast<void **>(&o_swap_damage)};
    }
    return n;
}

void set_ready() { g_ready.store(true, std::memory_order_release); }

}  // namespace ms::overlay
