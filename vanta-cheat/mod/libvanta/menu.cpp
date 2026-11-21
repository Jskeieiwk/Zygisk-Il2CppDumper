// menu.cpp — рендер меню и плавающего watermark @Cloud_Crack
#include "menu.h"
#include "state.h"
#include "imgui.h"

#include <stdio.h>
#include <string.h>

namespace vanta {

namespace {

// небольшая ТОГГЛ-кнопка в стиле macOS (round pill)
bool pill_toggle(const char* label, bool* v) {
    ImGui::PushID(label);
    ImVec2 p = ImGui::GetCursorScreenPos();
    const float h = ImGui::GetFrameHeight() * 0.9f;
    const float w = h * 1.75f;
    ImGui::InvisibleButton(label, ImVec2(w, h));
    bool hovered = ImGui::IsItemHovered();
    bool clicked = ImGui::IsItemClicked();
    if (clicked) *v = !*v;
    ImDrawList* d = ImGui::GetWindowDrawList();
    const ImU32 off = IM_COL32(50, 55, 68, 255);
    const ImU32 on  = IM_COL32(255, 60, 60, 255);
    const ImU32 knob = IM_COL32(245, 247, 253, 255);
    d->AddRectFilled(p, ImVec2(p.x + w, p.y + h), *v ? on : off, h * 0.5f);
    float kx = *v ? (p.x + w - h * 0.5f) : (p.x + h * 0.5f);
    d->AddCircleFilled(ImVec2(kx, p.y + h * 0.5f), h * 0.42f, knob);
    ImGui::PopID();
    return clicked;
}

void section_header(const char* text) {
    ImGui::Dummy(ImVec2(0, 4));
    ImDrawList* d = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    d->AddCircleFilled(ImVec2(p.x + 6, p.y + 10), 3.5f, IM_COL32(255, 60, 60, 255));
    ImGui::Dummy(ImVec2(16, 0)); ImGui::SameLine(0, 10);
    ImGui::TextColored(ImVec4(0.95f, 0.95f, 0.95f, 1), "%s", text);
    ImGui::Dummy(ImVec2(0, 4));
}

void row_toggle(const char* label, bool* v) {
    float row_h = ImGui::GetFrameHeight() + 6;
    ImGui::BeginGroup();
    ImVec2 start = ImGui::GetCursorScreenPos();
    ImGui::Dummy(ImVec2(0, 6));
    ImGui::TextUnformatted(label);
    ImGui::SameLine();
    float remaining = ImGui::GetContentRegionAvail().x;
    ImGui::Dummy(ImVec2(remaining - ImGui::GetFrameHeight() * 1.75f - 6, 0));
    ImGui::SameLine();
    pill_toggle(label, v);
    ImGui::EndGroup();
    (void)start; (void)row_h;
}

void row_slider_f(const char* label, float* v, float lo, float hi, const char* fmt = "%.2f") {
    ImGui::TextUnformatted(label);
    ImGui::PushItemWidth(-FLT_MIN);
    ImGui::PushID(label);
    ImGui::SliderFloat("##s", v, lo, hi, fmt);
    ImGui::PopID();
    ImGui::PopItemWidth();
}
void row_slider_i(const char* label, int* v, int lo, int hi) {
    ImGui::TextUnformatted(label);
    ImGui::PushItemWidth(-FLT_MIN);
    ImGui::PushID(label);
    ImGui::SliderInt("##s", v, lo, hi);
    ImGui::PopID();
    ImGui::PopItemWidth();
}

bool side_tab(const char* icon, const char* label, int idx, int* current) {
    ImGui::PushID(idx);
    const bool sel = (*current == idx);
    ImVec4 bg = sel ? ImVec4(0.14f, 0.16f, 0.22f, 1) : ImVec4(0,0,0,0);
    ImGui::PushStyleColor(ImGuiCol_Button, bg);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.11f,0.13f,0.17f,1));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f,0.17f,0.23f,1));
    char buf[64]; snprintf(buf, sizeof(buf), "%s  %s", icon, label);
    if (ImGui::Button(buf, ImVec2(-FLT_MIN, 38))) {
        *current = idx;
    }
    if (sel) {
        ImVec2 p = ImGui::GetItemRectMin();
        ImVec2 q = ImGui::GetItemRectMax();
        ImDrawList* d = ImGui::GetWindowDrawList();
        d->AddRectFilled(ImVec2(p.x, p.y + 6), ImVec2(p.x + 3, q.y - 6),
                         IM_COL32(255, 60, 60, 255), 2);
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();
    return sel;
}

