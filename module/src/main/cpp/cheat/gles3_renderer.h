#pragma once

struct ImDrawData;

namespace ms::gles3 {

// Creates shader, buffers and the font texture in the current GL context.
bool create();

// Forget every GL object without deleting it: used when the context they lived in is gone.
void abandon();

// Draws into the default framebuffer and restores the GL state it touched.
void render(ImDrawData *draw_data, int fb_width, int fb_height);

}  // namespace ms::gles3
