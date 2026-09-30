# `___mtold12` (`0x10020564`) digit-accumulator differential

Date: 2026-09-28. This is a bounded conversion-helper comparison, not a
production ASI or full CRT/game test.

- Ghidra shows a 12-byte output accumulator. The caller at `0x1001eb27`
  explicitly normalizes input characters with `c - '0'`, removes trailing
  zero digits, and only calls `___mtold12` with a nonempty digit sequence.
  Thus the helper's `char*` input contains numeric byte values `0..9`, not
  ASCII digit characters. Tests below follow that observed caller contract.
- The strict candidate is 371 bytes, has zero COFF relocations, no original
  HIGHLOW overlap, and fits its 484-byte entry gap. Capstone decoded all 141
  instructions; all 19 direct control-flow targets are inside the candidate
  body. Full-span Ghidra xrefs cover 486 byte-target rows; no external
  reference enters the overwritten interior.
- Probe:
  `build/pe-layout-probe/mtold12-10020564-probe-not-asi.bin`, SHA-256
  `A644C62E3A44ECD4DFFC48BE7AF845C4FD8405C8E4564A4FA4C7AF1270371CA2`.
  It changes 367 bytes, all within the function body.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness compared the full
  12-byte output from original and candidate mapped as `SEC_IMAGE`. **8 named
  sequences and 100,000 deterministic randomized normalized inputs** of 1-25
  digits passed; first and last digits were nonzero, with internal zeros
  allowed, matching the caller's preconditions.
- Harness SHA-256:
  `20BD99E75922BC2870543190CBF313F286FE5B9133BE22E153CDDC26DC44499C`.

This validates the helper over the tested normalized digit inputs; it does not
cover caller/parser integration, every CRT locale/rounding path, or gameplay.
