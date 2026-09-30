# `0x10006790` registration and state-2/state-3 differential — 2026-09-29

## Result

The expanded x86 harness passed **5,764 paired original-vs-candidate cases**
against the pinned `ImVehFt.asi` (SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`):

- 5,760 state-2/state-3 cases from the arithmetic/rotation differential;
- 4 `bytes[4] == 0` registration cases spanning both query outcomes and both
  registration-flag decisions.

The registration scenarios compare query `this` and selector, API call order,
API identities, context, callback addresses, mode values, resulting state
bytes, stack balance, and EBX/ESI/EDI preservation. The API and query addresses
are replaced in both images with deterministic recorders. The callback checks
therefore prove the branch/call contract, not the behavior of the live GTA
registration APIs.

The state-2/state-3 part compares the CMatrix receiver, exact float argument
bits, complete state record, stack balance, and EBX/ESI/EDI preservation. It
uses a recorder in place of the live `CMatrix::SetRotateXOnly` method.

## Reproduction artifacts

- Harness source: `tests/runtime_10006790_cmatrix_setrotatexonly_differential.cpp`
- Build/run script: `scripts/test-10006790-cmatrix-setrotatexonly-differential.ps1`
- Object set: `build/recheck/strict-xcode-nogs-o1-10006790-float-x87-final-20260929/`
- Executable: `build/abi-harness/10006790-callback-and-state23-differential-20260929/runtime_10006790_cmatrix_setrotatexonly_differential.exe`
- Harness source SHA-256: `D8E40ECEA1E131205EFD48269BF857B2793663BD74681987926E46F48065CDB7`
- Executable SHA-256: `6D1A36DD76ABCF3AC49ABF446C0F4838DAE04398E8DB1EF052E4BAB8F13A00D8`
- Candidate source SHA-256: `840FD4C239AC6727DCC68449240979F29C5FE375E83B197DD4FC80FA5C136180`
- Candidate object SHA-256: `589F7D859548093693394A0BA3BB4588C3B9936C96665A1FB4494F2BB63C9192`

The test compiled with MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` and ran
successfully. It does not cover `bytes[4] == 2..4`, the remaining state
transitions, callers' live vehicle data, DLL initialization, live GTA API
effects, production `.asi` linking/layout, or in-game behavior. Aggregate
705/705 compile, objective, and parity results remain structural checks and do
not imply 705-function semantic/runtime equivalence.
