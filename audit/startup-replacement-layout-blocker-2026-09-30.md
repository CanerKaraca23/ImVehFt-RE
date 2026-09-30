# Startup replacement bodies do not fit current appended slots

## Finding

The current v7/v8 appended-code layout was sized using the pre-fix MSVC objects. The corrected startup bodies are larger than their existing assigned slots, so replacing only their bytes in v8 would overlap the following function body. No such patch was made.

| Function | Assigned entry VA | Next assigned body | Available bytes | Old `.xcode` size | Corrected `.xcode` size | Overflow |
|---|---:|---:|---:|---:|---:|---:|
| `__CRT_INIT_12` (`10010f59`) | `0x1004B240` | `0x1004B380` (`10011032`) | 320 (`0x140`) | 316 (`0x13C`) | 329 (`0x149`) | 9 |
| `___DllMainCRTStartup` (`100110bd`) | `0x1004B3A0` | `0x1004B470` (`100111E0`) | 208 (`0xD0`) | 207 (`0xCF`) | 218 (`0xDA`) | 10 |

Evidence:

- Assigned body targets are from `audit/candidate-text-direct-bodies-plus-421-thunks-20260930.json`.
- Old sizes are from the pre-startup-fix full object set `build/recheck/strict-xcode-nogs-o1-live-rerun-20260930/`.
- Corrected sizes are from the fresh full build `build/recheck/strict-xcode-nogs-o1-ghidra-cleanup-exact-20260930/`.
- The corrected bodies independently match their normalized Ghidra instruction streams: CRT_INIT 99/99 and DllMain 87/87. Reports: `audit/instruction-parity-10010f59-full705-ghidra-cleanup-2026-09-30.json` and `audit/instruction-parity-100110bd-full705-ghidra-cleanup-2026-09-30.json`.

## Consequence and required follow-up

The v8 candidate predates both current bodies. In-place replacement would overwrite the next assigned roots by 9 and 10 bytes, respectively, and the new object DIR32 relocation sites also move. The next candidate must therefore use a refreshed body placement map and regenerated fixup/base-relocation data; entry-thunk targets and any callers of these functions must be checked against the new locations. Until that full relayout is verified, v7/v8 remain known-crashing experimental candidates and the current sources are not represented by a game-testable ASI.

The original ASI is unchanged (SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`).