void draw_tab_combat() {
    section_header("Aimbot");
    row_toggle("включить",         &g.aim_enabled);
    row_toggle("только при огне",  &g.aim_fire_only);
    row_toggle("в голову",         &g.aim_head);
    row_toggle("игнор тиммейтов",  &g.aim_ignore_team);
    row_toggle("только видимые",   &g.aim_visible);
    ImGui::Dummy(ImVec2(0, 4));
    row_slider_f("FOV (px)",       &g.aim_fov, 30.f, 600.f, "%.0f");
    row_slider_f("плавность",      &g.aim_smooth, 0.05f, 1.0f);
    row_slider_f("мёртвая зона",   &g.aim_dead, 0.f, 20.f, "%.1f");
}
void draw_tab_visuals() {
    section_header("ESP");
    row_toggle("рамки",     &g.esp_box);
    row_toggle("snap-линии",&g.esp_line);
    row_toggle("ник",       &g.esp_name);
    row_toggle("HP-бар",    &g.esp_hp);
    row_toggle("дистанция", &g.esp_dist);
    row_toggle("скелет",    &g.esp_skeleton);
    ImGui::Dummy(ImVec2(0, 4));
    int d = (int)g.esp_max_distance;
    row_slider_i("макс. дистанция (м)", &d, 20, 600);
    g.esp_max_distance = (float)d;
}
void draw_tab_utility() {
    section_header("Utility");
    row_toggle("no recoil", &g.util_no_recoil);
    row_toggle("no spread", &g.util_no_spread);
    row_toggle("fast loot", &g.util_fast_loot);
    row_toggle("auto heal", &g.util_auto_heal);
}
void draw_tab_player() {
    section_header("Player");
    row_toggle("god mode",  &g.player_god);
    row_toggle("fly",       &g.player_fly);
    row_toggle("speed",     &g.player_speed);
    row_slider_f("speed множитель", &g.player_speed_mul, 1.f, 5.f, "%.2fx");
}
void draw_tab_skins() {
    section_header("Skins");
    ImGui::TextDisabled("(заглушка — заполним офсетами при необходимости)");
}
void draw_tab_misc() {
    section_header("Misc");
    row_toggle("показ FPS",  &g.show_fps);
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::TextDisabled("vanta © @Cloud_Crack · read-only external");
}

} // anon

// ---------- плавающая кнопка открытия ----------
void draw_watermark_button() {
    if (g.menu_open.load()) return;
    ImGuiIO& io = ImGui::GetIO();
    const char* wm = "@Cloud_Crack";
    ImVec2 ts = ImGui::CalcTextSize(wm);
    float pad = 10.f;
    ImVec2 pos(g.wm_x * io.DisplaySize.x, g.wm_y * io.DisplaySize.y);
    ImVec2 size(ts.x + pad * 2, ts.y + pad * 1.5f);

    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(pad, pad * 0.6f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 14.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.035f, 0.040f, 0.055f, 0.82f));
    ImGui::PushStyleColor(ImGuiCol_Border,   ImVec4(1.0f, 0.18f, 0.18f, 0.9f));
    ImGui::Begin("##vanta_wm", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.22f, 0.22f, 1));
    ImGui::TextUnformatted(wm);
    ImGui::PopStyleColor();

    // клик на самой кнопке открывает меню
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0)) g.menu_open = true;

    // drag — перемещение (только если тап-протянули)
    if (ImGui::IsWindowHovered() && ImGui::IsMouseDragging(0, 12.f)) {
        ImVec2 delta = io.MouseDelta;
        g.wm_x += delta.x / io.DisplaySize.x;
        g.wm_y += delta.y / io.DisplaySize.y;
    }
    ImGui::End();
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);
}

