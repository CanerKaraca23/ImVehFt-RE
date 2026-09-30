# Exact COFF body-size entry-slot reconciliation

## Finding

The prior trampoline feasibility report derived candidate body lengths from linker-map COMDAT extents, while the in-place relocation audit measured the actual `.xcode` raw section in each COFF object. Those are different quantities: for example, `0x10001040` has a 761-byte object body but an 802-byte map extent. That caused the prior 429 direct-fit / 275 thunk estimate to disagree with the object audit.

`scripts/audit-entry-trampoline-feasibility.py` now accepts `--body-report` and, when supplied, uses each COFF audit's `candidate_body_size` for slot-fit decisions. Link-map symbols remain in use only for executable-target and rel32 reachability checks. The original script was preserved as `scripts/audit-entry-trampoline-feasibility.py.pre-coff-body-size-input-20260929.bak`.

## Fresh result

- `audit/entry-trampoline-feasibility-o1-manual-cookie-coff-body-exact-2026-09-29.json`: 705/705 executable targets resolved; 556 full bodies fit their bounded slots, 148 need a 5-byte rel32 entry thunk, and the final candidate fits the remaining `.text` tail. Minimum thunk slot is 8 bytes; all thunk displacements are in range. This reconciles exactly with the COFF-size in-place audit.
- `audit/inplace-candidate-relocation-coverage-o1-manual-cookie-coff-body-exact-2026-09-29.json`: same 556 fitting / 148 too-large split; 2,389 DIR32 and 2,053 REL32 relocations still need final-target-aware handling. It reports 1,868 original HIGHLOW overlap instances among fitting bodies (2,772 across all bodies, including oversized bodies).
- `audit/candidate-relocation-symbol-targets-o1-manual-cookie-coff-body-exact-2026-09-29.json`: all 4,442 COFF relocations found a unique diagnostic-map resolution (zero missing/ambiguous), but diagnostic addresses are not production targets. DIR32 target semantics, data placement, image-base fixups, startup/imports, hooks, and runtime remain unresolved.
- `py -m py_compile scripts/audit-entry-trampoline-feasibility.py` and `git diff --check -- scripts/audit-entry-trampoline-feasibility.py` pass.

This is a placement-feasibility reconciliation only. No PE bytes were changed; the diagnostic DLL remains non-installable, and this is not semantic or GTA runtime validation.

## Entry-thunk/base-relocation cross-check

The source ASI SHA-256 was rechecked against the overlap audit's pinned identity. The 148 planned thunk windows intersect 18 original `.text` HIGHLOW DWORDs: two wholly overwritten and 16 partially intersected. A scan of all 705 Ghidra exports with assembly found no direct `CALL`/`JMP` target into a thunk's interior bytes (`entry+1..entry+4`). This is useful bounded evidence, not proof against indirect control flow, function pointers, or unexported/ownerless code. A final image builder must reconcile all 18 fixup records, and safety of removing them remains unproven until all alternate references and runtime behavior are checked.

Reproducible report: `audit/entry-thunk-ghidra-crossrefs-o1-manual-cookie-v4-2026-09-29.json` (includes both export-scan findings and xrefs read from the existing Ghidra project); script: `scripts/audit-entry-thunk-ghidra-crossrefs.py`. Raw read-only query output is `audit/ghidra-entry-thunk-byte-xrefs-o1-manual-cookie-2026-09-29.csv`. The headless query ran with `-readOnly -noanalysis`, so it did not commit changes to the project or modify the original PE.

The project ReferenceManager query covered all 740 byte addresses in the 148 five-byte patch windows: none of the 592 interior bytes (`entry+1..entry+4`) had a recorded incoming reference; 144 entry bytes had incoming references and four did not. This is stronger than scanning decompiler `data_refs` (empty in these exports), but it remains bounded to references already represented in the saved Ghidra database. It does not establish the absence of runtime-computed pointers or undiscovered code/data references.

The four thunk entries without a recorded incoming reference are `0x1001a570`, `0x1001a5c0`, `0x1001cb20`, and `0x1001cdbd`. They are not presumed dead: indirect dispatch, external patching, or incomplete Ghidra references still need investigation before deciding how their entry slots are used.
