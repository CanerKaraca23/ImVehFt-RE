# MSVC COFF same-address data alias probe

Date: 2026-09-27. This isolated test checks whether MASM can define the
different decorated COFF external names used for one original ImVehFt data
address as labels at one shared storage offset.

## Result

Using address `0x1003c248` from the audited inventory, MASM x86 `/coff`
successfully assembled three distinct external names into one `.data` object
location:

```text
00000020 SECT2 External | ?DAT_1003c248@@3HC
00000020 SECT2 External | _DAT_1003c248
00000020 SECT2 External | ?DAT_1003c248@@3HA
```

The offset probe uses `ORG 20h`; `dumpbin /headers` reports a `.data` raw size
of `0x24`. Thus labels can be placed at controlled offsets within one object
section while preserving multiple exact COFF spellings at the same offset.
Probe sources are [`probe-coff-dat-aliases.asm`](../scripts/probe-coff-dat-aliases.asm)
and [`probe-coff-dat-alias-offset.asm`](../scripts/probe-coff-dat-alias-offset.asm);
objects are under `build/recheck/coff-dat-alias-probe.obj` and
`build/recheck/coff-dat-alias-offset-probe.obj`.

## What this enables and does not prove

This validates a viable mechanism for a future address-coherent COFF data
provider: exact C++ decorated names may be exported as aliases over shared
storage. It does **not** generate aliases for the full 418-address inventory,
prove every symbol's required extent, reproduce the original `.rdata/.data`
image, apply the original 1,521 data-section base relocations, resolve code
targets, or produce a loadable plugin. The whole-image relocation and hook
address problems remain open; no candidate source or installed game file was
changed.

## Reproduction

```powershell
$ml = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX64\x86\ml.exe'
$dumpbin = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\HostX64\x86\dumpbin.exe'
& $ml /nologo /c /coff /Fo:build/recheck/coff-dat-alias-offset-probe.obj scripts/probe-coff-dat-alias-offset.asm
& $dumpbin /symbols build/recheck/coff-dat-alias-offset-probe.obj
```
