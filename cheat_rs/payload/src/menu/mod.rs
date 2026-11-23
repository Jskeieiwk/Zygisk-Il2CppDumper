//! Native menu rendering through IL2CPP calls into Unity.
//!
//! Design: we are inside the game process on the Unity main thread (from the
//! `LateUpdate` hook). We call back into Unity via `runtime_invoke` to draw the
//! menu with Unity's own GUI / Graphics API. No Java, no Android overlay,
//! no SurfaceFlinger — the menu lives in Unity's render graph.
//!
//! Drawing primitives (filled rect, text, slider) reach Unity through:
//!   - `UnityEngine.Graphics::DrawTexture(Rect,Texture)` for filled boxes
//!   - `UnityEngine.GUI::Label(Rect,String)` for text
//!   - `UnityEngine.GUI::HorizontalSlider(Rect,float,float,float)` for sliders
//!
//! Input: we read `UnityEngine.Input::GetTouch(0)` once per tick and feed its
//! position + phase into our click-state machine.
//!
//! PORT STATUS: this file is the shape, not the implementation. Follow the
//! bullets at the bottom of the file to port each piece from
//! `project/java/com/cloudcrack/oxide/InternalEntry.java`.
use crate::il2cpp::Api;
use crate::state;

pub mod draw;
pub mod input;

/// Called once a tick from the LateUpdate hook, after features have run and
/// state has been updated. If the menu is closed, this is nearly free.
pub unsafe fn tick(api: &Api) {
    let menu = state::snapshot_menu();
    if !menu.open {
        // Still consume touch state so a tap outside the menu doesn't leak in
        // when the menu opens on the next frame.
        input::poll(api);
        return;
    }
    let touch = input::poll(api);
    draw::frame(api, &menu, &touch);
}

// TODO PORT: InternalEntry.java → Rust
// ---------------------------------------
// - sync()     → state::snapshot_config()
// - open()     → draw::frame + input::poll
// - close()    → state::with(|s| s.menu.open = false)
// - section()  → draw::section
// - row()      → draw::row
// - toggle()   → draw::toggle + input::hit
// - slider()   → draw::slider + input::drag
// - colorRow() → draw::color_row (RGB sliders)
// - fcBind / avBind draggable buttons → draw::drag_button
// - prefs.getSharedPreferences(...)   → config persistence via std::fs on
//   path derived from BRAND_PREFS_NAME, in the game's filesDir (
//   `/data/user/0/<pkg>/files/<BRAND_PREFS_NAME>.json`).
//
// Input mapping differences from the Java version:
//   - Java was dispatching onTouchEvent through View.dispatchTouchEvent.
//   - Rust reads Touch directly from Unity's Input API; no event dispatch.
//   - When the menu is OPEN, mark Unity touch as "consumed" by calling
//     `Input::ResetInputAxes()` so the game's own input pipeline does not
//     interpret menu taps as fire / move.
