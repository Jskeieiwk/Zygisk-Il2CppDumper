//! Internal mutable state: feature config, HUD snapshot, menu state.
//!
//! Ported from `native/internal_state.h` (C++). This is the single source of
//! truth that Rust reads/writes — no JNI, no Java mirror.
use parking_lot::Mutex;
use once_cell::sync::Lazy;

#[derive(Clone, Copy, Debug)]
pub struct Config {
    // --- Master toggles ---
    pub esp: bool,
    pub aim: bool,
    pub freecam: bool,
    pub auto_farm_feature: bool,
    pub auto_heal: bool,
    pub custom_crosshair: bool,
    pub custom_sky: bool,
    pub player_chams: bool,
    pub weapon_chams: bool,

    // --- Visuals ---
    pub boxes: bool,
    pub skeleton: bool,
    pub names: bool,
    pub distance: bool,
    pub hp: bool,
    pub arrows: bool,
    pub weapon: bool,
    pub fov_visible: bool,
    pub visible_only: bool,

    // --- Tunables ---
    pub esp_distance: i32,
    pub fov: i32,
    pub smooth: i32,
    pub camera_fov: i32,
    pub weapon_fov: i32,
    pub heal_threshold: i32,
    pub weapon_alpha: i32,

    // --- Colors ---
    pub chams: [u8; 3],
    pub weapon_rgb: [u8; 3],
    pub sky: [u8; 3],
    pub menu: [u8; 3],
    pub crosshair: [u8; 3],

    // --- Farm selector ---
    pub farm_kind: i32,
    pub crate_mask: i32,
    pub ore_esp: bool,
    pub animal_esp: bool,
    pub object_esp: bool,

    pub thickness: i32,
    pub color: i32,
}

impl Default for Config {
    fn default() -> Self {
        Self {
            esp: false, aim: false, freecam: false, auto_farm_feature: false,
            auto_heal: false, custom_crosshair: false, custom_sky: false,
            player_chams: false, weapon_chams: false,
            boxes: true, skeleton: false, names: true, distance: true, hp: true,
            arrows: true, weapon: true, fov_visible: true, visible_only: false,
            esp_distance: 300, fov: 180, smooth: 4, camera_fov: 0, weapon_fov: 0,
            heal_threshold: 60, weapon_alpha: 100,
            chams: [255, 255, 255], weapon_rgb: [255, 255, 255],
            sky: [160, 180, 220], menu: [124, 230, 228], crosshair: [255, 64, 64],
            farm_kind: 9, crate_mask: 0, ore_esp: false, animal_esp: false, object_esp: false,
            thickness: 2, color: 0xff_ff_ff_ff_u32 as i32,
        }
    }
}

#[derive(Clone, Copy, Debug, Default)]
pub struct Hud {
    pub players: i32,
    pub bots: i32,
    pub hp: i32,
    pub max_hp: i32,
    pub ammo: i32,
    pub sampled_ms: u64,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct MenuState {
    pub open: bool,
    pub page: u32,
    pub hits_pending: i32,
}

pub struct State {
    pub config: Config,
    pub hud: Hud,
    pub menu: MenuState,
    /// Enabled by the master toggle; master OFF freezes every feature.
    pub master: bool,
}

static STATE: Lazy<Mutex<State>> = Lazy::new(|| Mutex::new(State {
    config: Config::default(),
    hud: Hud::default(),
    menu: MenuState::default(),
    master: true,
}));

pub fn with<R>(f: impl FnOnce(&mut State) -> R) -> R {
    let mut g = STATE.lock();
    f(&mut *g)
}

pub fn snapshot_config() -> Config { STATE.lock().config }
pub fn snapshot_hud() -> Hud { STATE.lock().hud }
pub fn snapshot_menu() -> MenuState { STATE.lock().menu }

pub fn publish_hud(hud: Hud) { STATE.lock().hud = hud; }

/// Return current time in milliseconds since boot (monotonic).
pub fn now_ms() -> u64 {
    unsafe {
        let mut ts: libc::timespec = core::mem::zeroed();
        libc::clock_gettime(libc::CLOCK_MONOTONIC, &mut ts);
        (ts.tv_sec as u64) * 1000 + (ts.tv_nsec as u64) / 1_000_000
    }
}
