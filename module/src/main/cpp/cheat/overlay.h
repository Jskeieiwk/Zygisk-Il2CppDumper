#pragma once

#include <cstddef>
#include <cstdint>

#include "hook.h"

namespace ms::overlay {

enum class TouchKind : int { Down, Move, Up };

// Touch in Unity screen pixels, origin top-left.
struct TouchEvent {
    TouchKind kind;
    int finger;
    float x, y;
    float screen_w, screen_h;
    int64_t time_ms;
};

// Main thread: queue touches polled from UnityEngine.Input.
void push_touches(const TouchEvent *events, int count);

// Resolves eglSwapBuffers (required) and eglSwapBuffersWithDamageKHR (optional).
// Returns the count added, 0 if the required hook could not be resolved.
size_t fill_hook_specs(hook::Spec *out, size_t capacity);

void set_ready();

}  // namespace ms::overlay
