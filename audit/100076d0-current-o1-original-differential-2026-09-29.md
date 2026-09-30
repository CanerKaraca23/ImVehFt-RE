# Current `100076d0` O1 object differential rerun — 2026-09-29

## Result

Executed the current `/O1 /GS-` candidate object against the hash-pinned
original `ImVehFt.asi` in the PE32/x86 differential harness. Ten fresh
processes passed. Across the ten runs, the harness performed 350 paired
function invocations with zero mismatches: 16 model-info selectors in each
of two context routes (320 pairs), plus 10 each of the damaged-lights lookup,
controlled nested re-entry, and callback-time global flip with seeded entry
stack-slot cases.

The comparisons cover return pointer, full 24-byte input record, write-slot
contents/cursor advance, lookup IDs and names, callback inputs, and modeled
call deltas. The lookup/callback and game globals are redirected to
deterministic test fixtures/stubs. This is bounded original-binary
differential evidence, not a live GTA/RenderWare or whole-function proof.

## Harness correction discovered during rerun

The first current-object attempt failed its raw operand-count guard. Inspecting
the linked harness showed that its previous scanner searched *every*
executable section, including harness `.text`; the harness's own immediate
initialization of the `0x7F39F0` patch record was counted as a fifth candidate
reference. `dumpbin /disasm` located that false hit in harness `.text` at RVA
`0x1B2F`; the candidate itself is in a separate executable `.xcode` section.

The scanner now requires exactly one nonempty executable `.xcode` section and
patches only that candidate section. Its measured O1 candidate operand counts
are `0x7F39F0:4`, `0x74DBC0:2`, `0xC8800C:1`, `0xB74494:3`, `0xB4E47C:3`,
`0xB4E68C:2`, and `0xB4E690:1`. These counts were checked against the current
object's `.xcode` bytes/disassembly; the count differences from the older O2
object are compiler-layout differences, not original-binary reference
counts. The O1 defaults in `test-100076d0-model-info-harness.ps1` now select
the object actually tested.

## Reproducibility and integrity

- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate source SHA-256: `149AE0C88160BA6DFDBDF6097853373074DEC2133BC5ADF066EB6DD8A84EEEAD`
- Candidate object: `build/recheck/strict-xcode-nogs-o1-exception-fix-20260929/100076d0.obj`
- Candidate object SHA-256: `4F524388F76533465DF32A85C3FEE293B5969779CAC25EA367A3AD216A0C3558`
- Harness source SHA-256: `D228DCE93A3A6B03BF40C914B2852BEECFDA558812B4C50DA49DA153BE75D114`
- Harness executable: `build/abi-harness/100076d0-model-info-harness-20260929-054542-449.exe`
- Harness executable SHA-256: `9D22D191F79A3D6C36A7A06C9D44011AC718EB5B94C5780219900288C975A4D9`
- Reproduction from VS 2022 x86 developer environment: `scripts/test-100076d0-model-info-harness.ps1 -Repetitions 10`.

The harness source was backed up before its scan/count correction as
`tests/runtime_100076d0_model_info_harness.cpp.pre-xcode-only-candidate-scan-20260929.bak`;
the runner script's prior default was backed up as
`scripts/test-100076d0-model-info-harness.ps1.pre-current-nogs-o1-object-20260929.bak`.
The candidate `src/functions/100076d0.cpp` was not changed in this rerun.

## Remaining boundary

This strengthens evidence for the current build mode and fixes the harness's
self-match false positive. It does not determine whether a real RenderWare or
driver callback can re-enter `100076d0`, test initialized live registry
contents, cover every path in the function, validate the 705-function image,
produce an installable ASI, or establish gameplay behavior.
