# Relocation-aware provider v17 (2026-09-27)

## Result

Reconstructed 21 additional code-pointer targets as 18 small local-code stubs: 14 exact stack/register wrappers that call existing candidates (`__unlock_file`, `FUN_10017cd2`, or `__unlock_fhandle`), four identical SEH return-one blocks, one SEH boolean-result block, one trampoline, and one context shim. The source-byte templates are recorded in `scripts/reloc_local_code_stubs.py`. At each original address the generator and independent verifier compare the PE bytes with the template, verify each original relative/absolute target, and then check the generated object bytes, relocation kinds, target symbols, and data offsets. These are byte-level code fragments, not claims about restored original C++ functions or proven high-level SEH ownership.

The independent COFF verifier now passes **1,500/1,500** pointer fixups: 1,322 data-to-data, 119 exact candidate-function targets, and 59 local-code pointer sites. All **98** generated `.text` relocations are accounted for; the 22 startup thunk sequences remain 22/22 and the state-table byte crosswalk remains 177/177. It reports zero mismatches.

Fresh candidate gates were also run:

- VS2022 x86 `/O2 /W4 /WX /MT`: **705/705 compiled**, zero failures (`build/strict-reloc-v17-20260927.json`).
- ReAgent 0.4.0 structural objective: **705 PASS / 0 FAIL / 0 UNKNOWN** (`audit/objective-independent-reloc-v17-2026-09-27.json`).
- ReAgent parity across 705 functions: **704 GREEN / 1 YELLOW / 0 RED**; sole yellow remains `0x100076d0` (`build/parity-reloc-v17-20260927.json`). The parity warning was retained; green/compile results are not semantic or runtime proof.

## Reproduction artifacts

- Provider: `build/recheck/reloc-aware-dat-provider-v17-20260927.asm` and `.obj`.
- Manifest/report: `audit/reloc-aware-dat-provider-v17-2026-09-27.json` and this file.
- Generator/verifier: `scripts/generate-coff-dat-relocation-provider.py`, `scripts/verify-coff-dat-relocation-provider.py`, and `scripts/reloc_local_code_stubs.py`.

## Still open

**21** code-pointer sites and **3,160** original `.text` HIGHLOW relocations remain unimplemented, along with full image/global layout, hook retargeting, production linking/import integration, and in-game validation. No loadable `.asi` has been built. Candidate C++ files were not changed in this provider pass.
