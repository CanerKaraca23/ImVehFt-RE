# Relocation-aware provider v16 (2026-09-27)

## Result

Resolved two more `.text` pointer targets into relocatable local code:

- `0x100130d6`: the Ghidra-confirmed CRT cleanup helper, linked to the existing candidate objects for `__flushall`, conditional `__fcloseall`, and `_free`.
- `0x10001000`: a two-instruction context shim which stores the relocated pointer `0x10022250` through ECX and jumps to the exact candidate entry at `0x1001031f`. It is **not** the PE entrypoint: the original PE header's entrypoint VA is `0x100111b3` (RVA `0x111b3`).

The independent COFF verifier checks both target instruction sequences, emitted code bytes, exact candidate call/jump relocations, and the `.rdata`/`.data` symbol offsets. Across the diagnostic provider, it passes **1,479/1,479** pointer fixups: 1,322 data-to-data, 119 exact candidate-function, and 38 reconstructed local-code targets. All **81** emitted `.text` relocations are accounted for; 22 startup-thunk sequences match 22/22. The state-table callback crosswalk verifies 177/177 bytes, and the verifier reports zero mismatches. MASM assembly and Python bytecode compilation succeed.

## Reproduction artifacts

- `build/recheck/reloc-aware-dat-provider-v16-20260927.asm` and `.obj`.
- `audit/reloc-aware-dat-provider-v16-2026-09-27.json`.
- `scripts/generate-coff-dat-relocation-provider.py` and `scripts/verify-coff-dat-relocation-provider.py`.
- Ghidra instruction input for both new targets: `audit/pe-relocation-unmapped-code-target-instruction-windows-recheck-2026-09-27.csv`.

## Remaining limits

There are **42** unresolved code-pointer sites and **3,160** original `.text` HIGHLOW relocations not represented in this diagnostic object. Full image/function layout, hook retargeting, production linking/import integration, and game validation are still open; this is not a loadable `.asi`. Candidate-level results remain 705 strict compile, 705 structural PASS, and 704 GREEN / 1 YELLOW parity in the last recorded runs; no candidate TU changed in this provider-only work, so those suites were not rerun.
