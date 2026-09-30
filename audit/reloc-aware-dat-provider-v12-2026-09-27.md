# Relocation-aware provider v12 (2026-09-27)

## Result

Reconstructed the `0x100104bc` `_initterm_e` CRT allocation/`EncodePointer` callback from the Ghidra entry disassembly and its separately captured success-tail branch. The generated x86 MASM imports the observed `__calloc_crt` candidate entry and x86 `EncodePointer` IAT symbol, stores both CRT globals at their original `.data` offsets, and returns the observed `0x18` allocation failure code or zero on success. The callback pointer at `0x100221bc` now resolves to the local reconstructed stub.

The independent COFF verifier reports **1,476/1,476** `.data`/`.rdata` pointer fixups verified: 1,322 data-to-data, 119 exact candidate-function, and 35 reconstructed local-code targets. All **62** emitted `.text` COFF relocations are accounted for with exact site, relocation type, symbol, and target checks. The 22 startup-thunk instruction sequences still match 22/22. MASM assembly and Python bytecode compilation succeeded; the verifier reports zero mismatches.

## Reproduction

Inputs are the original installed `ImVehFt.asi`, the fresh 705-object directory `build/recheck/strict-fresh-after-source-discovery-20260927`, `audit/pe-data-relocation-target-coverage-current-2026-09-27.csv`, `audit/crt-init-array-source-crosswalk-2026-09-27.csv`, `audit/crt-initterm-e-entry-disassembly-2026-09-27.csv`, `audit/crt-initterm-e-branch-disassembly-2026-09-27.csv`, and the related v11 inputs. Output files are `build/recheck/reloc-aware-dat-provider-v12-20260927.asm`, `.obj`, and `audit/reloc-aware-dat-provider-v12-2026-09-27.json`.

The generator independently checks the allocation callback's entry block and success-tail rows against those two Ghidra captures. The verifier checks the resulting instruction bytes, all callback pointer/fixup sites, the candidate allocator call relocation, the `EncodePointer` import relocation, and both global section offsets.

## Remaining limits

The more complex `0x10013025` CRT state-table initializer is still open, along with **45** other code-pointer targets, **3,160** original `.text` HIGHLOW relocations, function/global image layout, hook retargeting, full production linking, and in-game validation. This provider remains diagnostic and is **not a loadable/testable `.asi`**. No candidate `.cpp` source was changed, and the previously recorded 705/705 strict compile, 705 structural PASS, and 704 GREEN / 1 YELLOW parity were not rerun in this provider-only change.
