# Fresh full-set diagnostic link and placement check

Date: 2026-09-28. Linked the 705 objects from the fresh current-source compile
`build/recheck/strict-705-live-20260928-3/` with the existing relocatable hook
shim and x86 support objects. This is deliberately a diagnostic DLL, not an
ASI, and it was not installed or loaded.

## Ordered link result

The `/OPT:REF` + `/ORDER` response was regenerated against the current 705
objects, with new DLL and map outputs:

- DLL: `build/link-probe/strict-705-live-20260928-3/ImVehFt-current-source-optref-order-diagnostic-not-ASI.dll`
- Map: `build/link-probe/strict-705-live-20260928-3/ImVehFt-current-source-optref-order-diagnostic-not-ASI.map`
- DLL SHA-256: `63E8830BA29F824FF7C4AF655B8CFAB3FD6CFE5382AA70451BF5CE161DD53F28`
- PE32 x86, image base `0x10000000`, `SizeOfImage=0x71000`, entrypoint VA
  `0x100106F0`.

The reference ImVehFt entrypoint is `0x100111B3`; this linked entrypoint is
`0xAC3` bytes earlier. The map places `FUN_10007030` at `0x10007AA0`
(`+0xA70` from its reference VA) and `FUN_100076d0` at `0x10007F40`
(`+0x870`). These are not exact original-address placements. The matching
reference ASI has `SizeOfImage=0x43000`, so this diagnostic image is also
larger than the original image.

## Checks that pass, and checks that do not

- Fresh per-entry comparison using the current object set and the current
  ordered link map resolves all **705/705** candidate entry symbols in
  executable code, but only **3/705** body symbols are actually at their
  original VAs; **702/705** are displaced. The fit/trampoline reports are
  `audit/original-entry-slot-fit-current-source-live-20260928-3.json` and
  `build/entry-trampoline-feasibility-current-source-live-20260928-3-current-map.json`.
  The latter finds 429 selected COMDATs small enough for the bounded gap, 275
  requiring a 5-byte rel32 thunk (minimum gap 8), and zero out-of-range targets.
  This is only placement feasibility: it does not emit those 705 entry
  bridges. The gap to the next mapped function is an upper bound, not a proven
  original function extent.
- Fresh map examples: `FUN_10007030` resolves to `0x10007AA0` rather than
  `0x10007030`; `FUN_100076d0` resolves to `0x10007F40` rather than
  `0x100076D0`. The largest entry-to-body distance is the recovered
  `1001cfab` entry at `0x10037493`, a `107,747`-byte rel32 displacement.
- Static installer-target verification: **22/22 patch sites, 20/20 unique
  wrappers PASS**. It checks map symbols, PE wrapper `JMP rel32` bytes, decoded
  destinations, and displacement range; it does not execute the installer.
- Entry-trampoline feasibility on this current map: **705/705 targets
  in-range; 429 bodies fit and 275 require 5-byte rel32 thunks; minimum gap
  8 bytes; zero out-of-range displacements**. This is a feasibility result,
  not emitted/integrated original-VA placement.
- Ghidra exact-byte check of the 12 supplemental hook targets against the
  linked PE: **0/12 exact matches; 12 mismatches; 0 unmapped** at the original
  target VAs. The shims link successfully, but remain at relocated addresses
  (for example `_ImVehFtHook_10003030` is at `0x10024A58`), not at the target
  site.

## Conclusion

The full object set and shim/support objects link, and installer wrappers are
statically self-consistent. However, function entry placement, module
entrypoint, image extent, and exact hook bytes are not equivalent to the
reference. This DLL is **not loadable/test-ready** and must not be put in the
game. The original project/build recipe is still absent; the archived 2014 SDK
is available, but that alone does not provide the missing original linker,
image-layout, CRT/startup, and relocation behavior. No production ASI or
gameplay validation is established.

## Build-artifact recovery note

The first non-ordered current-source relink used a response file whose map
path still pointed into `strict-704-historical-sdk`. Before restoring that
target, the newly produced current-source DLL and the then-current map were
copied to `.pre-map-rebuild-20260928.bak` and
`.pre-current-source-link-20260928.bak`, respectively. The historical
relocatable-shim DLL at that same output path was then regenerated from its
preserved response file and original object set; its map was likewise
regenerated. The regenerated historical DLL SHA-256 is
`25CF275F2F302769548C0244100B31688B5F934C71A4095A534F5838A011EBF4`, which
differs from the previously recorded build hash
`7C80DCBF062A91D3E1C00F49D700E70F5D87300BA7ED69E52B3F09415C901978` because
the linker emits a new timestamp. The exact previous DLL bytes were not backed
up and no local copy was found in the worktree/backup search; the original
recipe and old object set remain available for another reproducible relink.
No candidate source or reference binary was changed. The current-source
ordered DLL/map are safely in the new output directory above.
