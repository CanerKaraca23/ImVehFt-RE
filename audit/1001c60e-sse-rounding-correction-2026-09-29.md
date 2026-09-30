# `0x1001c60e` floating-point parity investigation — 2026-09-29

## Current candidate and history

The initial C++ arithmetic candidate compiled to x87 operations rather than preserving the original's SSE2 binary64 rounding points. Two intermediate explicit-intrinsic/vector rewrites were also tried; both failed mapped-original differential checks and are preserved only as `.bak` files. Neither is accepted as verified.

The current `src/functions/1001c60e.cpp` is a naked x86 assembly transcription of the Ghidra export at `C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\1001c60e.json`. Mnemonic/order review finds the same 95 instructions; the source uses local branch labels and symbolic relocations where Ghidra prints fixed addresses. Original and candidate mapped-image bytes also match for the checked polynomial constants, vector constants, reduction-table region, and `0x25880`/`0x25888` values. The prior sources are preserved in `src/functions/1001c60e.cpp.pre-sse-rounded-20260929.bak`, `.pre-sse-vector-20260929.bak`, and `.pre-sse-exact-asm-20260929.bak`.

## Fresh structural checks

- Strict x86 MSVC `/O1 /W4 /WX /MT /arch:IA32 /GS-` build: **705/705**, `build/strict-xcode-nogs-o1-math-exact-asm2-20260929.json`.
- Independent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, `audit/objective-math-exact-asm-2026-09-29.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**, `build/parity-math-exact-asm-2026-09-29.json`.

These are build/structural gates, not proof of runtime equivalence.

## Mapped-original differential result — partial PASS; exception tail unresolved

Ran `tests/runtime_1001c60e_sse_rounding_differential.cpp` against the original `ImVehFt.asi` (SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`) and the freshly linked diagnostic DLL `build/link-probe/entry-exact-nogs-o1-math-exact-asm2-20260929/ImVehFt-math-link-bridge-current-probe-not-ASI.dll`.

The first harness version failed on input `1.0` because it inherited the process MXCSR rounding mode. This function uses `CVTSD2SI`, whose rounding follows MXCSR; the test therefore did not provide a controlled, equal floating-point environment. Normalizing only MXCSR removed the mismatch; resetting x87 or the XMM registers was unnecessary. The harness now tests all four MXCSR rounding modes independently.

Result after controlling MXCSR: **200,480/200,480 bit-exact 80-bit returns matched** across directed sign/mantissa/exponent cases and 50,000 deterministic random cases per rounding mode. Directed cases include exponent-underflow scale-by-constant and return-input branches in addition to the finite reduction path. The original and candidate are separately mapped images; their checked polynomial/vector constants and reduction-table bytes were equal. This does not cover NaN/infinity, every exception state, or the exception tail.

## Exception-tail investigation

The first tail probe exposed that the existing candidate `src/functions/1001defe.cpp` did not apply the original GS-cookie epilog correctly. Ghidra's `0x1001defe` epilog loads the saved cookie at `[EBP-4]`, XORs it with `EBP`, then calls `__security_check_cookie`. The candidate had passed the pre-XOR value. Corrected the candidate to recombine its saved-cookie value with the aligned frame base before the check, preserving the old file as `src/functions/1001defe.cpp.pre-cookie-xor-validation-20260929.bak`.

The first exception-tail probe then exposed a second relocation defect in `src/functions/1002049a.cpp`: three `FLD m80fp` instructions emitted literal absolute addresses `0x100396dc` and `0x100396e8`. That works at the original preferred base but reads the wrong address when the diagnostic image is rebased. Changed them to relocatable references through the data symbol `DAT_100396d8` at offsets `+4` and `+0x10`; the pre-edit file is preserved as `src/functions/1002049a.cpp.pre-reloc-m80-loads-20260929.bak`. The fresh COFF object now contains `DIR32` relocations against `_DAT_100396d8` at all three sites.

After both fixes, strict compile is **705/705**, objective verifier **705 PASS / 0 FAIL / 0 UNKNOWN**, parity **705 GREEN / 0 YELLOW / 0 RED**, and a refreshed diagnostic-only full-set DLL links successfully (stale `/ORDER` LNK4037 warnings only). Mapped-original differential results: **200,480/200,480** exact returns through underflow-scale, return-input, and finite reduction paths, plus **16,384/16,384** exact exception-tail returns through the Ghidra-confirmed `0x1001c5f0` caller. Tail coverage is the cross-product of four MXCSR rounding modes and four x87 control words (`0x037f`, `0x027f`, `0x0b7f`, `0x0f7f`), with 96 directed cases at exponent words `0x40f6`, `0x40f7`, and `0x4100`, plus 1,000 deterministic randomized inputs per environment over exponent words `0x40f6..0x4100`, with varied mantissa/sign. For these mapped-image checks, imports are resolved manually while entrypoints/`DllMain` are intentionally not run.

This is substantially stronger isolated function evidence, but it is not complete runtime proof for all exception cases (e.g. NaN/infinity/other x87 status patterns), does not exercise the module's real startup/CRT initialization, and does not validate GTA gameplay. The diagnostic link remains not a production `.asi`.

## Remaining validation

No production project/SDK build, actual `.asi` creation, or GTA startup/gameplay test has been completed. The harness loads a diagnostic-only DLL, not an `.asi`.
