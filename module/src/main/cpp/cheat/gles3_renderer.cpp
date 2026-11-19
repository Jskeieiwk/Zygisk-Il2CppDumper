#include "gles3_renderer.h"

#include <cstddef>
#include <cstdint>

#include <GLES3/gl3.h>

#include "imgui.h"
#include "ms_log.h"

namespace ms::gles3 {

namespace {

GLuint g_program = 0;
GLuint g_vao = 0;
GLuint g_vbo = 0;
GLuint g_ibo = 0;
GLuint g_font_tex = 0;
GLint g_loc_proj = -1;
GLint g_loc_tex = -1;

constexpr const char *kVertexShader = R"(#version 300 es
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec4 aCol;
uniform mat4 uProj;
out vec2 vUV;
out vec4 vCol;
void main() {
    vUV = aUV;
    vCol = aCol;
    gl_Position = uProj * vec4(aPos, 0.0, 1.0);
})";

constexpr const char *kFragmentShader = R"(#version 300 es
precision mediump float;
uniform sampler2D uTex;
in vec2 vUV;
in vec4 vCol;
layout(location = 0) out vec4 oCol;
void main() {
    oCol = vCol * texture(uTex, vUV);
})";

GLuint compile(GLenum type, const char *src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = GL_FALSE;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512] = {};
        glGetShaderInfoLog(s, sizeof(log) - 1, nullptr, log);
        MS_LOGE("shader compile failed: %s", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

struct SavedState {
    GLint program, active_texture, texture, sampler, array_buffer, vao, draw_fbo;
    GLint viewport[4], scissor[4];
    GLint blend_src_rgb, blend_dst_rgb, blend_src_a, blend_dst_a, blend_eq_rgb, blend_eq_a;
    GLboolean color_mask[4];
    GLboolean blend, cull, depth, stencil, scissor_test, discard, a2c, poly_offset;

    void save() {
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);
        glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
        glActiveTexture(GL_TEXTURE0);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture);
        glGetIntegerv(GL_SAMPLER_BINDING, &sampler);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &array_buffer);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw_fbo);
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetIntegerv(GL_SCISSOR_BOX, scissor);
        glGetIntegerv(GL_BLEND_SRC_RGB, &blend_src_rgb);
        glGetIntegerv(GL_BLEND_DST_RGB, &blend_dst_rgb);
        glGetIntegerv(GL_BLEND_SRC_ALPHA, &blend_src_a);
        glGetIntegerv(GL_BLEND_DST_ALPHA, &blend_dst_a);
        glGetIntegerv(GL_BLEND_EQUATION_RGB, &blend_eq_rgb);
        glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &blend_eq_a);
        glGetBooleanv(GL_COLOR_WRITEMASK, color_mask);
        blend = glIsEnabled(GL_BLEND);
        cull = glIsEnabled(GL_CULL_FACE);
        depth = glIsEnabled(GL_DEPTH_TEST);
        stencil = glIsEnabled(GL_STENCIL_TEST);
        scissor_test = glIsEnabled(GL_SCISSOR_TEST);
        discard = glIsEnabled(GL_RASTERIZER_DISCARD);
        a2c = glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
        poly_offset = glIsEnabled(GL_POLYGON_OFFSET_FILL);
    }

    static void set(GLenum cap, GLboolean on) { on ? glEnable(cap) : glDisable(cap); }

    void restore() const {
        glUseProgram(static_cast<GLuint>(program));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(texture));
        glBindSampler(0, static_cast<GLuint>(sampler));
        glActiveTexture(static_cast<GLenum>(active_texture));
        glBindVertexArray(static_cast<GLuint>(vao));
        glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(array_buffer));
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLuint>(draw_fbo));
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
        glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
        glBlendEquationSeparate(static_cast<GLenum>(blend_eq_rgb), static_cast<GLenum>(blend_eq_a));
        glBlendFuncSeparate(static_cast<GLenum>(blend_src_rgb), static_cast<GLenum>(blend_dst_rgb),
                            static_cast<GLenum>(blend_src_a), static_cast<GLenum>(blend_dst_a));
        glColorMask(color_mask[0], color_mask[1], color_mask[2], color_mask[3]);
        set(GL_BLEND, blend);
        set(GL_CULL_FACE, cull);
        set(GL_DEPTH_TEST, depth);
        set(GL_STENCIL_TEST, stencil);
        set(GL_SCISSOR_TEST, scissor_test);
        set(GL_RASTERIZER_DISCARD, discard);
        set(GL_SAMPLE_ALPHA_TO_COVERAGE, a2c);
        set(GL_POLYGON_OFFSET_FILL, poly_offset);
    }
};

bool create_font_texture() {
    ImGuiIO &io = ImGui::GetIO();
    unsigned char *pixels = nullptr;
    int w = 0, h = 0;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);
    if (!pixels || w <= 0 || h <= 0) return false;

    GLint prev_tex = 0, prev_align = 0, prev_row = 0, prev_unpack_buf = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &prev_tex);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &prev_align);
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &prev_row);
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &prev_unpack_buf);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glGenTextures(1, &g_font_tex);
    glBindTexture(GL_TEXTURE_2D, g_font_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(prev_tex));
    glPixelStorei(GL_UNPACK_ALIGNMENT, prev_align);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, prev_row);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, static_cast<GLuint>(prev_unpack_buf));

    io.Fonts->SetTexID(static_cast<ImTextureID>(g_font_tex));
    return glGetError() == GL_NO_ERROR;
}

}  // namespace

