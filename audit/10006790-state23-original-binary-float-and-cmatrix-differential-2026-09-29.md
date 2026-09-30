# `0x10006790` state-2/state-3 original-binary differential — 2026-09-29

## Ghidra findings and candidate corrections

The original Ghidra listing shows `0x10006790` reads a floating-point scalar
from `[EBX+8]`, computes elapsed deltas with signed x87 `FILD dword` semantics,
and sends a float angle to `0x59AFA0` with `ECX = [EBX] + 0x10`. The earlier
candidate had three fidelity defects in the state-2/state-3 path:

1. It converted `unaff_EBX[2]` numerically from `uint32_t` instead of loading
   the float stored at byte offset `+8`.
2. It widened wrapped elapsed deltas as unsigned integers, while the original
   x87 `FILD dword` sign-extends the 32-bit value.
3. It rounded the integer elapsed value to `float` before division and did not
   model the original intermediate float store/reload before multiplying the
   binary64 scale constant.

The previous one-argument `__cdecl` call at `0x59AFA0` was also corrected to
`CMatrix::SetRotateXOnly`'s `__thiscall(CMatrix*, float)` contract, with the
receiver address derived exactly as Ghidra does. The receiver/signature is
independently confirmed by historical Plugin-SDK commit
`888a67c1587ece1053a05f0cb6219a0c6c4dad0a` and current SDK commit
`b55e89b336a81448c1aa1a5b188431c9845ebaa9`. The pre-float-load source is
preserved at
`src/functions/10006790.cpp.pre-ebx8-float-load-correction-20260929.bak`
(SHA-256 `6F8B28D7B1D86939C05FB4887CAF8921BE41D82CD9706A4BA3AEF45D350938AD`).
Further pre-edit snapshots cover the later signed-delta and x87 staging fixes.

## Mapped original-vs-candidate test

`tests/runtime_10006790_cmatrix_setrotatexonly_differential.cpp` maps the
pinned original ASI at its preferred image base without imports or startup,
then invokes original and candidate x86 code on paired, sentinel-filled state
records. It compares states 2 and 3 across 6 timer values, 6 prior-time
values, 8 elapsed edge values, 9 float edge values, plus an exact timer-delta
case per combination: **5,760 paired cases total**. The `0x59AFA0` call is
redirected in both images to a recorder that preserves the thiscall stack
contract. The original absolute timer load is redirected to a test cell.
Assertions cover the matrix receiver, exact float angle bits, complete record
bytes/state updates, ESP balance, and EBX/ESI/EDI preservation.

Result: **5,760/5,760 passed** against the pinned ASI SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
The harness was built against the final 705-object set. Harness source SHA-256:
`44475A4E7BCE11FD688D3AAC3C7C91F1ECE2FB1927987E4D1D268FE6159BCAB5`.
Executable SHA-256:
`D738A10A6F52905D132B6612F881C4A51ECF1613AA61BEE9B562F172FC20A8EF`.
Artifacts: `build/abi-harness/10006790-cmatrix-setrotatexonly-state23-full705-20260929/`.

## Whole-set checks on the corrected source set

- MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 compiled**;
  `build/strict-xcode-nogs-o1-10006790-float-x87-final-20260929.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-10006790-float-x87-final-2026-09-29.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-10006790-float-x87-final-20260929.json`.
- Source SHA/size manifest: **705 rows, zero mismatches**.

## Remaining scope boundary

The differential test covers only the state-2/state-3 arithmetic/rotation
path, with the GTA matrix function replaced by a deterministic recorder. It
does not validate the other `0x10006790` states/callback registrations, its
callers' real vehicle/object data, live GTA API effects, initialization,
production image layout, or in-game behavior. The 705 aggregate gates remain
structural checks, not 705-function runtime equivalence. No production `.asi`
or GTA gameplay test was produced here.
