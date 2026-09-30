# `10006be0` fresh current-source differential rerun — 2026-09-30

## Evidence

Rebuilt and reran `scripts/test-10006be0-original-binary-differential.ps1`
against the current `src/functions/10006be0.cpp` and
`src/functions/1001ba40.cpp`, using the hash-pinned original ImVehFt ASI
(`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`).
The fresh MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness completed with
**32,720/32,720 matched comparisons and zero mismatches**. Coverage included
directed edge cases, 4,096 deterministic variations, 21,600 downstream-tail
cases, and 4,096 IEEE-boundary tail cases. The harness reported 1,354
x87-condition-code-only differences; these are separately classified and are
not represented as complete machine-state identity.

The specifically audited parent-matrix branch calls GTA `0x7f18b0` with
destination, modelling matrix, and parent LTM as three stack arguments, then
cleans 12 bytes. Current candidate source declares this as a three-argument
`__cdecl` call. The fresh differential exercised the candidate's translated
matrix branch with its controlled matrix-helper stub; it did **not** execute
the live GTA helper in a running game.

Fresh output directory:
`build/abi-harness/10006be0-fresh-recheck-20260930/`.
Harness executable SHA-256:
`20938A3A033EE6AD8DF681FCDAE50BB08EEF99F510400A6E5484BAB593322C5A`.

## Scope boundary

This is fresh evidence for one function under the isolated differential
harness. GTA/RenderWare calls remain controlled or stubbed; it does not prove
full-game behavior, production ASI layout/loading, or semantic correctness of
the other 704 candidates. The full-set compile/objective/parity reports are
separate structural gates, not substitutes for per-function runtime evidence.
