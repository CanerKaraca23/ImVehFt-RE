# `0x100069e0` caller → `0x10006790` ABI differential — 2026-09-29

## Ghidra evidence and correction

Ghidra's original `0x100069e0` assembly computes the per-vehicle slot address
in `EBX` (`LEA EBX,[EDX + EDI + 0x4A0]`), pushes the incoming `param_1`, calls
`0x10006790`, then removes that one stack argument. The previous candidate
instead passed the pool pointer (`iVar3`) and never set `EBX` to the callback
record. `0x10006790` consumes both of these implicit inputs, so the prior C++
call could not reproduce the original caller/callee contract.

The candidate now derives the exact record pointer, sets `EBX` around the
callback, and passes the original vehicle argument. The prior source is saved
at `src/functions/100069e0.cpp.pre-100069e0-caller-contract-20260929.bak`
(SHA-256 `B33CF856998EC260A1ED260C2CAE7C914A380A4ED76961A9FFD1C4434007EDC1`).
The corrected optimized COFF listing uses `[EBP+8]` for the pushed vehicle
argument, loads the computed `[EBP-4]` callback-record address into `EBX`, and
restores its saved `EBX` after the call.

## Mapped caller differential

The existing mapped-ASI harness now additionally invokes original and candidate
`0x100069e0` with a controlled pool-manager fixture. It runs three vehicle
indices (0, 1, and 17), each with three distinct pool entries/record blocks.
For this caller-only subtest, the `FUN_10009360` manager lookup is redirected to
the same controlled fixture, and the `0x10006790` entry is redirected to an ABI
recorder. Assertions compare all nine callback EBX record addresses, all nine
vehicle arguments, ESP balance, and caller-preserved EBX/ESI/EDI against the
mapped original. Result: **3/3 caller cases passed (9/9 callback visits)**.

Together with the same harness's other mapped tests this run reports **5,779
paired cases**: 5,760 state-2/state-3 arithmetic/rotation cases, 4 direct
registration cases, 12 state-2..4 wrapper integration cases, and 3 caller
cases. The caller fixture proves slot selection and ABI inputs under controlled
memory; it does not execute the callback body during that caller-only portion.

Artifacts:

- Harness: `tests/runtime_10006790_cmatrix_setrotatexonly_differential.cpp`
- Runner: `scripts/test-10006790-cmatrix-setrotatexonly-differential.ps1`
- Object set: `build/recheck/strict-xcode-nogs-o1-100069e0-caller-contract-final-20260929/`
- Run: `build/abi-harness/100069e0-caller-contract-recheck-20260929/`
- Harness SHA-256: `EFF5CCDCA74F43534EE1F1FB85C833652FADB5B921F2C489B913BA0ED47A81DB`
- Executable SHA-256: `1AF3420370BA4311497BB9C228FB371349513AA1C96522FC6334D89DB09C957F`
- `100069e0.cpp` SHA-256: `CDCFF2D5EA2EB05149B81AEF6334E62B9B93CD983D08EE40DAF9206E9DCA29EE`
- `100069e0.obj` SHA-256: `A6C0AAEE688126C7B0870CD54FCE5B2ACA4D54FC9CE29DBC73353E0C5FB30EFF`

After this candidate source correction, full strict compile passed **705/705**,
independent objective verification passed **705/705**, and ReAgent parity was
**705 GREEN / 0 YELLOW / 0 RED**. Source manifests were refreshed and checked.
These aggregate gates do not imply semantic equivalence across 705 functions.
GTA startup, live API side effects, production `.asi` layout/linking, and
in-game behavior remain unverified.
