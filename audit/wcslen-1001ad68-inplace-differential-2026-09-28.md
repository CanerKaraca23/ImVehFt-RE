# `_wcslen` (`0x1001ad68`) in-place differential

Date: 2026-09-28. This is one function's bounded binary comparison, not a
production ASI or GTA runtime test.

- Ghidra identifies the function at `0x1001AD68` and decompiles a 16-bit
  terminator scan returning the number of wide characters before NUL.
- The strict candidate body is 23 bytes, has zero COFF relocations, overlaps no
  original HIGHLOW fixup, and fits its next-entry gap. Capstone decoded all 10
  candidate instructions; its one direct loop branch remains inside the new
  body. Full-span Ghidra evidence covers 28 byte-target rows; no external
  reference enters the overwritten interior.
- The separate probe is
  `build/pe-layout-probe/wcslen-1001ad68-probe-not-asi.bin`, SHA-256
  `C2E2E013A476F90C07726F95B33C74CC4D98E61AB1C5685425141461E7EDB732`.
  It differs from the pinned original in 22 bytes, all inside the 23-byte body.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness mapped both PE files
  as `SEC_IMAGE` and compared original/candidate return lengths. **32 named**
  cases across 2-byte and 4-byte alignment, **100,000 deterministic
  randomized** strings, and **128 guard-page-boundary** cases passed. The
  terminator was placed at the last accessible UTF-16 code unit for boundary
  tests.
- Harness SHA-256:
  `7FD3405D2A770ED9762066F6F09408CED130E2A94A7711B2BA3FCAA5168CB5F3`.

This covers valid NUL-terminated 16-bit strings in the tested range; it does
not prove invalid-pointer/fault behavior, full CRT compatibility, whole-image
startup, or gameplay.
