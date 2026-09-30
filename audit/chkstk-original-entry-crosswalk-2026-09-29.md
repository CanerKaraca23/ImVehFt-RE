# `__chkstk` candidate crosswalk — 2026-09-29

## Finding

The appended-candidate diagnostic link reports one `__chkstk` static-CRT
reference. The original image already contains a candidate at VA `0x1001B220`,
Ghidra-named `__alloca_probe`. Its export labels it as the Visual Studio 2010
`__chkstk` library implementation; its callers include `__alloca_probe_16`,
`__alloca_probe_8`, and `__write_nolock`.

The canonical strict object `build/recheck/strict-xcode-nogs-o1-fclose-dual-linkage-20260929/1001b220.obj`
defines `___alloca_probe@0`. Its `.xcode` body is 43 bytes, has zero COFF
relocations, and matches the original ASI `.text` bytes at `0x1001B220`
exactly. Both SHA-256 values are
`F8675B4976F7B8EFC0BD917AEBAB734D11CA90222D20BCD2A166CE9914ED2B6E`.
The original ASI remains pinned at
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Linker experiment and consequence

A temporary `/alternatename:__chkstk=___alloca_probe@0` directive was tested
in a separately compiled object. MSVC accepted the directive, but the full
diagnostic link still selected `libcmt:chkstk.obj` for `__chkstk`; the map
shows the candidate and CRT helper at distinct diagnostic addresses. The
temporary directive was removed and the canonical source restored byte-for-
byte to its pre-test SHA-256. The map snapshot from the experiment is
`build/link-probe/chkstk-alias-full-20260929/observed-current-link-map.map`.

Therefore this is **not** evidence that the diagnostic link has removed the
CRT dependency. It is evidence that final-image relocation can route that
generated helper reference to the existing original entry at `0x1001B220`
without adding helper code, provided the final image builder explicitly maps
the COFF external to that original VA. This routing still needs to be
implemented and validated in the final-image integration; no production ASI
or runtime test was performed.
