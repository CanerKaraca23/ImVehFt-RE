# Current 705 placement: callback-helper overlay and relocation audit

Date: 2026-09-29. This supplements
`current-original-va-placement-audit-2026-09-29.md` with the relocatable
callback helpers and supersedes the older generic relocation-directory
snapshot for the current placement counts.

## Callback helpers

`scripts/audit-candidate-helper-overlay-collisions.py` checks the 280 direct
bodies and 425 five-byte entry thunks against 100 support spans derived from
the callback JMP map, callback-entry verifier, and relocatable dispatcher
provider:

- 70 five-byte `JMP rel32` entries;
- 25 seven-byte `PUSH ECX; CALL rel32; RET` entries;
- five 75-byte dynamically installed plugin callback dispatchers.

The 900 helper bytes have no overlap with one another or any modified span in
the 705-entry placement plan. The five dispatcher bodies each have a COFF
`DIR32` at body offset `+3` to `IVF_RELOC_TARGET_1003C3CC`; that field coincides
with the original `.text` HIGHLOW site at VA `+3`. All five original relocation
sites remain in the regenerated final table. The other 95 helper spans do not
intersect original `.text` HIGHLOW fields.

Machine-readable result:
`candidate-helper-overlay-collisions-conservative-705-2026-09-29-v2.json`.

## Fresh relocation-directory reconciliation

The prior `all-705-candidate-code-relocation-directory-conservative-2026-09-29.json`
was generated from an intermediate **283 direct / 422 appended** placement
and is not the current inventory. The current 280/425 plan was serialized
again to `all-705-candidate-code-relocation-directory-conservative-280-425-2026-09-29.json`
and its matching `.bin` blob. Fresh counts: 4,681 original HIGHLOW sites;
949 removed from changed candidate/body-thunk ranges; 799 in-place DIR32s;
1,588 appended-code/local-rdata DIR32s; 6,119 final sites; exact encode/parse
round-trip; 12,824 bytes, fitting the original relocation section. The five
dispatcher operand sites listed above are present in that parsed final blob.

## Limits

These are interval, COFF-site, and relocation-table checks, not a patched PE.
They do not apply final relocation values, install hook patches, establish
every callback's runtime behavior, resolve every CRT/code target, or validate
imports/startup/loader behavior. No production ASI was emitted or loaded and
no GTA gameplay test was run.
