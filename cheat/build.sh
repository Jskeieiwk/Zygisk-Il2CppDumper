#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
sdk=${ANDROID_SDK_ROOT:-${ANDROID_HOME:-/workspace/android-sdk}}
ndk=${ANDROID_NDK_HOME:-"$sdk/ndk/27.2.12479018"}
llvm="$ndk/toolchains/llvm/prebuilt/linux-x86_64/bin"
platform="$sdk/platforms/android-35/android.jar"
build_tools="$sdk/build-tools/35.0.0"
javac=${JAVAC:-${JAVA_HOME:+$JAVA_HOME/bin/}javac}
cmake=${CMAKE:-cmake}
java_source_dir=${JAVA_SOURCE_DIR:-java}
for executable in "$javac" "$cmake" "$build_tools/d8" "$llvm/aarch64-linux-android25-clang++"; do
    command -v "$executable" >/dev/null 2>&1 || { echo "Missing build tool: $executable" >&2; exit 1; }
done
[ -f "$platform" ] || { echo "Missing Android platform: $platform" >&2; exit 1; }
mkdir -p build/classes build/dex dist
"$cmake" -S "$PWD/vendor/Dobby" -B build/dobby \
    -DCMAKE_TOOLCHAIN_FILE="$ndk/build/cmake/android.toolchain.cmake" \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-25 -DCMAKE_BUILD_TYPE=Release \
    -DDOBBY_GENERATE_SHARED=OFF -DDOBBY_DEBUG=OFF -DPlugin.SymbolResolver=OFF -DNearBranch=OFF >/dev/null
"$cmake" --build build/dobby --target dobby -j 4 >/dev/null
find "$java_source_dir" -name '*.java' -print | sort > build/sources.txt
rm -rf build/classes && mkdir -p build/classes
"$javac" -source 8 -target 8 -Xlint:-options -encoding UTF-8 -classpath "$platform" -d build/classes @build/sources.txt
find build/classes -name '*.class' -print | sort > build/classes.txt
rm -rf build/dex && mkdir -p build/dex
"$build_tools/d8" --min-api 25 --lib "$platform" --output build/dex @build/classes.txt
cp build/dex/classes.dex dist/oxide12034.dex

# Shared hardening flags for both binaries.
hard_cc="-fvisibility=hidden -fvisibility-inlines-hidden -ffunction-sections -fdata-sections \
    -fno-ident -fomit-frame-pointer -DNDEBUG"
hard_ld="-Wl,--gc-sections,-s,--build-id=none,-z,noexecstack,-z,relro,-z,now \
    -Wl,-z,max-page-size=16384"

"$llvm/aarch64-linux-android25-clang++" -std=c++17 -O2 -Wall -Wextra -Werror -fPIE -pie -static-libstdc++ \
    $hard_cc $hard_ld \
    native/injector.cpp -ldl -o dist/oxide-loader
"$llvm/aarch64-linux-android25-clang++" -std=c++17 -O2 -Wall -Wextra -Werror -shared -fPIC -static-libstdc++ \
    $hard_cc $hard_ld -Wl,--exclude-libs,ALL \
    native/oxide_features.cpp native/internal_ui.cpp \
    build/dobby/libdobby.a -Inative -ldl -llog -o dist/oxide12034.so
file dist/oxide-loader dist/oxide12034.so dist/oxide12034.dex
