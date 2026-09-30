# Fresh 705-object API and base-relocation rebuild (2026-09-29)

This follow-up regenerates the API reference inventory and complete base-relocation table from the current strict 705-object directory, then feeds that fresh table into the API-thunk planner. It does not modify the pinned ASI or emit a PE/ASI.

## Fresh evidence

- `audit/candidate-original-iat-api-rel32-references-fresh-2026-09-29.json`: scanned all 705 objects in `build/recheck/strict-xcode-nogs-o1-fclose-dual-linkage-20260929`; found 196 API `REL32` references across 45 functions, covering 21 symbols, and zero non-REL32 references to the matched API symbols. Ordered object digest: `8D7DC7E4E514627B534EEFE8AAD68D0590176F0003CB04A23E5601C7ABCE9B01`.
- `audit/complete-relocs-fresh-api-baseline-2026-09-29.json`: rebuilt the HIGHLOW table from the pinned original and current 280-in-place/425-appended plan. It removes 949 original sites in modified ranges, adds 799 in-place and 1,588 appended code/data sites, for 6,119 total records / 12,824 bytes; the table fits the original `.reloc` section.
- `audit/api-thunk-payload-rel32-from-fresh-baseline-2026-09-29.json`: based on those fresh inputs, plans 21 six-byte IAT tail thunks and all 196 API-call REL32 rewrites (139 in-place bodies, 57 appended bodies). The 21 thunk operands add 21 HIGHLOW sites, yielding 6,140 records / 12,864 bytes, also within the original `.reloc` capacity. All planned REL32 displacements are in range.
- Standalone payload and relocation bytes are in `build/pe-layout-probe/api-thunk-payload-rel32-from-fresh-baseline-20260929.bin` and `build/pe-layout-probe/complete-relocs-api-thunks-from-fresh-baseline-2026-09-29.bin`; payload SHA-256 `DF81C83ED4A8CD0BE6597AD9C920CB77735AD26519E492494990F05D55D831F8`, relocation blob SHA-256 `5470C3ECAF8FAFCC179B25D9CCACB561CB5FE7D3B892EE20539A0CFBE6F753D7`.
- The pinned original `ImVehFt.asi` hash still matches `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Scope and remaining work

The regenerated reports agree on their candidate-object digest and callsite counts, and the relocation directory round-trips exactly. This validates the inventory, placement arithmetic, thunk templates, and relocation-table serialization only. The COFF code/data relocations have not all been written into final image bytes; support/runtime targets, original entry/startup/hook interactions, PE headers/directories and loader behavior remain to be integrated and checked. The emitted `.bin` files are intermediate artifacts, not an ASI. No GTA process loaded this output, so there is no game/runtime validation.
