# RenderWare texture dictionary lookup audit

Date: 2026-09-27. This checks the other RenderWare routine called by candidate
`100076d0`, independently of the texture-destruction path.

## Identity and bounded Ghidra result

The historical local Plugin-SDK snapshot (`_sdk_history/snapshot-2014-04-27`,
`src/sdk/game_sa/RenderWare.h:2099`) maps `0x7F39F0` to
`RwTexDictionaryFindNamedTexture(dict, name)`. A Ghidra 12.1.3 `-noanalysis`
bounded CFG/decompile of the installed `gta_sa.exe` reached 54 instructions
and 115 bytes (`0x7F39F0` through `0x7F3A62`); it walks the dictionary's linked
list, compares names case-insensitively, returns the matching texture, or
returns null at the list sentinel. The bounded body contains no indirect call,
callback dispatch, or call to the ImVehFt vehicle-context writer.

Evidence: [`rw-texture-dictionary-find-bounded-2026-09-27.csv`](rw-texture-dictionary-find-bounded-2026-09-27.csv)
and [`rw-texture-dictionary-find-bounded-2026-09-27.c`](rw-texture-dictionary-find-bounded-2026-09-27.c).
These are bounded binary decompilation artifacts, not original source or
runtime evidence. PDB analyzers were not used (`-noanalysis`).

## Effect on `100076d0`

This rules out callback re-entry originating inside the known
`RwTexDictionaryFindNamedTexture` body itself. It does not rule out concurrent
or external mutation, nor resolve texture-destruction's RenderWare registry
callbacks reached through `0x74DBC0 -> 0x7F3820 -> 0x808740`. The conditional
stack-slot discrepancy therefore remains open; keep the candidate unchanged
and the semantic result YELLOW.
