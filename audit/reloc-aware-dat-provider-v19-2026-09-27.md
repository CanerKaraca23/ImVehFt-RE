# Relocation-aware provider v19 (2026-09-27)

## Result

Added 16 more small code-pointer fragments to `scripts/reloc_local_code_stubs.py`. Each template was checked against the original ASI bytes; each absolute or relative external reference was checked against its original target before generation. For MASM-only instruction forms (`fs:[0]` and `ldmxcsr`) the byte encodings are emitted directly, while the surrounding code remains assembled normally.

The provider's unresolved `.text` code-pointer relocation sites fell from **21 to 5**. The remaining target VAs are `0x10018a86`, `0x1001ce94`, `0x1001d0ff`, `0x1001d108`, and `0x1001d18f`.

Fresh artifacts:

- Generator output: `build/recheck/reloc-aware-dat-provider-v19-20260927.asm` and `.obj`.
- Independent COFF verifier: **1,516/1,516** data/code pointer fixups, zero mismatches; 1,322 data-data sites, 119 candidate-code sites, 75 reconstructed local-code sites, 117 generated `.text` code relocations, 22/22 startup thunks, and 177/177 state-table bytes.
- This is provider/relocation evidence only. The 3,160 original `.text` HIGHLOW relocations, full PE image and hook placement, import/link integration, the remaining five targets, and game/runtime testing are still outstanding. No loadable `.asi` is produced by this diagnostic provider.

The 705 candidate sources were not changed in this pass; existing 705/705 strict compile and 704-green/1-yellow parity results are unchanged, not rerun here. The parity yellow remains `0x100076d0`.
