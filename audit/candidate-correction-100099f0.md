# Candidate correction: `FUN_100099f0` frame-counter global

Date: 2026-09-24  
Reference image: `ImVehFt.asi`, SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Evidence and change

The Ghidra listing for `100099f0` loads the dword at `0x00B7CB4C` once (`0x100099f9`), compares it with state offset `+0x10` (`0x100099ff`), and on mismatch stores the same register value to that state field (`0x10009a04`). The local Plugin-SDK identifies `0xB7CB4C` as `CTimer::m_FrameCounter`, an `unsigned int&` backed by that absolute game address.

The candidate previously referenced an external signed C++ data symbol `_DAT_00b7cb4c`, which is not an exported symbol from GTA. It now reads the 32-bit unsigned value directly from the fixed game address into one local snapshot, then compares and stores that same value. This removes the fake link-time data-symbol dependency while retaining the single-load behavior visible in Ghidra. The optimized object disassembly confirms the expected `mov ecx, dword ptr [0B7CB4Ch]`, compare against `[eax+10h]`, and conditional store from `ECX`.

## Validation performed

- MSVC 2022 x86 C++20 `/O2`: full candidate set compiled and archived, **705/705**.
- Current `100099f0.cpp` compiled separately with `/O2 /W4 /WX /MT` successfully.
- ReAgent 0.4.0 targeted parity for `10003ba0`, `10003e60`, `100076d0`, and `100099f0`: **4 green / 0 yellow / 0 red**.
- ReAgent 0.4.0 objective verifier for those four current sources: **4/4 PASS**, no structural findings.
- Diagnostic full-set link against the historical SDK/static helper probe: unresolved unique externals decreased from **201 to 200**; no DLL was produced. This remains a diagnostic, non-production project.
- The 705-row source hash manifest was refreshed and checked against all source files.

## Limits

These checks establish compileability and static consistency for this correction, not full semantic equivalence. Aggregate 705/705 ReAgent counts still refer to an earlier source snapshot; only the four current corrections were rerun in targeted ReAgent checks. The full production plugin link and GTA in-game validation remain unperformed.
