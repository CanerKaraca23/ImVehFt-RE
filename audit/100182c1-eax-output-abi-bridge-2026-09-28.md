# `0x100182c1` EAX output-handle ABI bridge — 2026-09-28

## Finding and correction

The Ghidra export `ghidra_exports/100182c1.json` proves a sixth, register-passed input that the prior C candidate omitted: the entry executes `MOV ESI,EAX`; invalid-argument paths store `0xffffffff` through that pointer; `__alloc_osfhnd`'s result is written through it; subsequent OS-handle operations dereference it. The caller export `ghidra_exports/100189f5.json` independently confirms `MOV EAX,ESI` immediately before `CALL 0x100182c1`, after pushing five stack arguments, followed by caller cleanup `ADD ESP,0x14`.

`src/functions/100182c1.cpp` now keeps the five-argument candidate entry as a naked x86 ABI bridge. It captures the incoming EAX value, forwards it as an explicit first parameter to `FUN_100182c1_impl`, and forwards the five original stack arguments in their original order. The implementation aliases its file-handle state to that output pointer, so error initialization, allocation, subsequent handle operations, and returned state use the caller-visible slot. A unique pre-edit backup is `src/functions/100182c1.cpp.pre-eax-output-abi-bridge-20260928.bak`.

The fresh MSVC object `build/obj/100182c1-eax-bridge-probe.obj` disassembles to `push ebp; mov ebp,esp; push eax; push [ebp+18h] ... push [ebp+08h]; call FUN_100182c1_impl; add esp,18h; ...; ret`. Thus the bridge preserves the incoming pointer before any call, passes six C parameters in the expected order, and leaves the original five arguments for the caller's observed `ADD ESP,0x14`.

## Fresh validation evidence

- MSVC x86 `/std:c++20 /O2 /W4 /WX /MT /c`: **705/705 passed**, report `build/strict-all-eax-bridge-20260928.json`.
- ReAgent independent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, report `audit/objective-eax-bridge-2026-09-28.json` (structural check only).
- ReAgent full parity using the repository's original hook CSV: **704 GREEN / 0 YELLOW / 1 RED**, report `build/parity-eax-bridge-full-20260928.json`. The sole red is the already identified hook-label mismatch `FID_conflict:__sopen_helper` versus source identifier `FID_conflict___sopen_helper` at `0x100189f5`; no candidate file is missing.
- ReAgent full parity using a separate test-only CSV/config with that label normalized: **705 GREEN / 0 YELLOW / 0 RED**, report `build/parity-eax-bridge-full-alias-normalized-20260928.json`. The repository's original hook CSV was not edited. The individual `0x100182c1` parity check is GREEN (`build/parity-100182c1-eax-bridge-20260928.json`).
- All 705 fresh objects linked successfully into `build/link-probe/strict-704-historical-sdk/ImVehFt-final-eax-bridge-diagnostic-not-ASI.dll` (724,992 bytes) with map and response file alongside it. This is a diagnostic DLL, **not** a game-loadable `.asi`.

These gates and the local ABI reconstruction are meaningful progress, but not proof of complete semantic equivalence. The original ImVehFt project/build configuration and compatible historical SDK/runtime integration remain unverified; no `.asi` has been produced or loaded, and no in-game behavior has been tested. Do not describe all 705 functions as behaviorally/runtime validated.

## Follow-up: bridge argument-order defect caught by runtime harness

The first bridge revision above did **not** actually forward EAX as the implementation's first C argument. Its assembly pushed the five original stack arguments but omitted `push eax`; the original ABI harness consequently entered the body with shifted arguments. A fresh isolated x86 harness run reproduced the fault: the `flags=1` allocation-failure case was incorrectly interpreted as invalid mode, and the output-handle canary was unchanged.

The bridge now pushes the five original stack arguments in reverse order and then pushes the captured EAX value last, making it the first argument at the implementation entry. This matches the six-parameter `_impl` declaration and the observed caller contract (five stack arguments, EAX output pointer). The source SHA-256 row in `audit/source-sha256.csv` was refreshed; the previous manifest and documentation snapshots are preserved with `.pre-eax-bridge-stack-order-fix-20260928.bak` suffixes.

Fresh evidence after that correction:

- `build/abi-harness/100182c1-eax-output-harness-fixed-20260928.exe`: **2/2 PASS**. Invalid mode returns 22, stores `0xffffffff`, sets errno 22, and calls the invalid-parameter stub once. Allocation failure returns 24, stores `0xffffffff`, sets errno 24, and does not call the invalid-parameter stub.
- Expanded harness `build/abi-harness/100182c1-eax-output-harness-four-paths-20260928.exe`: **4/4 PASS**. It checks invalid mode 3 and modes 0/1/2 reaching the stubbed OS-handle-allocation failure; expected return codes, `0xffffffff` output, errno values, and invalid-parameter-call counts match.
- Success-path harness `build/abi-harness/100182c1-eax-output-harness-real-open-20260928.exe`: **5/5 PASS**, adding a real temporary-file open through Windows `CreateFileA` and `GetFileType`. It verifies return 0, descriptor 0, the local-context flag, and a valid stored Windows handle in the reconstructed table before closing/deleting the temporary file.
- Access-mode matrix harness `build/abi-harness/100182c1-eax-output-harness-access-matrix-20260928.exe`: **7/7 PASS**. In addition to the four error-path cases, it opens real temporary files with access modes 0 (read), 1 (write), and 2 (read/write), checking return 0, descriptor/context outputs, disk handle type, and the stored OS handle.
- Open/disposition matrix harness `build/abi-harness/100182c1-eax-output-harness-open-matrix-fixed-20260928.exe`: **11/11 PASS**. It adds real Win32 `OPEN_ALWAYS`, `TRUNCATE_EXISTING`, `CREATE_ALWAYS`, and `CREATE_NEW` cases. The first exploratory run used the wrong Win32 disposition label for the candidate's `0x500` flag and failed that expectation; mapping the decompiled local values to Win32's documented constants showed the test setup was wrong, not the candidate. The corrected matrix passes.
- `build/strict-all-eax-output-fixed-20260928.json`: **705/705** MSVC x86 `/O2 /W4 /WX /MT` compile.
- `audit/objective-eax-output-fixed-2026-09-28.json`: **705 PASS / 0 FAIL / 0 UNKNOWN** (structural verifier only).
- `build/parity-eax-output-fixed-20260928.json`: **705 GREEN / 0 YELLOW / 0 RED** on the original hook configuration.
- Fresh 705-object diagnostic link from the corrected strict object set succeeds: `build/link-probe/strict-704-historical-sdk/ImVehFt-eax-output-fixed-diagnostic-not-ASI.dll` (781,824 bytes; map alongside it). It is still a diagnostic DLL, not a game-loadable `.asi`.

These are isolated ABI/error-path checks plus successful access-mode and open/create-disposition cases using real Win32 file APIs; CRT allocation/table operations are stubbed. Sharing/security/text-encoding flags, behavior under the original CRT, production image layout/startup, actual `.asi` loading, and in-game behavior remain unverified. The first-revision bridge results above are historical and superseded by this follow-up.
