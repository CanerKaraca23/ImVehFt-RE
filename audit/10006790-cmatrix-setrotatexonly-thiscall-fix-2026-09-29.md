# `0x10006790` CMatrix `SetRotateXOnly` call ABI correction — 2026-09-29

## Evidence and correction

The previous candidate called `0x59afa0` as `__cdecl(float)` at both state-2
and state-3 output paths. Ghidra's original assembly instead loads `ECX` from
`[EBX] + 0x10`, pushes the computed angle, and calls `0x59afa0` (`MOV ECX,[EBX]`,
`ADD ECX,0x10`, `PUSH angle`, `CALL EAX`). This proves the matrix receiver is
part of the call contract and is not an ordinary one-argument C call.

Both SDK snapshots independently identify this address and ABI:

- Historical SDK snapshot commit
  `888a67c1587ece1053a05f0cb6219a0c6c4dad0a`,
  `src/sdk/game_sa/CMatrix.cpp`: `CMatrix::SetRotateXOnly(float)` calls
  `((void (__thiscall *)(CMatrix *, float))0x59AFA0)(this, angle)`.
- Current SDK commit `b55e89b336a81448c1aa1a5b188431c9845ebaa9`,
  `plugin_sa/game_sa/CMatrix.cpp` records the same address and `__thiscall`
  signature.

The candidate now passes `unaff_EBX[0] + 0x10` as the explicit CMatrix
receiver and uses a `__thiscall` function pointer for the float angle. The
calls are written inline at both original state-machine paths; the final
object contains no added `SetRotateXOnly` helper symbol. The pre-correction
source is preserved as
`src/functions/10006790.cpp.pre-cmatrix-setrotatexonly-thiscall-20260929.bak`
(SHA-256 `F711C5AE8059A9ED1D636EC427CFAD055D9B23A29367C6F74406D57E6B7B017A`).

## Verification

- Fresh strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` compile: **705/705**;
  report `build/strict-xcode-nogs-o1-cmatrix-verified-20260929.json`.
- Fresh independent ReAgent objective check: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-cmatrix-verified-2026-09-29.json`.
- Fresh ReAgent parity check: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-cmatrix-verified-20260929.json`.
- Source hash/size manifest reread: **705 rows, zero mismatches**.
- Final `10006790.obj` disassembly has both `0x59AFA0` call sites loading
  `[EBX] + 0x10` into ECX and passing the angle on the stack. No separate
  `SetRotateXOnly` symbol remains.

## Limits

The ABI correction is supported by original Ghidra instructions and two SDK
source snapshots, with object-level confirmation. The full `0x10006790`
state-machine behavior has not yet been differentially executed against the
original ASI; its external GTA helper/API effects and actual gameplay remain
unvalidated. The aggregate ReAgent results are structural checks, not
semantic-equivalence proof.
