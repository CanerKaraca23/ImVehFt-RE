# 705-object clean `RtlUnwind` link probe (2026-09-28)

> Superseded as the latest link result by
> [`relocation-provider-alias-recheck-2026-09-28.md`](relocation-provider-alias-recheck-2026-09-28.md): the later run changed only the recovered thunk's local symbol, rebuilt all 705 candidate objects, and linked all 705 actual objects. This document records the earlier test-only replacement probe.

## Finding

The previous full-object diagnostic link failed because candidate `1001b2b2`
defined the same decorated `_RtlUnwind@16` symbol as the KERNEL32 import
library, while its IAT reference was spelled `__imp__RtlUnwind` instead of
the import library's `__imp__RtlUnwind@16`. A `/FORCE` experiment produced an
image with duplicate-symbol warnings and was not accepted.

A test-only compile variant now demonstrates a clean alternative without
changing `src/functions/1001b2b2.cpp`: it retains the recovered one-instruction
thunk under the private symbol `_ImVehFt_Recovered_RtlUnwind@16`, and a linker
alternate-name directive maps its IAT reference to KERNEL32's canonical
`RtlUnwind` import slot. The normal linker completed with exit code 0 and no
warnings. The response file includes the other 704 freshly compiled candidate
objects plus this replacement object for the 705th candidate module position.

## Evidence

- Test source/object: `build/link-probe/strict-704-historical-sdk/1001b2b2-linkprobe.cpp/.obj`.
- Response file: `build/link-probe/strict-704-historical-sdk/strict-705-link-rtl-alias-test-20260928.rsp`.
- Output: `build/link-probe/strict-704-historical-sdk/ImVehFt-705-rtl-alias-test-not-ASI.dll` and `.map`.
- `dumpbin /disasm` confirms the recovered private thunk is exactly `FF 25 00 00 00 00` (`jmp dword ptr [__imp__RtlUnwind]`).
- The map places `_ImVehFt_Recovered_RtlUnwind@16` from the test object and resolves `_RtlUnwind@16` plus both decorated/undecorated IAT aliases to KERNEL32.
- `dumpbin /imports` confirms `KERNEL32.dll` imports `RtlUnwind` by name.
- The output is an x86 diagnostic DLL, not an `.asi` or game-testable artifact. It still uses diagnostic providers and does not solve original-image PE relocations, production CRT/startup/loader/hook layout, or runtime behavior. Do not load or rename it.

## Interpretation

This removes the *symbol-collision* obstacle to linking all 705 candidate
module positions in this diagnostic configuration. It does not establish that
the test-only alias strategy belongs in the eventual production build, nor
does it establish source/runtime equivalence. Keep the recovered candidate
source unchanged until its final import/thunk ownership is validated against
the original build configuration.

## Relink after the `100076d0` correction

The probe was repeated against `build/recheck/strict-all-post-conditional-slot-20260928/`.
Response file:
`build/link-probe/strict-704-historical-sdk/strict-705-link-stack-fix-rtl-alias-20260928.rsp`;
it contains 704 freshly compiled objects plus the test-only
`1001b2b2-linkprobe.obj`. Normal `link.exe` returned 0 with no warnings and
emitted `ImVehFt-705-stack-fix-rtl-alias-test-not-ASI.dll` (781,312 bytes) and
its 1,280,021-byte map. `dumpbin /imports` confirms `KERNEL32.dll!RtlUnwind`.
This validates the corrected objects in the same diagnostic harness only;
production-image and game/runtime limitations remain.
