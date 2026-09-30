# Diagnostic PE relocation coverage for appended-section move

Date: 2026-09-28

Input: `build/link-probe/original-entry-xcode-layout-20260929/ImVehFt-entry-xcode-layout-diagnostic-not-ASI.dll`.
This is an inventory only; no image bytes were changed.

## Results

- PE32 x86, image base `0x10000000`; base-relocation directory RVA `0x8F000`,
  size `0x3494`.
- The relocation directory contains 6,391 non-padding entries, all type 3
  (`IMAGE_REL_BASED_HIGHLOW`). Sites are in candidate/support `.xcode`,
  `.text`, `.rdata`, or `.data`: respectively 2,859, 1,108, 2,104, and 320.
- Stored values at those sites target candidate/support `.data` (2,672),
  `.rdata` (3,028), `.xcode` (304), `.text` (377), `.fptable` (7), or the
  image base itself (3). The three image-base values are sentinels, not section
  pointers, and must not receive the proposed section-move delta.
- A byte-by-byte overlapping DWORD scan of raw bytes in the sections proposed
  to move found 6,570 candidate values pointing inside those old section
  ranges. Of those, 6,388 coincide with HIGHLOW fixup sites; 182 do not:
  `.xcode` 21, support `.text` 10, `.rdata` 4, and `.data` 147.

The 182 are raw byte-pattern matches, not 182 confirmed broken pointers.
Follow-up classification in
`audit/diagnostic-relocation-hit-context-2026-09-28.md` found 14 executable
operands that intentionally target original `.rdata`/`.data` addresses, 97
diagnostic alias-probe hits, 44 exception-probe vtable entries (rebase only
if that probe is retained), six exact copies of original `.data` bytes, and
17 executable-section byte matches that did not decode as four-byte absolute
operands. A follow-up disassembled the three runtime sites from their
link-map function starts and identified short conditional branches; none of
the 17 is a four-byte absolute operand. The context report supersedes the
preliminary raw-scan interpretation below.

## Consequence for the proposed image move

The relocation table is useful but not sufficient by itself to safely shift
all diagnostic sections by `0x21000`. Before making a combined PE, the
remaining unclassified code hits need classification against linker symbols,
COFF relocations, disassembly, and original Ghidra cross-reference evidence.
Confirmed absolute pointers into moved sections must be adjusted; fixed-image
references into preserved sections and non-pointer numeric data must not be
adjusted. HIGHLOW fixup *site RVAs*
also move, while their stored targets only get the delta when the target is in
a moved section. The final PE must merge/rebuild the relocation directory and
update its data-directory RVA/size.

Reproduction:

```powershell
py .\scripts\audit-diagnostic-reloc-move-coverage.py `
  .\build\link-probe\original-entry-xcode-layout-20260929\ImVehFt-entry-xcode-layout-diagnostic-not-ASI.dll `
  --output .\audit\diagnostic-relocation-move-coverage-2026-09-28.json
```

The JSON retains every uncovered candidate location and value. This audit
does not validate imports, CRT/static initialization, ASI loader behavior,
original Ghidra semantics, or GTA runtime behavior.
