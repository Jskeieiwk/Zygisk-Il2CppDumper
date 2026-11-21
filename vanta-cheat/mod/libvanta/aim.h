#pragma once
namespace vanta {
void aim_start();
void aim_stop();
void aim_tick_and_update();   // вызывается перед renderer_draw (из render thread)
}
