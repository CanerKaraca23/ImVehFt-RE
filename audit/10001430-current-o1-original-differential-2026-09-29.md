# Current `10001430` O1 object differential — 2026-09-29

## Result

The current `/O1 /GS-` candidate object was compared with the hash-pinned
original `ImVehFt.asi` in a PE32/x86 harness. Ten fresh processes passed, with
64 paired calls per process (640 pairs total) and zero observed mismatches.
The harness compared allocator call count and requested size, returned buffer
identity relative to each implementation's fixture, and all five output
DWORDs for varied explicit parameters and hidden ESI context.

## Ghidra evidence

The target is `ghidra_exports/10001430.json` (name-map entry also checked).
Its observed success path requests 0x14 bytes through the call at VA
`0x10001438` to `0x10010893`, then writes `param_1`, `param_2`, and three DWORDs
from incoming ESI context to the allocated record, and returns with `ret 8`.
The candidate object's disassembly was checked for ESI preservation across the
allocator call and the five stores.

## Reproducibility and integrity

- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate source SHA-256: `74FCE4098D8DEBE541250C63897615A58070E14E453DE7868D54E24C7EED4213`
- Candidate object: `build/recheck/strict-xcode-nogs-o1-exception-fix-20260929/10001430.obj`
- Candidate object SHA-256: `0CFCE5E82851550017AC6C2047E42390A69791BF1CB3558ED7E6C74799C48001`
- Harness source SHA-256: `BA2C6B2ED18D5491E7A513A172FE296A83ACAF4F6FF2858EB012E48107F5AF4D`
- Harness executable SHA-256: `CBCFBA03DDEC23B1EF43DB2953D9E78CAE53D45939DDED75734DEBE8BE5069DE`
- Runner: `scripts/test-10001430-original-binary-differential.ps1`

The source hash agrees with the source manifest. The original ASI was not
modified; the harness maps it in memory and patches only the verified call to
a deterministic allocator stub.

## Remaining boundary

This is focused success-path differential evidence, not a full-function or
production-image proof. The allocator is stubbed; allocation failure and the
bad-allocation construction/throw path were not exercised. Production PE/ASI
relocation and section layout, interactions with real callers/allocator, and
live GTA behavior remain unverified. Full-set compile/objective/parity results
remain structural gates and do not substitute for semantic proof.
