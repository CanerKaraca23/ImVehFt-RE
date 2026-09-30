# Referenced `DAT_*` storage class recheck

Date: 2026-09-27. This audit maps every `DAT_*` address in the current 705-
object COFF inventory to the original ImVehFt PE section's file-backed or
zero-filled virtual extent. It distinguishes missing COFF definitions from
missing initial bytes; they are not the same problem.

## Result

The input image is the original `ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`, image
base `0x10000000`. The current source address inventory was independently
regenerated as `candidate-global-address-inventory-recheck-2026-09-27.csv`;
all **418/418** COFF-referenced addresses occur in the current candidate
source inventory.

| Storage class | Count | Notes |
| --- | ---: | --- |
| `.rdata`, file-backed | 100 | Initial bytes come from the original PE's raw section data. |
| `.data`, file-backed | 166 | Initial bytes come from the original PE's raw section data. |
| `.data`, virtual zero-fill | 152 | Addresses are beyond `.data`'s raw size and inside its virtual size; PE loading initializes this tail to zero. |
| Outside mapped sections | 0 | Every referenced address maps to a PE section. |

The original `.data` begins at VA `0x10029000`, has raw size `0x10A00` and
virtual size `0x1455C`. Its file-backed part ends at VA `0x10039A00`; the
zero-filled virtual tail runs through `0x1003D55C`. For example,
`DAT_1003c420` is in that zero-filled tail. A fresh Ghidra 12.1.3 import of
the exact-hash ASI independently read `00 00 00 00` at `0x1003c420` and
`0x1003c25c`, matching the PE-loader semantics. Do not treat file offset
`0x3AC20` as the contents of `0x1003c420`: that offset is outside the raw
`.data` extent and belongs to later file data.

## Reproduction

```powershell
py -3.13 scripts/audit-candidate-global-symbols.py `
  --source-root src/functions `
  --output audit/candidate-global-address-inventory-recheck-2026-09-27.csv

py -3.13 scripts/audit-coff-dat-pe-storage.py `
  C:/Users/caner/OneDrive/Documents/ImVehFt/ImVehFt.asi `
  audit/coff-dat-symbol-inventory-verified-2026-09-27.csv `
  --csv audit/coff-dat-pe-storage-recheck-2026-09-27.csv
```

The raw/zero-fill classifications are in
[`coff-dat-pe-storage-recheck-2026-09-27.csv`](coff-dat-pe-storage-recheck-2026-09-27.csv).
Ghidra byte probe:
[`asi-global-data-byte-probe-2026-09-27.csv`](asi-global-data-byte-probe-2026-09-27.csv).

## Link implication and limits

This removes a false assumption that every referenced global needs a
file-backed initializer: 152 addresses have well-defined PE zero-fill
initialization. It gives a stronger input for a future address-coherent data
provider, but **does not** create or validate such a provider. The other 266
referenced addresses need exact original bytes and relocation-aware mapping;
the 418 locations still have unresolved COFF symbol names, including
same-address aliases and differing source-level types. The separate 274
`.data` `HIGHLOW` relocation sites and 139 absolute operands in hook bodies
remain a whole-image relocation problem. No candidate source or game install
file was changed, and no candidate DLL/ASI was linked or loaded.