// ---------- само меню ----------
void draw_menu() {
    if (!g.menu_open.load()) return;
    ImGuiIO& io = ImGui::GetIO();

    ImVec2 pos(g.menu_x * io.DisplaySize.x, g.menu_y * io.DisplaySize.y);
    ImVec2 sz (g.menu_w * io.DisplaySize.x, g.menu_h * io.DisplaySize.y);
    ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(sz, ImGuiCond_FirstUseEver);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("##vanta_menu", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
    ImGui::PopStyleVar();

    float full_w = ImGui::GetContentRegionAvail().x;
    float full_h = ImGui::GetContentRegionAvail().y;

    // -------- TOP BAR: close (umbrella) + search + watermark --------
    ImGui::BeginChild("##top", ImVec2(full_w, 46), false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Dummy(ImVec2(6, 0)); ImGui::SameLine(0, 0);

    // UMBRELLA кнопка (close) — слева сверху
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1,0.18f,0.18f,0.15f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(1,0.18f,0.18f,0.30f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 18);
        if (ImGui::Button("☂", ImVec2(36, 36))) g.menu_open = false;
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
    }
    ImGui::SameLine(0, 10);

    // searchbox (визуальный, без логики пока)
    static char search[64] = "";
    ImGui::SetNextItemWidth(200);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.08f,0.09f,0.12f,1));
    ImGui::InputTextWithHint("##search", "search", search, sizeof(search));
    ImGui::PopStyleColor();
    ImGui::SameLine();
    float right_w = ImGui::CalcTextSize("@Cloud_Crack").x + 16;
    ImGui::SameLine(full_w - right_w);
    ImGui::TextColored(ImVec4(1.0f,0.22f,0.22f,1), "@Cloud_Crack");
    ImGui::EndChild();

    ImDrawList* dw = ImGui::GetWindowDrawList();
    ImVec2 win_tl = ImGui::GetWindowPos();
    dw->AddLine(ImVec2(win_tl.x, win_tl.y + 46),
                ImVec2(win_tl.x + full_w, win_tl.y + 46),
                IM_COL32(32,38,48,255));

    // -------- LEFT SIDEBAR + RIGHT CONTENT --------
    float side_w = 210.f;
    ImGui::BeginChild("##side", ImVec2(side_w, full_h - 46), false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Dummy(ImVec2(0, 6));
    side_tab("⌖", "Combat",  0, &g.tab_main);
    side_tab("◉", "Visuals", 1, &g.tab_main);
    side_tab("⚙", "Utility", 2, &g.tab_main);
    side_tab("☺", "Player",  3, &g.tab_main);
    side_tab("✦", "Skins",   4, &g.tab_main);
    side_tab("⋯", "Misc",    5, &g.tab_main);
    ImGui::EndChild();

    ImGui::SameLine(0, 0);
    dw->AddLine(ImVec2(win_tl.x + side_w, win_tl.y + 46),
                ImVec2(win_tl.x + side_w, win_tl.y + full_h),
                IM_COL32(32,38,48,255));

    ImGui::BeginChild("##content", ImVec2(0, full_h - 46), false, ImGuiWindowFlags_NoSavedSettings);
    ImGui::Dummy(ImVec2(0, 4));
    ImGui::Indent(14);
    switch (g.tab_main) {
        case 0: draw_tab_combat();  break;
        case 1: draw_tab_visuals(); break;
        case 2: draw_tab_utility(); break;
        case 3: draw_tab_player();  break;
        case 4: draw_tab_skins();   break;
        case 5: draw_tab_misc();    break;
    }
    ImGui::Unindent(14);
    ImGui::EndChild();

    // сохраняем позицию/размер
    ImVec2 cur_pos = ImGui::GetWindowPos();
    ImVec2 cur_sz  = ImGui::GetWindowSize();
    g.menu_x = cur_pos.x / io.DisplaySize.x;
    g.menu_y = cur_pos.y / io.DisplaySize.y;
    g.menu_w = cur_sz.x  / io.DisplaySize.x;
    g.menu_h = cur_sz.y  / io.DisplaySize.y;

    ImGui::End();
}

} // namespace vanta
