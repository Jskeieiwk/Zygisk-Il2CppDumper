//! Drawing primitives — call into Unity via IL2CPP runtime_invoke.
use crate::il2cpp::Api;
use crate::state::MenuState;
use super::input::TouchState;

/// Draw one full menu frame. Render order: glass → panel → sections → footer.
#[allow(unused_variables)]
pub unsafe fn frame(api: &Api, menu: &MenuState, touch: &TouchState) {
    // TODO PORT: InternalEntry.java:140-250 (open/sync/section/row layout).
    //
    // Pattern for every DrawTexture call:
    //     let rect = Rect { x, y, w, h };
    //     let args: *mut c_void[] = [&rect, &white_tex];
    //     il2cpp::call(api, GRAPHICS_DRAW_TEXTURE, ptr::null_mut(), &mut args);
    //
    // Cache the Rect and Texture2D objects across ticks — allocating a fresh
    // Texture2D each frame will crash GC.
    //
    // Colors come from state.config.menu[0..3]. Compose into a 1×1 Texture2D
    // once at init, then tint via GUI.color before DrawTexture.
}

/// A filled rounded rectangle. Rounding is faked with corner masks drawn as
/// four tiny Texture2D blits — Unity GUI has no built-in roundrect.
#[allow(unused_variables)]
pub unsafe fn rounded_rect(api: &Api, x: f32, y: f32, w: f32, h: f32, radius: f32, rgba: u32) {
    // TODO PORT: InternalEntry.java:146 (gradient header), draw two overlapping
    // filled rects then four 2×2 masks at the corners.
}

/// A horizontal slider track + knob + text label. Returns the new value when
/// `touch` is inside the slider rect, otherwise returns `current`.
#[allow(unused_variables)]
pub unsafe fn slider(
    api: &Api,
    x: f32, y: f32, w: f32, h: f32,
    label: &str,
    current: f32,
    min: f32,
    max: f32,
    touch: &TouchState,
) -> f32 {
    // TODO PORT: InternalEntry.java slider(...) section.
    current
}
