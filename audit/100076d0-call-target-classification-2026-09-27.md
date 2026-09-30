# `100076d0` call-target classification (binary-only)

Date: 2026-09-27. Target behavior below is from the reference `ImVehFt.asi`
and installed `gta_sa.exe` analyzed in Ghidra. No PDB or original source is
needed or used; Ghidra PDB analyzers were disabled for bounded GTA traces.
The candidate C++ was not changed by this audit.

## Calls relevant to the yellow finding

- The entry-time `[EBP-8]` initialization call at `ImVehFt.asi:0x100076e9`
  is guarded by the entry value of `DAT_1003c1fc`.
- Four indirect calls at `0x10007861`, `0x100078ae`, `0x100078fc`, and
  `0x1000794c` load `0x74dbc0` and call `RwTextureDestroy` before the later
  `DAT_1003c1fc` test/stack-slot read. A fifth nearby indirect call at
  `0x10007a1b` loads `0x7f39f0` and calls `RwTexDictionaryFindNamedTexture`.
  The callees are known; the unresolved re-entry window
  is specifically the runtime callback/allocator state reached during texture
  destruction, not an unknown target address. The fifth destroy call is after
  the slot read and is not part of this window.
- Calls using `0x7f39f0` reach `RwTexDictionaryFindNamedTexture`; bounded
  decompilation found list/name lookup and no callback dispatch in that body
  (`rw-texture-dictionary-find-bounded-2026-09-27.c`).
- Calls using `0x447090` reach a three-instruction palette-address helper
  (`rw-palette-helper-bounded-2026-09-27.c`), not a callback.

## Destruction chain and correction

The texture-destruction path dispatches the texture registry at `0x7f3820`
through `0x808740` (callback field at registry-record `+0x24`). GTA's own
texture-plugin destructor at `0x749030` simply returns its argument. However,
the texture destroy path then calls raster destroy `0x7fb020` when the texture
has an attached raster. `0x7fb020` dispatches the separate raster registry
rooted at `0x8e2518`, so raster callback behavior cannot be excluded.

GTA registration function `0x4c9ab0` registers raster-plugin ID `0x40c`,
size `0x24`, with constructor `0x4c9a60`, destructor `0x4c9a80`, and no copy
callback. The bounded constructor at `0x4c9a60` clears the slot at plugin-data
offset `+0x1c`. The destructor at `0x4c9a80` reads that slot, and, if non-null,
calls the pointed object's vtable entry at `+8`, then clears the slot.

That layout now has a strong binary/SDK match: the local 2014 Plugin-SDK
`RenderWare.h` defines a `RwD3DRaster` plugin structure of size `0x24`; its
`IDirect3DSwapChain9* swapChain` member is at offset `0x1c`. The installed
Windows D3D9 header defines `IDirect3DSwapChain9` as an `IUnknown` interface
whose third vtable entry is `Release` (offset `+8`). GTA's registration passes
precisely this plugin size and callback pair, and its constructor/destructor
match initialization/release of that swap-chain field. This makes the intended
operation `IDirect3DSwapChain9::Release`, not an arbitrary game callback. The
xref scan cannot prove the live field value/vtable at a particular runtime
point or what a driver implementation may do; the installed ASI/DLL inventory
only checked other mods' RenderWare registrations.

The 2014 SDK layout was independently compiled with the installed VS2022 x86
compiler using `scripts/probe-rwd3draster-layout.cpp`: both `sizeof(void*) == 4`,
`sizeof(RwD3DRaster) == 0x24`, and `offsetof(RwD3DRaster, swapChain) == 0x1c`
static assertions passed under `/W4 /WX /wd4201`. The single warning suppression
is for the old header's anonymous struct/union extension (C4201); it does not
weaken the layout assertions.

