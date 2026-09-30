# `__setmbcp_nolock` CP-to-LCID input correction — 2026-09-28

## Finding

The Ghidra export `ghidra_exports/10014566.json` shows that `__setmbcp_nolock` calls `FUN_100144ea` at `0x10014581`, then saves that call's EAX result in EDI at `0x10014586`. The two calls to `CPtoLCID` are preceded by `MOV EAX,EDI` at `0x100146a9` and `MOV EAX,[EBX+0x4]` at `0x1001470a`. The decompiler labels the first value `unaff_EDI`; the second is the system code page stored at context `+4`. In both branches, the locale ID must be derived from the resolved system code page, not the original request argument.

The candidate already computes that resolved value as `system_code_page`, but both calls in `src/functions/10014566.cpp` incorrectly passed the original `param_1`. Both now pass `system_code_page`. A pre-edit snapshot is `src/functions/10014566.cpp.pre-cptolcid-system-cp-fix-20260928.bak`.

This is a source-level call normalization: the recovered binary's private helper call supplies the value through EAX, while the rebuilt candidate-to-candidate C call uses a stack argument. The corrected value is the same Ghidra-proven system-code-page value in either ABI.

The same caller's `setSBCS` edge was also checked: Ghidra loads the context pointer from EBX into EAX before its private call, while the candidate passes the same `param_2` context through its normalized C call. Its sole recovered caller is `10014566`, so the candidate's source-level argument is already semantically aligned; no gratuitous EAX-only wrapper was added.

## Validation

- Fresh object disassembly `build/abi-harness/10014566-cptolcid-system-cp-fixed.obj` shows the two `_CPtoLCID` calls receive EDI and the saved resolved system-code-page local respectively; the relocation table resolves both to `_CPtoLCID`.
- Runtime harness `build/abi-harness/10014566-cptolcid-system-cp-lcid-and-sbcs-matrix.exe`: **5/5 PASS**. Four cases deliberately separate requested pages from resolved pages; 932/936/949/950 produce LCIDs 0x411/0x804/0x412/0x404. A fifth case drives the zero-system-page `setSBCS` fallback and checks the context fields and 0x201-byte table region. Actual candidate `__setmbcp_nolock`, `CPtoLCID`, and `setSBCS` translation units execute; `getSystemCP`, `setSBUpLow`, backing tables, and stack-cookie validation are test stubs.
- Fresh VS2022 x86 `/O2 /W4 /WX /MT` strict compile: **705/705**, `build/strict-all-cptolcid-system-cp-20260928.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, `audit/objective-cptolcid-system-cp-2026-09-28.json` (structural evidence, not behavioral equivalence).
- ReAgent parity on the original 705-hook config: **705 GREEN / 0 YELLOW / 0 RED**, `build/parity-cptolcid-system-cp-20260928.json`.
- Fresh 705-object diagnostic link succeeds: `build/link-probe/strict-704-historical-sdk/ImVehFt-cptolcid-system-cp-fixed-diagnostic-not-ASI.dll` (781,824 bytes).
- `audit/source-sha256.csv` and `audit/function-name-map.csv` were refreshed with recoverable pre-edit backups.

No dedicated runtime test of `__setmbcp_nolock` has yet been run against the original CRT. The linked artifact is still a diagnostic DLL, not a game-loadable `.asi`; project/startup and in-game validation remain open.
