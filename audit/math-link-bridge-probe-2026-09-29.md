# Math helper link-bridge probe — 2026-09-29

## Result

A disposable diagnostic link of the current 705 candidate object files succeeded after adding two linker-only `/alternatename` bridges. The response file and outputs are isolated under `build/link-probe/entry-exact-nogs-o1-math-diff-probe-20260929/`.

- Exit code: 0
- Output: `ImVehFt-math-link-bridge-probe-not-ASI.dll` (x86 PE DLL, 752,128 bytes)
- SHA-256: `89C1EF2A3C7DCD3DDA5998303BE579A3F6AD0DAFA65083815FD2CC954677816D`
- The map confirms `_FUN_1001c60e` was redirected to `?FUN_1001c60e@ReagentMathFunction@@QAEOXZ` and `?FUN_1001b3cf@ReagentMathError@@QAEOXZ` to `@FUN_1001b3cf@12`.

## Interpretation and limits

This establishes only that the current objects can be linked when those missing names are bridged. The aliases exist only in this probe response; no source-level alias or candidate source edit was made for either symbol. The output is explicitly **not an ASI** and is not evidence that either bridge has the correct calling convention, stack/register state, floating-point behavior, or semantics. No runtime differential test was run, so do not load this DLL into GTA or treat it as a validated build.

Ghidra evidence in `ghidra_exports/1001c60e.json` shows the normal calculation path and a tail jump at `0x1001c7b2` to `0x1001b3cf`; `1001c5f0` is a wrapper that calls `0x1001c60e`. The bridge therefore allows further investigation but does not resolve the remaining ABI/runtime validation requirement.

The original project source and historically matching plugin-sdk are still unavailable in this workspace, so project-native build validation and in-game validation remain open.
