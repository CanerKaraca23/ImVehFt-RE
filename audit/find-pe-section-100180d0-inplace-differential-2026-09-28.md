# `__FindPESection` (`0x100180d0`) in-place differential

Date: 2026-09-28. This is a function-level synthetic-PE comparison, not a
production ASI or GTA runtime test.

- Ghidra decompilation and the candidate both locate the section table from
  `e_lfanew`, `SizeOfOptionalHeader`, and `NumberOfSections`, then return the
  first header whose `[VirtualAddress, VirtualAddress + VirtualSize)` range
  contains the requested RVA.
- The strict x86 candidate is 68 bytes, has zero COFF relocations, overlaps no
  original HIGHLOW field, and fits its next-entry gap. Capstone decoded all 30
  instructions; its four direct control-flow targets remain in the candidate
  body. Ghidra full-span xrefs covered 68 target-byte rows without external
  references into the overwritten interior.
- Probe:
  `build/pe-layout-probe/find-pe-section-100180d0-probe-not-asi.bin`, SHA-256
  `5D070A1B8C2194F38F7EF435FF23152535916AB207B623D646B2798BC5E32A2D`.
  Exactly 60 bytes differ, all within the 68-byte function body.
- A strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness mapped both
  images as `SEC_IMAGE`, constructed bounded PE section tables in writable
  buffers, and checked both implementations against the expected first-match
  header pointer. **126 named boundary/overlap cases and 100,000 deterministic
  randomized layouts/RVAs passed.**
- Harness SHA-256:
  `2E7BB101FD7031898102A681E88F08CC203BA35EA2A31AE5125FEE956AC3C3D1`.

This covers valid bounded section-table layouts in the tested domain. It does
not validate malformed-pointer fault behavior, loader initialization, other
functions, or gameplay.