bool create() {
    while (glGetError() != GL_NO_ERROR) {}  // drop errors left by the game

    GLuint vs = compile(GL_VERTEX_SHADER, kVertexShader);
    GLuint fs = compile(GL_FRAGMENT_SHADER, kFragmentShader);
    if (!vs || !fs) {
        if (vs) glDeleteShader(vs);
        if (fs) glDeleteShader(fs);
        return false;
    }
    g_program = glCreateProgram();
    glAttachShader(g_program, vs);
    glAttachShader(g_program, fs);
    glLinkProgram(g_program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    GLint linked = GL_FALSE;
    glGetProgramiv(g_program, GL_LINK_STATUS, &linked);
    if (!linked) {
        MS_LOGE("program link failed");
        glDeleteProgram(g_program);
        g_program = 0;
        return false;
    }
    g_loc_proj = glGetUniformLocation(g_program, "uProj");
    g_loc_tex = glGetUniformLocation(g_program, "uTex");

    GLint prev_vao = 0, prev_ab = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prev_vao);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prev_ab);

    glGenVertexArrays(1, &g_vao);
    glGenBuffers(1, &g_vbo);
    glGenBuffers(1, &g_ibo);
    glBindVertexArray(g_vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ibo);  // recorded in g_vao
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert),
                          reinterpret_cast<void *>(offsetof(ImDrawVert, pos)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert),
                          reinterpret_cast<void *>(offsetof(ImDrawVert, uv)));
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert),
                          reinterpret_cast<void *>(offsetof(ImDrawVert, col)));
    glBindVertexArray(static_cast<GLuint>(prev_vao));
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(prev_ab));

    if (!create_font_texture()) {
        MS_LOGE("font texture upload failed");
        return false;
    }
    MS_LOGI("gles3 renderer ready");
    return true;
}

void abandon() {
    g_program = g_vao = g_vbo = g_ibo = g_font_tex = 0;
    g_loc_proj = g_loc_tex = -1;
}

void render(ImDrawData *dd, int fb_w, int fb_h) {
    if (!dd || !g_program || fb_w <= 0 || fb_h <= 0 || dd->CmdListsCount == 0) return;

    SavedState saved{};
    saved.save();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, fb_w, fb_h);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_RASTERIZER_DISCARD);
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_SCISSOR_TEST);

    const float l = dd->DisplayPos.x, r = dd->DisplayPos.x + dd->DisplaySize.x;
    const float t = dd->DisplayPos.y, b = dd->DisplayPos.y + dd->DisplaySize.y;
    const float proj[16] = {
        2.0f / (r - l), 0, 0, 0,
        0, 2.0f / (t - b), 0, 0,
        0, 0, -1.0f, 0,
        (r + l) / (l - r), (t + b) / (b - t), 0, 1.0f,
    };
    glUseProgram(g_program);
    glUniformMatrix4fv(g_loc_proj, 1, GL_FALSE, proj);
    glUniform1i(g_loc_tex, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindSampler(0, 0);
    glBindVertexArray(g_vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);

    const ImVec2 clip_off = dd->DisplayPos;
    const ImVec2 clip_scale = dd->FramebufferScale;
    for (int n = 0; n < dd->CmdListsCount; ++n) {
        const ImDrawList *list = dd->CmdLists[n];
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(list->VtxBuffer.Size * sizeof(ImDrawVert)),
                     list->VtxBuffer.Data, GL_STREAM_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(list->IdxBuffer.Size * sizeof(ImDrawIdx)),
                     list->IdxBuffer.Data, GL_STREAM_DRAW);
        for (int c = 0; c < list->CmdBuffer.Size; ++c) {
            const ImDrawCmd &cmd = list->CmdBuffer[c];
            if (cmd.UserCallback) {
                if (cmd.UserCallback != ImDrawCallback_ResetRenderState) cmd.UserCallback(list, &cmd);
                continue;
            }
            const float x0 = (cmd.ClipRect.x - clip_off.x) * clip_scale.x;
            const float y0 = (cmd.ClipRect.y - clip_off.y) * clip_scale.y;
            const float x1 = (cmd.ClipRect.z - clip_off.x) * clip_scale.x;
            const float y1 = (cmd.ClipRect.w - clip_off.y) * clip_scale.y;
            if (x1 <= x0 || y1 <= y0) continue;
            glScissor(static_cast<GLint>(x0), static_cast<GLint>(fb_h - y1),
                      static_cast<GLsizei>(x1 - x0), static_cast<GLsizei>(y1 - y0));
            glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(cmd.GetTexID()));
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(cmd.ElemCount),
                           sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,
                           reinterpret_cast<void *>(static_cast<uintptr_t>(cmd.IdxOffset * sizeof(ImDrawIdx))));
        }
    }

    saved.restore();
}

}  // namespace ms::gles3
