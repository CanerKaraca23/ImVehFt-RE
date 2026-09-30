# In-place `.text` capacity/fragmentation probe (2026-09-29)

## Inputs and result

Ran `scripts/audit-inplace-text-packing.py` read-only against the pinned `ImVehFt.asi` and the exact-COFF 705-entry feasibility report. The source image hash matches `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`. The PE32 `.text` section starts at VA `0x10001000`, has VirtualSize `131,707` (`0x2027b`) and RawSize `132,096` (`0x20400`).

Current candidate code extents total `114,707` bytes. Reserving one 5-byte entry jump for each of the 148 candidates that cannot fit its own gap gives `115,447` bytes, an aggregate difference of `16,260` bytes below `.text` VirtualSize. This aggregate comparison alone is not a feasible layout proof.

The deterministic heuristic keeps each of the 557 bodies that fit its bounded gap at its original entry (556 bounded gaps plus the final text-tail entry), reserves five bytes at each of the other 148 entries, and tries to put those 148 bodies largest-first into remaining contiguous slack, best-fit. It placed 146 and left two bodies without a contiguous interval:

| Entry | Body size | Available maximum interval in this run |
|---|---:|---:|
| `0x1001f203` | 4,108 | 2,333 |
| `0x1001eb27` | 2,640 | 2,333 |

After the 146 placements, the heuristic reports 23,008 free bytes in 647 fragmented intervals. Full machine-readable output is `audit/inplace-text-packing-o1-x87-frame-2026-09-29.json`.

## Interpretation

This shows why raw total-section capacity is misleading: contiguous interval size, not aggregate bytes, controls placement. It rejects this specific simple compaction strategy; it does **not** prove that no alternative reassignment of currently direct-fit bodies can produce an all-in-`.text` layout. An appended executable area (or a more complete global allocator) is needed to place the remaining bodies under this strategy.

The script does not inspect incoming references to reclaimed tails, shared function tails, instruction boundaries, base-relocation coverage, the 4,442 COFF relocations, data/startup placement, imports, PE metadata, or runtime behavior. It changes no candidate, original binary, or PE. A successful packing plan would still need those independent audits and a real PE/game-load test before it could be called a valid ASI.

## Ghidra-reference overlay check: the heuristic layout is rejected

After the capacity simulation, queried the saved Ghidra ReferenceManager read-only for **every byte** in the original `.text` range (`131,707` byte targets). The rerun recorded 8,563 incoming references to 5,293 target bytes; after excluding ordinary function-entry references and references whose source/target belong to the same Ghidra function, the export contains 437 non-entry records at 376 unique target bytes. Of those, 99 records/93 target bytes land inside a Ghidra-defined function body; 338 records/283 target bytes land in `.text` addresses not assigned to a containing function by this project snapshot. The unowned destinations must not be presumed to be free padding.

Compared those destinations with the heuristic's 146 moved-body intervals. **255 recorded reference rows (207 distinct target bytes) overlap 20 proposed body intervals.** For example, the proposed placement for entry `0x10016088` starts at `0x1001eb2c` and would overwrite referenced targets including `0x1001ebb7`, `0x1001ec09`, and `0x1001edd7` in the original `___strgtold12_l` code/data region. This is enough to reject the current in-place slack packing as a safe layout; these references would need to be preserved or explicitly redirected, and their source/data semantics adjudicated. The machine-readable overlap list is `audit/inplace-text-packing-xref-overlap-o1-x87-frame-2026-09-29.json`; the raw read-only Ghidra query is `ghidra_exports/text-nonentry-reference-audit-20260929.csv`.

Therefore the aggregate-capacity result is only a sizing observation. It does not justify reusing those intervals. A safe builder needs an explicit policy for the referenced legacy bytes (and complete instruction/data extents), likely a separately allocated executable region plus reference/relocation rewriting or retention of reachable legacy tails. No patch or image was emitted.
