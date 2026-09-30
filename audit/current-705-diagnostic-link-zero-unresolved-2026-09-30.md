# Current 705-object diagnostic link — zero unresolved symbols — 2026-09-30

## Fresh inputs and link result

Used the fresh current-source MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`
object set recorded in
`build/strict-xcode-nogs-o1-10006360-fastcall-full-20260930.json` (**705/705
compiled objects**). The first replay against the saved diagnostic response
reported two candidate-to-candidate undefined symbols. Recompiling the
current `1001b3cf.cpp` and `1001c60e.cpp` independently showed the fresh COFF
symbols now agree: `@FUN_1001b3cf@12` is defined by the former and referenced
by the latter; the latter defines both the decorated method entry and its
explicit `_FUN_1001c60e` alternate-name mapping. Thus the two errors came from
the older object inputs in the saved response, not a current source-level
undefined call.

With all 705 current objects, the only remaining undefined symbol was the
forced `/INCLUDE:?round@@YAMM@Z` root inherited from the old diagnostic
response. `rg` found no current source use of `round(float)` (only preserved
pre-edit backups contain `std::round`). Removed exactly that stale forced root
from a new response and linked successfully with **zero unresolved symbols**.
The response and output are under
`build/link-probe/current-set-recheck-clean-roots-20260930/`.

Diagnostic DLL SHA-256:
`8D7182410A53702C99C5012C244219F7D78309A68077BE7EE65A8142BEADC144`;
captured map:
`build/link-probe/current-set-recheck-clean-roots-20260930/ImVehFt-current-set-diagnostic-not-ASI.map`
(SHA-256 `9AA7CB702029BB3A5EABA541EDC576B165CF460C5D491906D12940F134490E19`).
The link emitted stale `/ORDER` LNK4037 warnings; absent symbols were ignored
by the linker. This is a successful diagnostic link, not a clean production
link.

## Why this is not a production ASI

The linked PE32 DLL is based at `0x10000000`, has `SizeOfImage=0xE9000`, and
entry point `0x1000DFFE`. The pinned original ASI is based at `0x10000000`,
has `SizeOfImage=0x43000`, and entry point `0x100111B3`. Representative
candidate mappings are also displaced: `10006360` mapped at `0x10005F16`,
`10006be0` at `0x100066EE`, and `100076d0` at `0x100070DE`, rather than their
original entry VAs. The link used an old COMDAT order list, compatibility
providers/aliases, and a diagnostic DLL entry. No original PE layout was
reconstructed; no output was copied over the pinned ASI, loaded into the game,
or treated as an `.asi`.

The original ImVehFt source/project/build settings remain absent. The local
2014 Plugin-SDK snapshot is reference/build material, not evidence of the
original ImVehFt build recipe. Full relocation, thunk, hook, data, startup and
entry-layout reconciliation plus live GTA testing remain open. Whole-set
compile/objective/ReAgent green gates and a zero-unresolved diagnostic link do
not prove 705-function semantic equivalence or game readiness.
