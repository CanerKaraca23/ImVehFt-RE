# Fresh link of the exact-startup 705-object set (diagnostic only)

## Result

Linked the 705 current x86 candidate objects from
`build/recheck/strict-xcode-nogs-o1-ghidra-cleanup-exact-20260930/` into a
diagnostic DLL. Link completed successfully with no unresolved-symbol errors.
The linker emitted stale `/ORDER` warnings for names absent from the current
object set; this is not a warning-free production build.

Artifacts are isolated under
`build/link-probe/current-set-ghidra-cleanup-exact-aliasprobe-20260930/`:

- response: `strict-705.rsp`
- diagnostic DLL: `ImVehFt-current-set-diagnostic-not-ASI.dll`
- map: `ImVehFt-current-set-diagnostic-not-ASI.map`
- DLL SHA-256: `2D60E4F38A95EF722CBCB886A92C2B365D982929AF7FB39344210B32CC5E1FDB`
- PE has six sections; `.text` 0x2C000, `.xcode` 0x1F000, `.rdata` 0x35000,
  `.data` 0x62000, `.reloc` 0x5000; `SizeOfImage` is 0xE9000.

## Important limitation

Seven `IVF_RELOC_TARGET_*` symbols unresolved by the existing diagnostic
provider were given `/alternatename` fallbacks to `__DAT_10039a14` solely to
let the diagnostic linker produce a map. The map confirms all seven resolve
to the same dummy diagnostic address `0x100DBF84`. Those addresses are not
the original PE targets and must not be carried into a candidate or treated
as semantically valid. The response file records these explicit fallbacks.

The linker's startup symbols are placed at displaced diagnostic addresses
(`___CRT_INIT_12@12` at `0x1000DEAB`; `@___DllMainCRTStartup@12` at
`0x1001D87C`), and `SizeOfImage` is far larger than the original image. This
link is useful for fresh COFF/map analysis only; it is not an ASI and has not
been passed to GTA.

## Remaining work

The diagnostic link does not resolve the actual original-image aliases, rebuild
the candidate PE layout, or generate final COFF fixups/base relocations. The
startup-body slot overflow documented in
`startup-replacement-layout-blocker-2026-09-30.md` remains. Do not patch/install
this DLL. A production candidate still requires a fresh placement plan, exact
original-VA target resolution, complete fixup and relocation audits, and
isolated runtime/game validation.
