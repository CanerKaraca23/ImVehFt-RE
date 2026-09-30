# `10010734` `_fopen` wrapper differential (2026-09-29)

## Ghidra evidence and test method

- The exported Ghidra record at `ghidra_exports/10010734.json` identifies
  `_fopen(char*, char*)` as `__cdecl`. Its original body pushes share flag
  `0x40`, forwards mode and filename to `__fsopen` at `0x10010678`, removes
  12 callee arguments, then returns with caller-cleanup semantics.
- Current candidate source `src/functions/10010734.cpp` has C linkage for
  `_fopen` and calls the recovered `__fsopen` candidate with `0x40`. Its
  `/alternatename` directive maps the previous decorated candidate name to
  `_fopen`; the full diagnostic link map resolves both spellings to the same
  candidate address.
- Added harness `tests/runtime_10010734_fopen_wrapper_differential.cpp`.
  It maps the pinned original ASI at its preferred base, verifies the original
  call instruction and target, redirects that call and the candidate's
  `__fsopen` edge to one recorder, then compares original and current candidate
  wrapper behavior, return value, and x86 stack deltas.

## Result

- VS 2022 x86 `/O1 /W4 /WX /MT /arch:IA32` harness build and link succeeded
  against the exact `10010734.obj` from the latest 705-object strict build.
- Five separate processes each passed five argument cases (25 paired
  original/candidate wrapper calls): filename pointer, mode pointer, share
  flag `0x40`, return value, callee ESP delta `-8`, and caller-restored ESP
  delta `0` all matched.
- Original ASI SHA-256 remained
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate source SHA-256:
  `6B58A8090EA7A8C30436B3609E768794E7BD9A734FB8CF4E0D0A5ACA40D0A545`.
  Harness source SHA-256:
  `4D6FE148549CEF40947D14BA65FE597155FF063F1202F5A4C7C273A9BFE9F2A8`.
  Candidate object SHA-256:
  `310B2A211A1356CE3BDDB568AE620A85C88D1886AE21B0C26647DCB706381798`.
  Harness executable SHA-256:
  `9A53E0B14DB9AED540043EF8AE01F2952DEEFD57F8C4DD45DAA20CC03052F44F`.

## Limits

The test stubs `__fsopen`, so it proves wrapper-level argument forwarding,
return propagation, and caller-cleanup ABI only. It does not compare actual
file opens, CRT state/error handling, or filesystem side effects. It is one
function-level result and does not validate the other 704 functions, a
production PE/ASI, initialization, or GTA gameplay.
