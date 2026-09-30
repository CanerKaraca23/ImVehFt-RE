# Current 705-object clean-signature diagnostic link — 2026-09-29

## Inputs and reproducibility

The current `source-sha256.csv` was checked against the working tree: 705 rows,
zero missing files, zero hash mismatches. The fresh MSVC x86 `/O1 /W4 /WX /MT
/arch:IA32 /GS-` report is
`build/strict-xcode-nogs-o1-100110bd-root-impl-20260929.json` (705 passed,
zero failed); its 705-object directory is
`build/recheck/strict-xcode-nogs-o1-100110bd-root-impl-20260929`.

The initial fresh link attempt exposed stale `/INCLUDE` roots for four symbols
whose COFF names had changed with current candidate signatures. The response
preparation script attempted to remove old directives by concatenating the
platform newline; the checked-in response uses LF, so those directives
survived. Before modifying the script, a byte-identical backup was made at
`scripts/prepare-volatilemetadata-off-link.ps1.pre-line-ending-fix-20260929.bak`
(SHA-256 `F309928D04A2BDA2AE47E9A7B78FBEE210D563594C180BE1A733CB70D914756B`).
The script now removes each complete line with a CRLF/LF-tolerant regex and
asserts that the stale directive is absent. The corrected response
`build/recheck/entry-xcode-nogs-o1-current-clean-signature-r5-20260929.rsp`
contains none of the four stale roots.

Address-bearing unresolved names from the preceding fresh link log were
compared with the pinned original PE and mapped to exact `.data`/`.rdata`
locations in `current-clean-link-address-aliases-2026-09-29.csv` (82 aliases:
70 `.data`, 12 `.rdata`). This is address/byte evidence only, not proof of each
symbol's C++ type, extent, or relocation semantics. The diagnostic link also
uses the existing CRT alias probe, the exact CRT alias-only provider, the
Ghidra-backed callback-vtable provider, and this exact-address provider.

## Result

The link completed with exit code 0, zero `LNK2005`, zero `LNK2019`, zero
`LNK2001`, and no `LNK1120`. It emitted an 890,880-byte diagnostic DLL:
`build/link-probe/entry-exact-nogs-o1-current-clean-signature-r5-with-aliases-20260929/ImVehFt-entry-xcode-current-clean-signature-diagnostic-not-ASI.dll`
(SHA-256
`125C4218B05861D4EF00F918076FB1B6CD6494C5D7D4E7DCE45A800D3716FA7C`).
The response SHA-256 is
`B9DFBD4ED20AB5F5C766E6E2F151AEE4B36FA71A1502BA42D739C91C2123FC40`; the
successful linker log SHA-256 is
`9BF21F3E9BDD30CE75E9DEAD1E499CB144BD9248EB028B99227655A0653729A9`.

## Why this is not a production ASI

Fresh `dumpbin /headers` inspection confirms the layout blocker. The original
ASI places `.rdata` at RVA `0x22000` and `.data` at `0x29000`. This diagnostic
places candidate `.xcode` at RVA `0x22000`, moves `.rdata` to `0x55000`, and
`.data` to `0x79000`; fixed original-image addresses therefore do not refer to
the intended sections in this output. Link success is not image-layout,
relocation, startup, loader, or gameplay validation. The file is explicitly
not installable, and no GTA process was running during this check.

The original project/solution is still absent from the repo, and
`C:\Users\caner\Downloads\SA Plugin SDK` remains absent; the available
`_sdk_history/snapshot-2014-04-27` is an SDK snapshot, not the original
ImVehFt project. No candidate function source or installed binary was changed.
