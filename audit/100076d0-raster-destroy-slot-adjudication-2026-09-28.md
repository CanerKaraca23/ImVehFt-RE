# `100076d0` raster-destroy slot adjudication

Date: 2026-09-28. This note separates the identity of the indirect RenderWare
operation from the still-unknown live function pointer and runtime effects.
No candidate source or prior audit file was changed.

## Evidence

- In the current matching GTA SA Ghidra database, `0x007FB020` is the
  `RwRasterDestroy` wrapper. Its bounded decompilation calls the function
  pointer at `RwEngineInstance + 0x5c` with arguments `(0, raster, 0)`, then
  calls the memory-free slot at `+0x148`.
- The preserved 2014-04-27 Plugin SDK snapshot defines the `RwGlobals` prefix
  as `curCamera`, `curWorld`, two 16-bit frame values, two 16-bit padding
  values, then `RwDevice`; its `RwDevice` is 0x38 bytes in the 32-bit SA
  layout. Therefore `stdFunc` begins at `0x10 + 0x38 = 0x48`; its element 5
  is at `0x48 + 5*4 = 0x5c`. The same header declares `RwStandardFunc` as
  `(void *pOut, void *pInOut, int nI)` and exports `RwRasterDestroy` at
  `0x007FB020`.
- Independent community RenderWare/GTA render-hook implementations likewise
  identify the standard raster-destroy operation as the raster-destruction
  callback (see https://github.com/petrgeorgievsky/gtaRenderHook and
  https://github.com/multitheftauto/mtasa-blue/blob/master/Client/sdk/game/RenderWare.h).
  These are corroboration, not evidence of the exact configured callback in
  this installed game process.

## Adjudication and limits

The call at `0x007FB020` is now identified with high confidence as dispatch to
`RwGlobals.stdFunc[5]` for standard raster destruction, rather than an
arbitrary plugin-registry callback. The adjacent `+0x148` indirect call is a
separate `memoryFree` field and must not be conflated with this slot.

This does **not** recover the runtime value installed in `stdFunc[5]`, prove
the full D3D raster-destroy implementation or its side effects, show whether
any loaded hook replaces it, or establish callback-time mutation/re-entry in
the original ImVehFt/GTA process. Existing controlled candidate harnesses do
not exercise the live driver. Keep the behavioral validation item for
`100076d0` OPEN until binary-backed runtime evidence closes those questions.

## Reproduction inputs

- GTA database and executable hash: see
  `audit/100076d0-gta-rw-callback-xref-rerun-2026-09-28.md`.
- SDK layout: `_sdk_history/snapshot-2014-04-27/src/sdk/game_sa/RenderWare.h`
  (`RwDevice`, `RwGlobals`, `RwStandardFunc`, and `RwRasterDestroy`).
- Ghidra bounded decompilation: `audit/rw-destroy-targets-2026-09-27.c`.
