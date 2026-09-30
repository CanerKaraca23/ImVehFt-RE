# `10012be1` `__initterm_e` original-binary differential (2026-09-29)

## Ghidra evidence and method

- Ghidra export `ghidra_exports/10012be1.json` identifies the function as a
  cdecl initializer-table walker. It reads entries in order, skips nulls,
  calls non-null entries, and stops on the first nonzero callback result.
- Added `tests/runtime_10012be1_initterm_e_original_differential.cpp`. The
  harness maps the pinned original ASI at its preferred base and calls the
  original at `0x10012be1` alongside the candidate from the latest strict
  705-object build. Callback functions are controlled stubs and record order,
  return values, and permitted table mutation.
- The harness also checks cdecl caller cleanup. A small independent dispatcher
  oracle checks callback order, early stop, and final table contents.

## Result

- VS 2022 x86 `/O1 /W4 /WX /MT /arch:IA32` harness built and linked against
  the exact current `10012be1.obj`.
- **100,007 cases passed**: empty/all-null tables, all-success traversal,
  early failures at several positions, a callback that fills a future null
  slot, and 100,000 deterministic randomized tables (0-32 slots, null and
  non-null entries, zero/negative/positive results, and occasional mutation).
- Original and candidate callback traces and final table contents matched the
  independent oracle. Both left cdecl arguments for caller cleanup (ESP delta
  `-8` after call and `0` after cleanup).
- Original ASI SHA-256 remained
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate source SHA-256:
  `8395359ED9E88E233F7950FA8017E485C55A674836E3E5763F0AB102033A0DA6`.
  Harness source SHA-256:
  `C07298F23AF3A3F0063722C4AC6B43B71FBC9ED452CAC4B2A64C4AC284C48C82`.
  Candidate object SHA-256:
  `508DCFADC5FBD13603E86118E24973DE864F3E14B343456F63197AC2BE8062F8`.
  Harness executable SHA-256:
  `D2E1D925B1DF4A5B01EF89CB9FFAB53E485E7FC34D6755EE405751B6348CECA2`.

## Scope limit

This validates the table-walker behavior with controlled callbacks only. Real
CRT initializer functions, CRT startup ordering/state, all other 704 targets,
production PE/ASI loading, and GTA gameplay remain untested. No candidate
source change was needed.
