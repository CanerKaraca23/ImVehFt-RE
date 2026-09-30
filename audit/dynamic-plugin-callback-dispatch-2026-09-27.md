# Five dynamically installed plugin callback dispatchers

Date: 2026-09-27. This pass follows five targets written into hook pairs by
candidate `FUN_1000bca0`: `0x1000caa0`, `0x1000caf0`, `0x1000cb40`,
`0x1000cb90`, and `0x1000cbe0`.

## Reconstruction and checks

- Ghidra references and original PE instruction bytes identify five 0x4b-byte
  dispatch bodies. Each reads the callback list through `0x1003c3cc`, calls
  entries from that list, calls a slot-specific function pointer, and invokes
  the `0x100099f0` helper on its success/failure paths.
- `scripts/reloc_local_code_stubs.py` now carries five separate source-byte
  templates, including the absolute global operand and both relative calls.
  The relocation-aware provider checks those targets against the original PE
  before emitting relocatable code.
- `src/functions/1000bca0.cpp` now refers to the five external dispatcher
  symbols in its hook pairs, rather than storing the original preferred-base
  addresses as constants. The fresh `1000bca0.obj` has undefined references to
  all five names; the provider object defines all five names. This confirms
  object-level symbol connectivity, not a final link or runtime hook install.
- Fresh VS2022 x86 `/O2 /W4 /WX /MT` compile: **705/705**;
  ReAgent structural objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  ReAgent parity: **704 GREEN / 1 YELLOW / 0 RED**. The sole YELLOW remains
  `0x100076d0`; these checks do not prove semantic or runtime equivalence.
- Provider v26 assembled with MASM. The independent verifier passed
  **1,521/1,521** original `.rdata`/`.data` fixups with zero mismatches,
  including 119 candidate-code targets, 80 local-code pointer sites,
  22/22 startup-thunk sequences, 177/177 state-table bytes, and 145 emitted
  `.text` COFF relocations. The five dynamically installed hook targets are
  emitted as local code stubs; their hook-pair symbol references are separate
  from those 1,521 data relocation sites.

Artifacts: `build/strict-five-hook-stubs-20260927.json`,
`audit/objective-five-hook-stubs-2026-09-27.json`,
`build/parity-five-hook-stubs-20260927.json`, and
`build/recheck/reloc-aware-dat-provider-v26-five-hooks-20260927.asm/.obj`.

## Still not a testable `.asi`

Provider v26 is a diagnostic COFF object, not a finished plugin. The 3,160
original `.text` HIGHLOW relocation sources, complete PE image/function/global
layout, hook patch installation and retargeting, production imports/linking,
and in-game execution are still not integrated or validated. Do not install
this object in GTA SA.
