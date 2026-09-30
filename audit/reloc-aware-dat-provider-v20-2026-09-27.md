# Relocation-aware provider v20 (2026-09-27)

## Result

Reconstructed the `0x10018a86` bitfield/unlock fragment from the reference ASI's exact x86 bytes. Its absolute state-table reference (`0x1003c420`) and relative call (`0x100191a6`) were checked against the original image; generated MASM/COFF output retained both as relocations.

The provider's remaining code-pointer relocation sites fell from **5 to 4**: `0x1001ce94`, `0x1001d0ff`, `0x1001d108`, and `0x1001d18f`.

Independent verification passes **1,517/1,517** fixups with zero mismatches, including 1,322 data-to-data sites, 119 exact candidate-code sites, 76 reconstructed local-code sites, 119 generated `.text` relocations, 22/22 startup thunks, and 177/177 state-table bytes. Artifacts: `build/recheck/reloc-aware-dat-provider-v20-20260927.asm` and `.obj`; manifest: `audit/reloc-aware-dat-provider-v20-2026-09-27.json`.

The reference image SHA-256 remains `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`. No candidate C++ unit changed in this pass; existing compile/objective/parity results were not rerun. This is not a loadable `.asi`: the original `.text` HIGHLOW relocations, complete image/hook layout, production imports/linking, four remaining code targets, and runtime/game tests remain open.
