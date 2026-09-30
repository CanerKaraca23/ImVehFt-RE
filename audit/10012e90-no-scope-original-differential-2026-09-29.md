# `10012e90` no-active-scope original differential

## Scope

Added `tests/runtime_10012e90_no_scope_differential.cpp` to compare the current `/O1 /GS-` candidate object with the original `__except_handler4` at `0x10012e90` from the pinned ImVehFt ASI. The original PE is mapped at its preferred base. Cases cover a valid EH4 frame with try-level `-2`, plus an active scope whose filter returns `-1` (reject) or `0` (continue to the no-scope sentinel). The test-only candidate `__security_check_cookie` records candidate checks; the original binary's own cookie checker runs against its pinned global cookie. The original calls its embedded `_EH4_CallFilterFunc`; the candidate call resolves to the statically linked VS 2022 CRT helper in the harness.

## Result

- Five fresh process runs passed all three cases.
- No-active-scope case: both returned `1`; try-level remained `-2`; candidate made one entry EH-cookie check.
- Active-scope filter `-1`: both returned `0`; try-level remained `0`; candidate made two EH-cookie checks (entry and common return).
- Active-scope filter `0`: both returned `1` after following the next-scope sentinel; try-level remained `0`; candidate made two EH-cookie checks.
- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate object SHA-256: `1F37DD6AD6447275E671EA912702374996489A1F8A92440DA79099F99A231185`.
- Harness source SHA-256: `E7DBC611B6BE59D66F152902099E780A029DB4C2045BA743978799AF93804C7A`.
- Harness executable SHA-256: `70511E87AC6A981A394C6CEA5CFED7E22607E516478A164988E802F7C488D16A`.

## Limits

This is narrow runtime evidence only. It does not test positive filter/handler transfer, C++ exception-object destruction, global/local unwind, cookie failure, OS-dispatched exceptions, or a production PE/ASI/GTA session. Candidate filter-helper behavior was exercised through the VS 2022 CRT implementation, not the candidate helper object; the original used the helper embedded in the pinned ASI. Those paths/implementation comparisons remain unverified; this result must not be generalized to full EH4 equivalence.

## Positive-transfer test investigation (not a passing result)

Ghidra shows `_EH4_TransferToHandler` (`0x10013a89`) records NLG state, clears EAX/EBX/ECX/EDX/EDI, then jumps to the handler address in ECX; the target is a compiler funclet, not an ordinary callback. A synthetic positive-filter experiment could make the original path enter a test handler, but returning through the original post-transfer block requires reproducing the funclet's register/frame continuation contract. When the candidate was linked against the VS 2022 static CRT's EH4 helpers, the positive path faulted inside that linked helper image (`0x005A61A4`); this is not evidence that the pinned candidate object fails, because the tested helper was not the candidate's VS2010-matched object. The experimental harness was removed rather than retained as a misleading test. Positive handler transfer and unwind remain open until a no-CRT harness can link the candidate EH4 helper objects with only explicit test stubs and a valid transfer funclet.

Follow-up: a no-CRT harness linked the candidate's `10012e90`, `10013a72`, and `10013a89` objects, with only global-unwind replaced by a recorder. The original filter and handler targets were reached, but execution then faulted while returning through the fabricated transfer frame. That frame did not reproduce the real compiler funclet's saved-register/stack-unwind contract; consequently the run is discarded as a differential result and does not establish a candidate defect or pass. The temporary harness source was removed. A trustworthy positive-path test needs a captured real EH4 registration/funclet frame or an assembly trampoline that preserves both images' respective continuation context without replacing the function under test.
