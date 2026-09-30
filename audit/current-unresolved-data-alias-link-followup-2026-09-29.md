# Current unresolved data-alias link follow-up — 2026-09-29

## Objective

Reduce the diagnostic link's unresolved original-address data references using
only symbols mapped to exact locations in the pinned reference PE. This is a
link diagnosis, not production image reconstruction or runtime validation.

## Evidence and result

- Reference ASI SHA-256: `409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.
- The CRT-alias-only diagnostic response reported 120 unresolved externals.
- Scanning those linker messages against the original PE section table produced
  46 exact decorated data-symbol aliases (40 `.data`, 6 `.rdata`), recorded in
  `unresolved-crt-link-exact-data-aliases-2026-09-29.csv`.
- The first alias-only MASM object assembled successfully and reduced the
  diagnostic link to 74 unresolved externals. This isolated result retained
  the CRT aliases and did not introduce the test-data probe objects.
- A second linker pass identified 46 distinct raw C-style original-address
  data aliases (43 `.data`, 3 `.rdata`), in
  `unresolved-crt-link-exact-data-aliases-v2-2026-09-29.csv`.
- Linking both alias-only objects together reduced the unresolved count to
  **28** (`LNK1120`); the log has 28 `LNK2019` plus 14 `LNK2001` diagnostics.
  No DLL/ASI was emitted. Combined log:
  `build/link-probe/entry-exact-nogs-o1-crt-data-provider-active-20260929/alias-only-combined-link-20260929.log`.
- The new generators are `scripts/extract-unresolved-pe-data-aliases.py` and
  `scripts/generate-exact-pe-alias-provider.py`. The latter emits the reference
  `.rdata`/`.data` bytes at the aliases' preferred-base offsets, but supplies
  no COFF pointer fixups and proves neither symbol ABI nor final image layout.

## Rejected experiment

Passing the full existing reloc-aware DAT provider together with the already
present provider caused duplicate DAT definitions (`LNK2005`). That attempt is
not used as evidence of resolution and emitted no accepted image. The isolated
alias-only object avoids those duplicate DAT symbol definitions.

## Remaining work and limits

The remaining 28 unresolved externals are the callback-manager vtable symbols
and exception/standard-runtime ABI names; they cannot be assigned arbitrary
addresses from their names. The earlier PE-layout and relocation audit still
applies: the diagnostic `.xcode` overlaps original data ranges, candidate and
original HIGHLOW relocation sites need full reconciliation, and imports/startup
plus the final appended-code layout remain unbuilt. No installed ASI was changed
and no game-load test was run.
