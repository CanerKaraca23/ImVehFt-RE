# Original-entry COFF slot-fit feasibility

Date: 2026-09-28

## Result

Ran `scripts/audit-original-entry-slot-fit.py` against the 705 strict x86
MSVC objects in `build/recheck/strict-all-live-20260928-2/`. The selected
public candidate COMDAT for each mapped entry was compared with the address
gap from that entry to the next address in `audit/function-name-map.csv`:

- 705 objects and entries classified.
- 429 selected COMDATs fit before the next mapped entry.
- 275 selected COMDATs exceed that gap.
- The last mapped entry has no following boundary.

Examples include `10001040` (802-byte COMDAT in a 784-byte gap), `10001430`
(152 bytes in a 112-byte gap), and `10002210` (4,245 bytes in a 3,872-byte
gap). This explains why source-order
`/ORDER` cannot by itself assign every entire selected COMDAT to its original
entry slot without crossing another mapped entry.

Machine-readable details: `audit/original-entry-slot-fit-2026-09-28.json`.
Reproduce with:

```powershell
python scripts/audit-original-entry-slot-fit.py `
  build/recheck/strict-all-live-20260928-2 `
  --output audit/original-entry-slot-fit-repeat.json
```

The script refuses to overwrite an existing output.

## Limits and consequence

The next mapped entry is a conservative upper bound on an available slot, not
a direct measurement of each original function body's final byte. A COMDAT
that exceeds the gap cannot be laid whole at its original entry under this
simple placement model; that does not prove a relocated implementation is
impossible. Calls may target relocated symbols, and bridges or split sections
could change placement, but those approaches still need complete relocation,
startup, PE-loader, and game validation. This audit makes no claim that a
loadable `.asi` has been produced.

No candidate source was changed by this linker feasibility check. The object
set is the strict compile noted above; this audit is not a new compile or
semantic/runtime test.
