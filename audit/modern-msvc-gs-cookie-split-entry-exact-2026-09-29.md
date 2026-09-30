# MSVC `/GS` cookie split in the entry-exact candidate build (2026-09-29)

## Finding

The current 705-object strict build uses MSVC 14.44 x86 with `/O2 /W4 /WX /MT /arch:IA32`; it does not pass `/GS-`, so stack-cookie instrumentation is enabled. The reconstructed legacy `___security_init_cookie` updates only the original-image globals `DAT_10029490` and `DAT_10029494`. In contrast, MSVC-instrumented candidate objects reference the separate CRT symbol `___security_cookie` and call the candidate's `@__security_check_cookie@4`.

This is a concrete ABI/runtime risk: the custom checker compares its argument to `DAT_10029490`, while compiler-generated prologues load `___security_cookie`. If startup randomizes the original cookie without also synchronizing the compiler cookie, an instrumented function can fail its check even with an intact stack. This finding is based on object and link evidence; an executing production image has not been built, so it is not yet a demonstrated game crash.

## Evidence

- `build/strict-xcode-entry-exact-20260929.json`: MSVC 14.44 x86, flags `/O2 /W4 /WX /MT /arch:IA32`; 705/705 translation units compile. No `/GS-` flag is present.
- `build/recheck/strict-xcode-entry-exact-20260929/10001040.obj`, `dumpbin /disasm`: prologue reads `[___security_cookie]`, XORs it with ESP, saves it, and epilogue passes the value to `@__security_check_cookie@4`.
- Same object, `dumpbin /symbols`: both `___security_cookie` and `@__security_check_cookie@4` are undefined external references.
- The COFF relocation crosswalk in `audit/candidate-relocation-symbol-targets-entry-exact-v2-2026-09-29.json` contains 50 DIR32 relocations to `___security_cookie` and 93 REL32 relocations to `@__security_check_cookie@4` across the 705 candidates. These are relocation-reference counts, not unique-function counts.
- Diagnostic link map `build/link-probe/entry-exact-diagnostic-20260929/ImVehFt-entry-xcode-layout-alloca-probe8-fix-diagnostic-not-ASI.map`: `___security_cookie` and its complement resolve to CRT `gs_cookie.obj` at `0x1008b5c0` and `0x1008b600`; `@__security_check_cookie@4` resolves to candidate `100172d5.obj` at `0x10038820`; `___security_init_cookie` resolves to candidate `10016eae.obj` at `0x100380e0`.
- `src/functions/10016eae.cpp` writes `DAT_10029490` and `DAT_10029494`, but does not write or alias `___security_cookie` or its complement.
- `src/functions/100172d5.cpp` compares its argument only to `DAT_10029490`.
- Exact reconstructed entry object `100111b3.obj` calls the candidate `___security_init_cookie` on process attach, then calls `@___DllMainCRTStartup@12`.
- Hash-pinned original `ImVehFt.asi` (`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`): initial bytes at `DAT_10029490` are `4e e6 40 bb` (`0xBB40E64E`), and at `DAT_10029494` are `b1 19 bf 44` (the complement).
- Original function at `0x10001040` begins `push ebp; mov ebp,esp; sub esp,0x17c`; disassembly of its bounded span to `0x10001350` found no absolute references to either cookie global and no call to `0x100172d5`. The new `/GS` object did add both a `___security_cookie` load and a check-helper call at this entry.

## Isolated runtime reproduction

Built and ran `build/runtime-check/gs-cookie-split-20260929/gs-cookie-split-nocrt.exe` as x86 with `/NODEFAULTLIB` and a direct entry point, so CRT startup cannot contaminate the observation. It links the actual candidate sources `10016eae.cpp` and `100172d5.cpp` and a separately compiled `/GS` probe whose disassembly explicitly loads `___security_cookie` and calls `@__security_check_cookie@4`.

- Actual legacy initializer path: the checker reported `CANDIDATE_GS_CHECK_FAILED`; process exit code 86.
- Positive control, where only the harness synchronizes `DAT_10029490` to the compiler cookie after the actual candidate initializer: `CANDIDATE_GS_CHECK_PASSED`; exit code 0.
- Harness SHA256: `375ED3CE153D5DFE68CF27CE058E3B73A9965E5158053B7E02903529F2DA6002`.
- Guarded COFF object SHA256: `6C96134543AB08F8C727F9E2892BDDF133A9C8A7E55757778F3AD591E01E78AF`.

