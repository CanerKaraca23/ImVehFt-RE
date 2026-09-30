# `FUN_10003fe0` in-place differential probe

Date: 2026-09-28. This is a single-function binary differential, not a
production ASI build or a GTA runtime test. The original ASI was not modified.

## Evidence and construction

- The hash-pinned original is `ImVehFt.asi`, SHA-256
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Ghidra 12.1.3 identifies `FUN_10003fe0` at VA `0x10003FE0`, with analyzed
  body through `0x10003FF4`. Its pseudocode stores
  `-(param_2 != 0) & 4` at `param_1 + 2`. The independently authored candidate
  source does the corresponding byte store.
- The strict x86 candidate is 19 bytes, fits the 32-byte next-entry gap, has
  zero COFF relocations, and intersects no original `.text` HIGHLOW field.
  Its object SHA-256 is
  `579CC0393DA718B7BE76F29D803E4216EF17A2D8D08319A82B8BAB6A6382C997`.
- A fresh all-byte Ghidra reference gate covered 26 rows through the original
  body end. The patch builder rejects external references into overwritten
  interior bytes and candidate branches/references into the preserved old
  tail; neither rejection condition occurred.
- The probe was created as
  `build/pe-layout-probe/byte-flag-10003fe0-probe-not-asi.bin` from a copy of
  the original, replacing only 19 bytes at raw offset `0x33E0` (VA
  `0x10003FE0`). Probe SHA-256:
  `6DD8419BFD601BEF2EE4D69E85AB96908D130CDB77DBE25D1D25E8A70AB1293E`.
- Independent PE structure comparison confirmed equal file length (247,296),
  PE header offset, five sections, image base, entry point, and 16 data
  directories. Exactly 19 bytes differ, all in the candidate span.

## Differential test

MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` mapped original and probe as
`SEC_IMAGE` and called the function in both images with separate input buffers.
All 8 named integer inputs and 100,000 deterministic randomized integer/input
buffer pairs produced identical buffer mutations. Harness SHA-256:
`A85E4A55771A18761B25D0CB3602C54C9BBB917735218DB637C80C7EBD8D2AB1`.

This verifies the tested bounded function behavior and the in-place patch
mechanism for this candidate only. It does not prove behavior for every
possible input, the rest of the 705 functions, initialization/import/hook
compatibility, ASI loading, or GTA gameplay.
