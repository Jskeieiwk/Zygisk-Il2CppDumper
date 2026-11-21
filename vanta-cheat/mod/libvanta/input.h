// input.h — тач-ввод для ImGui. читает /dev/input/event* в своём треде.
// при открытом меню — перехватывает касания в области меню, остальные пропускает.
#pragma once

namespace vanta {

bool input_start();
void input_stop();
void input_new_frame(int fb_w, int fb_h);  // вызывается renderer_new_frame

} // namespace vanta
