#!/usr/bin/env python3
"""Check r09 adapter coverage/fingerprints against the supplied ELF, without executing it."""
import json
import re
import struct
import sys
from pathlib import Path

project = Path(__file__).resolve().parents[1]
binary = Path(sys.argv[1]) if len(sys.argv) > 1 else project.parent / 'inputs/libil2cpp.so'
blob = binary.read_bytes()
assert blob[:6] == b'\x7fELF\x02\x01', 'Expected ELF64 little endian'
assert struct.unpack_from('<H', blob, 18)[0] == 183, 'Expected AArch64'
phoff = struct.unpack_from('<Q', blob, 32)[0]
phsize, phnum = struct.unpack_from('<HH', blob, 54)
segments = [struct.unpack_from('<IIQQQQQQ', blob, phoff + i * phsize) for i in range(phnum)]
def read_rva(rva, size):
    for kind, flags, offset, address, _, filesz, _, _ in segments:
        if kind == 1 and flags & 1 and address <= rva and rva + size <= address + filesz:
            return blob[offset + rva - address:offset + rva - address + size]
    raise AssertionError(f'RVA {rva:#x} is not file-backed executable code')
ids = []
for kind, _, offset, _, _, size, _, _ in segments:
    if kind != 4:
        continue
    end = offset + size
    while offset + 12 <= end:
        namesz, descsz, typ = struct.unpack_from('<III', blob, offset)
        offset += 12
        name = blob[offset:offset + namesz]
        offset += (namesz + 3) & ~3
        desc = blob[offset:offset + descsz]
        offset += (descsz + 3) & ~3
        if typ == 3 and name == b'GNU\0':
            ids.append(desc.hex())
assert '76e47a1addbd7aee36595c8dc2bb2f7eac1ffc5e' in ids, ids
header = (project / 'native/runtime_12034.h').read_text()
rows = re.findall(r'\{"([a-z_]+)",0x([0-9a-f]+),\{([^}]+)\}\}', header)
entries = {}
for name, address, rawwords in rows:
    words = [int(word, 16) for word in rawwords.split(',')]
    assert len(words) == 4
    address = int(address, 16)
    assert read_rva(address, 16) == struct.pack('<4I', *words), name
    assert name not in entries, name
    entries[name] = hex(address)
source = (project / 'native/oxide_features.cpp').read_text()
required = set(re.findall(r'BIND\(([a-z_]+)\);', source))
assert required == entries.keys(), {'missing': sorted(required - entries.keys()), 'extra': sorted(entries.keys() - required)}
# Independent checks of important branch targets and ABI evidence.
branches = {0x61efe60: 0x624b0e4, 0x624b0e4: 0x623f1f0,
            0x61efe88: 0x6249180, 0x61f0748: 0x6246de0,
            0x61f07d4: 0x6224a80, 0x61f059c: 0x61e7bdc,
            0x61f05d4: 0x61e7fc8, 0x61f061c: 0x61e8144}
for address, target in branches.items():
    word, = struct.unpack('<I', read_rva(address, 4))
    assert word >> 26 == 5
    delta = word & 0x3ffffff
    if delta & 0x2000000:
        delta -= 0x4000000
    assert address + delta * 4 == target, hex(address)
assert read_rva(0x61e7fdc, 4) == bytes.fromhex('17c87392'), '64-bit GC handle mask changed'
# Both LookAt overloads really exist in this build, with distinct RVAs.
assert read_rva(0xe38063c, 4) != read_rva(0xe3806f8, 4)
print(json.dumps({'build_id': ids[0], 'fingerprints_checked': len(entries),
                  'bind_coverage': 'complete', 'branch_targets_checked': len(branches),
                  'device_tested': False, 'entries': entries}, indent=2))
