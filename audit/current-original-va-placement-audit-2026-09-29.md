# Current original-VA placement and code-relocation audit — 2026-09-29

This supersedes the older `429 in-place / 275 thunk` and `147 thunk` layout
estimates for the current candidate objects. Inputs are the pinned original
ASI (`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`),
the fresh strict `/O1 /GS-` object directory
`build/recheck/strict-xcode-nogs-o1-1001cb37-add-esp-20260929`, and saved
Ghidra exports dated 2026-09-29.

## Current conservative placement inventory

- Of 705 candidate bodies, **280** are assigned to replace their original
  spans in place; their candidate ends are on a linearly decoded original
  x86 instruction boundary and the saved Ghidra non-entry xref export has no
  reference into their replacement span.
- **425** are assigned to an appended code/data section plus a five-byte
  `E9 rel32` entry thunk. This includes 44 functions whose old HIGHLOW-bearing
  instruction crossed the candidate-sized end; checking all remaining direct
  candidates found 231 more body ends that cut an original instruction; three
  further direct candidates had saved interior xrefs. The final counts are
  `280 + 425 = 705`.
- The saved Ghidra entry-window export records no xrefs to offsets `+1..+4`
  for the 425 proposed thunk windows. It records 64 old `.text` HIGHLOW fields
  overlapping those five-byte patches; these must be removed from the final
  base-relocation set.
- Ghidra's non-entry export has 92 references into preserved old bodies after
  their thunk windows: 90 `DATA` references across six functions and two
  unconditional branches into `__NLG_Notify` and
  `__startOneArgErrorHandling`. The direct-body set's three xref-bearing
  functions were moved to the thunk set, leaving zero recorded interior
  references in the 280 spans. Absence of static xrefs is not proof against
  runtime-computed or external references.

## Full candidate-code relocation-site set

The current reconciliation removes **949** original HIGHLOW fields whose
bytes are changed by either the 280 in-place bodies or 425 thunk windows,
then adds **799** COFF DIR32 sites for the in-place candidate bodies and
**1,588** for appended code plus its referenced local `.rdata`. The resulting
site set contains **6,119** HIGHLOW relocations. It serializes and reparses
exactly to a **12,824-byte** relocation directory, fitting the original
`.reloc` section (16,196 virtual bytes / 16,384 raw bytes).

Artifacts:

- `audit/entry-trampoline-feasibility-conservative-425-thunks-2026-09-29.json`
- `audit/inplace-candidate-original-instruction-boundaries-2026-09-29.json`
- `audit/direct-candidate-interior-ghidra-xrefs-conservative-280-2026-09-29.json`
- `audit/thunk-entry-window-ghidra-relocation-audit-425-2026-09-29.json`
- `audit/inplace-base-relocation-reconciliation-conservative-280-bodies-2026-09-29.json`
- `audit/appended-thunk-relocation-targets-conservative-425-2026-09-29.json`
- `audit/appended-thunk-payload-census-conservative-425-2026-09-29.json`
- `audit/all-705-candidate-code-relocation-directory-conservative-2026-09-29.json`
- `build/pe-layout-probe/all-705-candidate-code-relocs-conservative-2026-09-29.bin`

This is materially better placement/relocation evidence, **not a built or
loadable ASI**. Candidate DIR32 target values still need final-address
resolution/application; the 705-object data/global providers, imports, CRT
startup/installer hooks, original build recipe, PE section/header mutation,
loader test, and GTA runtime/game test remain open. No candidate C++ source or
the pinned original ASI was modified in this pass; therefore the earlier
705-object compile/objective/parity reports were not rerun by this layout-only
audit.
