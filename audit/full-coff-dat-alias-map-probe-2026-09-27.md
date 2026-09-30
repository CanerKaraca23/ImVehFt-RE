# Full COFF `DAT_*` alias-map probe

Date: 2026-09-27. This scales the one-address MASM alias proof to every
unresolved `DAT_*` external in the current 705-object inventory and checks
that each external lands at its original section-relative offset.

## Result

`generate-coff-dat-alias-provider.py` generated an alias-only MASM source from
the audited COFF inventory and PE storage map. VS2022 x86 MASM assembled it
into `build/recheck/coff-dat-alias-provider-probe.obj`. The resulting object
has `.rdata` and `.data` sections with `ORG`-positioned public labels.
`verify-coff-dat-alias-provider.py` parsed `dumpbin /headers` and `/symbols`
and compared the exact external names, section numbers, and section offsets
against the inputs:

```text
expected names=601; provider names=601; missing=0; extras=0;
offset/section mismatches=0
```

Thus the COFF name/alias and address-offset mapping is mechanically
reproducible for all 601 currently missing decorated names. It also confirms
that the source-declared type spelling differences can be represented as
labels to the same storage without silently choosing a different address.

## Reproduction

```powershell
py -3.13 scripts/generate-coff-dat-alias-provider.py `
  audit/coff-dat-symbol-inventory-verified-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  --asm build/recheck/coff-dat-alias-provider-probe.asm

$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX64\x86\ml.exe'
$dumpbin = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX64\x86\dumpbin.exe'
& $ml /nologo /c /coff /Fo:build/recheck/coff-dat-alias-provider-probe.obj build/recheck/coff-dat-alias-provider-probe.asm
py -3.13 scripts/verify-coff-dat-alias-provider.py `
  audit/coff-dat-symbol-inventory-verified-2026-09-27.csv `
  audit/coff-dat-pe-storage-recheck-2026-09-27.csv `
  build/recheck/coff-dat-alias-provider-probe.obj `
  --dumpbin $dumpbin
```

Both generators refuse to overwrite existing outputs. For a repeat run, use
new `.asm` and `.obj` paths (or first preserve and move the prior probe
artifacts); do not delete the existing audit outputs just to reuse their names.

Scripts:
[`generate-coff-dat-alias-provider.py`](../scripts/generate-coff-dat-alias-provider.py)
and
[`verify-coff-dat-alias-provider.py`](../scripts/verify-coff-dat-alias-provider.py).

## Strict limits

This object is **not** a valid data provider: it emits zero padding rather
than the original 266 file-backed global values, does not reproduce the full
original `.rdata/.data` section extents, and contains no base-relocation
fixups. It does not resolve the 139 absolute operands in hook bodies or prove
that relocated code/data references target correct objects. It has not been
linked with the 705 objects into a plugin, and it must not be loaded into the
game. Its only passed property is exact resolution of all 601 COFF aliases at
the intended section-relative offsets.
