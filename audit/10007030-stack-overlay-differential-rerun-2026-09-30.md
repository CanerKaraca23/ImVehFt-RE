# `10007030` fresh stack-overlay differential rerun — 2026-09-30

Rebuilt the current candidate and `tests/runtime_10007030_stack_overlay_differential.cpp`
with MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32`, then compared against the
hash-pinned original ImVehFt ASI
(`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`).
All four directed scenarios reported `MATCH`: direct corona, alpha above
threshold, alpha below threshold, and suppressed-alpha mode. Each reported
`transform-abi=PASS`, `matrix-alias=PASS`, and `corona-path=PASS`.

The harness exercises the candidate/original stack-overlay behavior and its
controlled matrix/corona interfaces. This is a focused four-case regression
check, not broad input-space coverage and not a live GTA/RenderWare run.

Fresh output: `build/abi-harness/10007030-fresh-recheck-20260930/`.
Candidate SHA-256: `DC18EBD109BC51AB3D9BE95E294DC8186E8B472A16870D87E34CF7B700337A15`.
Harness SHA-256: `B3C2B81734C390FAD00BE69D56F4D8BD9ADBB84CCF5960424261986FFA8D9A6F`.
Executable SHA-256: `C764541423E3807F3F8C9DE0F174D2999C6FAE4875EE58402598B7528994C3EF`.

This establishes fresh targeted evidence for this candidate only. It does not
prove production ASI layout/loading, in-game effects, or the other 704
functions.
