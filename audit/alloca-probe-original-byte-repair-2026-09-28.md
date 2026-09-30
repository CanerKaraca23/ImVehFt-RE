# x86 alloca-probe helpers — original-byte repairs — 2026-09-28

## Finding and repair

Ghidra's original bytes at `0x1001b220` showed the x86 stack-probe helper
touching each 4 KiB page with `test dword ptr [eax], eax` before switching the
stack pointer. The candidate implementation instead used a 1 KiB address
countdown without touching the intervening pages. That is not equivalent: a
large dynamic stack allocation could skip the Windows guard page and fault
instead of allowing stack growth.

Updated `src/functions/1001b220.cpp` to implement the original instruction
sequence. Its MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` object emits a 43-byte
`.xcode` body with zero COFF relocations. All 43 bytes match the corresponding
original `ImVehFt.asi` bytes exactly.

The related `__alloca_probe_8` at `0x1001b266` had another substantive mismatch:
the candidate returned after calculating an allocation size, while the
original aligns using the caller's actual stack address, preserves ECX, and
tail-jumps to `__alloca_probe`. Replaced its body with the Ghidra assembly flow.
The resulting 22-byte body exactly fills the 22-byte slot before `0x1001b27c`;
it has one `REL32` relocation at byte offset 18. Resolving that relocation to
the fixed helper address `0x1001b220` yields the exact original 22 bytes.

A verified pre-edit backup of `src/functions/1001b266.cpp` is preserved as
`src/functions/1001b266.cpp.pre-original-alloca-probe8-20260928.bak` (SHA-256
`7646CC010C0030E702422492890041932944156639B3C3C706893958EC1D8CE8`). The
`1001b220.cpp` source backup is also preserved alongside that source file.

The third helper, `__alloca_probe_16` at `0x1001b250`, was not changed because
its existing source already matches Ghidra's 16-byte alignment and tail-jump
flow. Its 22-byte COFF body exactly fills the slot ending at `0x1001b266`; after
resolving its single REL32 relocation to `0x1001b220`, all 22 bytes match the
original image. Thus all three stack-probe helpers in this contiguous helper
cluster now have original-byte evidence at their fixed addresses.

## Controlled x86 runtime check — 2026-09-29

Added `tests/alloca_probe_stack_growth_harness.cpp` and ran it on Windows x86
against the three strict-build COFF objects. The harness creates an isolated
thread with a 2 MiB reserved stack, exercises 19 requested allocation sizes
from 0 through `0x70000` (including values around 4 KiB page boundaries), and
checks the resulting stack delta for each of the plain, 8-byte, and 16-byte
helpers: **57 checks, 0 mismatches, no exception, thread exit 0**. Executable
SHA-256: `A7F7AE55C65EE9110C27C7465AA31EB0EA6E43F253D641973CCD76FBAC7A9E7A`.

This is controlled helper-level runtime evidence for allocation size,
alignment, and multi-page stack growth. It is not a GTA session or a complete
replacement-plugin test.

## Fresh checks

- Strict MSVC x86 compilation after both changes: **705/705 translation
  units**, 0 failures — `build/strict-xcode-alloca-probe8-fix-20260928.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN** —
  `audit/objective-independent-alloca-probe8-fix-2026-09-28.json`.
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED** —
  `build/parity-alloca-probe8-fix-20260928.json`.
- Scoped-adjudication guard: **13** explicit call-count-only checks retained;
  the `0x100076d0` callback/re-entry limitation remains explicit.
- Fresh full-set diagnostic link against the available Plugin SDK library:
  **failed**, MSBuild reports `LNK1120: 1109 unresolved externals`; no DLL or
  ASI was emitted. Probe project/log are under
  `build/link-probe-alloca-fixes-20260928/`. The unresolved set includes
  ImVehFt-addressed global/function/vtable symbols and CRT/SEH configuration
  symbols, so the 705 translation units still do not constitute a link-ready
  plugin.
- Separately refreshed the diagnostic `.xcode` placement layout using all 705
  current objects and its existing data providers (this is not a production
  plugin link). The resulting entry-slot audit reports **429** bodies fitting
  their bounded gaps and **275** requiring 5-byte rel32 entry bridges; every
  bridge has at least 8 bytes available, and all 705 diagnostic targets resolve
  to executable sections. The current relocation inventory classifies 33
  fitting bodies as relocation-free, 114 as REL32-only, 282 as DIR32/REL32, and
  275 as exceeding their entry gaps. Both alloca helpers fit: `1001b220` is
  43/48 bytes with zero object relocations; `1001b266` is 22/22 bytes with one
  REL32 that resolves to the original bytes. Reports are
  `audit/original-entry-slot-fit-alloca-probe8-fix-2026-09-28.json`,
  `audit/entry-trampoline-feasibility-alloca-probe8-fix-2026-09-28.json`, and
  `audit/inplace-candidate-relocation-coverage-alloca-probe8-fix-2026-09-28.json`.
- Original `ImVehFt.asi` SHA-256 remained
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Scope limitation

These are source-structure, compile, parity, and exact-byte checks for these two
helpers. They do **not** prove semantic equivalence of all 705 functions or
establish in-game behavior. The supplied `.ImVehFt` directory currently
contains game resources/configuration, not the original C++ project. A local
2014-04-27 plugin-sdk snapshot and a newer plugin-sdk checkout exist, but a
fresh isolated 705-object link probe against the newer SDK library failed with
1,109 unresolved externals, including missing ImVehFt data/function/vtable
definitions and CRT/SEH configuration symbols. No replacement `.asi` has been
linked; the original binary remains unchanged.
