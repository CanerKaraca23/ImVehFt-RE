# In-place entry reference-window audit (2026-09-29)

This audit applies the current entry placement modes to the full-range Ghidra
reference export. Direct-at-entry placements overwrite the candidate body
extent; `jmp-rel32-thunk` placements overwrite only the 5-byte entry jump.
Reference destinations are tested against those actual proposed overwrite
intervals.

## Result

- Pinned original ImVehFt.asi SHA256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- 437 Ghidra non-entry reference rows scanned for 705 entries.
- The initial `/O1` body-size report yielded 19 rows / 17 unique target VAs.
  After exact body corrections and a fresh feasibility report, the current
  count is **18 rows / 16 unique target VAs** across `100060d0`, `10009790`,
  `100154dc`, `10018f75`, and `1001cb37`. `1001c5b8` no longer overlaps its
  `0x1001c5e0` data/code target: its exact candidate body is now 40 bytes and
  ends exactly at `0x1001c5e0`.
- The earlier claim that 16 source bytes outside overwrite intervals were
  “surviving references” was too strong; byte location alone does not prove
  liveness. The xref/context graph adjudicates the current 18 rows as follows:
  - Six `100060d0` and eight `100154dc` rows are old switch-table cells. Their
    only recorded readers are dispatch instructions inside the corresponding
    candidate bodies, which are replaced; the candidate sources use rebuilt
    switch logic. The old table cells may remain as inert bytes.
  - Two `10009790` rows originate inside that same replaced body.
  - The `10018f75` row is an old branch at `10018f73`, after the 5-byte entry
    thunk at `10018f6c`; the old residual prologue is cut off by the thunk and
    Ghidra records no separate incoming edge to `10018f73`.
  - The `1001cb37` row is a branch at `1001cb35` in `1001cb20`; that larger
    candidate is thunked at entry, its old tail is no longer reached, and the
    replacement `1001cb37` body now matches all 60 original bytes after the
    `__87except` REL32 fixup.
- The fresh geometric report records source bytes outside overwritten spans
  without claiming those bytes execute. This audit covers recorded Ghidra
  references only; undiscovered indirect/runtime-computed references remain
  possible. Exact body reports are `audit/1001c5b8-inplace-exact-boundary-final-2026-09-29.json`
  and `audit/1001cb37-inplace-byte-identical-final-2026-09-29.json`.

The current geometry detail is in
`audit/inplace-entry-reference-byte-windows-final-current-2026-09-29.json`;
the preceding v2 report is retained as an earlier, over-interpreted analysis
snapshot.
Re-run with:

```powershell
py -3 scripts/audit-inplace-entry-reference-byte-windows.py --output <new-report.json>
```

The script refuses to overwrite its output. This is a static placement audit;
it changes no PE bytes and does not produce or validate an ASI.
