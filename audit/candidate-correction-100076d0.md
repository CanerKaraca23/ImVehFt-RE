# Candidate correction: `FUN_100076d0` fixed-address texture globals

Date: 2026-09-24  
Reference image: `ImVehFt.asi`, SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Evidence and change

The local Ghidra listing for `100076d0` accesses the 32-bit slots at `0x00B4E47C`, `0x00B4E68C`, and `0x00B4E690` directly: it checks/loads the first slot at `0x10007758`, `0x1000778d`, and `0x100077a9`, loads the second at `0x10007a24` and compares it at `0x10007a34`, and loads the third at `0x10007d6f`. The historical/local Plugin-SDK `CVehicleModelInfo.cpp` names these `ms_pRemapTexture`, `ms_pLightsTexture`, and `ms_pLightsOnTexture`, respectively, each a `RwTexture*` global.

The candidate previously modeled these executable globals as external symbols. `src/functions/100076d0.cpp` now reads each from its actual fixed address through a typed `RwTexture**` slot. This avoids requiring a linker-exported C++ symbol for memory owned by the running GTA executable. Existing logic and branch behavior were otherwise retained. This establishes address/type correspondence, not full semantic equivalence.

## Validation performed

- MSVC 2022 x86, C++20, `/O2`: the full set compiled and archived, **705/705**.
- MSVC 2022 x86 `/O2 /W4 /WX /MT`: the three currently corrected translation units passed; the other 702 were unchanged from the prior complete strict audit.
- ReAgent 0.4.0 targeted parity: **3 green / 0 red** for `10003ba0`, `10003e60`, and `100076d0`.
- ReAgent 0.4.0 objective verifier: **3/3 pass**, no structural failures.
- The `100076d0` object disassembly contains direct reads from the three expected addresses, consistent with the corresponding Ghidra accesses.
- The current diagnostic full-set link has **201 unique unresolved externals** and produced no DLL. It is not the original production project/link.

## Remaining warning and limits

The parity report records a scoped, manually adjudicated call-count heuristic for `100076d0`: optimized control flow merges mutually exclusive lookup tails. It also explicitly records MSVC `/W4 /WX` warning C4701 for `local_c`. Follow-up inspection confirms the concern is not dismissible as a simple false positive: Ghidra assembly initializes stack slot `[EBP-8]` only on the entry path guarded by `DAT_1003c1fc != 0` (`0x100076df` through `0x1000770e`), then re-reads that global at `0x10007c4b` before consuming `[EBP-8]` at `0x10007c54`. The candidate set also contains a writer to this global in `100074d0.cpp`. This makes a changed-between-checks state a plausible hazard; the inspected listing does not establish that such a transition is reachable during this function, so the warning remains open. A direct `/W4 /WX` compile of the current file succeeds, but does not resolve this interprocedural control-flow question. Do not report this function as warning-free/fully validated until the state invariant is proved or the candidate is deliberately hardened with the behavior difference documented.

The aggregate 705/705 ReAgent totals refer to a prior source snapshot; only these three corrected candidates were rerun in the targeted ReAgent checks. No complete plugin link or GTA in-game validation has been performed. The work is therefore not 705/705 semantically or dynamically verified, and does not establish a byte-identical reconstruction of the author's source.
