#!/bin/bash
# Local verification build of the Cloud StandKnife loader APK.
# Mirrors the project's build.sh, but with the tools available in this container:
#   ecj (Maven Central), android-all API 34 jar (Maven Central), apt aapt/zipalign/apksigner, dx.
# Differences from build.sh: dx --min-sdk-version=${DX_MIN:-26} replaces d8 --min-api 24 (d8 is not obtainable here).
# Usage: build-local.sh <project-dir> <output-apk-name>
set -euo pipefail
P="$1"; OUT="$2"
T=/tmp/claude-0/-home-user-Zygisk-Il2CppDumper/03da0c1d-5fb7-5ded-a82f-7d84c737df9b/scratchpad/tools
cd "$P"
rm -rf build; mkdir -p build/classes build/package-assets
node --check assets/module.js
java -jar "$T/ecj.jar" -8 -encoding UTF-8 -proc:none -cp "$T/android-all.jar" -d build/classes ${SRC_DIR:-src}/*.java
/usr/lib/android-sdk/build-tools/debian/dx --dex --min-sdk-version=${DX_MIN:-26} --output=build/classes.dex build/classes
cp assets/inject-arm assets/inject-arm64 build/package-assets/
mkdir -p build/package-assets/watermark
cp watermark-assets/*LICENSE* build/package-assets/watermark/
python - <<'PY'
import json,base64
s=open('assets/module.js').read();assert s.count('__MENU_HTML__')==1
fonts={name:base64.b64encode(open('watermark-assets/'+name,'rb').read()).decode() for name in ['Inter.ttf','JetBrainsMono.ttf','fa-solid-900.ttf','fa-brand-900.ttf']}
s=s.replace('__WATERMARK_FONTS__',json.dumps(fonts))
s=s.replace('__RENDER_DEX__',json.dumps(base64.b64encode(open('build/classes.dex','rb').read()).decode()))
open('build/module-entry.js','w').write("import Java from 'frida-java-bridge';\n"+s.replace('__MENU_HTML__',json.dumps(open('menu.html').read())))
PY
node_modules/.bin/esbuild build/module-entry.js --bundle --format=iife --platform=neutral --target=es2020 --outfile=build/package-assets/module.js
node --check build/package-assets/module.js
aapt package -f -M AndroidManifest.xml -I "$T/android-all.jar" -A build/package-assets -F build/unsigned.apk
python - <<'PY'
import zipfile
with zipfile.ZipFile('build/unsigned.apk','a',compression=zipfile.ZIP_DEFLATED) as z:z.write('build/classes.dex','classes.dex')
PY
zipalign -f 4 build/unsigned.apk build/aligned.apk
apksigner sign --ks loader.p12 --ks-key-alias loader --ks-pass pass:cloud-magic-dev --out "$OUT" build/aligned.apk
apksigner verify --verbose "$OUT"
ls -l "$OUT"
