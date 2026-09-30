# All-705 entry patch-window xref audit (2026-09-29)

## Read-only Ghidra query

Ran `GhidraEntryThunkSlotReferences.java` against the saved `ImVehFt.asi` Ghidra program with `-readOnly -noanalysis`, using the current 705-row `audit/function-name-map.csv` (SHA-256 `F07A948F619655EF1B7B97574541421FC9ACAAF98820E4D4A64CBCA86A2F2768`). The script queried the first five bytes of all 705 candidate entry addresses: **3,525 byte targets**, **2,346 incoming-reference rows**, with references recorded at **695** queried target bytes.

Only two references target a nonzero offset in those 705 five-byte windows:

| Slot queried | Target byte | Source | Interpretation |
|---|---|---|---|
| `0x10018f94` | `0x10018f97` (`+3`) | `0x100185e7` | This is the *next candidate entry*, not an interior byte of `0x10018f94`; the `0x10018f94` body is 3 bytes and remains in place. |
| `0x1002044b` | `0x1002044e` (`+3`) | `0x10020019` | Likewise the next candidate entry, not an interior byte; the 3-byte body remains in place. |

Neither address is one of the 148 entries currently designated for an `E9 rel32` thunk. For those 148 planned thunk windows, the saved Ghidra project recorded **zero incoming xrefs to bytes +1 through +4**. This supports the patch-window control-flow feasibility check in the analyzed snapshot; it does not exclude runtime-computed or external fixed-address entry.

Twelve candidate entries have no recorded incoming reference to byte `+0` in this saved project: `0x100014a0`, `0x100101a5`, `0x100101f2`, `0x10013a56`, `0x10016e8e`, `0x10018e60`, `0x1001a570`, `0x1001a5c0`, `0x1001b266`, `0x1001cb20`, `0x1001cdbd`, and `0x1001d906`. This is not proof they are unused; preserve their entries and do not omit their candidate implementations based only on static xrefs.

The same 148 windows intersect **97 original `.text` HIGHLOW relocation records across 18 windows** (29 fixup DWORDs fully covered, 68 partially covered). Any eventual PE builder must remove/reconcile those records for the patched bytes and regenerate the complete relocation directory. This query does not do that.

## Why the initial compact-in-`.text` layout is not acceptable

The earlier packing heuristic placed 146 moved bodies into original gaps and overlapped 255 reference rows at 207 distinct destinations across 20 placements. A fresh code-unit context query shows the overlapped destinations are not all padding: **220 are Ghidra instructions and 35 are Ghidra data units**. The rows include **50 conditional and six unconditional branch references**. Example: the proposed body placement at `0x1001d591` would cover original instructions at `0x10008890` and `0x1000892e`, which are direct destinations of branches from `0x10008843`, `0x1000888b`, and other instruction sites. The rest include address-table/data references, including references into CRT routines. These spans must not be reused without a proved redirection or preservation strategy.

This rejects that particular compacting plan, not the candidate sources. The plausible image-layout direction is to leave referenced legacy ranges intact and place the 148 thunked candidate bodies in a newly allocated executable section, while retaining the 557 bodies that fit their own slots. That is only a layout hypothesis: the `.xcode` section, object/data relocation application, import/startup integration, and loader/game behavior have not been built or validated. In particular, some original cross-function references still land inside candidate-function interiors; each must be classified as live alternate entry, self/jump-table data, or an obsolete path before claiming full semantic replacement.

## Reproduction artifacts

- Entry query output: `ghidra_exports/all-705-entry-slot-xrefs-20260929.csv` (SHA-256 `876E824E4E6AA446EB721CF4B3F3F8B76C10E0388C5EB2B7E40EB415E9BB669C`).
- Full-range non-entry references: `ghidra_exports/text-nonentry-reference-audit-20260929.csv`.
- Ghidra code-unit context: `ghidra_exports/text-nonentry-codeunit-context-20260929.csv` (SHA-256 `E51C15F7C9FA32443B5634A39BCE647A42552F0A99CC1C54398BECA6940070B2`).
- Entry thunk/HIGHLOW overlap: `audit/entry-thunk-relocation-overlap-o1-x87-frame-coff-exact-2026-09-29.json`.
- Invalid heuristic placement collisions: `audit/inplace-text-packing-xref-overlap-o1-x87-frame-2026-09-29.json`.

All these are static evidence from the pinned original ASI and saved Ghidra database. They are not runtime proof, and no production PE/ASI was emitted.
