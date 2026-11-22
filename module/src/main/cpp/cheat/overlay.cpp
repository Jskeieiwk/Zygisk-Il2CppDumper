#include "overlay.h"
#include "cheat.h"
#include "hook.h"
#include "font8x8.h"
#include "../log.h"
#include "../game.h"

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <dlfcn.h>
#include <atomic>
#include <cstring>
#include <cstdio>
#include <cstdlib>

typedef EGLBoolean (*eglSwapBuffers_t)(EGLDisplay, EGLSurface);
static eglSwapBuffers_t s_orig_swap = nullptr;

static std::atomic<bool> s_menu_visible{false};
void overlay_set_menu_visible(bool v) { s_menu_visible.store(v); }
bool overlay_menu_visible() { return s_menu_visible.load(); }

// =========================================================================
//   Minimal GLES3 renderer for a bitmap-font watermark.
//   Compiles one shader on first frame, renders N textured quads per frame.
// =========================================================================

static const char *kVS =
    "#version 300 es\n"
    "layout(location=0) in vec2 aPos;\n"
    "layout(location=1) in vec2 aUV;\n"
    "uniform vec2 uViewport;\n"
    "out vec2 vUV;\n"
    "void main(){\n"
    "  vec2 p = aPos / uViewport * 2.0 - 1.0;\n"
    "  gl_Position = vec4(p.x, -p.y, 0.0, 1.0);\n"
    "  vUV = aUV;\n"
    "}\n";

static const char *kFS =
    "#version 300 es\n"
    "precision mediump float;\n"
    "in vec2 vUV;\n"
    "uniform sampler2D uTex;\n"
    "uniform vec4 uColor;\n"
    "out vec4 oColor;\n"
    "void main(){\n"
    "  float a = texture(uTex, vUV).r;\n"
    "  if (a < 0.5) discard;\n"
    "  oColor = uColor;\n"
    "}\n";

static GLuint s_prog = 0;
static GLuint s_vao = 0, s_vbo = 0;
static GLuint s_tex = 0;
static GLint  s_u_viewport = -1, s_u_color = -1, s_u_tex = -1;

static bool s_gl_ready = false;

