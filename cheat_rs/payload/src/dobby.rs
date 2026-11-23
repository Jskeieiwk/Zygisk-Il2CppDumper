//! FFI to Dobby's `DobbyHook`/`DobbyDestroy`.
//!
//! Dobby still rewrites the first 4–16 bytes of the target function — this is
//! the `.text`-touching surface we noted in UNDETECT.md. The follow-up is to
//! migrate to `MethodInfo.methodPointer` swapping once the IL2CPP MethodInfo
//! layout is pinned for Build ID 76e47a1a…
use core::ffi::c_void;

extern "C" {
    /// `int DobbyHook(void* target, void* replacement, void** original)`
    pub fn DobbyHook(
        target: *mut c_void,
        replacement: *mut c_void,
        original: *mut *mut c_void,
    ) -> i32;

    /// `int DobbyDestroy(void* target)`
    #[allow(dead_code)]
    pub fn DobbyDestroy(target: *mut c_void) -> i32;
}

/// Install a hook. Returns the original callable pointer on success.
pub unsafe fn hook(target: usize, replacement: *mut c_void) -> Option<*mut c_void> {
    let mut original: *mut c_void = core::ptr::null_mut();
    let rc = DobbyHook(target as *mut c_void, replacement, &mut original);
    if rc == 0 { Some(original) } else { None }
}
