#pragma once
#include <EGL/egl.h>
namespace vanta {
bool hook_egl_swap();
void unhook_egl_swap();
}
