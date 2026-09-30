# Binary64 constant-width candidate corrections

Date: 2026-09-28. Target binary: `ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Finding and changes

A cross-check of exact-binary Ghidra assembly operands against original PE
`.rdata` bytes and emitted candidate objects found several sites where Ghidra
uses an x87 `double ptr` constant but the candidate declared/read the same
address as `float`. At addresses such as `0x10024fd8`, the low four bytes are
zero while the full eight bytes encode `16.0`; treating that location as a
float silently changes the calculation. The review also excluded apparent
matches where candidate inline assembly already issued a qword operation.

Corrected candidate translation units: `10003400`, `10003660`, `10004bb0`,
`10005b60`, `10005d30`, `10005ef0`, `10006360`, `10006790`, `10006a50`,
`10006be0`, and `10007030`. Explicit casts now mark binary32 stores/call
arguments where the Ghidra sequence performs binary64 arithmetic before
rounding to a float. The source backups use suffix
`.pre-double-constant-width-batch-20260928.bak`.

The full source inventory is recorded in
`candidate-global-address-inventory-double-width-2026-09-28.csv`.
Both 705-row source manifests were refreshed with the same backup suffix.

## Validation evidence

- Targeted MSVC x86 `/O2 /W4 /WX /MT` compile: all 11 corrected TUs passed.
- Full strict compile: **705/705**, report
  `../build/strict-all-double-constant-width-20260928.json`.
- Independent objective scanner: **705 PASS / 0 FAIL / 0 UNKNOWN**, report
  `objective-double-constant-width-2026-09-28.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**, report
  `../build/parity-double-constant-width-20260928.json`.
- The relocation-aware diagnostic data provider now exports the needed float
  and double COFF labels at identical byte locations. A fresh 705-object
  diagnostic link succeeded to
  `../build/link-probe/strict-704-historical-sdk/ImVehFt-double-constant-width-diagnostic-not-ASI.dll`.

These are compile, structural/objective, parity, and diagnostic-link checks.
The objective/parity labels are not proof that a reconstructed function is
semantically equivalent. The linked artifact is a diagnostic DLL, **not a
loadable `.asi`**. There is still no original build project and matching
historical SDK/library set in this checkout, and no game/runtime validation
was performed. Function-level behavior and floating-point edge cases remain
to be reviewed against the original code paths.
