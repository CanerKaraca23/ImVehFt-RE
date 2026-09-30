# `100076d0` focused differential rerun — 2026-09-29 09:57

Re-ran `scripts/test-100076d0-model-info-harness.ps1 -Repetitions 10` from a
VS 2022 Build Tools x86 developer shell against the hash-pinned original
`C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi` and the current
`/O1 /GS-` candidate object. All ten fresh PE32/x86 processes passed. The
harness performed 350 bounded original-vs-candidate invocation pairs across
the 16 model-info selectors and its damaged-lights, controlled nested
re-entry, and callback-time global-flip cases; it reported zero mismatches.

- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate object SHA-256: `4F524388F76533465DF32A85C3FEE293B5969779CAC25EA367A3AD216A0C3558`
- Harness source SHA-256: `D228DCE93A3A6B03BF40C914B2852BEECFDA558812B4C50DA49DA153BE75D114`
- This run's executable SHA-256: `97AA0A43322DCAFF83AFA1987D8345B1F1DC4907711D3DE3410AE745FF65F24F`
- Executable: `build/abi-harness/100076d0-model-info-harness-20260929-095657-692.exe`

The harness uses deterministic fixtures/stubs and maps the original ASI for
bounded function comparison. It does not run GTA's live RenderWare plugin
registry, real driver/allocator callbacks, a production-linked 705-function
ASI, or gameplay. Therefore the live callback/re-entry and installed-game
validation findings remain open. No candidate source or installed binary was
modified.
