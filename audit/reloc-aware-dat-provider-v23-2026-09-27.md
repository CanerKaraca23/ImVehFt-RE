# Relocation-aware provider v23 (2026-09-27)

## Result

Resolved the final remaining `.rdata`/`.data` code-pointer target, `0x1001ce94`, as a reconstructed SEH continuation. The continuation restores the saved stack and registers, then re-enters the unwind-map loop and cleanup path. Instead of redirecting into the prologue of candidate `___FrameUnwindToState`, the provider emits separate local blocks for the referenced loop/convergence/cleanup addresses. This preserves the path's stack state. Every block's source bytes and every original `REL8`/`REL32` call or branch destination were verified against the reference PE before assembly; the COFF verifier then checked the assembled bytes, local branch destinations, external relocations, and destination symbols.

The provider manifest now reports **zero unresolved code-pointer sites**. The generated MASM/COFF provider passes independent verification: **1,521/1,521** fixups, zero mismatches; 1,322 data-to-data sites, 119 exact candidate-code sites, 80 local-code pointer sites, 130 generated `.text` relocations, 22/22 startup thunks, and 177/177 state-table bytes. Artifacts: `build/recheck/reloc-aware-dat-provider-v23-20260927.asm`, `.obj`, and `audit/reloc-aware-dat-provider-v23-2026-09-27.json`.

Ghidra's saved export has no defined function entry at `0x1001ce94`; this continuation was byte-decoded from the original 2014 PE and cross-checked against the adjacent mapped `___FrameUnwindToState` entry and call targets. It is a machine-code reconstruction, not a claim that Ghidra or a PDB supplied the original source.

## Still not a loadable plugin

This provider result does not solve the **3,160** original `.text` HIGHLOW relocations, complete PE section/global layout, installer hook retargeting, production import/library/runtime linkage, or game execution. No `.asi` is ready for testing. The fresh 705-candidate gates remain those in v21: strict compile 705/705, objective 705 PASS, parity 704 GREEN / 1 YELLOW (`0x100076d0`) / 0 RED, and 13/13 scoped call-count adjudications. Those checks are not semantic or runtime proof.
