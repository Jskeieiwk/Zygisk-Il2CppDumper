// renderer.h — инициализация ImGui и рендер каждого кадра поверх игры.
// привязка: вызывается из hooked eglSwapBuffers ПЕРЕД оригинальным swap.
#pragma once

namespace vanta {

bool renderer_init_if_needed(int fb_w, int fb_h);
void renderer_new_frame(int fb_w, int fb_h);
void renderer_draw();        // отрисовывает всё меню + ESP
void renderer_shutdown();

} // namespace vanta
