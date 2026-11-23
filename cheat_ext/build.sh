#!/usr/bin/env bash
# External PIE binary — Phase 1 probe. No .so injection, no linker, no
# ptrace: just process_vm_readv/writev from outside the game process.
set -euo pipefail
cd "$(dirname "$0")"
sdk=${ANDROID_SDK_ROOT:-${ANDROID_HOME:-/workspace/android-sdk}}
ndk=${ANDROID_NDK_HOME:-"$sdk/ndk/27.2.12479018"}
llvm="$ndk/toolchains/llvm/prebuilt/linux-x86_64/bin"
cxx="$llvm/aarch64-linux-android25-clang++"
command -v "$cxx" >/dev/null 2>&1 || { echo "missing: $cxx" >&2; exit 1; }
mkdir -p dist

# Hardening flags mirror UNDETECT.md: no build-id, dead-code elimination,
# hidden visibility, stripped comment/note sections, relro+now.
hard_cc="-fvisibility=hidden -fvisibility-inlines-hidden -ffunction-sections -fdata-sections \
    -fno-ident -fomit-frame-pointer -DNDEBUG"
hard_ld="-Wl,--gc-sections,-s,--build-id=none,-z,noexecstack,-z,relro,-z,now \
    -Wl,-z,max-page-size=16384 -Wl,--exclude-libs,ALL"

"$cxx" -std=c++17 -O2 -Wall -Wextra -Werror -fPIE -pie -static-libstdc++ \
    $hard_cc $hard_ld \
    src/main.cpp src/mem.cpp -o dist/oxide_ext

"$llvm/llvm-strip" --strip-all --remove-section=.comment --remove-section=.note dist/oxide_ext
file dist/oxide_ext
ls -lh dist/oxide_ext
