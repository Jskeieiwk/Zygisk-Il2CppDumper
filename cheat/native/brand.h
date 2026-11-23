#pragma once
// Build-time randomised identifiers. pack.sh rewrites these macros per build.
// Defaults below are a FALLBACK ONLY; never ship with them.
#ifndef BRAND_TAG
#define BRAND_TAG "aud"
#endif
#ifndef BRAND_PKG
#define BRAND_PKG "com.android.oemsupport"
#endif
#ifndef BRAND_CLASS_BRIDGE
#define BRAND_CLASS_BRIDGE "com.android.oemsupport.NativeBridge"
#endif
#ifndef BRAND_CLASS_ENTRY
#define BRAND_CLASS_ENTRY "com.android.oemsupport.OverlayEntry"
#endif
#ifndef BRAND_LIB_PREFIX
#define BRAND_LIB_PREFIX "art_"
#endif
#ifndef BRAND_PREFS_NAME
#define BRAND_PREFS_NAME "oem_overlay_cfg"
#endif
#ifndef BRAND_SOUND_NAME
#define BRAND_SOUND_NAME "notification.ogg"
#endif
