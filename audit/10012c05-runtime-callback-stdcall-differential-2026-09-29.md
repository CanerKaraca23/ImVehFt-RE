# `10012c05` `__cinit` runtime-callback ABI correction and differential

Date: 2026-09-29. Reference ASI SHA-256:
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Assembly finding and candidate change

The original bytes at `0x10012c8a` push the three callback arguments
`0, 2, 0`. At `0x10012c92`, the code performs `CALL DWORD PTR [0x1003d554]`;
the function then immediately executes `XOR EAX,EAX; POP EBP; RET` at
`0x10012c98`. There is no caller-side `ADD ESP,0x0c` after the indirect call.
This establishes callee stack cleanup for this callback. The candidate had
declared it `__cdecl`; changed its `RuntimeFunction` type to `__stdcall`.
The previous source is preserved as
`src/functions/10012c05.cpp.pre-runtime-callback-stdcall-20260929.bak`.

## Differential test

Added `tests/runtime_10012c05_cinit_data_aliases.asm` and
`tests/runtime_10012c05_cinit_original_differential.cpp`. The x86 harness maps
the hash-pinned original image at its preferred base, redirects only the
external CRT-service calls to controlled stubs, and runs the original and
candidate `__cinit` against matching initializer tables. An independent
dispatcher oracle checks trace order and return behavior. Cases cover the
floating-point callback gate, pre-initializer early failures, atexit callback
registration, 24 runtime initializer slots, the optional three-argument
callback, and stack cleanup. The randomized sequence is deterministic.

Result: **10,005/10,005 cases passed** (5 directed and 10,000 randomized).
Original, candidate, and oracle traces/results matched, including the
callee-cleanup callback ABI and `__cinit` caller-cleanup stack state. Build:
VS 2022 x86 `/O1 /W4 /WX /MT /arch:IA32`; candidate object was freshly
compiled from the corrected source.

## Current structural checks

- Fresh ReAgent objective run: 705 PASS, 0 FAIL, 0 UNKNOWN in
  `audit/objective-cinit-stdcall-2026-09-29.json`.
- Fresh ReAgent parity run: 705 GREEN, 0 YELLOW, 0 RED in
  `build/parity-cinit-stdcall-2026-09-29.json`.
- Source manifests refreshed for all 705 units; pre-refresh copies were
  preserved with `.pre-runtime-callback-stdcall-20260929.bak` suffixes.
- Fresh strict x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` full-set build:
  705/705 passed, 0 failed, in
  `build/strict-xcode-nogs-o1-cinit-stdcall-20260929.json`.

## Limits

This is a focused function-level differential, not semantic validation of all
705 functions. CRT service routines (`__IsNonwritableInCurrentImage`,
`__initp_misc_cfltcvt_tab`, `_atexit`) and initializer callbacks are controlled
stubs. Real CRT startup state, the full project link, production PE/ASI layout,
GTA loading, and gameplay are not covered. No changes were made to the
reference ASI.
