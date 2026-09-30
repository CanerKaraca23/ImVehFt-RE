# Current diagnostic PE relocation-coverage cross-check

Date: 2026-09-28. Reran `audit-diagnostic-reloc-move-coverage.py` on the
freshly linked 705-object diagnostic PE:
`build/link-probe/original-entry-xcode-layout-current-20260928-4/ImVehFt-entry-xcode-layout-diagnostic-not-ASI.dll`.

Fresh report:
`audit/diagnostic-relocation-move-coverage-current-2026-09-28-4.json`,
SHA-256 `424A686935FD615336AFD2951AE5DAB37C09ACB7E3B33B50E3610D9E183A72B4`.

## Cross-check against the prior context classification

Compared with `audit/diagnostic-relocation-move-coverage-2026-09-28.json`,
the section table and all relocation/target fields are byte-for-byte equal at
the JSON-structure level: relocation type/site/target counts, image-base
sentinels, all 6,570 raw DWORD target hits, and the full 182-entry uncovered
hit list. The fresh and prior link maps also have 5,325 parsed symbol-address
lines each, with **zero differences**. Thus the earlier address- and
symbol-context review in `audit/diagnostic-relocation-hit-context-2026-09-28.md`
applies to this freshly compiled/linked diagnostic artifact as well; the 182
uncovered byte-window matches are not a new unresolved pointer class.

The report still counts 6,391 HIGHLOW relocations, of which 6,388 coincide
with raw target hits into proposed moved-section ranges; three image-base
values are sentinels. The independent source PE's **3,160 `.text`
HIGHLOW relocation sites remain a separate unresolved integration problem**:
this cross-check does not synthesize a combined production image, relocate
every candidate-to-original reference, validate CRT/import startup, or run GTA.
No PE or candidate source was modified, and the diagnostic DLL remains not
loadable as an ASI.
