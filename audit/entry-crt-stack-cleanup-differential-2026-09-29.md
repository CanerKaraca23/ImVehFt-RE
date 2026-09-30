# Entry CRT stack-cleanup correction and differential

Date: 2026-09-29.

## Ghidra evidence and correction

The pinned original `ImVehFt.asi` entry at `0x100111b3` pushes
`[EBP+8]` before calling `___DllMainCRTStartup`, then executes `POP ECX`,
`POP EBP`, and `RET 0x0c`. This proves the CRT callee leaves that one pushed
argument for the entry wrapper to remove. The candidate declared the target as
`__fastcall`, which caused MSVC to assume callee cleanup; the first differential
harness also used a normal C++ `__fastcall` stub and therefore modeled the
wrong behavior. Its access violation is invalid test evidence, not evidence
that the original entry itself faults.

`src/functions/100111b3.cpp` now uses a small MSVC x86 naked wrapper to preserve
the original hotpatch prologue, argument forwarding, and caller cleanup
instruction-for-instruction. The emitted function body is 33 bytes, matching
the original entry slot length. Before editing, the source was saved as
`src/functions/100111b3.cpp.pre-crt-caller-cleanup-20260929.bak`.
The intermediate C++/`add esp,4` version was separately preserved as
`src/functions/100111b3.cpp.pre-exact-entry-assembly-20260929.bak`.

## Verification

- New x86 harness stub records ECX, EDX, and the stack argument, returns the
  controlled result, and deliberately leaves stack cleanup to the caller, as
  shown by the original wrapper assembly.
- Candidate vs. original-assembly oracle: 10,000 deterministic argument cases,
  including attach/detach values: **0 mismatches**.
- Fresh object disassembly matches the original entry's complete 33-byte
  instruction sequence (the two call displacements are COFF relocations).
- Fresh strict MSVC x86 build of all 705 units: **705/705** (see latest
  `entry-exact-20260929` reports).
- Fresh independent objective check: **705 PASS / 0 FAIL / 0 UNKNOWN**.
- Fresh ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**; the 13 scoped
  call-count-only adjudications pass their guard, and the existing
  `0x100076d0` callback/re-entry limitation remains open.
- Rebuilt alloca helpers against this fresh object set: **57/57 stack-growth
  checks**, no exception, thread exit 0.
- Relinked all 705 objects with the diagnostic link recipe and reran entry
  placement analysis: all 705 entry symbols resolve in executable sections;
  429 bounded slots fit full bodies, 275 need 5-byte relative trampolines and
  all are in range. The `0x100111b3` body fits. This output remains a
  diagnostic DLL, not an installable ASI; original data-section placement and
  runtime initialization are still unresolved.
- Fresh in-place relocation classification finds 2,664 candidate DIR32 and
  2,183 REL32 relocations. Of the 429 bodies whose code size fits, 303 overlap
  1,274 original `.text` HIGHLOW sites. The fresh diagnostic PE has 6,391
  HIGHLOW fixups and 6,570 raw target hits (182 not classified as fixup hits).
  No combined-image relocation rewrite has been applied; this is the next
  integration gate, not a pass.
- Follow-up field crosswalk:
  `audit/inplace-base-relocation-reconciliation-entry-exact-v3-2026-09-29.json`.
  Across fitting bodies, 1,274 old HIGHLOW fields overlap replacement bodies
  and those bodies introduce 1,182 DIR32 fields: 134 pairs start at the same
  byte, 503 pairs overlap at shifted offsets, 671 old fields intersect no new
  DIR32 field, and 562 new DIR32 fields intersect no old HIGHLOW field. 31 old
  fields straddle a candidate body's end. These are geometric classes only;
  target values and correct PE relocation-table edits remain to be established
  from each instruction and symbol.

These checks validate the entry wrapper's modeled ABI and the listed static
and focused runtime gates. They do not produce a production ASI, prove all 705
functions semantically equivalent, resolve the remaining whole-image data and
relocation layout, or validate loading and gameplay in GTA San Andreas.
