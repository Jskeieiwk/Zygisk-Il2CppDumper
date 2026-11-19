#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build/classes build/package-assets
node --check assets/module.js
java -jar tools/ecj.jar -8 -encoding UTF-8 -proc:none -cp tools/android-35/android.jar -d build/classes src/*.java
java -cp tools/android-15/lib/d8.jar com.android.tools.r8.D8 --lib tools/android-35/android.jar --min-api 24 --output build build/classes/dev/cloud/standknife/*.class
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
tools/android-15/aapt package -f -M AndroidManifest.xml -I tools/android-35/android.jar -A build/package-assets -F build/unsigned.apk
python - <<'PY'
import zipfile
with zipfile.ZipFile('build/unsigned.apk','a',compression=zipfile.ZIP_DEFLATED) as z:z.write('build/classes.dex','classes.dex')
PY
tools/android-15/zipalign -f 4 build/unsigned.apk build/aligned.apk
tools/android-15/apksigner sign --ks loader.p12 --ks-key-alias loader --ks-pass pass:cloud-magic-dev --out Cloud-StandKnife-root-v38-test.apk build/aligned.apk
tools/android-15/apksigner verify --verbose Cloud-StandKnife-root-v38-test.apk
