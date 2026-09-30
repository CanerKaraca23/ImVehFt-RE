# Current `/O1 /GS-` `__ValidateImageBase` in-place differential (2026-09-29)

## Fresh candidate and placement

- Ghidra export and the pinned-image reference audit identify
  `__ValidateImageBase` at `0x10018090`, ending at `0x100180c4`; the next
  mapped entry is `0x100180d0`.
- Used current source `src/functions/10018090.cpp` and its object from the
  latest strict `/O1 /W4 /WX /MT /arch:IA32 /GS-` full-set build, rather than
  the older `/O2` object used by the prior probe.
- Current candidate COMDAT is 47 bytes, has zero COFF relocations, fits the
  64-byte entry gap, overlaps zero original `.text` HIGHLOW fields, and has no
  recorded Ghidra incoming references into replaced interior/tail bytes.
- The new binary is a disposable copy of the hash-pinned original ASI:
  `build/pe-layout-probe/validate-image-base-single-function-o1-current-20260929-not-asi.bin`.
  Only the candidate's original `.text` window changed. Output SHA-256:
  `1D6677757D50714ED2DD26514F694471827D9E12A30EADB36ECCE1C2DDA6948A`.

## Differential result

- `scripts/test-validate-image-base-inplace-probe.ps1` rebuilt the x86 harness
  with VS 2022 and mapped both original and probe PE images as `SEC_IMAGE`.
- Five named PE-header cases and 100,000 deterministic bounded randomized
  buffers passed against the original implementation.
- Harness source SHA-256:
  `7B7D4E1B80063968454BA8787A0F6DC3C2C74419DA2DB441C13C0FEBB8D6B3C1`.
  Executable SHA-256:
  `374F62E72E5E0726A7E79B0460700B29353466167758C465CEB4F5C30C8F2913`.
- Machine placement record:
  `audit/validate-image-base-single-function-o1-current-2026-09-29.json`.

## Scope limit

This is a current-object, one-function differential and patch-mechanism test.
The probe was not loaded as a plugin/ASI, does not exercise DllMain or GTA, and
does not validate the other 704 candidates or the whole-image relocations,
imports, startup, and hook integration.
