#!/usr/bin/env python3
"""Decrypts a global-metadata.dat that is protected with a repeating XOR key.

Observed on the Oxide Remake build (Unity 6000.3.27f1, metadata version 39): every byte i of the file is XORed with key[i % 32].
The key is not stored anywhere in the file; it is recovered statistically: plaintext metadata is full of 0x00 bytes (padding, small
integers), so for each of the key's positions the most frequent ciphertext byte at that position is the key byte. The result is accepted
only if the decrypted header starts with the IL2CPP sanity value 0xFAB11BAF.

Usage: decrypt_metadata.py <global-metadata.dat> <output.dat>
Exit code 0 only when the sanity check passes and every key position was decisive (most frequent byte at least 1.5x the runner-up).
"""
import collections, struct, sys

SANITY = 0xFAB11BAF

def recover_key(data, period):
    key = bytearray(period)
    weakest = 1e9
    for r in range(period):
        top = collections.Counter(data[r::period]).most_common(2)
        key[r] = top[0][0]
        weakest = min(weakest, top[0][1] / max(1, top[1][1]))
    return bytes(key), weakest

def apply_key(data, key):
    period = len(key)
    # byte-wise XOR with the key tiled over the whole length
    tiled = (key * (len(data) // period + 1))[:len(data)]
    return bytes(a ^ b for a, b in zip(data, tiled))

def main(src, dst):
    data = open(src, 'rb').read()
    if len(data) < 0x200:
        sys.exit('file too small for a metadata header')
    if struct.unpack_from('<I', data)[0] == SANITY:
        sys.exit('the file already starts with the IL2CPP sanity value: nothing to decrypt')
    for period in (32, 16, 64, 8, 4, 128):
        key, weakest = recover_key(data, period)
        head = apply_key(data[:8], key)
        if struct.unpack_from('<I', head)[0] == SANITY and weakest >= 1.5:
            out = apply_key(data, key)
            open(dst, 'wb').write(out)
            print('period=%d key=%s weakest=%.2f version=%d' % (period, key.hex(), weakest, struct.unpack_from('<I', out, 4)[0]))
            return 0
    print('no repeating-XOR key with periods 4..128 produced the sanity value: the protection is something else', file=sys.stderr)
    return 1

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    sys.exit(main(sys.argv[1], sys.argv[2]))
