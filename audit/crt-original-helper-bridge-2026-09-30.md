# CRT arithmetic fixups via original helper entries — 2026-09-30

## Evidence

The current 421-thunk relocation inventory has nine unresolved arithmetic-helper calls in two bodies: `__cftoa_l` (`0x1001bee6`: `__alldiv` ×4 and `__allrem` ×4) and `__fwrite_nolock` (`0x10014003`: `__aulldiv` ×1). Ghidra identifies the original arithmetic helpers `__alldvrm` at `0x1001dda0` and `__aulldvrm` at `0x1001a900` as Visual Studio 2010 Release library functions.

The current 705-object candidates for those two helpers are both byte-identical to the pinned original image at their original VAs, with zero COFF relocations:

- `0x1001dda0`: 223 bytes, SHA-256 `8944A6BD345F2B75CB86BD3483531448B9A5557C60A3F3EE7D025076739099B7`.
- `0x1001a900`: 149 bytes, SHA-256 `106B501E819FC91BBE63E9D1399D58966A0AD64E9DB30078334CCDF21F01FDF8`.

This allows the bridges to reuse exact original code instead of the previously extracted MSVC 14.44 helper copies. The 82-byte x86 bridge payload saves/restores EBX, duplicates the original 16-byte arguments for the stdcall helper, returns quotient in EDX:EAX, and for `__allrem` moves the original helper's remainder result from EBX:ECX into EDX:EAX. Its three internal REL32 fixups target the byte-verified helpers above.

## Validation

The bridge object was assembled with the installed x86 MASM. An isolated `/MT` x86 harness linked the bridge and the two candidate helper objects, then passed **100,209** signed quotient/remainder and unsigned quotient cases against the compiler's arithmetic operators. The test excludes division by zero and the signed `INT64_MIN / -1` overflow case. This validates the wrapper ABI/result mapping against these exact helper bodies, not a live GTA/plugin load.

The initial flat-layout REL32 plan at `0x1005B290` has been superseded and must not be used. The current provisional three-section plan is [`crt-original-helper-bridge-three-section-rel32-fixups-2026-09-30-v2.json`](crt-original-helper-bridge-three-section-rel32-fixups-2026-09-30-v2.json): it separates executable code, read-only data, and writable data, and places the bridge at provisional VA `0x1005AA20`. It covers all nine candidate caller sites and has in-range displacements. This is still only a layout calculation: the plan is **not applied**, the final PE sections/relocations/startup have not been emitted and checked, and there has been no loader or game validation. Any change to section order, RVA, or alignment requires recomputing every displacement.

Evidence: [`crt-original-helper-bridge-rel32-fixups-2026-09-30.json`](crt-original-helper-bridge-rel32-fixups-2026-09-30.json), [`1001dda0-original-body-byte-identity-2026-09-30.json`](1001dda0-original-body-byte-identity-2026-09-30.json), [`1001a900-original-body-byte-identity-2026-09-30.json`](1001a900-original-body-byte-identity-2026-09-30.json), [bridge assembly](../src/compat/crt64_original_helper_bridges.asm), and [differential harness](../tests/crt64_bridge_harness.cpp).
