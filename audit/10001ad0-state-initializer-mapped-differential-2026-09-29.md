# `0x10001ad0` isolated state-initializer differential — 2026-09-29

## Ghidra evidence and test setup

`ghidra_exports/10001ad0.json` shows an 11-instruction `__cdecl` routine with
no recorded direct callers: it loads `DAT_1003aacc`, writes a DWORD value of
1 at `base + param_1`, then writes three zero DWORDs at the next offsets. The
candidate source is `src/functions/10001ad0.cpp`.

Added `tests/runtime_10001ad0_state_initializer_differential.cpp`. It maps the
pinned original ASI and the current diagnostic DLL without initialization,
sets each image's `DAT_1003aacc` provider to a private sentinel buffer, and
invokes the original at `0x10001ad0` and the candidate at diagnostic VA
`0x10001948`. An independent expected-buffer oracle models the four DWORD
stores, and compares every byte of both 4-KiB buffers after each invocation.

## Result

The strict x86 MSVC `/O2 /W4 /WX /MT /arch:IA32` harness passed **51,025**
cases: every byte offset from -512 through +512, plus 50,000 fixed-seed
offset/pattern cases spanning -1024 through +1024. Original, candidate, and
the independent memory-effect oracle agreed exactly, including unaligned
offsets, unchanged surrounding bytes, and guard regions.

Harness executable: `build/abi-harness/10001ad0-20260929/harness.exe`.
The prior harness source is preserved as
`tests/runtime_10001ad0_state_initializer_differential.cpp.pre-independent-memory-oracle-20260929.bak`.

## Scope limit

Ghidra records no static caller for this function, so this verifies its
isolated mapped-code memory contract only; it does not establish that the
routine participates in normal gameplay, nor validate its caller context,
plugin initialization, or GTA runtime. The diagnostic DLL is not a production
`.asi`.
