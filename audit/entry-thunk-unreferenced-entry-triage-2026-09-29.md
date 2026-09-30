# Triage of four thunk entries without recorded incoming references

## Scope and inputs

The current exact-COFF placement report assigns all four entries below a 5-byte `E9 rel32` thunk because each candidate body is larger than the original gap. The saved Ghidra project's ReferenceManager query and the 705 exported assembly scan recorded no incoming xrefs/direct branches for these four entries. This follow-up adds a raw-byte pointer-pattern check against the pinned original PE; it does not infer that the functions are dead or safe to omit.

Reference image: `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi`, SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`, image base `0x10000000`.

| Entry | Ghidra name | Candidate bytes / original gap | Observed static reference evidence |
|---|---|---:|---|
| `0x1001a570` | `_strcspn` | 91 / 80 | No exported Ghidra callers/data refs; no saved-project incoming xref; no direct branch target; zero raw occurrences of VA `0x1001a570` or RVA `0x0001a570` |
| `0x1001a5c0` | `_strpbrk` | 93 / 64 | No exported Ghidra callers/data refs; no saved-project incoming xref; no direct branch target; zero raw occurrences of VA `0x1001a5c0` or RVA `0x0001a5c0` |
| `0x1001cb20` | `FUN_1001cb20` | 72 / 23 | No exported Ghidra callers/data refs; no saved-project incoming xref; no direct branch target; zero raw occurrences of VA `0x1001cb20` or RVA `0x0001cb20` |
| `0x1001cdbd` | `___FrameUnwindFilter` | 80 / 79 | No exported Ghidra callers/data refs; no saved-project incoming xref; no direct branch target; zero raw occurrences of VA `0x1001cdbd` or RVA `0x0001cdbd` |

The generated entry placements still resolve to executable diagnostic-body addresses and fit signed rel32 range. The raw scan searched all file bytes for the exact little-endian 32-bit VA and image-relative RVA patterns; it was not a PE-aware typed-pointer analysis. The 2014 Plugin-SDK snapshot at `_sdk_history/snapshot-2014-04-27` remains available (commit `888a67c`), but the user-provided `.ImVehFt` mod-loader directory contains the original ASI and logs, not `.cpp`/header/project files. No exact original project/build definition was found in the workspace.

## Interpretation and remaining checks

This is converging *negative static evidence*, not proof of unreachability. It does not rule out `REL32` encodings other than decoded direct branches, split/encoded pointers, runtime-computed addresses, external code calling by fixed VA, exception/runtime registration not represented in the exported references, or code absent from the current Ghidra analysis. Do not drop these candidates or omit their address slots on this basis. The exception-filter entry especially requires review of the original exception metadata/registration path before any reachability conclusion.

Before a production image builder relies on these thunk windows, independently reconcile every overlapping HIGHLOW record with the patched bytes and final base-relocation directory, then validate entry reachability from all executable/data references and runtime registration paths. This report resolves none of those production-image requirements and is not a game-load test.
