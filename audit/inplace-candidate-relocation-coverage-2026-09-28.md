# All-705 in-place candidate relocation inventory

Date: 2026-09-28. Ran
`scripts/audit-inplace-candidate-relocations.py` over the latest strict x86
object set, fresh entry-slot/placement reports, function map, and hash-pinned
original `.text` HIGHLOW inventory. Machine-readable report:
`audit/inplace-candidate-relocation-coverage-current-2026-09-28.json`,
SHA-256 `86D101FCECA918C2421CE9932746DFFE87D90052137A296AD5BFD989847055A6`.

## Placement and relocation facts

- All **705** entry symbols matched their corresponding COFF function sections.
- **429** candidate bodies fit between their mapped entry and the next mapped
  entry; **275** exceed that gap; the final entry has no following boundary.
- Of the 429 body-fit candidates, **34** have no COFF relocations, **113** have
  REL32-only relocations, and **282** include DIR32 plus/or REL32 fixups. The
  whole set contains **2,664 DIR32** and **2,182 REL32** COFF relocation
  occurrences, so most candidate bytes cannot simply be copied from their
  unlinked object sections.
- Of the 34 no-COFF-relocation bodies, **6** still overlap original PE
  HIGHLOW fields. The other **28** avoid those old fixups; these are only
  mechanical placement candidates pending Ghidra incoming-reference and
  function-specific behavior checks.
- Among all 429 body-fit ranges, 303 intersect original HIGHLOW fields
  (1,274 per-body overlaps / unique relocation sites in this sample). The
  builder must remove superseded old fixups and emit any new fixups at the
  correct candidate locations; adjacent-range crossing cases still require
  boundary review.

The single-function `__ValidateImageBase` probe previously validated one
member of this low-relocation path with a mapped-binary differential test. This
inventory does **not** prove the other 704 candidates, safe arbitrary
in-place placement, whole-image startup, or game behavior. It writes no PE
bytes and changes no candidate source.
