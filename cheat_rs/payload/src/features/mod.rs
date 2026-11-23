//! Feature dispatch. One `run_tick` is called from the LateUpdate hook, after
//! the IL2CPP method pointers have been resolved.
//!
//! Every feature below is a stub with a "PORT FROM" reference pointing at the
//! exact C++ source file:line that already implements it. Port them one by one
//! as Rust functions with the same signatures. Keep the host order unchanged
//! to preserve timing.
use crate::il2cpp::Api;
use crate::state;

pub unsafe fn run_tick(api: &Api) {
    let cfg = state::snapshot_config();
    let now = state::now_ms();

    // Ordered 1:1 with oxide_features.cpp:tick (starting around line 650).
    //
    // sky::apply(api, &cfg);
    // chams::sweep(api, &cfg, now);
    // auto_heal::maybe_use(api, &cfg, now);
    // ballistic::aim(api, &cfg, now);
    // weapon_fov::apply(api, &cfg);
    // camera_fov::apply(api, &cfg);
    // freecam::step(api, &cfg, now);
    // auto_farm::step(api, &cfg, now);
    // esp::sample_world(api, &cfg, now);
    // esp::publish(api, &cfg, now);

    let _ = (api, cfg, now);
}

// ---- Stubs. Each is a direct target for porting. ----

pub mod esp {
    // PORT FROM: native/oxide_features.cpp:696-813  (per-player loop)
    //            native/oxide_features.cpp:347-389  (world markers for ore/animals/crates)
}

pub mod aim {
    // PORT FROM: native/oxide_features.cpp:822-838  (bestPoint + camera LookAt)
    //            native/oxide_features.cpp:582-613  (motion history + bullet model)
    //            native/ballistics.h                (integrator + solve_intercept)
}

pub mod chams {
    // PORT FROM: native/oxide_features.cpp:431-486
}

pub mod sky {
    // PORT FROM: native/oxide_features.cpp:390-411
}

pub mod freecam {
    // PORT FROM: native/oxide_features.cpp:308-327  (updateFreecam)
    //            native/oxide_features.cpp:296-302  (replacementMove)
}

pub mod auto_farm {
    // PORT FROM: native/oxide_features.cpp:517-581
}

pub mod auto_heal {
    // PORT FROM: native/oxide_features.cpp:487-516
}

pub mod camera_fov {
    // PORT FROM: native/oxide_features.cpp:682-687
}

pub mod weapon_fov {
    // PORT FROM: native/oxide_features.cpp:672-680
}

pub mod hitsound {
    // PORT FROM: native/oxide_features.cpp:303-307 (replacementOneShot)
}

pub mod crosshair {
    // PORT FROM: native/oxide_features.cpp:614-649 (hideCrosshair*, crosshairUpdate hook)
}
