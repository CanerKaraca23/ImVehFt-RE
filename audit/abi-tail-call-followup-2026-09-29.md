# ABI/tail-call follow-up — 2026-09-29

## `10011872`: decoded handler must receive the original argument frame

Ghidra's original entry at `0x10011872` saves EBP only while decoding the
global pointer; for a non-null decoded target it restores EBP and executes
`JMP EAX`. Thus the target sees the original return address and five original
stack arguments. The old candidate made an ordinary zero-argument indirect
call and then returned, shifting the target's stack view. It has been replaced
with a naked x86 bridge: push the encoded global, call `DecodePointer`, jump to
the decoded target without changing the original caller frame, and tail-jump
to `__invoke_watson` on the null path.

Backup: `src/functions/10011872.cpp.pre-tail-jump-abi-audit-20260929.bak`.

The strict object sequence is `PUSH [DAT_10039a04]; CALL DecodePointer; TEST
EAX,EAX; JZ; JMP EAX; JMP __invoke_watson`. The mapped-original harness
`tests/runtime_10011872_tailjump_abi.cpp` redirects only `DecodePointer` and
the decoded handler to test functions. With the pinned original ASI hash
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`, five
fresh x86 processes x 512 non-null-target cases (2,560 pairs) matched all five
handler arguments, target return value, and ESP delta. The null/Watson path,
real DecodePointer cookie behavior, and live handler effects remain untested.

Harness SHA-256:
`84DBFFBA62A2325BA3746CC169D001969C28632C5A7B0CA44D99AABC08F6FAD7`.
Final tested executable SHA-256:
`A9A034DC4629EE4F9488742A9442E195F1F8771B31591B5FA40A4ED80D436181`.

## `1001074b`: original wrapper uses caller cleanup

Ghidra's `10008dd0` caller executes `CALL 0x1001074b; ADD ESP,4`. The old
candidate declared `1001074b` as `__stdcall`, which would move cleanup to the
callee. The wrapper instead tail-jumps to `10010756`, which tail-jumps to
`_free`; these are caller-cleanup semantics. Both `1001074b` and its caller
declaration in `10008dd0` are now `__cdecl`. In the fresh MSVC object,
`1001074b` is a five-byte tail `JMP` to `10010756`; its candidate caller keeps
the `ADD ESP,4` after its call, matching the original call boundary.

Backups:

- `src/functions/1001074b.cpp.pre-cdecl-cleanup-20260929.bak`
- `src/functions/10008dd0.cpp.pre-cdecl-cleanup-20260929.bak`

The mapped-original harness `tests/runtime_1001074b_cdecl_abi.cpp` redirects
the original free tail target and candidate `_free` call to a recorder. Five
fresh x86 processes x 512 cases (2,560 pairs) matched the freed pointer, the
callee's uncleaned four-byte stack argument, and the caller's final ESP. Real
heap behavior is not exercised. Harness SHA-256:
`DE058517BAEBD013A7255578875C633491627DD97D3153BAD7A4412A2EA4AE09`;
tested executable SHA-256:
`FF9C2BE2225E313C70D57D263707A660A84697D1C0CEE08569860F7031713353`.

## `1001156b`: preserve the return path after `RaiseException`

Ghidra's body calls the `RaiseException` IAT target and then executes
`LEAVE; RET 8`. The candidate had marked both `RaiseException` and
`__CxxThrowException_8` as `noreturn`, which caused MSVC to emit `INT 3` after
the call instead of the observed epilogue. The implementation TU now leaves
`RaiseException` and its own body return-capable; separate throw call sites
retain their `noreturn` declarations. The current COFF emits `LEAVE; RET 8`.

Backup: `src/functions/1001156b.cpp.pre-raiseexception-return-abi-20260929.bak`.

`tests/runtime_1001156b_raiseexception_abi.cpp` maps the pinned original ASI
and redirects original/candidate `RaiseException` calls to a recorder that
returns. Five fresh x86 processes x 512 cases (2,560 pairs) matched the
exception tuple, payload words, and `RET 8` stack cleanup. This deliberately
tests the previously missing returning path; actual SEH dispatch and C++
unwinding remain untested. Harness SHA-256:
`8A0E4202E90E92C86BE0F83C50C7AF8765A5BBA6D4FE6FC0F505BEF69661723A`;
tested executable SHA-256:
`88FBE315A6258C7269B8A0091E4EDB65CA2979206D648F026FAE2640463B7AD3`.

## Fresh full-set checks after both corrections

- MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705**, report
  `build/strict-xcode-nogs-o1-1156b-raiseexception-20260929.json`.
- ReAgent objective: **704 PASS / 1 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-1156b-raiseexception-20260929.json`.
- ReAgent parity: **704 GREEN / 0 YELLOW / 1 RED**;
  `build/parity-1156b-raiseexception-20260929.json`.
- Both structural failures point only to `100110bd`'s entry/implementation
  split. The separate controlled original-binary startup differential passes
  its recorded cases, but the red is retained.
- Source manifests were refreshed with backups using suffix
  `.pre-1001156b-raiseexception-return-20260929.bak`.

These focused tests and structural checks do not establish complete
705-function equivalence, production PE/ASI readiness, or in-game behavior.
