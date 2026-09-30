# `___statfp` (`0x1002044e`) x87 status-word differential

Date: 2026-09-28. This is a controlled host x87-state test, not a production
ASI or gameplay test.

- Ghidra identifies a zero-argument CRT helper returning the current x87 status
  word as a sign-extended 16-bit value. The candidate performs `fstsw` into a
  16-bit local and returns that value.
- Candidate body: 11 bytes, zero COFF relocations, no original HIGHLOW overlap,
  fits its next-entry gap. Capstone decoded six instructions and found no
  direct control-flow targets. Full-span Ghidra xrefs covered 16 target-byte
  rows with no external reference into the overwritten interior.
- Probe:
  `build/pe-layout-probe/statfp-1002044e-probe-not-asi.bin`, SHA-256
  `3925D18686F010A47FAF2D56C85B4EB6AF82B7798A8B45F4F7173F2850B88BCE`.
  It changes 11 bytes, all inside the function body.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness established ten
  masked x87 states (clear, ordered comparisons, divide-by-zero, invalid
  operation, denormal operand, inexact operation, and stack overflow), read
  the expected status word directly, and compared both mapped implementations.
  **All ten states passed; 100,000 deterministic selections among those states
  also passed.**
- Harness SHA-256:
  `56662998DF4D8F37591190A9BB89CDA20CB739DEF7BEAADA6204C30343C2DC17`.

This verifies status-word reporting for the constructed x87 states only; it
does not validate all CRT floating-point behavior, exception delivery, or
gameplay.
