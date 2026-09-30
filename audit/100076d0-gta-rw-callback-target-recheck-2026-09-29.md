# `100076d0` GTA RenderWare callback-target recheck — 2026-09-29

## Inputs and method

Re-ran a read-only, `-noanalysis` Ghidra 12.1.3 query against the existing
PDB-disabled `raster_audit` program. The script records disassembly, function
decompilation where available, and references for the GTA texture/raster
registration and destruction routines. It asks Ghidra to decode the callback
addresses that were previously listed as data labels rather than functions.

- GTA executable SHA-256:
  `F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`.
- Reference ImVehFt ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Raw query output: `gta-rw-target-trace-2026-09-29.log`.
- Raw query output SHA-256:
  `0D9DD6B5A35E6E77CAF985A1D12FD7BA63803651C7000F29AAE678F274384EC0`.
- Reproduction script: `../scripts/ghidra_dump_gta_rw_callback_targets.java`.

## Confirmed from current GTA bytes

- GTA's `RwTextureRegisterPlugin` caller at `0x748f70` registers ID `0x127`
  with ctor `0x749020`, dtor `0x749030`, and copy callback `0x749040`.
- The ctor sets one plugin byte to 1. The dtor is exactly `MOV EAX,[ESP+4]; RET`:
  it returns its incoming plugin-data pointer and has no call or side effect.
  The copy callback copies that one byte. Thus this stock GTA plugin callback
  is not the source of an ImVehFt re-entry.
- `RwTextureDestroy` at `0x7f3820` traverses its texture-plugin callback list
  via `0x808740` (`CALL dword ptr [record+0x24]`), then repairs the texture
  list, destroys an attached raster through `0x7fb020`, and releases the
  texture. The callback walker follows the linked records at `+0x34`.
- `RwRasterDestroy` at `0x7fb020` traverses a separate raster-plugin callback
  list via the same walker, then calls the runtime `stdFunc[5]` slot at
  `RwGlobals+0x5c`, then the allocator free slot at `+0x148`.
- GTA's raster plugin destructor at `0x4c9a80` calls an object vtable `+8`
  only when the registered raster record's `+0x1c` pointer is non-null, then
  clears the pointer. The callback remains data-dependent at runtime.

## Impact and remaining uncertainty

This narrows the re-entry window: the stock GTA texture destructor is benign;
remaining possible side effects are the loaded texture/raster plugin callback
lists, the conditional COM `Release`, runtime `stdFunc[5]`, allocator behavior,
or another external hook. The static image does not reveal those live targets,
callback-list contents/order, or whether any of them re-enters the ImVehFt
vehicle processing callback while `100076d0` is between its texture-destroy
calls and subsequent global/stack-slot read. The prior 15-case dispatcher
differential does not cover those GTA/RenderWare runtime targets.

Therefore `100076d0` behavioral/runtime status stays OPEN; this is not a reason
to change its candidate source or claim live-game correctness. No candidate
source, reference ASI, or GTA executable was modified. Ghidra reported and
discarded changes to the read-only program after the query.
