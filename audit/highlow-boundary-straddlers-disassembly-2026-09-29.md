# Current relocation/body-boundary disassembly check — 2026-09-29

The earlier boundary-straddler count was rechecked against the exact current
strict `/O1 /GS-` COFF directory
`build/recheck/strict-xcode-nogs-o1-1001cb37-add-esp-20260929` and the pinned
reference image (`ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`). The
reconciliation input is
`audit/inplace-base-relocation-reconciliation-current-1001cb37-2026-09-29.json`.

`scripts/audit-highlow-boundary-straddlers.py` linearly disassembled the
original x86 code from each reported function entry through the candidate
body end. Its machine-readable output is
`audit/highlow-boundary-straddlers-disassembly-1001cb37-2026-09-29.json`.

## Result

- All **44/44** original HIGHLOW fields are fully contained in one decoded
  original instruction.
- All **44/44** decoded instructions cross the current candidate body end;
  30 candidate spans end after two bytes of the four-byte relocation field,
  nine after one byte, and five after three bytes.
- The cut instructions include absolute loads/stores, indirect calls/jumps,
  and immediates. Example: entry `0x100060d0` has an original seven-byte
  indexed indirect jump at `0x10006315`, while the candidate body ends one byte
  before that instruction ends. Replacing the candidate-sized span in place
  would leave an invalid fragment, not an instruction-aligned boundary.
- The saved Ghidra entry-byte reference CSV contains each of the 44 entries;
  all have an incoming reference at byte `+0`, and none of the recorded
  references targets `+1..+4`. This only speaks to the five-byte entry window
  in that saved analysis. It does not prove that the rest of each original
  function has no interior branch/data references or runtime registration.
- A separate crosswalk against the saved full `.text` non-entry xref export
  (`C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\text-nonentry-reference-audit-20260929.csv`)
  found six references into the candidate-sized span after the first five
  bytes, all `DATA` references for `0x100060d0`; the other 43 spans had none in
  that export. The machine-readable crosswalk is
  `audit/highlow-boundary-straddlers-interior-ghidra-xrefs-2026-09-29.json`.
  The six references are consistent with code/table data in the switch-heavy
  function, but static reference type alone does not prove deadness or runtime
  reachability.

## Consequence and limit

These 44 candidates must **not** be written over their whole original
candidate-sized spans under the current in-place plan. Preserving the old body
and redirecting at the entry with a rel32 thunk is a plausible alternative,
but it is not yet approved by this report: interior references, original
HIGHLOW records intersecting the five-byte entry patch, candidate body/rdata
relocations, and complete PE loader behavior still need reconciliation.
No original image or candidate source/object was modified, and no `.asi` was
produced by this audit.

This is a byte/instruction-boundary finding, not semantic equivalence, PE
loadability, or GTA runtime proof. Reproduce with:

```powershell
python scripts/audit-highlow-boundary-straddlers.py `
  --original 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi' `
  --objects build/recheck/strict-xcode-nogs-o1-1001cb37-add-esp-20260929 `
  --reconciliation audit/inplace-base-relocation-reconciliation-current-1001cb37-2026-09-29.json `
  --output audit/highlow-boundary-straddlers-disassembly-1001cb37-2026-09-29.json
```
