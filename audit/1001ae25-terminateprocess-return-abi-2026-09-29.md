# `___report_gsfailure` TerminateProcess return path — 2026-09-29

Ghidra's original body at `0x1001ae25` reaches `LEAVE; RET` after the
`GetCurrentProcess` / `TerminateProcess` import calls. The previous candidate
marked the routine `noreturn` and followed `TerminateProcess` with
`__assume(0)`, so MSVC emitted `INT 3` instead of the observed return path.
The implementation declaration is now return-capable and the false
`__assume(0)` is removed. Other translation units that call the fail-fast
routine retain their separate `noreturn` declarations, so their call-site
optimization contracts are unchanged.

Backup: `src/functions/1001ae25.cpp.pre-terminateprocess-return-abi-20260929.bak`.

The latest strict x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` object ends in
`LEAVE; RET`, matching the original function's return behavior. Full strict
build: **705/705** at
`build/strict-xcode-nogs-o1-1ae25-return-20260929.json`. Fresh objective and
ReAgent structural results remain **704 PASS / 1 FAIL** and **704 GREEN / 1
RED**, with only `100110bd` red. There is no dedicated original-binary runtime
differential for this large crash-report routine; its external APIs and
`FUN_100172cd` have not been behaviorally exercised here.
