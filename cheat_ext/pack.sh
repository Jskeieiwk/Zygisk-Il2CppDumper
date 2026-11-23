#!/usr/bin/env bash
# Pack the external ELF into a self-extracting .sh loader: `.sh` extension so
# MT Manager runs it through sh; actual payload is the base64-encoded ELF that
# gets written to /data/local/tmp under a randomised name and exec'd.
set -euo pipefail
cd "$(dirname "$0")"

rand()  { dd if=/dev/urandom bs=256 count=1 2>/dev/null | LC_ALL=C tr -dc 'a-z0-9' | head -c "$1"; }
randl() { dd if=/dev/urandom bs=256 count=1 2>/dev/null | LC_ALL=C tr -dc 'a-z'   | head -c "$1"; }

BIN_NAME=${BIN_NAME:-"up_$(rand 6)"}
SCRIPT=${SCRIPT:-"oxide_ext_$(randl 3).sh"}

bash build.sh
install -m 0755 dist/oxide_ext "dist/${BIN_NAME}"

out="dist/${SCRIPT}"
cat > "$out" <<EOF
#!/system/bin/sh
set -eu
pkg=com.catsbit.oxidesurvivalisland
mode=\${1:-run}
if [ "\$mode" = run ] && [ "\$(id -u)" != 0 ]; then
    command -v su >/dev/null 2>&1 || { echo "root required" >&2; exit 1; }
    case "\$0" in /*) sp=\$0 ;; *) sp="\$PWD/\$0" ;; esac
    exec su 0 /system/bin/sh "\$sp" run
fi
dst=/data/local/tmp/${BIN_NAME}
sed '1,/^__ELF__\$/d' "\$0" | base64 -d > "\$dst"
chmod 700 "\$dst"
exec "\$dst"
__ELF__
EOF
base64 "dist/${BIN_NAME}" >> "$out"
chmod 755 "$out"
ls -lh "$out"
