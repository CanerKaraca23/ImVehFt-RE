# CRT initializer thunk completion follow-up (2026-09-27)

## Ghidra-backed reconstruction

The v6 verifier's complete-instruction comparison exposed that
`0x100208d0` performs more than callback registration. It sets/reads the
one-time guard at `DAT_1003c3fc`, clears `DAT_1003c3e8` and `DAT_1003c3ec`,
registers callback `0x10020a80` through `_atexit` only on the first path, then
stores `&DAT_1003c3e8` in `DAT_1003c38c`. The v7 generator recreates the
instruction order and condition, and relocates each global/callback reference
through symbols at its original section offset. The initializer-array pointer
now targets the emitted code label rather than the original fixed VA.

Together with the earlier `0x100209f0` correction (helper call plus global
pointer store) and the 20 simple registration-only routines, all **22
noncandidate initializer entry thunks** in the `.CRT$XCU` range now have
reconstructed COFF code labels. The separate candidate initializer
`0x10020870` remains its own source object and is referenced through its
candidate symbol.

## Fresh verification

- Ghidra instruction sequences and callback addresses match **22/22** thunk
  entries exactly at the recorded assembly level.
- MASM x86 `/coff` assembly succeeded.
- The COFF verifier passes **1,435/1,435 data-pointer relocations**: 1,322
  data-to-data, 91 exact candidate-function entries, and 22 reconstructed
  thunk pointers. It checks their exact source sites, relocation kinds, target
  symbols, sections, and original offsets; zero mismatches.
- All **53** code relocations inside the 22 reconstructed thunks are checked,
  including callback/helper calls, data-cell references, and `_atexit`; thunk
  opcodes, branch, and zero addends are also verified. Zero mismatches.
- **86** original data-to-code pointer sites remain unresolved.

No candidate `.cpp` was changed in this reconstruction pass. The current
independent candidate validations remain the recorded fresh results: strict
compile 705/705, structural objective 705 PASS, and ReAgent parity 704 GREEN /
1 YELLOW / 0 RED. These checks are not runtime or full-link proof.

## Limits

The diagnostic provider is still **not a testable `.asi`**. Remaining work
includes the 86 data-to-code pointer targets (notably exception/funclet and
CRT/runtime entries), the separate `_initterm_e` array and four noncandidate
CRT initialization bodies, the original `.text` section's 3,160 HIGHLOW
relocations, full function/global image layout and all game hook retargeting,
production linking, and actual in-game validation. This object must not be
installed or loaded.

Reproduction uses `scripts/generate-coff-dat-relocation-provider.py` and
`scripts/verify-coff-dat-relocation-provider.py` with the same source files
and switches listed in the preceding v6 report, substituting
`reloc-aware-dat-provider-v7-20260927` for v6 and adding:

```powershell
--inventory audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv
```

The exact current command/output artifacts are `build/recheck/reloc-aware-dat-provider-v7-20260927.asm`, `.obj`, and `audit/reloc-aware-dat-provider-v7-2026-09-27.json`.