Fresh independent full Ghidra analysis of installed `gta_sa.exe` (PDB
analyzers disabled) found 41 caller functions referencing the raster-plugin
offset global or its constructor/destructor/raster-destroy APIs. Results are
in `raster-plugin-xrefs-independent-2026-09-27.csv` and `.c`; this includes
the raster create path and its slot accesses. A second full-analysis xref pass
directly against the registration wrappers found exactly one GTA executable
caller of `RwRasterRegisterPlugin` (`0x7fb0b0`): `FUN_004c9ab0`, the function
which supplies this constructor/destructor pair. It also found one GTA caller
of `RwTextureRegisterPlugin` (`0x7f3bb0`), `FUN_00748f70`. See
`raster-register-api-callers-independent-2026-09-27.csv` and `.c`. The current
64-file local ASI/DLL byte scan has no `RwRasterRegisterPlugin` occurrence.
Together these identify the known GTA raster registration route, but do not
prove runtime registry contents or exclude dynamically constructed API calls.

As a separate candidate-side cross-check, `dumpbin /symbols` over all 705
objects from `build/recheck/strict-all-post-raster-20260927` found the external
symbol `DAT_1003c1fc` in only `100074d0.obj` and `100076d0.obj`. The former
declares the global volatile and stores `param_1`; the latter reads it. This
agrees with the source search and the reference-binary map
(`1003c1fc-reference-map-2026-09-27.csv`: one literal write in `0x100074d0`,
seven literal reads in `0x100076d0`). It does not exclude alias writes or
runtime code outside the 705 TUs.

Frame-plugin registrations in the game executable are separate from this
texture/raster destruction chain. Their existence alone is not evidence of
re-entry here.

## Fresh setter/re-entry xref check

A new read-only query against the existing GTA Ghidra project reconfirmed
that `0x6D64F0` has one incoming code call, from `0x005532A9` in vehicle
processor `0x00553260`; that processor calls setter hook site `0x6D6617`
before calling the registered callback at `0x4C8430`. `0x4C8430` has only
that parent call as an incoming reference. Separately, a fresh bounded
direct-call walk from `0x74DBC0` follows the known destruction chain
`0x74DBC0 -> 0x7F3820 -> {0x808740, 0x7FB020}` and then the raster registry
dispatch. Across ten bounded entries (256 instructions), it records eight
direct call edges and twelve indirect-call occurrences, with no direct call
edge back to `0x6D64F0` or `0x00553260`.

This makes the known binary path to the context setter distinct from the
known destruction path. It still cannot decide the runtime targets of four
unique indirect sites (`0x7F3889`, `0x80875A`, `0x7FB03A`, `0x7FB04E`) or
exclude ModLoader/driver callbacks and dynamic re-entry; the `100076d0`
stack-state invariant therefore remains unresolved.

Fresh artifacts: `gta-sa-100076d0-reentry-xref-check-2026-09-27.csv` and
`gta-sa-100076d0-reentry-call-audit-2026-09-27.csv`. Both used Ghidra 12.1.3
in read-only/no-analysis mode against the existing `gta_sa.exe` project.

## Conclusion

This follow-up corrects the earlier over-broad statement that raster callbacks
are not reached from texture destruction, and identifies the GTA-owned virtual
call as the D3D swap-chain `Release` operation from the matching SDK layout. It
does not observe live registry contents or prove that no external release
implementation can re-enter. Keep `100076d0` YELLOW;
do not alter its initialization and do not count structural/objective or
compile passes as semantic proof. The 705/705 strict compile and 705/705
structural objective result remain unchanged; ReAgent parity remains 704 green,
1 yellow, 0 red.

Primary evidence: `rw-destroy-targets-2026-09-27.c`,
`rw-registration-callers-2026-09-27.c`,
`rw-registered-callbacks-2026-09-27.c`,
`raster-plugin-xrefs-independent-2026-09-27.csv` and `.c`,
`100076d0-call-audit-2026-09-27.csv`, and the bounded helper artifacts named
above. These are temporary Ghidra decompilations/decoded ranges, not recovered
developer source.
