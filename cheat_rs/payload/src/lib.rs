//! Internal payload — Rust port of `native/oxide_features.cpp` +
//! `native/internal_ui.cpp`. Loaded by the existing C++ loader
//! (`project/native/injector.cpp`); the entry point is the ELF `.init_array`
//! constructor below.
//!
//! No JNI, no Java UI thread calls on the hot path. The menu draws from inside
//! Unity's own render graph through IL2CPP runtime invokes — see `menu`.
//!
//! Panics abort — `panic = "abort"` is set in the workspace profile so any
//! panic inside a hooked function terminates instead of corrupting the engine.

use std::ffi::c_void;
use std::ptr;
use std::sync::atomic::{AtomicBool, Ordering};

use parking_lot::Mutex;

#[macro_use]
mod log;
mod game;
mod dobby;
mod il2cpp;
mod state;
mod features;
mod menu;

static READY: AtomicBool = AtomicBool::new(false);
static ORIGINAL_LATE_UPDATE: Mutex<Option<unsafe extern "C" fn(*mut c_void, *mut c_void)>> =
    Mutex::new(None);
static API: Mutex<Option<il2cpp::Api>> = Mutex::new(None);

/// Replacement for `PlayerManager::LateUpdate(this, methodInfo)`.
/// Runs on the Unity main thread; the original runs first so game logic
/// completes before we read state.
unsafe extern "C" fn late_update(this: *mut c_void, method_info: *mut c_void) {
    if let Some(orig) = *ORIGINAL_LATE_UPDATE.lock() {
        orig(this, method_info);
    }

    if !READY.load(Ordering::Acquire) {
        if initialize_from_main_thread() {
            READY.store(true, Ordering::Release);
        } else {
            return;
        }
    }

    // Hold the API borrow for the whole tick. The lock is uncontended on the
    // main thread since nothing else touches it after init.
    let guard = API.lock();
    if let Some(api) = guard.as_ref() {
        features::run_tick(api);
        menu::tick(api);
    }
}

unsafe fn initialize_from_main_thread() -> bool {
    let base = game::BASE.load(Ordering::Acquire);
    let api = match il2cpp::resolve_api(base) {
        Some(a) => a,
        None => return false,
    };
    *API.lock() = Some(api);
    log_info!("rt ok");
    true
}

unsafe fn boot_thread() {
    // Wait for libil2cpp.so (the host process may still be mapping it when
    // our .init_array runs).
    for _ in 0..200 {
        if game::locate() && game::BASE.load(Ordering::Acquire) != 0 { break; }
        libc::usleep(100_000);
    }
    if game::BASE.load(Ordering::Acquire) == 0 {
        log_err!("no il2cpp");
        return;
    }
    if !game::signature_matches() {
        log_err!("sig");
        return;
    }
    // Install the primary hook. Runtime resolve stays deferred so we never
    // touch IL2CPP from this unregistered pthread.
    let target = game::BASE.load(Ordering::Acquire) + shared::PLAYER_LATE_UPDATE.0;
    let orig_void = match dobby::hook(target, late_update as *mut c_void) {
        Some(p) => p,
        None => { log_err!("h"); return; }
    };
    let typed = std::mem::transmute::<
        *mut c_void,
        unsafe extern "C" fn(*mut c_void, *mut c_void),
    >(orig_void);
    *ORIGINAL_LATE_UPDATE.lock() = Some(typed);
    log_info!("hook ok");
}

#[ctor::ctor]
fn start() {
    let mut tid: libc::pthread_t = 0;
    extern "C" fn trampoline(_: *mut c_void) -> *mut c_void {
        unsafe { boot_thread(); }
        ptr::null_mut()
    }
    unsafe {
        if libc::pthread_create(&mut tid, ptr::null(), trampoline, ptr::null_mut()) == 0 {
            libc::pthread_detach(tid);
        }
    }
}
