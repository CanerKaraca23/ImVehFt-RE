# Relocation-aware provider v14 (2026-09-27)

## Result

Reconstructed the CRT cleanup helper at `0x100130d6` from the Ghidra instruction window. Its body calls candidate `__flushall`, conditionally calls candidate `__fcloseall` when byte flag `0x10039a34` is nonzero, then passes the `0x1003c520` CRT allocation pointer to candidate `_free`. The callback table pointer stored at `0x100221dc` now resolves to a local relocatable COFF stub. No candidate C++ source was edited.

The independent verifier now checks the exact eight-instruction Ghidra sequence, emitted x86 code bytes, all three candidate call relocations, both global `.data` offsets, and the callback pointer relocation. The complete diagnostic provider passes **1,478/1,478** pointer fixups: 1,322 data-to-data, 119 exact candidate-function targets, and 37 reconstructed local-code targets. All **79** emitted `.text` COFF relocations are accounted for; startup-thunk Ghidra matches remain **22/22**. The verifier reports zero mismatches, MASM assembly succeeds, and both Python scripts pass bytecode compilation.

## Reproduction artifacts

- `build/recheck/reloc-aware-dat-provider-v14-20260927.asm` and `.obj`.
- `audit/reloc-aware-dat-provider-v14-2026-09-27.json`.
- `scripts/generate-coff-dat-relocation-provider.py` and `scripts/verify-coff-dat-relocation-provider.py`.
- Ghidra instruction rows: `audit/pe-relocation-unmapped-code-target-instruction-windows-recheck-2026-09-27.csv`.

## Remaining limits

There are **43** unresolved code-pointer sites. The original `.text` still has **3,160** HIGHLOW relocations not implemented in this diagnostic object, and image layout, hooks, full production linking/import integration, and game validation remain open. This is not a loadable `.asi`. The last recorded candidate-level checks remain 705/705 strict compile, 705 structural PASS, and 704 GREEN / 1 YELLOW parity; they were not rerun because no candidate TU changed in this provider-only work.
