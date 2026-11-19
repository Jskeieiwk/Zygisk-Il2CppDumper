# Oxide Remake: global-metadata.dat

Source: `global-metadata.dat` from the release `dump3` of this repository, 9 402 352 bytes, SHA-256 `d5e5155d376344082ce5bbc66635aa13a181c3850b6baf5f0ce67d2a7050452e`
(game build as in the on-device Il2CppDumper error: Unity 6000.3.27f1, first bytes `9D 4A C4 48` instead of `AF 1B B1 FA`).

## Measured
- Protection: a repeating XOR over the whole file. Key (32 bytes, tiled from offset 0):
  `325175b2ed9dc0aeb686e94a49faacb877a04ed4c9a25832bf475f865c17d8ad`. It is not stored in the file; `decrypt_metadata.py` recovers it from the data
  (the most frequent ciphertext byte per key position is the key byte, because plaintext metadata is full of zeros) and accepts it only when the decrypted
  header starts with the IL2CPP sanity value `0xFAB11BAF`. Every one of the 32 positions was decisive (weakest top-1/top-2 ratio 2.66).
- Decrypted file: SHA-256 `86a28455f406bd3ec883dcb18a52691e721c28a61fe7e1d9e9adece13fe13ccb`, header version **39**.
- The string table is readable (`<Module>`, `.ctor`, `get_IsWeapon`, `Assembly-CSharp`...). About 14 000 of 98 846 strings are obfuscated identifiers written in two-byte UTF-8
  characters (an identifier-renaming obfuscator, not encryption); the other ~84 000 are plain.
- Namespaces seen: `OxideOld.Weapons`, `.Game`, `.Core`, `.Player`, `.DynamicPlayer`, `.InputSystem`, `.Building`, `.Network`, `.World`, `.UI`, `.AntiCheat`;
  networking is Mirror (`MirrorServerStatus`, `mirrorPort`); `OxideOld.AntiCheat.AttestationHeartbeatChallengeMsg/ResponseMsg` exist. What the attestation checks is not known.

## Not measured / missing
- The game's `libil2cpp.so` (arm64) and package name are not in the repository; offsets, class layouts and method addresses need them (or a runtime dump with the Zygisk module of this repository,
  which reads the library's own il2cpp API and does not depend on the file's protection or on the metadata version).
- Metadata version 39 is newer than what Il2CppDumper v6.7.x parses; use a dumper that supports it, or the runtime dump above.

## Use
`python3 oxide/decrypt_metadata.py global-metadata.dat global-metadata.dec.dat`
