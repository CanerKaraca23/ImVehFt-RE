# `100076d0` GTA RenderWare callback xref rerun

Date: 2026-09-28. Reopened the existing `raster_audit/gta_sa.exe` Ghidra
program with Ghidra 12.1.3 `analyzeHeadless.bat`, using `-readOnly -noanalysis`
and the existing full-analysis database. The current installed executable SHA-256
is `F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`,
matching the previously audited game binary. The headless run exited normally;
no GTA or Ghidra process remained active afterward.

Fresh generated artifacts:

- `audit/gta-sa-rw-registration-xrefs-rerun-2026-09-28.csv`
- `audit/gta-sa-rw-registration-xrefs-rerun-2026-09-28.c`

The bounded query collected 47 references across the six requested addresses
and decompiled 20 containing callers:

- `RwRasterRegisterPlugin` at `0x007fb0b0` has one code reference, from
  `0x004c9ab0`. Its decompilation registers plugin ID `0x40c`, size `0x24`,
  constructor `0x004c9a60`, destructor `0x004c9a80`, and a null copy callback.
- `RwTextureRegisterPlugin` at `0x007f3bb0` has one code reference, from
  `0x00748f70`.
- The raster-destroy API `0x007fb020` has 42 references in this analyzed
  program; `0x004c9a80` has one data reference from the registration call.
- The known vehicle callback path is still present: `0x00553260` calls
  `0x006d64f0`, and `0x006d64f0` calls `0x004c8430` with the entity field at
  `param_1 + 0x18`.
- The current decompilation of texture destruction at `0x007f3820` releases the
  texture registry entry, calls raster destruction when a raster is attached,
  then invokes a function pointer through the `DAT_00c97b24` table. This agrees
  with the prior callback-chain classification; the indirect runtime target
  and live registry contents are not recovered by this cross-reference query.

## Conclusion and limit

This rerun reproduces the static GTA registration and caller edges against the
current matching `gta_sa.exe` and confirms the known D3D swap-chain plugin
registration path. It still cannot observe the live raster-registry callback,
the COM object's runtime implementation, or whether any external callback
changes `DAT_1003c1fc` or re-enters ImVehFt. Therefore the separate
`100076d0` runtime callback/re-entry risk remains **OPEN**. This is Ghidra
static evidence only, not a game run or candidate `.asi` test.
