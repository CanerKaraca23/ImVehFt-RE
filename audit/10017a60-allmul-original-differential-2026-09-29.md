# `10017a60` `__allmul` original-binary differential (2026-09-29)

## Target and oracle

- Ghidra export `ghidra_exports/10017a60.json` identifies the target as the
  VS2010 `__allmul` helper, `__stdcall`, with four 32-bit stack words and a
  64-bit result in `EDX:EAX`; the original returns with `RET 0x10`.
- Added
  `tests/runtime_10017a60_allmul_original_differential.cpp`. It maps the pinned
  original ASI at its preferred base and invokes both original `0x10017a60`
  and the candidate from the latest strict-build object using a raw x86 call
  harness. A separately computed 32x32-limb product supplies an independent
  truncated-64-bit arithmetic oracle.
- The test also verifies stdcall callee stack cleanup and preservation of
  `EBX`, `ESI`, and `EDI` on both implementations.

## Result

- VS 2022 x86 `/O1 /W4 /WX /MT /arch:IA32` harness built and linked against
  the exact `10017a60.obj` in the latest strict 705-object build.
- **1,001,296** cases passed: all 1,296 combinations of six edge words across
  the four limbs, plus 1,000,000 deterministic random 64-bit operand pairs.
  Original, candidate, and independent oracle agreed on `EDX:EAX`; both
  implementations returned with zero ESP delta after `RET 0x10` and preserved
  the tested nonvolatile registers.
- Original ASI SHA-256 remained
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate source SHA-256:
  `1CDEEBC82C0D15577ECFCDA70C2FA680EA589F0C73CA0444F6C2C994042DC8FB`.
  Harness source SHA-256:
  `6B6B93F30E428D5CA4FE8108F0F383B8427BAAB7E2F64A9AE30185D9C269D193`.
  Candidate object SHA-256:
  `8D48F5F77F32B6C4BC0D4282F79715FFF72C6B5907A0DAA7FD4B8426400FD7C3`.
  Harness executable SHA-256:
  `102232EBA649B8B62B08A4F9D8C667872B8C8E14AAC6ED4D9B4509F796850669`.

## Scope limit

This is focused arithmetic/ABI evidence for one helper under valid controlled
calls. It does not exercise the caller's real conversion logic, all CRT state,
the remaining 704 targets, PE startup, or GTA. No candidate source change was
needed.
