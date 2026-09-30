# `__cinit` exit callback correction

Date: 2026-09-27. Reference: local ImVehFt ASI, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Finding and correction

The Ghidra export for `__cinit` (`0x10012c05`) decompiles the success path as
`_atexit(FUN_10016cec)`. Its assembly pushes `0x10016cec` at `0x10012c48`,
calls `_atexit` at `0x10012c4d`, then iterates the initializer array from
`0x10022154` up to (exclusive) `0x100221b4`.

The candidate previously called `_atexit(FUN_10020870)`. That target is not the
exit callback in the original assembly: it is the first non-null initializer
in the array. Its body initializes `DAT_1003c25c` and registers
`thunk_FUN_100013e0` itself. Registering `10020870` as an exit callback would
therefore rerun initializer behavior during shutdown and fail to match the
original callback selection.

`src/functions/10012c05.cpp` now registers `FUN_10016cec`, matching the
original target. The source hash is synchronized in both source manifests.
The 24-slot initializer table is separately documented in
[`pe-relocation-code-target-site-classification-2026-09-27.md`](pe-relocation-code-target-site-classification-2026-09-27.md).

## Validation

- Fresh MSVC 2022 x86 object disassembly for `10012c05.cpp` pushes the
  `_FUN_10016cec@0` symbol immediately before calling `__atexit`; the same
  object references the expected initializer-array bounds
  `_DAT_10022154` and `_DAT_100221b4`.
- Fresh full strict compile: **705/705** TUs passed `/O2 /W4 /WX /MT`.
- Independent ReAgent structural verification: **705 PASS / 0 FAIL / 0
  UNKNOWN**; the report records the corrected source hash.
- Fresh whole-set ReAgent parity: **704 GREEN / 1 YELLOW / 0 RED**.
  `__cinit` (`0x10012c05`) is GREEN; the sole YELLOW remains `0x100076d0`.

These are source/object and static-verifier checks, not a complete plugin link
or a game runtime test. The startup thunks and original `.rdata` data provider
remain missing, as do broader global-symbol and relocation requirements.
