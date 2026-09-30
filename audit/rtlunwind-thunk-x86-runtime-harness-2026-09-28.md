# Isolated x86 runtime harness: recovered RtlUnwind thunk

Date: 2026-09-28. Linked the current candidate object
`build/recheck/strict-all-live-20260928-1/1001b2b2.obj` into an x86 PE32 test
executable. Its IAT cell `_imp__RtlUnwind` was pointed to a harmless test
recorder with the same four-argument `__stdcall` ABI.

## Result

The executable invoked the actual naked candidate thunk 32 times, with four
different sentinel arguments per iteration. Each call reached the IAT test
target exactly once and forwarded all four arguments in order; repeated calls
returned to the caller without stack/return corruption. Exit code: **0**.

- Test source: `tests/runtime_rtlunwind_thunk_harness.cpp`
- PE32 x86 executable: `build/abi-harness/rtlunwind-thunk-live-20260928.exe`
- SHA-256: `7A506189F5F7963EEA199D2F853E3CB5F381001C4B753B5DB1F50B01C14D86A7`
- Toolchain: MSVC 14.44, `/O2 /W4 /WX /MT /GS`, x86.

The test matches the static evidence: Ghidra marks `0x1001b2b2` as a thunk
with one `JMP dword ptr [0x100220b8]`; the original ASI's `KERNEL32!RtlUnwind`
IAT entry is exactly `0x100220b8`; the candidate object relocates the indirect
jump through `_imp__RtlUnwind`.

## Boundary

This verifies only the thunk's indirect-dispatch ABI against a test target.
The actual Windows unwinder was deliberately not invoked, and this is not a
GTA/plugin-loader test or a substitute for the full production ASI build.
No candidate source was changed.
