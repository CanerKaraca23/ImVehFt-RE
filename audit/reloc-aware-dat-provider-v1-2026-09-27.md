# Relocation-aware data-provider probe (2026-09-27)

## Result

Generated and assembled a diagnostic x86 COFF provider from the installed
reference ASI, the fresh 705-object DAT inventory, the PE storage crosswalk,
and the data-relocation coverage CSV. The provider emits the original
`.rdata`/`.data` bytes and loader zero-fill, defines all 601 unresolved DAT
spellings, and expresses each data-to-data HIGHLOW site as `DD OFFSET` to a
synthetic label at its original target offset.

Fresh validation:

- MASM x86 `/coff` assembly succeeded.
- The COFF verifier found **1,322 expected data-to-data sites**, **1,322
  `.data`/`.rdata` relocation records**, and verified **all 1,322 exact site
  offsets, `DIR32` types, target symbols, target sections, and target offsets**;
  zero mismatches.
- All **199** data/code relocation sites are intentionally retained as
  preferred-base constants and remain unresolved by this provider.
- The 601 symbol aliases and original data-byte/zero-fill checks are inherited
  from the preceding initialized-provider probe; this diagnostic does not link
  or execute the 705 function objects.

Reproduction:

```powershell
py -3.13 scripts/generate-coff-dat-relocation-provider.py `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --asm build/recheck/reloc-aware-dat-provider-v1-20260927.asm `
  --manifest audit/reloc-aware-dat-provider-v1-2026-09-27.json

$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX86\x86\ml.exe'
& $ml /nologo /c /coff /Fo build/recheck/reloc-aware-dat-provider-v1-20260927.obj `
  build/recheck/reloc-aware-dat-provider-v1-20260927.asm

py -3.13 scripts/verify-coff-dat-relocation-provider.py `
  build/recheck/reloc-aware-dat-provider-v1-20260927.obj `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv
```

## Limits

This is **not a loadable plugin or a rebuilt `.asi`**. The 199 code-target data
relocations, 3,160 `.text` HIGHLOW relocations, relocated function/global
addresses, original section/image layout, CRT startup tables, installer hook
retargeting, and runtime behavior remain unimplemented or unverified. Do not
install or load this object. Its pass proves only that the listed data-to-data
COFF fixups match their original PE sites and targets.