This proves the candidate initializer and checker are incompatible with an independently-valued MSVC compiler cookie under the reproduced path. It does not by itself prove the exact cookie values or all loader/startup sequencing in a production ASI; the positive control deliberately synchronizes values and is diagnostic only.

## Full-set `/GS-` compile experiment

To test fidelity implications without replacing the existing strict-build evidence, compiled all 705 candidate sources into a separate object directory with MSVC 14.44 x86, `/O2 /W4 /WX /MT /arch:IA32 /GS-` and the same forced `.xcode` section header. The first 705/705 result predates the `1001b71d` source correction and is historical only. A fresh post-correction run is currently writing `build/recheck/strict-xcode-nogs-ehcookie-20260929`; its result is not claimed until the command completes.

The pre-correction COFF audit found 4,742 relocations total, including explicit source-level security-check calls and an explicit `___security_cookie` reference in `1001b71d`. The original-binary comparison below showed that reference came from an incorrect source reconstruction, not generated stack protection.

## Binary-backed correction to `1001b71d`

The original ASI disassembly for `0x1001b71d` disproved that C++ reconstruction's cookie source: it loads `[param_2+8]`, XORs with `param_2`, and checks that value before forwarding fields to `___InternalCxxFrameHandler`. The C++ candidate instead formed a guard using the separate CRT `__security_cookie` and a local stack address. The source was backed up as `src/functions/1001b71d.cpp.pre-exact-x86-eh-cookie-20260929.bak` and replaced with the bounded original x86 instruction sequence.

Focused proof: the new candidate COFF `.xcode` body is exactly `0x33` bytes, matching original `0x1001b71d..0x1001b74f`. Every non-relocation byte matches the original ASI; the two `REL32` fields resolve in the original to `0x100172d5` (the candidate checker) and `0x1001d923` (`___InternalCxxFrameHandler`). The candidate COFF carries those same two symbols as relocations. Thus the instruction/body match is exact modulo the two intended relocatable call fields. Ghidra's `ghidra_exports/1001b71d.json` agrees on the per-instruction sequence, function signature, and callee addresses; its decompiler comment confirms the inserted security-check call is a Ghidra injection rather than visible C pseudocode.

After this correction, the full no-GS compile completed **705/705** in `build/strict-xcode-nogs-ehcookie-20260929.json`. Fresh relocation inventory: **4,741** total COFF relocations; **34** explicit calls to the reconstructed checker across 17 functions; **zero** compiler-cookie global references in the 705 candidate objects. The default-GS strict build was also rerun on the corrected source set and completed **705/705** in `build/strict-xcode-entry-exact-ehcookie-20260929.json`.

Current-source automated checks completed after the edit: independent objective verifier **705 PASS / 0 FAIL / 0 UNKNOWN** (`audit/objective-independent-after-eh-cookie-2026-09-29.json`) and ReAgent 0.4.0 parity **705 GREEN / 0 YELLOW / 0 RED** (`build/parity-after-eh-cookie-2026-09-29.json`). These are still structural checks; notably, ReAgent's GREEN result does not expose the incorrect original cookie source that the instruction-level Ghidra/byte comparison found.

## Status and safe next gate

One candidate source, `1001b71d.cpp`, was changed with a preserved backup based on Ghidra and direct original-ASI bytes. The published compiler configuration, linker alias, original ASI, and diagnostic DLL were not changed. Both default-GS and no-GS full-set compiles, the objective verifier, and ReAgent parity were rerun after the edit. Source manifests were refreshed with preserved `.pre-exact-x86-eh-cookie-20260929.bak` copies; all 705 source SHA256 entries match.

Before attempting a production PE/ASI, audit original-image equivalents for the remaining explicit checker callers and verify exact loader/startup ordering and cookie values. Compare the 705-object no-GS set against those original bodies. Only then select a fidelity-preserving build strategy (including whether `/GS-` plus an explicit CRT-cookie-to-original-global mapping is supported by binary evidence). The new `1001b71d` body is byte-matched modulo its two relocation fields; the no-GS compile alone does not resolve the overall cookie/runtime question.
