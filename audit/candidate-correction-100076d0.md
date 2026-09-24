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

The parity report records a scoped, manually adjudicated call-count heuristic for `100076d0`: optimized control flow merges mutually exclusive lookup tails. It also explicitly records MSVC `/W4 /WX` warning C4701 for `local_c` as unresolved. The candidate mirrors a conditionally initialized/use pattern seen in the decompilation, but that observation alone does not prove the path safe. This warning needs direct control-flow/data-flow review and should not be described as a clean strict-warning result for this function until resolved or documented with decisive evidence.

The aggregate 705/705 ReAgent totals refer to a prior source snapshot; only these three corrected candidates were rerun in the targeted ReAgent checks. No complete plugin link or GTA in-game validation has been performed. The work is therefore not 705/705 semantically or dynamically verified, and does not establish a byte-identical reconstruction of the author's source.
