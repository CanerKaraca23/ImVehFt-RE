# Callback label survival under current 705 placement — 2026-09-30

Ran `scripts/audit-callback-labels-preserved-by-current-placement.py` against
the pinned original ASI, saved callback maps/MASM, and the fresh 705-entry
283-in-place / 422-thunk placement plan.

- All 70 saved `E9 rel32` callback labels and all 25 `PUSH ECX; CALL rel32;
  RET` labels are raw-backed in original `.text`.
- Every original instruction transfer was decoded from the pinned bytes and
  matches the saved target map; all 95 targets are current candidate entry
  VAs.
- None of the 95 label instruction ranges intersects a body-at-entry overwrite
  or a five-byte entry-thunk patch in the current plan.
- Machine-readable per-label bytes/targets and checks:
  `audit/callback-label-preservation-current-placement-2026-09-30.json`.

Thus the 95 `_LAB_100...` external symbols in the appended-object link map can
be assigned their original callback label VAs without emitting duplicate
callback helper code, provided the final image preserves original `.text`
outside the planned candidate patches. This is static address/byte evidence;
it does not prove callback semantics, full PE correctness, startup behavior,
or GTA runtime behavior.
