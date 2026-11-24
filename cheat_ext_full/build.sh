#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
sdk=${ANDROID_SDK_ROOT:?Set ANDROID_SDK_ROOT}
ndk=${ANDROID_NDK_HOME:?Set ANDROID_NDK_HOME}
jdk=${JAVA_HOME:?Set JAVA_HOME}
llvm="$ndk/toolchains/llvm/prebuilt/linux-x86_64/bin"
tools="$sdk/build-tools/35.0.0"
platform="$sdk/platforms/android-35/android.jar"
mkdir -p build/classes build/dex build/package/lib/arm64-v8a dist
mkdir -p build/package/assets
python3 - <<'PY'
from hashlib import sha256
from pathlib import Path
path=Path('build/package/assets/size-padding.bin')
with path.open('wb') as out:
    for index in range(65536):
        out.write(sha256(b'Oxide external transparent size padding'+index.to_bytes(4,'little')).digest())
PY
"$llvm/aarch64-linux-android25-clang++" -std=c++17 -O2 -Wall -Wextra -Werror \
  -fPIE -pie -static-libstdc++ native/main.cpp -o build/package/lib/arm64-v8a/libexternal.so
"$llvm/llvm-strip" --strip-all build/package/lib/arm64-v8a/libexternal.so
find android/src -name '*.java' | sort > build/sources.txt
"$jdk/bin/javac" -source 8 -target 8 -Xlint:-options -classpath "$platform" -d build/classes @build/sources.txt
find build/classes -name '*.class' | sort > build/classes.txt
"$tools/d8" --min-api 25 --lib "$platform" --output build/dex @build/classes.txt
"$tools/aapt" package -f -M android/AndroidManifest.xml -I "$platform" -F build/package/base.apk
cp build/dex/classes.dex build/package/classes.dex
(cd build/package && zip -q -u base.apk classes.dex lib/arm64-v8a/libexternal.so)
(cd build/package && zip -q -0 -u base.apk assets/size-padding.bin)
"$tools/zipalign" -P 16 -f 4 build/package/base.apk build/package/aligned.apk
if [ ! -f build/debug.jks ]; then
  "$jdk/bin/keytool" -genkeypair -keystore build/debug.jks -storepass android -keypass android \
    -alias oxideexternal -keyalg RSA -keysize 2048 -validity 3650 -dname 'CN=Oxide External Debug' >/dev/null 2>&1
fi
"$tools/apksigner" sign --ks build/debug.jks --ks-key-alias oxideexternal \
  --ks-pass pass:android --key-pass pass:android --out dist/Oxide_12034_external_v30.apk build/package/aligned.apk
"$tools/apksigner" verify --verbose dist/Oxide_12034_external_v30.apk
"$tools/aapt" dump badging dist/Oxide_12034_external_v30.apk | head -4
