# Initialized `DAT_*` provider probe

Date: 2026-09-27. This diagnostic step follows the fresh strict compile,
objective/parity reruns, and COFF audit. It asks whether the missing data
symbols can be backed by the exact original PE bytes rather than the zero-fill
alias-only probe. It does **not** claim to produce a loadable plugin.

## Inputs and generated object

The input ImVehFt image is the installed file at
`GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`. The
current storage inventory classifies 266 referenced locations as raw-backed
(100 in `.rdata`, 166 in `.data`) and 152 as loader zero-fill locations in the
`.data` virtual tail.

[`generate-coff-dat-initialized-provider.py`](../scripts/generate-coff-dat-initialized-provider.py)
generated a MASM object with all 601 currently missing decorated `DAT_*`
names at their audited section-relative offsets. It emits the complete
preferred-base `.rdata` and `.data` byte ranges: `.rdata` is `0x7000` bytes;
`.data` is `0x1455c` bytes, consisting of the original `0x10a00` file-backed
bytes plus zero fill. The generator cross-checks every referenced raw-backed
global's PE file offset and initial bytes against the storage CSV.

Validation results:

- VS2022 x86 MASM assembled the generated source successfully.
- `verify-coff-dat-alias-provider.py`: **601 expected names, 601 provider
  names, 0 missing, 0 extras, 0 section/offset mismatches**.
- [`verify-coff-dat-initialized-provider.py`](../scripts/verify-coff-dat-initialized-provider.py):
  **2/2 section byte streams exact** against the original PE plus loader
  zero-fill. Object `.rdata` and `.data` sections contain zero COFF relocation
  entries. The verified v2 provider object SHA-256 is
  `6F24F16B314A1BC2B492F8EA403A7753476299AE8E27AE931A95C16300A368BE`.
- Merged with the 705 fresh strict objects, the 706-object archive's
  `audit-coff-data-symbols.py` inventory reports **602 undefined decorated
  spellings, 0 without an exact definition**. The 418 addresses remain
  referenced by candidate objects; 152 addresses have multiple spellings.

The generator's exact source/image hashes and section extents are recorded in
[`initialized-dat-provider-source-manifest-v2-2026-09-27.json`](initialized-dat-provider-source-manifest-v2-2026-09-27.json).
The merged-archive address inventory is
[`coff-dat-symbols-after-initialized-provider-v2-2026-09-27.csv`](coff-dat-symbols-after-initialized-provider-v2-2026-09-27.csv).

## Relocation follow-through

The existing 1,521-entry `.rdata`/`.data` relocation coverage CSV
([`pe-data-relocation-target-coverage-current-2026-09-27.csv`](pe-data-relocation-target-coverage-current-2026-09-27.csv))
lets us separate relocations that can point into rebuilt data sections from
those that require code-target recovery:

| Site section | Stored target section | Sites | Unique target VAs | Exact current candidate address matches |
|---|---|---:|---:|---|
| `.data` | `.data` | 30 | 10 | 2 target VAs have a candidate global spelling |
| `.data` | `.rdata` | 234 | 143 | 0 target VAs have a candidate global spelling |
| `.data` | `.text` | 10 | 1 | 0; all point to CRT helper `0x1001AF2B`, outside the 705 entries |
| `.rdata` | `.data` | 166 | 92 | 1 target VA has a candidate global spelling |
| `.rdata` | `.rdata` | 892 | 467 | 1 target VA has a candidate global spelling |
| `.rdata` | `.text` | 189 | 143 | 73 target VAs are exact candidate function entries; 70 are not |

Thus **1,322 data-section relocation sites** point to `.data`/`.rdata` targets
and are structurally amenable to symbol-based COFF fixups if every target byte
is labeled. The other **199 sites** point to code: 73 exact function entries,
70 interior/noncandidate text targets, and the one CRT fallback helper (ten
sites). The counts and target-owner distinctions are from the preserved CSV;
they do not yet implement those fixups. The initialized provider still has
zero relocations, so none of these target pointers has been retargeted.

## Remaining link/runtime blockers

The provider preserves bytes containing preferred-base addresses as raw
constants. It does not emit relocation records for the original image's 274
`.data`, 1,247 `.rdata`, or 3,160 `.text` HIGHLOW relocations; it does not
retarget pointers into moved functions/data, recreate original section RVAs,
resolve CRT/helper bodies, or integrate the 12 hook shims and their 139
image-internal fixups. The candidate link map still moves functions and state
away from the fixed addresses expected by installer/hook code. Therefore this
object/archive is evidence that the DAT names and initial bytes can be
reproduced, **not** evidence of a production link, valid `.asi`, or safe game
test. Do not install or load it.

## Reproduction

```powershell
py -3.13 scripts/generate-coff-dat-initialized-provider.py `
  'C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi' `
  audit/coff-dat-symbols-fresh-after-source-discovery-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  --asm build/recheck/fresh-initialized-dat-provider-v2-20260927.asm `
  --manifest audit/initialized-dat-provider-source-manifest-v2-2026-09-27.json

$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX86\x86\ml.exe'
& $ml /nologo /c /coff /Fo build/recheck/fresh-initialized-dat-provider-v2-20260927.obj `
  build/recheck/fresh-initialized-dat-provider-v2-20260927.asm
```
