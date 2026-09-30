# Entry-symbol linker experiment

Date: 2026-09-28. This was a linker-only diagnostic experiment; candidate
source files and the previously successful diagnostic DLL were not changed.

## Evidence

The latest `/OPT:REF` + 746 `/INCLUDE` + COMDAT `/ORDER` response file selected
`?entry@@YGXIHH@Z`, which the successful link map places at `0x100106A0`.
The candidate startup routine's actual public COFF symbol, confirmed by the
successful link map and the object containing `src/functions/100110bd.cpp`,
is `@___DllMainCRTStartup@12`.

A separate response file was generated to try that routine directly using
`/ENTRY:@___DllMainCRTStartup@12`. MSVC LINK searched for
`_@___DllMainCRTStartup@12` and failed with LNK2001; no output DLL was
produced. The requested direct entry therefore cannot be selected this way
with this x86 decorated symbol. This was not a successful startup or PE
validation.

## PE-entry byte cross-check

A fresh read-only PE-header and entry-byte comparison was run on the preserved
original ASI and the latest current-object diagnostic DLL:

| Image | SHA-256 | Image base | Entry RVA / VA | Entry bytes |
|---|---|---|---|---|
| Original `ImVehFt.asi` | `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3` | `0x10000000` | `0x111B3` / `0x100111B3` | `8B FF 55 8B EC 83 7D 0C 01 75 05 E8 EB 5C 00 00 FF 75 08 8B 4D 10 8B 55 0C E8 EC FE FF FF 59 5D` |
| Current ordered diagnostic DLL | `3B7ED5FB6D63D93188D743C2A8267A4FEDDB1BD2D92AB880CD4661F6D3AF39CC` | `0x10000000` | `0x106A0` / `0x100106A0` | `83 7C 24 08 01 75 05 E8 D4 69 00 00 FF 74 24 04 8B 54 24 0C 8B 4C 24 10 E8 03 FF FF FF C2 0C 00` |

The original bytes corroborate the source-level `entry` wrapper: on process
attach it calls the security-cookie initializer, rearranges the three loader
arguments, and calls `___DllMainCRTStartup`; it is not itself the
`___DllMainCRTStartup` function. The current diagnostic PE also selects the
`entry` wrapper (its decoded code follows the same attach check, cookie call,
argument forwarding, and stdcall return shape), but its RVA is different.
Therefore the failed `/ENTRY:@___DllMainCRTStartup@12` experiment tested the
wrong entry routine and is not evidence that the correct wrapper cannot link.

## Conclusion

Keep the failed direct-CRT-entry response discarded; do not replace the
successful diagnostic DLL. The correct wrapper is selected in that DLL, so
the unresolved entry issue is placement, not selecting the CRT routine.
Original entry RVA is `0x111B3`; current is `0x106A0`. The DLL still has
unacceptable whole-image address/data-layout differences and is diagnostic
only, not an ASI or runtime validation. This cross-check does not close the
production link or game-validation gates.
