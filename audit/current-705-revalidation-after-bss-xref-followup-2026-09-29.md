# Current 705-set revalidation after BSS xref audit — 2026-09-29

## Exact source and fresh compile

- Current source tree: 705 `.cpp` files; both `audit/source-sha256.csv` and `audit/function-name-map.csv` have 705 rows and zero current-file SHA-256 mismatches.
- Fresh VS 2022 Developer x86 MSVC compile from current sources: `/O1 /W4 /WX /MT /arch:IA32 /GS-`, **705/705 passed, 0 failed**. Report: `build/strict-xcode-nogs-o1-finalfresh-20260929.json`; objects: `build/recheck/strict-xcode-nogs-o1-finalfresh-20260929/`.
- Fresh ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**, report `build/parity-global-bss-xref-followup-fresh-2026-09-29.json`.
- Fresh independent objective audit: **704 PASS / 1 FAIL / 0 UNKNOWN**, report `audit/objective-global-bss-xref-followup-fresh-2026-09-29.json`. The single `10011724` warning is the known source-counter limitation: it counts four visible symbolic calls but misses three indirect IAT calls in the naked assembly body. The independent fixup-aware full-body comparison `audit/10011724-inplace-byte-reconstruction-context-asm-final-2026-09-29.json` proves all 0x129 bytes identical at the original entry, with eight COFF fixups and four matching original HIGHLOW fields. The objective result itself is not relabeled.

## Rebuilt-object reproducibility

The complete COFF file SHA-256 digests changed between the saved 19:15 object directory and the fresh build, so this was tested at the relevant executable-content level. `scripts/compare-coff-bodies-and-relocations.py` compared all 705 root `.xcode` bodies against `audit/entry-trampoline-feasibility-conservative-425-thunks-fclose-dual-linkage-2026-09-29.json`: **0 body-byte mismatches, 0 relocation-record mismatches, and 0 section-number mismatches**. Report: `audit/coff-object-body-relocation-comparison-current-vs-fresh-2026-09-29.json`. Thus the full-object digest drift did not reflect candidate code or relocation changes.

Fresh scans of the rebuilt objects again found 196 API REL32 references across 21 API symbols and 45 functions, plus the same 2,874 COFF fixups across the 425 appended-body set. Reports are `audit/candidate-original-iat-api-rel32-references-strictfresh-2026-09-29.json` and `audit/appended-thunk-relocation-targets-strictfresh-425-2026-09-29.json`.

## Scope boundary

These checks establish current-source freshness, strict compilation, structural parity, the known objective-verifier limitation, and reproducible function-body/fixup content. They do not produce or load a production ASI, prove semantic equivalence of all 705 functions, or test GTA. The pinned original ASI remains unchanged at SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
