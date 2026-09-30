# Current thunk address-encoded target validation — 2026-09-30

Ran `scripts/audit-address-encoded-coff-targets-in-original-pe.py` against the
fresh 2026-09-30 current 422-thunk link-map resolution report and the pinned
original ImVehFt ASI (SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`).

- All 441 unique address-encoded symbols / 952 relocation occurrences map to
  an original PE section; none are unmapped.
- The targets comprise 325 `.data` raw-backed references, 538 `.data`
  virtual-only (zero-fill) references, and 89 `.rdata` raw-backed references.
- The current machine-readable result is
  `audit/appended-thunk-address-encoded-original-pe-current-2026-09-30.json`.

This validates that the encoded preferred-base VAs fall in mapped sections; it
does not establish target type, initialization/lifetime, or semantic correctness.
The `.data` virtual-only targets have no bytes in the original file and need
correct zero-fill and startup behavior in any rebuilt PE. No thunk bytes have
been patched, and no production PE/ASI or game runtime has been validated.
This accounts for the address-encoded subset of the 1,504 fixup occurrences.
Separately, a current name-and-DLL crosswalk identifies original IAT targets for
116 occurrences, and `audit/current-api-call-rel32-patch-plan-2026-09-30.md`
plans the 57 API callsites within the 422 appended bodies (139 additional
in-place callsites are also planned). Thus 1,125 of the 1,504 appended-body
external fixup occurrences have a target class/address or generated-thunk
target plan. The current callback-label preservation audit resolves another 95
code aliases to original addresses without overlay collisions. The fresh
provider alias and code-target crosswalks then account for the data aliases,
candidate entries, external GTA text, and callback dispatchers. Overall,
1,495/1,504 appended-body external fixups now have an original preferred-base
target address or generated-call-thunk plan; the remaining nine are three
static-CRT arithmetic helpers. None of these 1,504 fixups has yet been applied
to a reconstructed image. See
`audit/current-appended-thunk-target-resolution-2026-09-30.md` for the exact
accounting and limits.
