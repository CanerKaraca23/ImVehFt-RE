# Ghidra x87 absolute-value and rounded conversion follow-up — 2026-09-29

## Changes grounded in the pinned Ghidra export

- `src/functions/10003400.cpp` no longer calls `std::fabs`; its inline x87
  `FLD / FABS / FSTP float` sequence reproduces the original float-width
  absolute-value operation before widening and multiplying. The previous
  source is preserved as `10003400.cpp.pre-fabs-inline-asm-20260929.bak`.
- `src/functions/10005b60.cpp` no longer uses `std::round`. Ghidra shows a
  signed-byte input, x87 multiplication, a temporary rounding-control change
  to truncate, `FISTP`, and restoration of the original control word. The
  candidate now emits that sequence with inline assembly, including the
  required `FMULP st(1), st(0)`. A review of the first draft caught the missing
  `FMULP` before it was accepted; that draft is preserved in
  `10005b60.cpp.pre-x87-fmulp-correction-20260929.bak`, and the preceding
  source is preserved in `10005b60.cpp.pre-x87-roundf-reconstruction-20260929.bak`.

## Fresh checks

- MSVC 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 passed**;
  report `build/strict-xcode-nogs-o1-fabs-fmulp-final-20260929.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  report `audit/objective-independent-fabs-fmulp-final-2026-09-29.json`.
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**;
  report `build/parity-fabs-fmulp-final-20260929.json`.
- All 705 source hashes and byte counts in `audit/source-sha256.csv` match.
- Fresh COFF inspection confirms the `10003400.obj` and `10005b60.obj`
  objects have no undefined `_fabs` or `round` helper. The `10005b60.obj`
  disassembly contains `FNSTCW`, `FMULP`, `FLDCW`, `FISTP`, and restoration
  `FLDCW` in Ghidra's order.

## Limits and unresolved work

These checks establish compileability, verifier/parity status, and the stated
instruction sequence only. They do not establish full semantic equivalence,
all x87 exception/control-word cases, a production PE/ASI, loader/startup
behavior, or GTA gameplay. A fresh diagnostic link using an older response
template is not accepted as a pass: it contains stale forced roots/provider
assumptions and fails after the current symbols differ. The response/link
recipe must be regenerated from current objects before drawing a current
unresolved-symbol conclusion. Original project/source availability, full
relocation and image layout, and runtime validation remain open.

## Follow-up: `0x1001c60e` call-entry crosswalk

Ghidra's `0x1001c5f0` assembly preserves its incoming ECX, transfers the x87
argument into XMM0, and directly calls `0x1001c60e`. The candidate caller object
has the matching `_FUN_1001c60e` undefined reference, while the callee object
exports the same naked body as
`?FUN_1001c60e@ReagentMathFunction@@QAEOXZ`. Added an explicit MSVC
`/alternatename` directive in the callee translation unit to bind those two
spellings. A fresh map lists both names at the same address in the diagnostic
link, and the refreshed gates pass: strict x86 compile **705/705**, objective
**705 PASS**, ReAgent parity **705 GREEN**, and source manifest **705/705
match**. The source backup is
`src/functions/1001c60e.cpp.pre-cdecl-entry-crosswalk-20260929.bak`.

The ordinary full diagnostic link has zero unresolved externals after the
crosswalk but stops on one duplicate `__tolower` between candidate `10015237`
and `libucrt.lib(tolower_toupper.obj)`. With linker `/FORCE:MULTIPLE`, it emits
a 762,880-byte diagnostic DLL and map; the log has one LNK4006 duplicate,
22 stale COMDAT-order LNK4037 warnings, and LNK4088 explicitly warns that the
forced image may not run. The map puts both `0x1001c60e` spellings at the same
entry. This forced output is not accepted as a clean link or loadable plugin.
Its `.xcode` is at RVA `0x1000`, copied `.text` at `0x20000`, `.rdata` at
`0x32000`, and `.data` at `0x59000`; these do not preserve the original ASI's
fixed layout. No production `.asi` or GTA execution was attempted.

The response-generation script's optional candidate-root pass formerly
recognized only `.text` sections and failed on this repository's `.xcode`
objects. It now accepts both section prefixes; a backup is preserved at
`scripts/relink-current-candidate-diagnostic.ps1.pre-xcode-public-code-roots-20260929.bak`.

## Mapped-original rerun on the current entry map

Reran `tests/runtime_1001c60e_sse_rounding_differential.cpp` against the pinned
original ASI SHA-256
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3` and the
current forced diagnostic DLL SHA-256
`6AEE706F60514A25F95575726D2AC5CA7BB04C30602FB22F2FFF9F8724DCD454`.
The DLL map put the candidate function/caller at RVAs `0x18921`/`0x18909` and
data symbols at the current provider RVAs; the harness was updated to those
map addresses with its previous form backed up as
`tests/runtime_1001c60e_sse_rounding_differential.cpp.pre-current-data-map-rerun-20260929.bak`.
It first verifies 18 constant addresses and the 0x800-byte reduction table
against the original before invoking either function.

Result: **200,480/200,480 bit-exact normal-path 80-bit returns** across all
four MXCSR rounding modes, and **16,384/16,384 bit-exact exception-tail
returns** through the original Ghidra-confirmed caller, across four MXCSR
modes and four x87 control words. The initial stale-RVA attempt stopped at the
constant precheck and did not invoke the function; that was a harness-map
error, not a candidate mismatch. The corrected run passed.

Scope remains isolated: the DLL was loaded without its entrypoint, imports
were resolved by the harness, and its link required `/FORCE:MULTIPLE` for the
known UCRT/candidate duplicate. Its section layout is not the original ASI
layout. These results add direct original-binary evidence for this one math
entry and caller; they do not validate full plugin startup, all 705 functions,
or GTA gameplay.
