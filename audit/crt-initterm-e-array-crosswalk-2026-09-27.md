# CRT `_initterm_e` initializer array crosswalk

Date: 2026-09-27. Reference binary: local ImVehFt ASI, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Array and execution order

Ghidra's exact `__cinit` assembly pushes end address `0x100221d0`, then start
address `0x100221b8`, and calls `__initterm_e` (`0x10012be1`). The helper
walks `[start,end)` in 4-byte increments and returns immediately on the first
nonzero initializer result. A read-only byte probe of the six slots confirms
one null sentinel followed by five initializer addresses:

| Slot | Stored value | Candidate mapping | Observed behavior |
|---|---|---|---|
| `0x100221b8` | `0` | — | Null entry skipped |
| `0x100221bc` | `0x100104bc` | Not an exact 705 entry | Allocates 0x20 bytes, calls the `EncodePointer` IAT slot at `0x1002205c`, writes two CRT data globals; returns 0 on allocation success and 0x18 on failure |
| `0x100221c0` | `0x10013025` | Not an exact 705 entry; adjacent to `FUN_1001301f` but begins after its six-byte `MOV EAX,imm32; RET` body | Allocates and initializes CRT lock/state tables; defaults a count to 0x200 (minimum 0x14), returns 0 on success or 0x1a on failure |
| `0x100221c4` | `0x100148e9` | `src/functions/100148e9.cpp` (`___initmbctable`) | Sets the multibyte code page to -3 when not initialized; returns 0 |
| `0x100221c8` | `0x1001704c` | Not an exact 705 entry; 16 bytes before `_abort` entry `0x1001705c` | Calls imported `IsProcessorFeaturePresent(10)`, stores the result to `0x1003c414`, returns 0 |
| `0x100221cc` | `0x1001c5e0` | Not an exact 705 entry; 16 bytes before candidate entry `0x1001c5f0` | Calls imported `IsProcessorFeaturePresent(10)`, stores the result to `0x1003c40c`, returns 0 |

The exact slot bytes are in
[`crt-initterm-e-array-bytes-ghidra-2026-09-27.csv`](crt-initterm-e-array-bytes-ghidra-2026-09-27.csv).
Ghidra's read-only symbol/xref query resolves `0x1002205c` as
`PTR_EncodePointer_1002205c` and `0x1002210c` as
`PTR_IsProcessorFeaturePresent_1002210c`; results are in
[`crt-initterm-e-symbol-xrefs-ghidra-2026-09-27.csv`](crt-initterm-e-symbol-xrefs-ghidra-2026-09-27.csv).
The bounded code windows and branch-tail decodes are recorded in
[`crt-initterm-e-entry-disassembly-2026-09-27.csv`](crt-initterm-e-entry-disassembly-2026-09-27.csv),
[`crt-initterm-e-branch-disassembly-2026-09-27.csv`](crt-initterm-e-branch-disassembly-2026-09-27.csv),
[`crt-initterm-e-size-tail-disassembly-2026-09-27.csv`](crt-initterm-e-size-tail-disassembly-2026-09-27.csv),
and [`crt-initterm-e-allocation-cleanup-disassembly-2026-09-27.csv`](crt-initterm-e-allocation-cleanup-disassembly-2026-09-27.csv).
The temporary-function decompilations are in
[`crt-initterm-e-entry-decompilations-2026-09-27.csv`](crt-initterm-e-entry-decompilations-2026-09-27.csv).
For `0x10013025`, the temporary Ghidra function body's recorded `body_max`
(`0x10013038`) is shorter than the decompiler's recovered control-flow body
(which reaches `0x100130d5`). Treat that metadata bound as incomplete; the
separately recorded branch and instruction windows corroborate the allocation,
fallback, state-table initialization, and return paths. They were decoded in
temporary Ghidra imports with auto-analysis disabled;
the saved Ghidra project was only queried `-noanalysis -readOnly` for bytes
and symbols.

## Link and fidelity implications

The `_initterm_e` array is separate from the 24-slot `.CRT` initializer array
at `0x10022154..0x100221b4`. The candidate `__cinit` source correctly calls
`__initterm_e` before registering the later exit callback and traversing the
second array, but its `DAT_100221b8` and `DAT_100221d0` references are external
symbols with no definition in the 705-object archive. The five initializer
entries are not equivalent to five ordinary function aliases: four point to
noncandidate entry bodies with global writes, failure returns, and imported
calls. Replacing the array with nulls or redirecting entries to nearby
candidate starts would skip or alter CRT initialization and error propagation.

This is static binary evidence only. No candidate sources were changed for
this audit, no complete plugin link was produced, and no game runtime test was
performed.
