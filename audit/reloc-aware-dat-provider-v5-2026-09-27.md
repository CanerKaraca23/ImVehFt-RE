# CRT registration-thunk relocation follow-up (2026-09-27; superseded)

## Result

The first v5 probe treated 21 remaining initializer entries as simple
exit-registration thunks. A deeper check against all Ghidra instructions found
that **20** have the same ABI-level sequence: push callback, call candidate
`_atexit`, pop the argument into ECX (preserving EAX), return. Entry
`0x100209f0` additionally calls candidate `0x1000a090` and stores the pointer
`0x10024c74` into `DAT_1003c328` before registering its callback. The v5 object
omitted those operations, so it is **not a semantically valid reconstruction
of that entry**. The discrepancy was caught before any link or game test; v5 is
superseded by [v6](reloc-aware-dat-provider-v6-2026-09-27.md). The
callback/TU mapping is recorded in
[`crt-init-array-source-crosswalk-2026-09-27.csv`](crt-init-array-source-crosswalk-2026-09-27.csv).

The v5 diagnostic provider emitted public code labels and retargeted the 21
initializer-array pointers, but did not preserve the full `0x100209f0`
behavior. The interim object must not be used for linking or runtime testing.

Fresh results:

- MASM x86 `/coff` assembly succeeded.
The earlier v5 structural object check passed its then-current expected form,
but did not compare the full original Ghidra instruction sequence for every
thunk. That check was too weak to establish semantic equivalence. The expanded
v6 verifier performs that Ghidra comparison and corrects `0x100209f0`.

Reproduction:

```powershell
py -3.13 scripts/generate-coff-dat-relocation-provider.py `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --objects-dir build/recheck/strict-fresh-after-source-discovery-20260927 `
  --init-array-crosswalk audit/crt-init-array-source-crosswalk-2026-09-27.csv `
  --asm build/recheck/reloc-aware-dat-provider-v5-20260927.asm `
  --manifest audit/reloc-aware-dat-provider-v5-2026-09-27.json

$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX86\x86\ml.exe'
& $ml /nologo /c /coff /Fo build/recheck/reloc-aware-dat-provider-v5-20260927.obj `
  build/recheck/reloc-aware-dat-provider-v5-20260927.asm

py -3.13 scripts/verify-coff-dat-relocation-provider.py `
  build/recheck/reloc-aware-dat-provider-v5-20260927.obj `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --objects-dir build/recheck/strict-fresh-after-source-discovery-20260927 `
  --init-array-crosswalk audit/crt-init-array-source-crosswalk-2026-09-27.csv
```

## Limits

This v5 output is retained only as a historical, superseded probe. One
different stateful initializer at `0x100208d0` remains unreconstructed. The
separate `_initterm_e` table and its four
noncandidate initialization bodies, the original `.text`'s 3,160 HIGHLOW
relocations, complete function/global image layout, patch/hook retargeting,
production link, and runtime behavior remain open. This provider is not a
testable `.asi`; do not load it in the game.