static GLuint compile(GLenum type, const char *src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        LOGE("[Cloud] shader compile: %s", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

// Build a 128x128 atlas from kFont8x8: 16x16 grid of 8x8 glyphs.
static void build_font_atlas() {
    const int W = 128, H = 128;
    uint8_t buf[W * H];
    memset(buf, 0, sizeof(buf));
    for (int code = 0x20; code <= 0x7F; ++code) {
        int idx = code - 0x20;
        int gx = (code & 0x0F) * 8;
        int gy = ((code >> 4) & 0x0F) * 8;
        const uint8_t *g = kFont8x8[idx];
        for (int y = 0; y < 8; ++y) {
            uint8_t row = g[y];
            for (int x = 0; x < 8; ++x) {
                if (row & (1 << x)) buf[(gy + y) * W + (gx + x)] = 255;
            }
        }
    }
    glGenTextures(1, &s_tex);
    glBindTexture(GL_TEXTURE_2D, s_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, W, H, 0, GL_RED, GL_UNSIGNED_BYTE, buf);
}

static bool gl_init() {
    GLuint vs = compile(GL_VERTEX_SHADER, kVS);
    GLuint fs = compile(GL_FRAGMENT_SHADER, kFS);
    if (!vs || !fs) return false;
    s_prog = glCreateProgram();
    glAttachShader(s_prog, vs);
    glAttachShader(s_prog, fs);
    glLinkProgram(s_prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    GLint ok = 0;
    glGetProgramiv(s_prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(s_prog, sizeof(log), nullptr, log);
        LOGE("[Cloud] prog link: %s", log);
        return false;
    }
    s_u_viewport = glGetUniformLocation(s_prog, "uViewport");
    s_u_color    = glGetUniformLocation(s_prog, "uColor");
    s_u_tex      = glGetUniformLocation(s_prog, "uTex");

    glGenVertexArrays(1, &s_vao);
    glGenBuffers(1, &s_vbo);
    glBindVertexArray(s_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    build_font_atlas();
    return true;
}

struct V4 { float x, y, u, v; };

// Append one glyph quad (two triangles) to buf; returns new count.
static int push_glyph(V4 *buf, int cnt, char c, float x, float y, float sz) {
    if (c < 0x20 || c > 0x7F) c = ' ';
    int gx = (c & 0x0F);
    int gy = ((c >> 4) & 0x0F);
    float u0 = (gx * 8.0f) / 128.0f;
    float v0 = (gy * 8.0f) / 128.0f;
    float u1 = u0 + 8.0f / 128.0f;
    float v1 = v0 + 8.0f / 128.0f;
    V4 a = {x,      y,      u0, v0};
    V4 b = {x + sz, y,      u1, v0};
    V4 c2= {x,      y + sz, u0, v1};
    V4 d = {x + sz, y + sz, u1, v1};
    buf[cnt++] = a; buf[cnt++] = b; buf[cnt++] = c2;
    buf[cnt++] = b; buf[cnt++] = d; buf[cnt++] = c2;
    return cnt;
}

static void draw_text(const char *s, float x, float y, float sz, float r, float g, float b, float alpha) {
    V4 buf[6 * 128];
    int cnt = 0;
    float cx = x;
    for (const char *p = s; *p && cnt + 6 <= (int)(sizeof(buf)/sizeof(buf[0])); ++p) {
        if (*p == ' ') { cx += sz * 0.6f; continue; }
        cnt = push_glyph(buf, cnt, *p, cx, y, sz);
        cx += sz * 0.75f;
    }
    glBufferData(GL_ARRAY_BUFFER, cnt * sizeof(V4), buf, GL_STREAM_DRAW);
    glUniform4f(s_u_color, r, g, b, alpha);
    glDrawArrays(GL_TRIANGLES, 0, cnt);
}

static void render_watermark(int vp_w, int vp_h) {
    (void)vp_h;
    if (!g_cfg.enabled_watermark) return;

    // Save a tiny slice of GL state so we don't trash the game's rendering.
    GLint prev_prog = 0, prev_vao = 0, prev_buf = 0, prev_tex = 0, prev_active = 0;
    GLboolean prev_blend = glIsEnabled(GL_BLEND);
    GLboolean prev_cull  = glIsEnabled(GL_CULL_FACE);
    GLboolean prev_depth = glIsEnabled(GL_DEPTH_TEST);
    GLboolean prev_stencil = glIsEnabled(GL_STENCIL_TEST);
    GLboolean prev_scissor = glIsEnabled(GL_SCISSOR_TEST);
    glGetIntegerv(GL_CURRENT_PROGRAM,       &prev_prog);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING,  &prev_vao);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING,  &prev_buf);
    glGetIntegerv(GL_ACTIVE_TEXTURE,        &prev_active);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(s_prog);
    glBindVertexArray(s_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glActiveTexture(GL_TEXTURE0);
    glGetIntegerv(GL_TEXTURE_BINDING_2D,    &prev_tex);
    glBindTexture(GL_TEXTURE_2D, s_tex);
    glUniform1i(s_u_tex, 0);
    glUniform2f(s_u_viewport, (float)vp_w, (float)vp_h);

    const char *txt = CheatWatermark;
    float x = 16.0f, y = 16.0f, sz = 28.0f;
    // soft shadow
    draw_text(txt, x + 2, y + 2, sz, 0, 0, 0, 0.75f);
    // bright red
    draw_text(txt, x, y, sz, 1.0f, 0.12f, 0.17f, 1.0f);

    // restore
    glBindTexture(GL_TEXTURE_2D, (GLuint)prev_tex);
    glActiveTexture((GLenum)prev_active);
    glBindBuffer(GL_ARRAY_BUFFER, (GLuint)prev_buf);
    glBindVertexArray((GLuint)prev_vao);
    glUseProgram((GLuint)prev_prog);
    if (prev_blend == GL_FALSE)     glDisable(GL_BLEND);
    if (prev_cull  == GL_TRUE)      glEnable(GL_CULL_FACE);
    if (prev_depth == GL_TRUE)      glEnable(GL_DEPTH_TEST);
    if (prev_stencil == GL_TRUE)    glEnable(GL_STENCIL_TEST);
    if (prev_scissor == GL_TRUE)    glEnable(GL_SCISSOR_TEST);
}

static EGLBoolean hk_swap(EGLDisplay dpy, EGLSurface surf) {
    if (!s_gl_ready) {
        s_gl_ready = gl_init();
        if (!s_gl_ready) {
            LOGE("[Cloud] GL init failed; disabling overlay");
            g_cfg.enabled_overlay = false;
            g_cfg.enabled_watermark = false;
            return s_orig_swap(dpy, surf);
        }
    }

    GLint viewport[4] = {0, 0, 1920, 1080};
    glGetIntegerv(GL_VIEWPORT, viewport);
    int w = viewport[2], h = viewport[3];

    render_watermark(w, h);

    return s_orig_swap(dpy, surf);
}

void overlay_install() {
    void *libegl = dlopen("libEGL.so", RTLD_NOW);
    if (!libegl) {
        LOGE("[Cloud] dlopen libEGL.so failed: %s", dlerror());
        return;
    }
    void *sym = dlsym(libegl, "eglSwapBuffers");
    if (!sym) {
        LOGE("[Cloud] dlsym eglSwapBuffers failed");
        return;
    }
    if (!inline_hook(sym, (void*)hk_swap, (void**)&s_orig_swap)) {
        LOGE("[Cloud] eglSwapBuffers hook install failed");
        return;
    }
    LOGI("[Cloud] overlay installed on eglSwapBuffers (%p)", sym);
}
