# Relocation-aware provider v13 (2026-09-27)

## Result

Reconstructed the `0x10013025` `_initterm_e` CRT state-table initializer using its Ghidra entry/branch/loop/cleanup instruction captures. Ghidra's temporary body omitted the five-byte loop-head instruction at `0x1001307e`; the exact source-PE bytes at that address are `A1 20 C5 03 10` (`MOV EAX,[0x1003c520]`). The verifier cross-checks the 172 bytes represented by Ghidra rows against the original PE and separately verifies those five omitted bytes from the same hashed source PE before accepting the reconstruction.

The MASM callback preserves the observed fallback allocation, error return `0x1a`, lock-table pointer initialization, state-slot scan, and success return. It uses relocatable COFF references to the original `.data` offsets and the `__calloc_crt` candidate object, and its initializer-array pointer at `0x100221c0` now targets the reconstructed callback.

The independent COFF verifier reports **1,477/1,477** pointer-fixup sites verified: 1,322 data-to-data, 119 exact candidate-function, and 36 reconstructed local-code targets. All **74** emitted `.text` relocation records are exactly accounted for; the 22 existing CRT registration thunks still match Ghidra 22/22. The new callback's emitted code bytes, 12 data/call relocation records, and seven data symbol offsets are explicitly checked. MASM assembly and Python bytecode compilation passed; zero verifier mismatches.

## Reproduction artifacts

- Assembly/object: `build/recheck/reloc-aware-dat-provider-v13-20260927.asm` and `.obj`.
- Manifest: `audit/reloc-aware-dat-provider-v13-2026-09-27.json`.
- Generator/verifier: `scripts/generate-coff-dat-relocation-provider.py` and `scripts/verify-coff-dat-relocation-provider.py`.
- Ghidra inputs: `audit/crt-initterm-e-entry-disassembly-2026-09-27.csv`, `audit/crt-initterm-e-branch-disassembly-2026-09-27.csv`, `audit/crt-initterm-e-size-tail-disassembly-2026-09-27.csv`, and `audit/crt-initterm-e-allocation-cleanup-disassembly-2026-09-27.csv`.

## Still open

This provider remains diagnostic, not a loadable `.asi`. **44** code-pointer sites remain unresolved, as do **3,160** original `.text` HIGHLOW relocations, full function/global image layout, hook retargeting, production linking/import integration, and in-game validation. The candidate-level results recorded previously (705 strict compiles, 705 structural PASS, and 704 GREEN / 1 YELLOW parity) were not rerun in this provider-only turn; they do not establish whole-plugin semantics or runtime behavior.
