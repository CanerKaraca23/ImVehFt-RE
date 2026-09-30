# Isolated legacy `.rdata` linker-metadata probe — 2026-09-29

## Setup and result

Re-linked only the saved section-layout probe objects (`text.obj`,
`rdata.obj`, `data.obj`, `code.obj`, and `resource.res`) with the VS 2022 x86
linker, `/BASE:0x10000000`, `/FIXED`, and `/NOENTRY`. This is a synthetic
layout probe, not an ImVehFt image. The output preserved `.text` at RVA
`0x1000`, placed `.rdata` at `0x22000`, `.xcode` at `0x3F000`, and the
reserved `.data` after `.rdata`.

The original image has `.rdata` raw/virtual reservation `0x7000` bytes, with
meaningful virtual data through RVA `0x28F44`; `.data` starts at RVA `0x29000`.
The probe's linker map instead reports `.rdata` virtual size `0x7028`, moving
`.data` to RVA `0x2A000`. The excess `0xE4` is fully accounted for by:

| Linker output | Bytes | Evidence |
|---|---:|---|
| `.rdata` extension / PE Debug Directory | `0x1C` | Debug Directory at RVA `0x28F44`; `.rdata` begins at `0x22000` |
| `.rdata$voltmd` | `0x18` | linker map; `___volatile_metadata` at RVA `0x28F60` |
| `.rdata$zzzdbg` | `0xB0` | linker map; starts at RVA `0x28F78` |
| **Total** | **`0xE4`** | brings `.rdata` to `0x7028` |

This exact sum identifies the bytes forcing the next section-alignment step;
it does **not** prove these bytes can be discarded. The `.xcode` probe's
placement at `0x3F000` is also within the original image's address span and is
not a proposed final placement.

## Byte-content check against the pinned ASI

Parsed the generated PE section table and compared its reserved-section
prefixes with the same-length original ASI ranges. The probe is **not** a
content-preserving copy: the first `.text` byte is `90` in the probe versus
`C7` in the original; the first bytes of its `.rdata` and `.data` reservations
are zero versus nonzero original bytes. Consequently the section-geometry
experiment establishes linker placement only; it cannot prove that removing
the measured linker tail would yield a safe original `.rdata`/`.data` layout.

## Attempts to identify a linker switch

Two independently named probe links were made with and without `/DEBUG:NONE
/PDB:NONE`. Both produced the same `.rdata` size, the same `voltmd` and
`zzzdbg` contributions, and the same Debug Directory. A second pair used
copies of the four probe COFF objects after removing their `.debug$S` sections
with `llvm-objcopy`; the linker output was unchanged again. These checks rule
out those particular switches/sections as a solution; they do not rule out
other linker options or a carefully validated PE post-link transformation.
An isolated `/MERGE:.rdata$voltmd=.data` attempt was also rejected by the
linker with LNK1184 (invalid section name); no output was emitted. This exact
subsection-redirection spelling is therefore not a usable option in this
toolchain invocation.

Artifacts are under `build/layout-probe/standalone-debug-20260929/`,
`build/layout-probe/standalone-nodebug-20260929/`, and
`build/layout-probe/section-order-stripped-debug-20260929/`. The original ASI
was not modified. Its current SHA-256 remains
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Status

The original `.data` RVA is still not preserved by this linker layout. Before
attempting to excise any generated range, inspect references to
`___volatile_metadata`, the Debug Directory fields, section bytes, and all
base relocations in the candidate output. Any proposed transformation must
also preserve loader-required data and be validated against the original
section/relocation maps. No production `.asi` or GTA runtime validation was
created by these probes.
