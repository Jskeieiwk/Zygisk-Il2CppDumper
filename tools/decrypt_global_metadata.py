#!/usr/bin/env python3
"""Restores a global-metadata.dat whose *header* is protected (body is plaintext).

Observed on the StandKnife build (metadata version 39, 31 sections, header 0x17C bytes):
  * sanity (0xFAB11BAF) and version are in the clear;
  * the rest of the header is 31 records of three uint32 (offset, size, count);
  * every one of those uint32 is XORed with one 32-bit key (0xA5C3F19D in this build; libil2cpp.so
    carries it as `mov w,#0xf19d; movk w,#0xa5c3,lsl#16; eor ...`);
  * the 31 records are stored in a shuffled order, so the loader reads them at fixed shuffled slots.

Neither the key nor the shuffle is hard-coded here. Both are recovered from the file itself:
  * the section bodies are laid out back to back in the canonical il2cpp order, so after the right
    XOR the records, sorted by offset, must tile the file exactly: first offset == header size,
    each next offset == previous end (up to 3 bytes of alignment), last end == file size;
  * every distinct header word is tried as the key, and the result is accepted only if exactly one
    key (or several giving the identical header) passes that tiling test.
Records with size 0 share the offset of the following section; their relative order is only
ambiguous between identical (offset, 0, 0) records, so the result is the same either way.

Output = same file with the header rewritten in canonical order, XOR removed. The body is copied
byte for byte.

Usage: decrypt_global_metadata.py <in global-metadata.dat> <out.dat>
Exit code 0 only when the tiling test and the name check both pass.
"""
import struct
import sys

SANITY = 0xFAB11BAF
VERSION = 39
RECORDS = 31
HEADER_SIZE = 8 + 12 * RECORDS  # 0x17C
CANONICAL = (
    "stringLiteral", "stringLiteralData", "string", "events", "properties", "methods",
    "parameterDefaultValues", "fieldDefaultValues", "fieldAndParameterDefaultValueData",
    "fieldMarshaledSizes", "parameters", "fields", "genericParameters",
    "genericParameterConstraints", "genericContainers", "nestedTypes", "interfaces",
    "vtableMethods", "interfaceOffsets", "typeDefinitions", "images", "assemblies", "fieldRefs",
    "referencedAssemblies", "attributeData", "attributeDataRange",
    "unresolvedIndirectCallParameterTypes", "unresolvedIndirectCallParameterRanges",
    "windowsRuntimeTypeNames", "windowsRuntimeStrings", "exportedTypeDefinitions",
)


def decode(words, key):
    return [(words[3 * i] ^ key, words[3 * i + 1] ^ key, words[3 * i + 2] ^ key) for i in range(RECORDS)]


def tiles(records, file_size):
    ordered = sorted(records, key=lambda r: (r[0], r[1]))
    pos = HEADER_SIZE
    for off, size, _ in ordered:
        if not (pos <= off <= pos + 3):
            return None
        pos = off + size
        if pos > file_size:
            return None
    if not (0 <= file_size - pos <= 3):
        return None
    return ordered


def recover(words, file_size):
    found = {}
    for key in set(words):
        ordered = tiles(decode(words, key), file_size)
        if ordered is not None:
            found[key] = ordered
    if not found:
        return None
    if len({tuple(v) for v in found.values()}) != 1:
        raise ValueError("several keys pass the tiling test with different results: %s" % [hex(k) for k in found])
    key = min(found)
    return key, found[key]


def check_names(data, ordered):
    """The images section must resolve to printable names inside the string table."""
    sec = dict(zip(CANONICAL, ordered))
    str_off, str_size, _ = sec["string"]
    img_off, img_size, img_count = sec["images"]
    if img_count == 0 or img_size % img_count:
        raise ValueError("images section has an inconsistent size/count")
    stride = img_size // img_count
    names = []
    for i in range(img_count):
        name_index = struct.unpack_from("<I", data, img_off + i * stride)[0]
        if name_index >= str_size:
            raise ValueError("image %d: name index 0x%x outside the string table" % (i, name_index))
        end = data.index(b"\0", str_off + name_index, str_off + str_size)
        raw = data[str_off + name_index:end]
        if not raw or any(c < 0x20 or c > 0x7E for c in raw):
            raise ValueError("image %d: name is not printable ASCII" % i)
        names.append(raw.decode("ascii"))
    return stride, names


def main(src, dst):
    data = bytearray(open(src, "rb").read())
    if len(data) < HEADER_SIZE or struct.unpack_from("<I", data)[0] != SANITY:
        print("not a metadata file: bad sanity", file=sys.stderr)
        return 1
    version = struct.unpack_from("<i", data, 4)[0]
    if version != VERSION:
        print("version %d: this tool is written for %d (31 records of offset,size,count)" % (version, VERSION), file=sys.stderr)
        return 1
    words = struct.unpack_from("<%dI" % (3 * RECORDS), data, 8)
    result = recover(words, len(data))
    if result is None:
        print("no XOR key makes the records tile the file: the protection is something else", file=sys.stderr)
        return 1
    key, ordered = result
    stride, names = check_names(bytes(data), ordered)
    struct.pack_into("<%dI" % (3 * RECORDS), data, 8, *[v for rec in ordered for v in rec])
    open(dst, "wb").write(data)
    print("key=0x%08X  version=%d  header=0x%X  file=0x%X" % (key, version, HEADER_SIZE, len(data)))
    for name, (off, size, count) in zip(CANONICAL, ordered):
        print("  %-38s off=0x%08X size=0x%08X count=0x%08X" % (name, off, size, count))
    print("images: %d x %d bytes, first: %s ... last: %s" % (len(names), stride, ", ".join(names[:3]), names[-1]))
    return 0


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    sys.exit(main(sys.argv[1], sys.argv[2]))
