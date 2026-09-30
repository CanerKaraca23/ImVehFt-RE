# `_strlen` (`0x10011650`) in-place differential

Date: 2026-09-28. This is a bounded binary differential probe, not a production
ASI or GTA runtime test.

## Construction evidence

- Original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Ghidra maps `_strlen` to `0x10011650` through `0x100116DA`. Its decompiler
  infers a 32-bit load in the initial unaligned-byte loop; disassembly of the
  original bytes shows `mov al, byte ptr [ecx]`, confirming that the candidate's
  byte read matches the actual machine instruction semantics.
- The strict x86 candidate is 115 bytes, has no COFF relocations, no original
  HIGHLOW overlap, and fits the next-entry gap. Capstone decoded the full
  candidate as 54 x86 instructions. All seven direct branch targets land at
  candidate instruction boundaries inside its replacement span; none enters
  the preserved tail.
- Fresh Ghidra xrefs cover 152 target-byte rows through the old body end. No
  external reference enters the overwritten interior.
- Probe:
  `build/pe-layout-probe/strlen-10011650-probe-not-asi.bin`, SHA-256
  `DADDEEC215476C1F8A4087BE671D562D4D13118F0B1E73D8D6F3E72B4A4476A7`.
  It changes 110 bytes, all within the 115-byte function span. File size,
  PE-header offset, section count, image base, entry point, and all 16 data
  directory bytes remain unchanged.

## Differential result

MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` mapped the original and probe as
`SEC_IMAGE` and compared returned lengths for the same valid strings:

- **68 named cases** spanning all four starting alignments and lengths from
  0 through 4,091 bytes;
- **100,000 deterministic randomized** strings with varied alignment and
  length;
- **256 guard-page boundary** strings ending at the final accessible byte.

All cases passed. Harness SHA-256:
`03071AABE780AFEB67D5DCF8B0A9FF15B428DAD6E39284D723C2FFB8CEF52754`.

This proves equality for the tested string domain and mapped-image patch
mechanism for this candidate. It does not establish every possible memory
fault/invalid-pointer behavior, CRT-wide equivalence, startup/import/hook
compatibility, or gameplay.
