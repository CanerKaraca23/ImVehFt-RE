# External reference scan for `DAT_1003c1fc`

Date: 2026-09-27. Scope: installed GTA SA directory, scanning non-backup
`.exe`, `.asi`, and `.dll` files for the little-endian preferred-VA bytes of
`DAT_1003c1fc` (`FC C1 03 10`). The scan covered 68 files. It is a static
byte/reference check only; it does not establish which ModLoader entries were
active in a particular game session.

## Hits and classification

- `modloader/My Scripts/.ImVehFt/ImVehFt.asi`, file offset `0x6A84`: expected
  literal write to the ImVehFt global, independently present in the Ghidra
  cross-reference map as `MOV [0x1003c1fc], EDI` in `100074d0`.
- `modloader/My Scripts/SkyGfx Remix/skygfx.asi`, file offset `0xE062`:
  `dumpbin /disasm` decodes the occurrence as `divss xmm2, dword ptr
  ds:[1003C1FCh]` at image VA `0x1000EC5E`, a read, not a write. The operand
  has a base-relocation entry at RVA `0xC62`; `0x1003C1FC` is within this
  SkyGfx image's own `.rdata` range (`0x1003C000..0x1004D025`). This is a
  module-internal absolute reference under the preferred image base, not
  evidence that SkyGfx addresses ImVehFt's global.
- `modloader/.data/plugins/gta3/std.asi.dll`, file offset `0x31FA4`: the
  occurrence is in `.rdata`, not executable code. It is at RVA `0x337A4` and
  has a `HIGHLOW` relocation to `0x1003C1FC`; that address is inside this
  module's own `.rdata` range (`0x10032000..0x1003E7C7`). It is therefore a
  relocated module-internal data pointer, not a code write to ImVehFt state.

No other byte hits were found in the 68-file scan. In particular, the scan
found no additional external module code reference to the ImVehFt preferred
global address, let alone a classified external store. This narrows the
static alias-writer concern, but cannot rule out dynamically computed aliases,
callbacks, an unscanned/late-loaded module, or runtime re-entry. The game
process was not running during this check, so no live memory or callback state
was observed.

## Effect on the open finding

This is new corroborating evidence that the only statically identified
literal writer is the expected `100074d0` setter. It does not prove that the
setter cannot run re-entrantly while `100076d0` is inside texture/raster
destruction. Keep `100076d0` YELLOW and its candidate source unchanged. Do not
interpret this static scan, compilation, or ReAgent parity as runtime proof.
