# `0x10024ed0` double-width and corona rounding correction

Date: 2026-09-28. Target binary: `ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Binary and Ghidra evidence

The PE image base is `0x10000000`. At RVA `0x24ed0`, the original `.rdata`
bytes are `00 00 00 00 00 00 d0 3f`, which decode as little-endian IEEE-754
binary64 `0.25`. The next four bytes at `0x10024ed8` are `cd cc 4c 3e`
(`0.2f`). The width is therefore eight bytes, not four.

The exact-binary Ghidra exports for `10006be0` and `10007030` use
`FLD double ptr [0x10024ed0]` / `FMUL double ptr [0x10024ed0]`. In
`10006be0`, the surrounding instructions also load the low byte of stack
argument 6 for the first scaled dimension and argument 5 for the second;
the conversion sets x87 rounding-control bits `0xc00` (truncate) before
`FISTP` and restores the saved control word afterward.

## Candidate correction

Both candidate TUs now declare `_DAT_10024ed0` as `double`. `10007030`'s
existing x87 instructions now encode qword loads/multiplies, matching the
Ghidra operand width. `10006be0` now computes its two scaled dimensions with
the Ghidra-indicated argument bytes, qword constant, x87 multiplication, and
temporary truncate rounding mode. It restores the previous control word and
cleans its temporary x87 stack value after each isolated conversion.

Exact pre-edit files are preserved as:

- `src/functions/10006be0.cpp.pre-ed0-double-width-fix-20260928.bak`
- `src/functions/10007030.cpp.pre-ed0-double-width-fix-20260928.bak`

The fresh MSVC x86 objects emit `FLD qword ptr` at the symbol relocation for
`10024ed0`, and `10006be0` emits `FILD` from its two corrected argument-byte
locals followed by x87 multiply, truncate-mode `FISTP`, control-word restore,
and temporary stack cleanup.

## Validation and limits

- Strict MSVC x86 `/O2 /W4 /WX /MT`: **705/705**, report
  `build/strict-all-ed0-double-width-20260928.json`.
- Independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**, report
  `audit/objective-ed0-double-width-2026-09-28.json`.
- Full ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**, report
  `build/parity-ed0-double-width-20260928.json`.
- The relocation-aware provider copy
  `build/recheck/reloc-aware-dat-provider-ed0-double-aliases-20260928.asm`
  now publishes both the existing float-decorated label and the corrected
  double-decorated label at the same `.const` offset. `dumpbin /symbols` shows
  both at section offset `0x2ed0`; the fresh 705-object map resolves both to
  `0x10089d90`. The 705-object diagnostic link emitted a 781,824-byte DLL at
  `build/link-probe/strict-704-historical-sdk/ImVehFt-ed0-double-width-diagnostic-not-ASI.dll`
  **without a linker alias for this symbol**. The response still contains
  unrelated, previously required CRT/name aliases. This fixes the symbol in
  this relocation-aware diagnostic provider, not in an unavailable original
  production project.
- Both 705-row source manifests were refreshed and backed up.
- The regenerated global-address inventory now records `0x10024ed0` as an
  8-byte `double` referenced from `10006be0` and `10007030`:
  `audit/candidate-global-address-inventory-post-ed0-2026-09-28.csv`.

These gates and the emitted-object inspection validate the corrected operand
width and selected instruction semantics; they do not establish full
equivalence of either function, all floating-point environment effects, a
production ASI build, callback behavior, or in-game behavior. No game test was
run.
