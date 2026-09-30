# Relocation-aware data-provider follow-up (2026-09-27)

## Result

The v1 probe handled 1,322 data-to-data HIGHLOW sites. This follow-up also
resolves code-target sites whose address is an exact entry in the current 705
function map and whose fresh x86 object exposes one public function symbol at
`.text` offset zero.

From the original relocation-coverage CSV, the fresh 705-object directory, and
the installed reference ASI, the generator emitted:

- **1,322** data-to-data `DIR32` relocations to synthetic labels at exact
  original target offsets;
- **91** additional `DIR32` relocations (65 distinct public candidate-function
  symbols) to exact function-entry targets;
- **108** code-target pointer sites left untouched because they are not an
  exact candidate entry with a uniquely identified public candidate symbol.

The new x86 MASM object assembled successfully. The COFF verifier then checked
all **1,413** emitted records: exact source section/site offset, `DIR32` type,
and target symbol/section/offset, with **zero mismatches**. For code references,
it verifies the undefined external symbol in the provider object against the
public section-zero symbol at offset zero in the corresponding fresh candidate
object.

Reproduction:

```powershell
py -3.13 scripts/generate-coff-dat-relocation-provider.py `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --objects-dir build/recheck/strict-fresh-after-source-discovery-20260927 `
  --asm build/recheck/reloc-aware-dat-provider-v3-20260927.asm `
  --manifest audit/reloc-aware-dat-provider-v3-2026-09-27.json

$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX86\x86\ml.exe'
& $ml /nologo /c /coff /Fo build/recheck/reloc-aware-dat-provider-v3-20260927.obj `
  build/recheck/reloc-aware-dat-provider-v3-20260927.asm

py -3.13 scripts/verify-coff-dat-relocation-provider.py `
  build/recheck/reloc-aware-dat-provider-v3-20260927.obj `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --objects-dir build/recheck/strict-fresh-after-source-discovery-20260927
```

## Limits

This remains a diagnostic object, not a rebuilt or testable `.asi`. The 108
unresolved code-target sites include noncandidate CRT/exception targets,
interior/funclet entries, and addresses without an exact candidate function
entry. The original `.text` has 3,160 additional HIGHLOW relocation records;
fixed image layout, all hook/shim retargeting, CRT startup tables and thunks,
linking against all dependencies, and game behavior remain unresolved. No game
test was performed, and this object must not be installed or loaded.
