# `___AdjustPointer` (`0x1001cf82`) differential

Date: 2026-09-28. This validates a bounded C++ RTTI-style PMD pointer
adjustment helper; it is not a production ASI or gameplay test.

- Ghidra shows the non-virtual path adds the member displacement. When the
  vbtable displacement (`pdisp`) is nonnegative, it additionally loads the
  vbtable pointer from the object, reads the signed virtual-base adjustment at
  `vdisp`, then adds that adjustment and `pdisp`.
- Candidate body is 35 bytes, has zero COFF relocations, overlaps no original
  HIGHLOW field, and fits its entry gap. Capstone decoded all 15 instructions;
  its conditional target is inside the replacement body. Full-span Ghidra
  xrefs cover 44 byte-target rows; no external reference enters the replaced
  interior.
- Probe:
  `build/pe-layout-probe/adjust-pointer-1001cf82-probe-not-asi.bin`, SHA-256
  `D4787D1EC68C16F431300865B52AF30549E346B96D116871F959A585EF9FF3AF`.
  It changes 32 bytes, all within the function body.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness built safe
  synthetic object/vbtable layouts and compared returned 32-bit addresses
  against the Ghidra-derived PMD formula. **8 named virtual/non-virtual cases
  and 100,000 deterministic randomized cases passed** against both original
  and candidate.
- Harness SHA-256:
  `A7E5A8141DD86069663252CDA8754482822FC370EFD443BD48BB0359C1581B21`.

This covers the generated in-bounds PMD layouts, not malformed descriptors,
all RTTI/runtime cases, or full-image/game behavior.
