#!/usr/bin/env python3
"""pack.py — собирает vanta.sh из vanta.sh.in + inject-arm64 + libvanta.so"""
import argparse, base64, pathlib, sys

AP = argparse.ArgumentParser()
AP.add_argument("--template", required=True)
AP.add_argument("--inj", required=True)
AP.add_argument("--so",  required=True)
AP.add_argument("--out", required=True)
args = AP.parse_args()

tpl = pathlib.Path(args.template).read_text()
inj = pathlib.Path(args.inj).read_bytes()
so  = pathlib.Path(args.so).read_bytes()

def b64(b):
    return base64.encodebytes(b).decode().rstrip()

out = tpl.replace("@@INJ_PAYLOAD@@", b64(inj)).replace("@@SO_PAYLOAD@@", b64(so))
pathlib.Path(args.out).write_text(out)
print(f"[+] wrote {args.out}: {len(out)} bytes (inj={len(inj)}B so={len(so)}B)")
