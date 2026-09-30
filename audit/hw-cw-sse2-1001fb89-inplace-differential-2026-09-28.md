# `___hw_cw_sse2` (`0x1001fb89`) bit-field differential

Date: 2026-09-28. This is a pure-result function comparison, not a production
ASI or game test.

- Ghidra decompilation and the candidate map the x87 control-word flags,
  precision field, and rounding mode into an SSE control word. The function is
  `__fastcall`: the second input is supplied in EDX; the ignored first input
  occupies ECX.
- Candidate body is 160 bytes, has zero COFF relocations, overlaps no original
  HIGHLOW field, and exactly fills its mapped entry gap. Capstone decoded all
  45 instructions; all 14 direct branch targets land in the candidate body.
  Ghidra's 163 byte-target reference rows contain no external reference into
  the overwritten interior.
- Probe:
  `build/pe-layout-probe/hw-cw-sse2-1001fb89-probe-not-asi.bin`, SHA-256
  `911A6B4263F0CE35B7903A56EB1604731C42958591D05A2058B52BDB49E199A2`.
  It changes 133 bytes, all within this function's 160-byte span.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness compared original
  and candidate as `SEC_IMAGE` and checked results against an independently
  encoded Ghidra-derived mapping. All **1,024 combinations** of the function's
  six independent flag bits and two 2-bit fields passed, as did **100,000
  deterministic randomized ECX/EDX pairs**.
- Harness SHA-256:
  `CBEEF49011E44E9B4BC30B5C280BA4169C462B0877F2C0CEFE8FC14565F8BFDA`.

This validates the returned mask for the tested inputs; it does not prove
hardware state mutation, other CRT helpers, startup, or gameplay.
