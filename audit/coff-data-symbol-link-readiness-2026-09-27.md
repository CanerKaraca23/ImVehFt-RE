# Candidate COFF data-symbol link readiness

Date: 2026-09-27. This audit checks external `DAT_*` symbol definitions in the
fresh 705-object archive produced from the current strict-compile objects. It
does not claim a full link or semantic/runtime verification.

## Reproduction and result

The archive contains exactly 705 members from
`build/recheck/strict-final-current-20260927`. MSVC `dumpbin /symbols` output
was parsed by [`scripts/audit-coff-data-symbols.py`](../scripts/audit-coff-data-symbols.py):

```powershell
py -3.13 scripts/audit-coff-data-symbols.py `
  build/recheck/strict-final-current-20260927/strict-final-current-20260927.lib `
  --dumpbin 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x86\dumpbin.exe' `
  --csv audit/coff-dat-symbol-inventory-verified-2026-09-27.csv
```

The resulting inventory contains **418 distinct `DAT_*` addresses** referenced
by object files: **100** fall in the original ASI `.rdata` range and **318** in
its `.data` range. Every address has at least one undefined external reference.
Only **one address**, `0x1003c398`, has any definition in the 705-object
archive, and that definition is only the single decorated symbol
`?DAT_1003c398@@3IA`. The inventory contains **602 unique undefined decorated
symbol/address associations**; **601 decorated names have no exact definition**
in this archive. At **152 addresses**, the objects reference multiple distinct
C++-decorated names for the same address (up to four variants at one address).
The complete per-address names and counts are in
[`coff-dat-symbol-inventory-verified-2026-09-27.csv`](coff-dat-symbol-inventory-verified-2026-09-27.csv).

The 100/318 section totals were classified against the original ASI PE layout:
`.rdata` starts at `0x10022000`, `.data` starts at `0x10029000`, and the
`.data` virtual range ends at `0x1003d55c`. All 418 addresses fell within one
of those two ranges. `0x1003c398` is defined by `src/functions/1000db80.cpp`;
its other pointer/integer/undecorated symbol forms still require aliases if
they are to refer to that same storage.

## Link implication

The 705 translation units compile, but they do not provide a standalone global
data image. A production link needs an address-coherent provider for these
globals, including same-address decorated aliases, with initial bytes and
runtime initialization grounded in the original ASI/Ghidra evidence. The
successful diagnostic link used synthetic alias providers and therefore does
not close this gap. The provider must also coexist with the original ASI's
274 `.data` `HIGHLOW` relocations and the 139 external operands in the 12
supplemental hook bodies; see
[`asi-data-relocation-target-classification-2026-09-27.md`](asi-data-relocation-target-classification-2026-09-27.md)
and [`hook-target-relocation-risk-2026-09-27.md`](hook-target-relocation-risk-2026-09-27.md).

No candidate source or game installation file was changed by this audit.
