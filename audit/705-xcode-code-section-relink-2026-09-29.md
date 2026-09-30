# 705-candidate separate-code-section relink

Date: 2026-09-29. This is a controlled layout experiment toward keeping the
original ImVehFt code-address range available for entry stubs while moving the
reconstructed candidate bodies elsewhere. It does not produce a loadable ASI.

## Candidate compilation and object integrity

- Fresh strict MSVC 14.44 x86 C++20 build with `/O2 /W4 /WX /MT /arch:IA32`
  and a forced `#pragma code_seg(".xcode")`: **705/705 compiled**. Full report:
  `build/strict-xcode-705-v2-20260929.json`.
- The independent ReAgent objective verifier was rerun against current source:
  **705 PASS / 0 FAIL / 0 UNKNOWN**, structural checks only:
  `audit/objective-independent-xcode-layout-2026-09-29.json`.
- Existing baseline COFF objects were copied and stripped of `.debug$*` sections
  into `build/recheck/strict-705-nodebug-v2-20260929/`; originals were retained.
  The reproducible tool `scripts/strip-coff-debug-sections.py` processed all
  705 objects and removed 1,296 debug sections. Its COFF verifier confirmed
  every non-debug section's bytes/flags/relocations and every defined external
  symbol unchanged.
- The same debug-only stripping was applied to the 705 `.xcode` objects at
  `build/recheck/strict-xcode-705-nodebug-20260929/`.
- `scripts/verify-xcode-object-equivalence.py` compared all 705 baseline and
  forced-section COFF objects: candidate code bytes, section flags, relocation
  targets/types, non-code runtime sections, and defined external symbols match
  exactly. Only section naming changes from `.text*` to `.xcode`; the
  non-loaded `.chks64` compiler metadata section is excluded from the
  cross-build comparison.

## Full 705-object diagnostic link

The current 705 forced-section candidate objects and existing support inputs
linked successfully with the preserved ordered response and COMDAT order file:

- PE: `build/link-probe/xcode-705-diagnostic-20260929/ImVehFt-xcode-705-diagnostic-not-ASI.dll`
- SHA-256: `E4A2B22F823D32E92A9A938139B70B58B59C28D19512D61B14EA4B599E632F5D`
- PE32/x86, base `0x10000000`, `SizeOfImage=0x72000`.
- Candidate `.xcode`: `0x10001000`, virtual size `0x230D5`, executable/readable.
- Remaining support `.text`: `0x10025000`, virtual size `0x13D1C`.
- All 705 function-body symbols resolve to executable targets; the refreshed
  entry/rel32 feasibility audit reports 705/705 targets, zero out-of-range
  displacements, 429 direct body-fit intervals, and 275 five-byte thunk cases:
  `audit/xcode-705-separated-code-entry-feasibility-2026-09-29.json`.

## What this proves and what it does not

The forced `.xcode` placement changes no candidate function bytes or runtime
relocations, and the full candidate set links into a separate executable
section. This removes the earlier overlap between relocated candidate bodies
and the addresses intended for entry stubs in the **current ordered diagnostic
image**.

The experiment does not yet include the original `.text` bytes with emitted
stubs. Its current `.xcode` starts at `0x10001000`, so it still occupies the
legacy code range; `.text` support code follows at `0x10025000`. `.rdata` and
`.data` consequently remain relocated (`0x10039000` and `0x10048000`), not at
the original `0x10022000` and `0x10029000`. The original resource/relocation
directories, startup/CRT/TLS requirements, static installer execution, and
GTA behavior have not been reconstructed or tested. Do not install or load
this diagnostic DLL.
