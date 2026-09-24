# Diagnostic full-set link probe (2026-09-24)

## Result

The latest local MSVC 2022 x86 diagnostic link attempt against all 705 strict-audit objects and the historical static Plugin-SDK library ended with **LNK1120: 210 unresolved externals**. No DLL was produced. The probe is not the original project build and is not a runtime-valid ImVehFt plugin.

The previous comparable probe had 215 unresolved externals after an initial set of address shims. This follow-up reduced that count by five with additional diagnostic-only wrappers. These include RenderWare camera begin/end update (`0x7EE190`, `0x7EE180`), shader operations (`0x7F9FB0`, `0x7F9FF0`), frame traversal (`0x7F0DC0`), and a sprite rectangle helper (`0x727BE0`). Their address mappings were found in the local modern Plugin-SDK `RenderWare.cpp` / `CSprite2d.cpp`; candidate call shapes were inspected for x86 link compatibility.

The probe-only implementation is outside `src/functions/` and does not change any of the 705 reconstructed candidate files. It calls fixed GTA executable addresses if executed, so it must not be treated as a safe or tested plugin implementation. The link step does not execute those calls.

## What this does and does not validate

- Validates that the probe source compiles and that five previously unresolved symbol names can be supplied for this linker experiment.
- Does not validate function semantics, exact original prototypes, the target executable version, or runtime safety.
- Does not establish that the original ImVehFt build used these SDK wrappers.
- Does not resolve the remaining 210 externals, which include missing image data/globals, GTA functions, CRT/EH ABI differences, and other unresolved symbols.
- Does not establish source equivalence or pass any in-game test.

The original candidate source manifest and per-function hashes remain unchanged by this probe.
