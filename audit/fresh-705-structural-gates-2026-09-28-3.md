# Fresh 705 structural-gate rerun (2026-09-28)

Reran the three independent structural gates against the current candidate
tree. No candidate source files were edited for these runs.

## Results

- Strict MSVC x86 compile, C++20 `/O2 /W4 /WX /MT /arch:IA32`, forced `.xcode`
  section: **705/705 passed, 0 failed**.
  Report: `build/strict-xcode-current-20260928-3.json`.
- Independent local ReAgent objective verifier using Ghidra JSON exports:
  **705 PASS / 0 FAIL / 0 UNKNOWN**.
  Report: `audit/objective-independent-current-2026-09-28-3.json`.
- Local ReAgent 0.4.0 Ghidra-JSON parity: **705 GREEN / 0 YELLOW / 0 RED**.
  The separate waiver guard also passed: 13 explicit call-count-only
  adjudications, with the `0x100076d0` callback/re-entry limitation retained.
  Report: `build/parity-current-ghidra-recheck-20260928-3.json`.

SHA-256 hashes:

- Compile report: `1E80430FF6052C6C8FF7390F25FE6E0C3EDE67F43E6034DAB10AFEB630BED0BD`
- Objective report: `8707F02F31640A74CDD7EFB1E15DC9B23BC1AD730594E9B3DDC412848B64AF2B`
- Parity report: `3C5B947F86CEB4D844C7AE1AABDAFEB1FED458190C0E034A0F3C078020B118DF`

## Scope

These checks cover compilation and structural agreement against the local
decompilation/export records. They do not prove all 705 functions semantically
equivalent, validate the original startup/PE layout, create a production
`.asi`, or constitute in-game testing. The local ReAgent checkout/config is
modified; the parity check made no model/API calls. The `0x100076d0` live
callback/re-entry finding remains open.
