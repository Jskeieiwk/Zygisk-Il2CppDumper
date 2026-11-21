// esp.cpp — рисование ESP через ImGui background draw list
#include "esp.h"
#include "state.h"
#include "game.h"
#include "imgui.h"

#include <math.h>
#include <vector>
#include <stdio.h>

namespace vanta {

static bool world_to_screen(const Vec3& w, const CamSnap& c, int sw, int sh,
                            float& outX, float& outY) {
    float dx = w.x - c.pos.x, dy = w.y - c.pos.y, dz = w.z - c.pos.z;
    float fl = sqrtf(c.forward.x * c.forward.x + c.forward.y * c.forward.y + c.forward.z * c.forward.z);
    if (fl < 1e-5f) return false;
    float fx = c.forward.x / fl, fy = c.forward.y / fl, fz = c.forward.z / fl;
    float rx = fz, ry = 0, rz = -fx;
    float rl = sqrtf(rx*rx + rz*rz);
    if (rl < 1e-5f) return false;
    rx /= rl; rz /= rl;
    float ux = ry * fz - rz * fy;
    float uy = rz * fx - rx * fz;
    float uz = rx * fy - ry * fx;

    float dFwd   = dx * fx + dy * fy + dz * fz;
    if (dFwd < 0.1f) return false;
    float dRight = dx * rx + dy * ry + dz * rz;
    float dUp    = dx * ux + dy * uy + dz * uz;

    float fovRad = c.fov > 1.f ? c.fov * 3.14159265f / 180.f : 60.f * 3.14159265f / 180.f;
    float tanHalf = tanf(fovRad * 0.5f);
    float aspect = (float)sw / (sh > 0 ? sh : 1);
    float ndcX = dRight / (dFwd * tanHalf * aspect);
    float ndcY = dUp / (dFwd * tanHalf);
    outX = (ndcX * 0.5f + 0.5f) * sw;
    outY = (1.f - (ndcY * 0.5f + 0.5f)) * sh;
    return true;
}

void draw_esp_overlay() {
    static std::vector<PlayerSnap> pls;
    game_copy_players(pls);
    const CamSnap& cam = game_camera();
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    ImGuiIO& io = ImGui::GetIO();
    int sw = cam.screen_w > 0 ? cam.screen_w : (int)io.DisplaySize.x;
    int sh = cam.screen_h > 0 ? cam.screen_h : (int)io.DisplaySize.y;
    if (sw <= 0 || sh <= 0) return;
    float cx = io.DisplaySize.x * 0.5f;
    float cy = io.DisplaySize.y * 0.5f;

    if (g.aim_enabled) {
        dl->AddCircle(ImVec2(cx, cy), g.aim_fov, IM_COL32(255, 60, 60, 120), 64, 1.2f);
    }

    for (const auto& p : pls) {
        if (!p.alive || p.local) continue;
        if (p.distance > g.esp_max_distance) continue;

        float fx, fy, hx, hy;
        bool okF = world_to_screen(p.pos,  cam, sw, sh, fx, fy);
        bool okH = world_to_screen(p.head, cam, sw, sh, hx, hy);
        if (!okF && !okH) continue;
        float footX = okF ? fx : hx;
        float footY = okF ? fy : hy + 100;
        float headX = okH ? hx : footX;
        float headY = okH ? hy : footY - 100;
        float h = fabsf(footY - headY); if (h < 10) h = 60;
        float w = h * 0.45f;
        float left = headX - w / 2, right = headX + w / 2;
        float top = headY, bottom = footY;

        ImU32 col = p.teammate ? g.color_team : g.color_enemy;

        if (g.esp_box) {
            dl->AddRect(ImVec2(left, top), ImVec2(right, bottom), col, 2.f, 0, 1.5f);
        }
        if (g.esp_hp) {
            float frac = p.max_hp > 0 ? fmaxf(0.f, fminf(1.f, p.hp / p.max_hp)) : 0.f;
            ImU32 hpc = (frac > 0.6f) ? IM_COL32(0,230,118,255)
                     : (frac > 0.3f) ? IM_COL32(255,193,7,255)
                                      : IM_COL32(255,23,68,255);
            float xleft = left - 6;
            dl->AddRectFilled(ImVec2(xleft - 2, top), ImVec2(xleft + 2, bottom),
                              IM_COL32(0,0,0,110), 1.f);
            dl->AddRectFilled(ImVec2(xleft - 2, bottom - (bottom - top) * frac),
                              ImVec2(xleft + 2, bottom), hpc, 1.f);
        }
        if (g.esp_name) {
            const char* nick = p.nick[0] ? p.nick : "unknown";
            ImVec2 ts = ImGui::CalcTextSize(nick);
            ImVec2 pos(headX - ts.x / 2, top - ts.y - 4);
            dl->AddRectFilled(ImVec2(pos.x - 4, pos.y - 2),
                              ImVec2(pos.x + ts.x + 4, pos.y + ts.y + 2),
                              IM_COL32(10, 12, 18, 180), 4.f);
            dl->AddText(pos, g.color_text, nick);
        }
        if (g.esp_dist) {
            char buf[32]; snprintf(buf, sizeof(buf), "%dм", (int)p.distance);
            ImVec2 ts = ImGui::CalcTextSize(buf);
            dl->AddText(ImVec2(headX - ts.x / 2, bottom + 4), IM_COL32(200,200,200,220), buf);
        }
        if (g.esp_line) {
            dl->AddLine(ImVec2(cx, io.DisplaySize.y), ImVec2(headX, (headY + bottom) * 0.5f),
                        col, 1.2f);
        }
    }
    if (g.show_fps) {
        char buf[48]; snprintf(buf, sizeof(buf), "%.0f fps · %d игроков", io.Framerate, (int)pls.size());
        dl->AddText(ImVec2(io.DisplaySize.x - 220, 16), IM_COL32(255,255,255,210), buf);
    }
}

} // namespace vanta
