# `100076d0` GTA parent-caller review

Date: 2026-09-27. This follow-up checks the known GTA callers of vehicle
parent `FUN_00553260` for a static route from texture destruction back into the
ImVehFt context setter. It uses the installed `gta_sa.exe` Ghidra project in
`-readOnly -noanalysis` mode. No candidate source was changed; no PDB data was
used.

## Evidence

The existing full-analysis Ghidra xref inventory records four direct call
sites to `0x00553260`: `0x00553c52` and `0x00553cb8` in `FUN_00553aa0`,
`0x00553d8f` in `FUN_00553d00`, and `0x00732c48` in `FUN_00732b40`.
`GhidraInspectFunctionAddresses.java` was run read-only to decompile those
three containing functions; the output is preserved in
[`gta-sa-parent-caller-functions-2026-09-27.c`](gta-sa-parent-caller-functions-2026-09-27.c)
and the incoming-reference inventory in
[`gta-sa-parent-caller-functions-2026-09-27.csv`](gta-sa-parent-caller-functions-2026-09-27.csv).

- `FUN_00553aa0` iterates the active vehicle/render lists and calls
  `FUN_00553260` for eligible entries.
- `FUN_00553d00` prepares render state and calls `FUN_00553260` for the
  current `DAT_00b745d4` object.
- `FUN_00732b40` handles a model/entity rendering branch and calls
  `FUN_00553260` when the object's state takes that branch.

Within `FUN_00553260`, the callback dispatcher at `0x006d64f0` is reached only
on the branch where `((state_byte_at_object+0x36) & 7) == 2` (`0x00553286` to
`0x005532a9`). The dispatcher calls the installed ImVehFt setter hook at
`0x006d6617` before it calls callback dispatcher `0x004c8430` at
`0x006d662b`. The callback registrations inspected so far identify
ImVehFt's texture destructor `FUN_10001b00` as calling `RwTextureDestroy`,
but show no direct call from that destructor to `FUN_00553260`,
`FUN_006d64f0`, or the setter hook.

## Interpretation and limits

The known direct GTA call paths into the setter/dispatcher originate in
vehicle/model render/update functions, not in the inspected texture/raster
destruction or registered texture-destructor bodies. Combined with the
installed-module scan, this lowers the static likelihood of the specific
null-to-non-null `DAT_1003c1fc` transition during `100076d0`'s texture cleanup.
It is not a proof that the transition cannot happen: indirect function
pointers, driver callbacks, dynamically loaded modules, asynchronous activity,
and live RenderWare registry contents are not resolved/observed. No running
game or candidate plugin was instrumented. Keep `100076d0` YELLOW and retain
the candidate initializer pending runtime evidence.
