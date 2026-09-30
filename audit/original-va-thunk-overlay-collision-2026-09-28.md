# Current-map collision audit for original-VA entry thunks

Date: 2026-09-28. This audit asks whether the 5-byte `E9 rel32` entry bridges
shown as *feasible* by
`build/entry-trampoline-feasibility-current-source-live-20260928-3-current-map.json`
can be written directly into that same diagnostic PE without destroying
current linked candidate code.

## Method and result

For each candidate, reconstruct its current linked `.text` COMDAT interval
from the entry symbol VA in the trampoline report and the current COFF fit
report (`coff_text_comdat_size - symbol_offset_in_comdat`). For every displaced
entry (702 total), compare the proposed five-byte patch interval at the
original VA against all 705 current candidate COMDAT intervals.

Reproduce with:

```powershell
python scripts/audit-original-va-thunk-overlap.py `
  --trampolines build/entry-trampoline-feasibility-current-source-live-20260928-3-current-map.json `
  --fit-report audit/original-entry-slot-fit-current-source-live-20260928-3.json `
  --output audit/original-va-thunk-overlay-collision-current-map-2026-09-28.json
```

The checker records input SHA-256 values in
`audit/original-va-thunk-overlay-collision-current-map-2026-09-28.json` and
refuses to overwrite an existing report.

| Measurement | Result |
|---|---:|
| Displaced candidate entries needing a bridge | 702 |
| Patch/body intersection pairs | 667 |
| Distinct patch slots intersecting candidate code | 666 |
| Slots intersecting a different candidate's body | 658 |
| Slots intersecting their own candidate's relocated body | 8 |
| Slots with no candidate-COMDAT overlap | 36 |
| Candidate COMDATs touched | 359 |

The 658 foreign-body slots cannot be patched in-place without overwriting
another current candidate body. The eight same-candidate overlaps also destroy
part of the current linked body. The 36 non-overlapping slots alone do not
make a complete 705-entry overlay safe; this comparison also excludes linked
support/runtime code and supplemental shim bodies, so it is a lower-bound
collision inventory.

## Consequence

The prior `429 body-fit / 275 thunk-fit` count describes bounded room between
reference entry addresses and next mapped entries. It does **not** establish
that thunks can be overlaid on top of this particular linked image. Before
emitting entry bridges, the candidate implementation bodies need a layout
disjoint from the original-VA thunk slots, or a new image layout must be
generated that accounts for all code and relocation edges. No PE bytes were
patched by this audit.

This confirms the current `/ORDER` diagnostic DLL cannot be turned into an
original-entry-compatible image by merely writing 702 jumps into its existing
`.text`. It remains a diagnostic DLL, not a production ASI; no GTA test was
performed.
