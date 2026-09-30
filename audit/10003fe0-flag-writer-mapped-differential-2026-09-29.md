# `0x10003fe0` flag-writer mapped differential — 2026-09-29

## Ghidra evidence

`ghidra_exports/10003fe0.json` describes six direct callers and a leaf body:
it computes `0` when `param_2 == 0`, otherwise `4`, and stores that byte at
`param_1 + 2`. The original body is 21 bytes; the candidate is
`src/functions/10003fe0.cpp`.

## Differential setup and result

`tests/runtime_10003fe0_flag_writer_differential.cpp` maps the pinned original
ASI and current diagnostic DLL without initialization. It invokes the original
entry at `0x10003fe0` and candidate at diagnostic VA `0x10003bfe`. The test
uses separate sentinel buffers, tests every valid buffer offset 0-61 with 11
edge values (including zero, positive/negative values and signed extremes),
then runs 100,000 fixed-seed random offset/value/pattern cases. An independent
byte-buffer oracle checks the designated flag byte and every untouched byte.

Result: **100,682/100,682** memory-effect cases matched for original,
candidate, and oracle. The x86 test harness was compiled with MSVC
`/O2 /W4 /WX /MT /arch:IA32` and is stored at
`build/abi-harness/10003fe0-20260929/harness.exe`.

## Scope limit

This isolates the leaf function with controlled buffers; it does not execute
any of its six callers, validate their game-state inputs, run DllMain, or test
GTA. The diagnostic DLL is not a production `.asi`.
