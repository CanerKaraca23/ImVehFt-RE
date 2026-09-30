# Current 705-object original-IAT API call patch plan — 2026-09-30

Re-ran the x86 IAT call-thunk verifier against the saved MASM COFF object and
the pinned original-IAT crosswalk, then inventoried all current candidate
objects and recomputed every API `CALL rel32` displacement using the current
283-in-place / 422-appended placement plan.

- 21 unique API thunks are verified as exact six-byte `FF 25 imm32` bodies,
  with 21 `DIR32` relocations to their corresponding original-IAT symbols.
- Across all 705 candidate COFF objects, 196 API `CALL rel32` sites in 45
  functions map to those thunks: 139 are in-place callsites and 57 are in
  appended bodies. The displacement range is 26,210 through 354,530 bytes;
  all are within signed x86 `rel32` range, and zero non-REL32 API code
  references were found.
- The planned thunk payload is 126 bytes after five alignment bytes. Adding
  its 21 HIGHLOW records expands the current 6,115-site relocation table to
  6,136 sites / 12,860 bytes; it round-trips exactly and fits the original
  `.reloc` section.
- Full machine-readable patch list:
  `audit/current-api-call-rel32-patch-plan-2026-09-30.json`.
- Exact six-byte thunk object audit:
  `audit/original-iat-api-thunks-current-coff-verification-2026-09-30.json`.
- All-object raw reference inventory:
  `audit/candidate-original-iat-api-rel32-references-current-2026-09-30.json`.

This computes a proposed payload and the exact callsite patch values but does
not write candidate bodies, merge this payload into the 422-body section,
construct a final PE, or execute the image. Its appended RVA is provisional;
other helper/CRT/provider targets and startup/import integration remain open.
No production ASI or GTA runtime validation resulted.
