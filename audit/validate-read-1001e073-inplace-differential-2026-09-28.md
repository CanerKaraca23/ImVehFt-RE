# `_ValidateRead` (`0x1001e073`) in-place differential

Date: 2026-09-28. This is a bounded function-level binary comparison, not a
production ASI or GTA runtime test.

- Ghidra decompilation shows `_ValidateRead(pointer, size)` returns whether
  `pointer` is non-null; the size argument is unused.
- The strict x86 candidate is 10 bytes, has zero COFF relocations, overlaps no
  original HIGHLOW field, and fits its mapped gap. Capstone decodes all four
  instructions; it contains no direct control-flow targets. Fresh Ghidra
  evidence covers 27 target-byte rows with no external reference entering the
  overwritten interior.
- Probe:
  `build/pe-layout-probe/validate-read-1001e073-probe-not-asi.bin`, SHA-256
  `35CB2B1D806AF6AC5837C2E0BFB2FF2D93B2A5DF66CD4679412BFFE61D9426C7`.
  It changes 10 bytes, all inside this function.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness compared original
  and probe as `SEC_IMAGE`: **24 named null/non-null pointer and size
  combinations plus 100,000 deterministic randomized pointer/size pairs
  passed**. Non-null randomized pointers were constrained to a valid local
  buffer; the function body is confirmed by Ghidra to perform no dereference.
- Harness SHA-256:
  `7A4BF5AD8738EDDBD66B982FB1B0FE6724631FF13479A75C7F9EDCD605FBEB57`.

This proves the observed return behavior for the tested inputs. It does not
validate fault behavior for invalid addresses beyond the null check, broader
CRT compatibility, PE startup/import/hook integration, or gameplay.
