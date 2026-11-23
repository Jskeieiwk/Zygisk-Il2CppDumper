//! Build-time identifiers and target constants.
//!
//! `pack.sh` rewrites this file each build with randomised values. The defaults
//! here are fallbacks only and must not be shipped.
#![no_std]

// ---------- Identifiers ----------

pub const BRAND_TAG: &str = "aud";
pub const BRAND_PKG: &str = "com.android.oemsupport";
pub const BRAND_CLASS_BRIDGE: &str = "com.android.oemsupport.NativeBridge";
pub const BRAND_CLASS_ENTRY: &str = "com.android.oemsupport.OverlayEntry";
pub const BRAND_LIB_PREFIX: &str = "art_";
pub const BRAND_PREFS_NAME: &str = "oem_overlay_cfg";

// ---------- Target binary ----------

/// Expected Build ID of the target `libil2cpp.so`.
pub const TARGET_BUILD_ID: [u8; 20] = [
    0x76, 0xe4, 0x7a, 0x1a, 0xdd, 0xbd, 0x7a, 0xee, 0x36, 0x59,
    0x5c, 0x8d, 0xc2, 0xbb, 0x2f, 0x7e, 0xac, 0x1f, 0xfc, 0x5e,
];

/// RVA and first ARM64 instruction word of `Oxide.PlayerManager::LateUpdate`.
pub const PLAYER_LATE_UPDATE: (usize, u32) = (0x7818_ED8, 0xf81e_0ffe);
/// Secondary signature — `Oxide.PlayerManager::Update`.
pub const PLAYER_UPDATE: (usize, u32) = (0x7819_8A4, 0xd102_03ff);
/// `UnityEngine.AudioSource::PlayOneShot(AudioClip,float)` for headshot sound.
pub const AUDIO_PLAY_ONE_SHOT: (usize, u32) = (0xE2C5_B88, 0xfc1d_0fe8);
