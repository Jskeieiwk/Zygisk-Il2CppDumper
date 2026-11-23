#!/usr/bin/env bash
# Build the Rust payload .so and the C++ loader binary.
# The loader stays C++ (it is simple, verified and self-contained); only the
# in-process payload is Rust.
set -euo pipefail
cd "$(dirname "$0")"

sdk=${ANDROID_SDK_ROOT:-${ANDROID_HOME:-/workspace/android-sdk}}
ndk=${ANDROID_NDK_HOME:-"$sdk/ndk/27.2.12479018"}
llvm="$ndk/toolchains/llvm/prebuilt/linux-x86_64/bin"
sysroot="$ndk/toolchains/llvm/prebuilt/linux-x86_64/sysroot"

for executable in "$llvm/aarch64-linux-android25-clang++" "${CARGO:-cargo}" cmake rustup; do
    command -v "$executable" >/dev/null 2>&1 \
        || { echo "Missing build tool: $executable" >&2; exit 1; }
done

mkdir -p dist build

# --- Dobby ---
cmake -S "$PWD/../cheat/vendor/Dobby" -B build/dobby \
    -DCMAKE_TOOLCHAIN_FILE="$ndk/build/cmake/android.toolchain.cmake" \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-25 -DCMAKE_BUILD_TYPE=Release \
    -DDOBBY_GENERATE_SHARED=OFF -DDOBBY_DEBUG=OFF -DPlugin.SymbolResolver=OFF -DNearBranch=OFF >/dev/null
cmake --build build/dobby --target dobby -j 4 >/dev/null

# --- C++ loader (reused from ../project) ---
hard_cc="-fvisibility=hidden -ffunction-sections -fdata-sections -fno-ident -fomit-frame-pointer -DNDEBUG"
hard_ld="-Wl,--gc-sections,-s,--build-id=none,-z,noexecstack,-z,relro,-z,now \
    -Wl,-z,max-page-size=16384"
"$llvm/aarch64-linux-android25-clang++" -std=c++17 -O2 -Wall -Wextra -Werror -fPIE -pie -static-libstdc++ \
    $hard_cc $hard_ld \
    ../cheat/native/injector.cpp -I ../cheat/native -ldl -o dist/loader

# --- Rust payload ---
rustup target add aarch64-linux-android >/dev/null

target_tc="$llvm"
target_sysroot="$sysroot"

export CC_aarch64_linux_android="$target_tc/aarch64-linux-android25-clang"
export CXX_aarch64_linux_android="$target_tc/aarch64-linux-android25-clang++"
export AR_aarch64_linux_android="$target_tc/llvm-ar"
export CARGO_TARGET_AARCH64_LINUX_ANDROID_LINKER="$target_tc/aarch64-linux-android25-clang"
export CARGO_TARGET_AARCH64_LINUX_ANDROID_RUSTFLAGS="-C link-arg=--sysroot=$target_sysroot"

export DOBBY_LIB_DIR="$PWD/build/dobby"

${CARGO:-cargo} build --release -p payload --target aarch64-linux-android

cp target/aarch64-linux-android/release/libpayload.so dist/payload.so
"$llvm/llvm-strip" --strip-all --remove-section=.comment --remove-section=.note dist/loader dist/payload.so
file dist/loader dist/payload.so
