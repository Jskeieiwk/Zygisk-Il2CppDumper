// renderer.cpp — обёртка над ImGui + GL ES3 backend
#include "renderer.h"
#include "menu.h"
#include "esp.h"
#include "input.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLES3/gl3.h>
#include <android/log.h>

#define LOGR(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-render", fmt, ##__VA_ARGS__)

namespace vanta {

static bool g_initialized = false;
static int  g_last_w = 0, g_last_h = 0;

static void apply_theme() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowRounding    = 12.f;
    s.FrameRounding     = 8.f;
    s.GrabRounding      = 8.f;
    s.PopupRounding     = 10.f;
    s.ChildRounding     = 10.f;
    s.ScrollbarRounding = 10.f;
    s.TabRounding       = 8.f;
    s.ItemSpacing       = ImVec2(10, 8);
    s.FramePadding      = ImVec2(10, 6);
    s.WindowPadding     = ImVec2(14, 14);
    s.ScrollbarSize     = 8.f;
    s.GrabMinSize       = 14.f;
    s.WindowBorderSize  = 1.0f;
    s.FrameBorderSize   = 0.0f;
    s.PopupBorderSize   = 1.0f;

    ImVec4* c = s.Colors;
    const ImVec4 bg_deep   = ImVec4(0.035f, 0.040f, 0.055f, 0.96f);
    const ImVec4 bg_panel  = ImVec4(0.060f, 0.070f, 0.090f, 1.00f);
    const ImVec4 bg_card   = ImVec4(0.085f, 0.100f, 0.125f, 1.00f);
    const ImVec4 stroke    = ImVec4(0.130f, 0.155f, 0.190f, 1.00f);
    const ImVec4 accent    = ImVec4(1.000f, 0.180f, 0.180f, 1.00f);    // красный
    const ImVec4 accent_hv = ImVec4(1.000f, 0.280f, 0.280f, 1.00f);
    const ImVec4 text      = ImVec4(0.950f, 0.957f, 0.973f, 1.00f);
    const ImVec4 text_dim  = ImVec4(0.603f, 0.640f, 0.698f, 1.00f);

    c[ImGuiCol_WindowBg]         = bg_deep;
    c[ImGuiCol_ChildBg]          = bg_panel;
    c[ImGuiCol_PopupBg]          = bg_panel;
    c[ImGuiCol_Border]           = stroke;
    c[ImGuiCol_BorderShadow]     = ImVec4(0,0,0,0);
    c[ImGuiCol_Text]             = text;
    c[ImGuiCol_TextDisabled]     = text_dim;
    c[ImGuiCol_FrameBg]          = bg_card;
    c[ImGuiCol_FrameBgHovered]   = ImVec4(0.11f,0.13f,0.17f,1);
    c[ImGuiCol_FrameBgActive]    = ImVec4(0.13f,0.15f,0.19f,1);
    c[ImGuiCol_TitleBg]          = bg_deep;
    c[ImGuiCol_TitleBgActive]    = bg_deep;
    c[ImGuiCol_TitleBgCollapsed] = bg_deep;
    c[ImGuiCol_ScrollbarBg]      = ImVec4(0,0,0,0);
    c[ImGuiCol_ScrollbarGrab]    = stroke;
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f,0.21f,0.26f,1);
    c[ImGuiCol_ScrollbarGrabActive]  = accent;
    c[ImGuiCol_CheckMark]        = text;
    c[ImGuiCol_SliderGrab]       = accent;
    c[ImGuiCol_SliderGrabActive] = accent_hv;
    c[ImGuiCol_Button]           = bg_card;
    c[ImGuiCol_ButtonHovered]    = ImVec4(0.12f,0.14f,0.18f,1);
    c[ImGuiCol_ButtonActive]     = accent;
    c[ImGuiCol_Header]           = bg_card;
    c[ImGuiCol_HeaderHovered]    = ImVec4(0.12f,0.14f,0.18f,1);
    c[ImGuiCol_HeaderActive]     = accent;
    c[ImGuiCol_Separator]        = stroke;
    c[ImGuiCol_SeparatorHovered] = accent;
    c[ImGuiCol_SeparatorActive]  = accent_hv;
    c[ImGuiCol_Tab]                 = bg_card;
    c[ImGuiCol_TabHovered]          = accent_hv;
    c[ImGuiCol_TabSelected]         = accent;
    c[ImGuiCol_TabDimmed]           = bg_card;
    c[ImGuiCol_TabDimmedSelected]   = accent;
}

bool renderer_init_if_needed(int fb_w, int fb_h) {
    if (!g_initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;
        io.LogFilename = nullptr;
        io.DisplaySize = ImVec2((float)fb_w, (float)fb_h);
        io.MouseDrawCursor = false;
        apply_theme();
        if (!ImGui_ImplOpenGL3_Init("#version 300 es")) {
            LOGR("ImGui_ImplOpenGL3_Init failed");
            return false;
        }
        g_initialized = true;
        LOGR("ImGui init %dx%d", fb_w, fb_h);
    }
    if (fb_w != g_last_w || fb_h != g_last_h) {
        g_last_w = fb_w; g_last_h = fb_h;
        ImGui::GetIO().DisplaySize = ImVec2((float)fb_w, (float)fb_h);
    }
    return true;
}

void renderer_new_frame(int fb_w, int fb_h) {
    ImGui_ImplOpenGL3_NewFrame();
    input_new_frame(fb_w, fb_h);  // пушим события и io.MousePos из тач-хука
    ImGui::NewFrame();
}

void renderer_draw() {
    draw_watermark_button();
    draw_menu();
    draw_esp_overlay();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void renderer_shutdown() {
    if (!g_initialized) return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    g_initialized = false;
}

} // namespace vanta
