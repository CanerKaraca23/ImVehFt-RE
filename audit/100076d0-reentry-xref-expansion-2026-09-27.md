# `100076d0` re-entry xref expansion

Date: 2026-09-27. Read-only queries used the existing GTA SA Ghidra project in
headless `-noanalysis` mode; no PDB was searched or used.

## Findings

- The only recorded direct GTA code reference to `FUN_006d64f0` is
  `0x005532a9`, in `FUN_00553260`. The caller listing
  (`gta-sa-vehicle-callback-parent-553260-20260927.txt`) shows this call is
  behind a state test of the entity byte at `+0x36` (`& 7 == 2`), after a
  virtual call at vtable offset `+0x4c`. It then proceeds through the patched
  call site at `0x6d6617` and the callback dispatcher at `0x6d662b` described
  in `gta-sa-dispatcher-crosscheck-2026-09-27.md`.
- `FUN_00553260` has four recorded direct callers at `0x00553c52`,
  `0x00553cb8`, `0x00553d8f`, and `0x00732c48`, listed in
  `gta-sa-vehicle-callback-parent-xrefs-20260927.csv`.
- A fresh address-xref inventory for `0x74dbc0` (`RwTextureDestroy`),
  `0x7f3820` (`RwTextureDestroy` wrapper), `0x808740` (texture registry
  callback walker), `0x4c9a80` (the registered raster-plugin destructor),
  and `0x6d64f0` found no recorded direct reference from the queried
  destruction-chain functions into the vehicle callback. The inventory is
  `gta-sa-reentry-xrefs-20260927.csv`; previous bounded call-chain audits
  describe the indirect registry/allocator edges.

## Limit

This narrows the statically visible GTA path: no direct call edge was found
from the inspected texture/raster destruction chain to the vehicle callback.
It does not resolve indirect COM/driver callbacks, other loaded modules,
function-pointer dispatch, or live registry state. Therefore it cannot rule
out runtime re-entry or the null-to-nonnull transition of `DAT_1003c1fc`.
Keep the `100076d0` finding YELLOW and leave its candidate unchanged. A live
game test with an integrated, correctly relocated plugin is still unavailable.
