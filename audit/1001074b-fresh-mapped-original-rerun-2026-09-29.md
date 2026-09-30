# `1001074b` fresh mapped-original ABI rerun (2026-09-29)

## Evidence

- Ghidra export `ghidra_exports/1001074b.json` shows `1001074b` tail-jumping to
  `10010756`; its direct caller `10008dd0` performs `ADD ESP,4` after the call.
  The candidate and caller declarations are `__cdecl`, and the candidate
  tail-jumps to the recovered free wrapper.
- Ran `build/abi-harness/1001074b-cdecl-abi-20260929/runtime_1001074b_cdecl_abi.exe`
  in five new x86 processes against `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi`.
- Each process compared 512 calls (2,560 paired calls total) against the
  original image mapped at its preferred base. Every process reported PASS for
  freed pointer, one `_free` dispatch, callee ESP delta (-4), and final caller
  ESP delta (0).
- Original ASI SHA-256 before/after the run:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
  Harness SHA-256: `FF9C2BE2225E313C70D57D263707A660A84697D1C0CEE08569860F7031713353`.

## Limits

- The harness redirects the original `_free` tail target and candidate `_free`
  to a recorder. It validates this wrapper's pointer forwarding and caller-
  cleanup ABI, not real heap effects, allocator state, or in-game use.
- This is a focused function-level result; it does not establish readiness of
  the other 704 targets, a production ASI, or GTA runtime behavior.
