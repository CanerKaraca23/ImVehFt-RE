# `10006be0` / GTA `RegisterCorona` cross-check

Date: 2026-09-27. This cross-check uses the installed game executable, not a
symbol database. Ghidra 12.1.3 headless imported
`C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe` as PE x86 and
analyzed it in a temporary project. Executable SHA-256:
`F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`.

## Evidence

- `audit/gta-sa-006fc580-decompile-20260927.txt` records the target at
  `0x006FC580`: it reads the corona-type byte from `[ESP+0x28]`, replaces that
  stack slot with the corresponding pointer from `0x00C3E000 + type*4`, then
  tail-jumps to `0x006FC180`. This confirms why the SDK has both texture and
  corona-type overloads at the same address.
- `audit/gta-sa-006fc180-decompile-20260927.txt` records the common target.
  Its seventh stack parameter is a `float*`. With a null attached entity, it
  reads all three components directly. With an entity, it passes the same
  pointer and the entity matrix to `FUN_0059C890`, then reads the resulting
  coordinates. It later copies the three input components into the corona
  record as well. Therefore the position reference is consumed on both paths;
  it is not an ignored placeholder for attached coronas.
- In ImVehFt's `10006be0` listing, the callback argument pointer is
  `[EBP-0x38]`. The earlier claim that this region has no initialization was
  incorrect: the `param_9 == 0` path copies 16 dwords from object `+0x10` to
  `[EBP-0x68]`, and the position pointer is offset `+0x30` into that copy.
  Thus its three floats come from source dwords 12-14. The alternate path calls
  `0x7F18B0` with destination `[EBP-0x68]`, left operand `object + 0x10`, and
  right operand `*(uint32_t*)(object + 4) + 0x10`. The 2014 SDK snapshot names
  `0x7F18B0` as `RwMatrixMultiply(result, left, right)`; the GTA executable's
  fresh Ghidra listing/decompile at that address independently confirms the
  three-pointer matrix operation. This is a parent-matrix composition, not a
  variable-length copy. The same SDK lays out `RwFrame` with `parent` at `+4`,
  its `modelling` matrix at `+0x10`, and `ltm` at `+0x50`.
  Those offsets explain both branches: copy the modelling matrix for an
  unattached frame, or multiply it by the parent frame's modelling matrix when
  attached. The position pointer targets the resulting matrix's `pos` at
  offset `+0x30`. `FUN_1001ba40` receives `[EBP-0x3C]` in `ECX`, but its own
  listing does not read or write through `ECX`.
  The callback's object type is corroborated by its caller: `10004430`
  registers itself with GTA helper `0x7F0DC0`. Fresh Ghidra analysis shows that
  helper walks from `[arg+0x98]` and advances through each entry's
  `[entry+0x9C]`; these match `RwFrame::child` and `RwFrame::next` in the 2014
  SDK. Thus the callback's first argument is a child `RwFrame*`, not an
  arbitrary byte buffer.
- The previous candidate compiled the 16-dword buffer at `[EBP-0x6C]`, shifting
  the position vector by one dword relative to the target. The source frame
  offsets have now been corrected: a fresh optimized object copies the buffer
  at `[EBP-0x68]`, uses `[EBP-0x78]` for the transform output, `[EBP-0x14]`
  and `[EBP-0x10]` for the target's additional vector/float locals, and passes
  `[EBP-0x38]` as the callback position pointer. These addresses now match the
  Ghidra listing.

## Consequence and limits

The position vector is consumed and correctly sourced from `RwMatrix::pos` in
both branches. The previous apparent uninitialized-vector bug was an audit
mistake caused by overlooking the overlap between the bulk-copy range and the
vector local. A second candidate defect was found: it treated the
`RwMatrixMultiply` call as a three-argument `memcpy` and used the parent pointer
as a byte count. The candidate now passes the parent modelling-matrix address
as the right operand. Its fresh optimized MSVC object shows the target call
setup exactly: `ECX = object + 0x10`, third argument `*(object + 4) + 0x10`,
destination `[EBP-0x68]`, then call `0x7F18B0`. The strict compile passes all
705 units; the independent objective run is 705 PASS, and the full ReAgent
parity run is 704 GREEN / 1 YELLOW (the existing `100076d0` warning). The
function is still not fully semantically or dynamically verified: remaining
work includes complete branch-by-branch stack/x87 comparison and in-game
validation. The latest reproducible reports after the final frame-layout
change are `build/strict-rwframe-layout-20260927.json`,
`audit/objective-independent-rwframe-layout-2026-09-27.json`, and
`build/parity-rwframe-layout-705-20260927.json`.

Ghidra emitted unrelated auto-analysis/decompiler warnings elsewhere in the
game executable; the target listings discussed above were successfully
created and decompiled. This static result does not prove behavior in a live
game process.
