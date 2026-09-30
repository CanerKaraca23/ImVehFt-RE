# `100076d0` current-object differential — 2026-09-30

## Evidence identity

- Pinned reference ASI: `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi`
- Reference SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Current candidate object: `build/recheck/strict-xcode-nogs-o1-live-rerun-20260930/100076d0.obj`
- Candidate object SHA-256: `10A94E6B6ED77B2CB54C933D5E2D5682E1660F40438E48124DA83CD3A964F185`
- Harness source: `tests/runtime_100076d0_model_info_harness.cpp`
- Harness source SHA-256: `D228DCE93A3A6B03BF40C914B2852BEECFDA558812B4C50DA49DA153BE75D114`
- Harness executable: `build/abi-harness/100076d0-model-info-harness-20260930-074627-258.exe`
- Harness executable SHA-256: `2F29D8FBE7A5F1480649E4B2BF3DC1E4BD1F214116D3FCDFFB91EE6923449E5B`
- Runner: `scripts/test-100076d0-model-info-harness.ps1`, invoked from a VS 2022 x86 developer environment with `-Repetitions 10` and the current object above.

## Result and coverage

The runner compiled the harness against the current object and reported **10/10 fresh x86 processes passed**. Each process compares the candidate object against the pinned original binary through address-redirected stubs. The harness source specifies both model-info routes for each of 16 selectors (32 route/selector comparisons), damaged-vehicle-lights lookup, controlled callback re-entry, and a callback-time context-global flip with a seeded entry stack slot. It checks relevant input/output bytes, return pointer, write slots/cursor, lookup IDs/names, callback arguments, and modeled call counts.

The current object is thus covered by a fresh bounded differential regression for these cases; this removes the stale-object caveat from the 2026-09-29 harness record. It does **not** prove all paths or full semantic equivalence.

## Limits / status

The test uses synthetic memory and stubs for game/RenderWare calls. It does not execute against the live plugin registry, real RenderWare resources, ModLoader, or GTA process; it does not establish real callback ordering, allocator/resource ownership, or behavior for unmodeled states. No candidate ASI was installed or loaded. `100076d0` remains **partially differential-tested, runtime/game validation open**.

Reproduction:

```powershell
scripts/test-100076d0-model-info-harness.ps1 `
  -ObjectPath build/recheck/strict-xcode-nogs-o1-live-rerun-20260930/100076d0.obj `
  -Repetitions 10
```
