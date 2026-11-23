//! Touch input, read once per frame from `UnityEngine.Input::GetTouch`.
use crate::il2cpp::Api;

#[derive(Clone, Copy, Debug, Default)]
pub struct TouchState {
    /// Screen-space pixel coordinates; origin is bottom-left per Unity.
    pub x: f32,
    pub y: f32,
    /// `TouchPhase` from Unity: 0=Began, 1=Moved, 2=Stationary, 3=Ended, 4=Canceled.
    pub phase: i32,
    /// True if a touch is present this frame.
    pub present: bool,
    /// True on the first frame a touch began inside any hit rect.
    pub down: bool,
}

/// Read `touchCount` and `GetTouch(0)` through IL2CPP. Returns the current
/// touch; a non-present touch has `present=false`.
#[allow(unused_variables)]
pub unsafe fn poll(api: &Api) -> TouchState {
    // TODO PORT:
    //   let count = call(api, INPUT_TOUCH_COUNT, null, []) : i32
    //   if count <= 0 { return default }
    //   let t    = call(api, INPUT_GET_TOUCH, null, [&0_i32]) : Touch struct
    //   unbox Touch { position: Vec2, phase: TouchPhase, fingerId: i32, … }
    //
    // Ported from InternalEntry.java:dispatchTouchEvent() + Java onTouch
    // handlers. The big difference: that path received events, this path
    // samples state. Edge detection (down / up) has to be synthesised from
    // consecutive frame samples — keep a `static mut PREV: TouchState` here.
    TouchState::default()
}

/// Rect-in-screen test: did the current touch start inside the given rect?
pub fn hit(touch: &TouchState, x: f32, y: f32, w: f32, h: f32) -> bool {
    touch.down && touch.x >= x && touch.x <= x + w && touch.y >= y && touch.y <= y + h
}
