# CRT initializer reconstruction correction (2026-09-27; superseded)

This is the v6 intermediate result. A subsequent full-entry review reconstructed
the remaining stateful `0x100208d0` initializer; see
[`reloc-aware-dat-provider-v7-2026-09-27.md`](reloc-aware-dat-provider-v7-2026-09-27.md).

## Ghidra discrepancy caught and corrected

The expanded verifier compared every reconstructed registration thunk against
the full Ghidra instruction list and caught an error in the v5 approximation:
`0x100209f0` was not a simple four-instruction thunk. It first calls
`FUN_1000a090`, then pushes the exit callback, writes the `.rdata` pointer
`0x10024c74` to `DAT_1003c328`, calls `_atexit`, pops the argument while
preserving EAX, and returns. The v5 interim object omitted the first call and
global write. It was never linked or loaded; v5 is marked superseded in its
[historical report](reloc-aware-dat-provider-v5-2026-09-27.md).

The v6 provider now reconstructs that sequence, using the corresponding
current candidate COFF symbols and preserving the original global/data
offsets. The other 20 exit-registration entries retain their verified
push/call/pop/return sequences. The stateful initializer `0x100208d0` is still
not reconstructed.

## Fresh verification

- Ghidra instruction/callback sequences match **21/21** reconstructed entry
  bodies, including the additional `0x100209f0` call and global-pointer store.
- All **1,434 data-pointer fixups** pass exact COFF site/type/target checks:
  1,322 data-to-data, 91 exact candidate-function-entry, and 21 local
  reconstructed-thunk targets; zero mismatches.
- All **45 code relocations** in the thunk code match their intended symbols:
  the 20 simple thunks have one callback `DIR32` and one `_atexit` `REL32`
  each; `0x100209f0` adds the helper `REL32`, callback `DIR32`, global-cell
  `DIR32`, data-pointer `DIR32`, and `_atexit` `REL32`.
- MASM x86 `/coff` assembly and Python bytecode compilation of both generator
  and verifier succeeded.
- **87** of the original data-to-code pointer sites remain unresolved.

The verifier additionally confirms that `DAT_1003c328` and
`IVF_RELOC_TARGET_10024C74` point to their original `.data`/`.rdata` offsets
inside this diagnostic COFF object. This is not a full program link or runtime
test.

Reproduction:

```powershell
py -3.13 scripts/generate-coff-dat-relocation-provider.py `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --objects-dir build/recheck/strict-fresh-after-source-discovery-20260927 `
  --init-array-crosswalk audit/crt-init-array-source-crosswalk-2026-09-27.csv `
  --asm build/recheck/reloc-aware-dat-provider-v6-20260927.asm `
  --manifest audit/reloc-aware-dat-provider-v6-2026-09-27.json

$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX86\x86\ml.exe'
& $ml /nologo /c /coff /Fo build/recheck/reloc-aware-dat-provider-v6-20260927.obj `
  build/recheck/reloc-aware-dat-provider-v6-20260927.asm

py -3.13 scripts/verify-coff-dat-relocation-provider.py `
  build/recheck/reloc-aware-dat-provider-v6-20260927.obj `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/pe-data-relocation-target-coverage-current-2026-09-27.csv `
  --objects-dir build/recheck/strict-fresh-after-source-discovery-20260927 `
  --init-array-crosswalk audit/crt-init-array-source-crosswalk-2026-09-27.csv `
  --thunk-disassembly audit/pe-relocation-code-target-disassembly-fresh-2026-09-27.csv `
  --inventory audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv
```

## Remaining limits

This diagnostic object is not a rebuilt/testable `.asi`. The 87 remaining
data-to-code sites, stateful initializer `0x100208d0`, `_initterm_e` table and
four noncandidate CRT bodies, the original `.text`'s 3,160 HIGHLOW relocations,
full function/global image layout and hook retargeting, production link, and
game runtime validation remain open. Do not load this object into the game.
