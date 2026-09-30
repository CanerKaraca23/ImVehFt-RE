# Appended 425-body external game-code target presence check — 2026-09-29

This checks the direct-address targets named by the current 425-thunk COFF
relocation inventory against the installed GTA SA executable. It does not
resolve candidate addresses inside the rebuilt ASI, or validate call ABI.

Inputs:

- `audit/appended-thunk-link-map-resolution-conservative-425-2026-09-29.json`
- `C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe`
- PE image base `0x00400000`; SHA256 `F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`

The 13 GTA/RenderWare direct-code targets referenced by the current 425-body
link-map inventory all translate to file-backed addresses inside the original
executable's `.text` section. Their target entry bytes are:

| COFF target name | VA | Raw bytes at VA |
|---|---:|---|
| `_FUN_727be0` | `0x00727BE0` | `8B 44 24 08 50 50 50 50 8B 44 24 14 50 E8 2E F8` |
| `_FUN_0052cee0` | `0x0052CEE0` | `8A 44 24 04 8A 54 24 08 3A C2 90 E9 F3 48 ED FF` |
| `_FUN_7ee180` | `0x007EE180` | `8B 44 24 04 89 44 24 04 FF 60 1C 90 90 90 90 90` |
| `_FUN_7ee190` | `0x007EE190` | `8B 44 24 04 89 44 24 04 FF 60 18 90 90 90 90 90` |
| `_FUN_7f9fb0` | `0x007F9FB0` | `A1 48 24 8E 00 56 8B 74 24 08 3B C6 74 23 A1 28` |
| `_FUN_7f9ff0` | `0x007F9FF0` | `A1 4C 24 8E 00 56 8B 74 24 08 3B C6 74 23 A1 28` |
| `?FUN_00730e60@@YAHI@Z` | `0x00730E60` | `83 EC 18 56 8B 74 24 20 8D 44 24 14 50 8D 4C 24` |
| `?FUN_007ec9d0@@YAHIPAFH@Z` | `0x007EC9D0` | `83 EC 08 53 8B 5C 24 10 55 56 8B 03 57 48 83 F8` |
| `?FUN_007ed2d0@@YAHIHPAHPAE@Z` | `0x007ED2D0` | `83 EC 0C 8D 44 24 04 8D 4C 24 10 8D 54 24 00 56` |
| `?FUN_007f3600@@YAHXZ` | `0x007F3600` | `A1 24 7B C9 00 8B 0D 4C 7B C9 00 56 68 16 00 03` |
| `?FUN_007f36a0@@YAXH@Z` | `0x007F36A0` | `A1 4C 7B C9 00 8B 0D 24 7B C9 00 53 8B 5C 24 08` |
| `?FUN_007f3730@@YAXHIH@Z` | `0x007F3730` | `8B 4C 24 04 53 55 56 8B 41 08 57 8D 79 08 3B C7` |
| `?FUN_007f3980@@YAXHH@Z` | `0x007F3980` | `8B 44 24 08 8B 48 04 85 C9 74 11 8B 48 0C 8B 50` |

This verifies that the encoded addresses exist in the expected external game
image and are executable-section targets. The RenderWare lifecycle/control
flow for several of these is independently visible in
`audit/mext-owned-texture-lifecycle-2026-09-29.log` and the saved Ghidra
decompilation; the table alone is not a complete function-boundary, signature,
calling-convention, version-compatibility, or runtime proof. The relocation
table's final candidate values must still target these exact runtime VAs, and
the final ASI must still pass loader and in-game tests.
