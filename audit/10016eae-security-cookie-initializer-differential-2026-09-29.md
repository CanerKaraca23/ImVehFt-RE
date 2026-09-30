# `0x10016eae` security-cookie initializer differential — 2026-09-29

## Result

The fresh `/O1 /GS-` candidate object for `___security_init_cookie` matches the pinned original function's observable cookie/complement state and Win32 API call trace in **10 fresh x86 processes × 7 deterministic input cases** (70 pairs, no mismatches).

The harness maps the original ASI at its preferred image base and redirects the five original IAT entries identified in `ghidra_exports/10016eae.json` to deterministic Win32-compatible stubs. It also patches the executable's own import address table so the candidate object calls those same stubs. Candidate `DAT_10029490` / `DAT_10029494` references resolve to test variables; original references use the mapped image globals. Each pair resets both initial states and API outputs before invocation.

Cases cover the default cookie, zero and low-word-only invalid seeds, the generated default-cookie collision (must become `0xBB40E64F`), the low-word expansion path, and two valid preexisting cookies. The harness compares resulting cookie, complement, and API order (`GetSystemTimeAsFileTime`, process ID, thread ID, tick count, performance counter); valid-cookie paths are expected not to call the APIs.

## Reproduction and pinned inputs

- Harness: `tests/runtime_10016eae_cookie_initializer_differential.cpp`.
- Runner: `scripts/test-10016eae-cookie-initializer-original-differential.ps1`.
- Candidate object: `build/recheck/strict-fputs-asm-rerun-20260929/10016eae.obj`, SHA-256 `C0862815D15CF521EB97C390527A76BE35550EC8CCA376DCD4956D548DCF26DC`.
- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Harness executable SHA-256: `FD866D41CF46820BC5D6D12E3901986C64A25A617F6335AD7181E935CE8A023F`.
- Command result: 10/10 processes passed, 7 cases each.

## Limits

This closes the earlier isolated candidate-vs-MSVC-cookie mismatch for the tested original-image cookie algorithm when using the `/O1 /GS-` candidate object. It does **not** prove the real loader's IAT state, concurrent initialization behavior, actual timing/API values beyond the deterministic matrix, all explicit `__security_check_cookie` call sites, default-`/GS` compatibility, production PE layout, or GTA startup/game behavior. The default-`/GS` split documented in `audit/modern-msvc-gs-cookie-split-entry-exact-2026-09-29.md` remains a real build-profile incompatibility; `/O1 /GS-` is not thereby certified as the final product build.
