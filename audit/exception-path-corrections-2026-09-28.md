# Exception-path fidelity corrections (2026-09-28)

Three more Ghidra-led corrections are now in the candidate set, in addition to the `_CallSETranslator` local continuation relocation documented in `translator-continuation-relocation-2026-09-28.md`.

## `_UnwindNestedFrames` continuation

Ghidra export `ghidra_exports/1001b693.json` shows the `RtlUnwind` continuation at `0x1001b6be`, which is the instruction immediately after the call inside `_UnwindNestedFrames`. Replaced the fixed target with `OFFSET unwind_nested_frames_continue` in a naked x86 reconstruction of the observed routine. Fresh object disassembly puts the label at `+0x2b`, exactly `0x1001b6be - 0x1001b693`, with a DIR32 relocation to the local label and a REL32 call to `ImVehFt_Recovered_RtlUnwind`. The original argument cleanup (`ret 8`), saved registers, exception flags, and `FS:[0]` restoration are represented in the emitted sequence.

## `__except_handler4` destructor callback ABI

Ghidra export `ghidra_exports/10012e90.json` shows two pushes before the indirect destructor callback at `0x10012f9a`, then `add esp,8`; there is no third handler-address argument. The candidate's third argument (`0x10012ed9`) was unsupported by the machine code and has been removed. The fresh x86 object now emits the two-argument callback (`exception_record`, `1`) and caller cleanup of eight bytes. A pre-edit source backup is retained.

## `__cftoa_l` error return values

Ghidra export `ghidra_exports/1001bee6.json` shows `ESI=0x16` for the invalid-parameter path and `ESI=0x22` for the insufficient-buffer path; both flow through the callback and return that error value. The candidate had overwritten the value with interior code address `0x1001bf29` in both branches. Those two assignments were removed. Fresh MSVC object disassembly returns `0x16` and `0x22` on the corresponding paths; a pre-edit source backup is retained.

## Current verification snapshot

- Strict MSVC x86 `/O2 /W4 /WX /MT`: 705/705 passed (`build/strict-all-final-three-fixes-20260928.json`).
- Independent objective verifier: 705 PASS / 0 FAIL / 0 UNKNOWN (`audit/objective-final-three-fixes-2026-09-28.json`).
- ReAgent parity: 705 GREEN / 0 YELLOW / 0 RED (`build/parity-final-three-fixes-20260928.json`).
- Fresh 705-object diagnostic link succeeds: `build/link-probe/strict-704-historical-sdk/ImVehFt-final-three-exception-corrections-diagnostic-not-ASI.dll`; the map resolves `__except_handler4` and `_UnwindNestedFrames` to their candidate objects and `ImVehFt_Recovered_RtlUnwind` to `1001b2b2.obj`.
- The residual internal-image literal scan is v27: 9 occurrences / 9 addresses, 8 without exact function-entry matches. It includes comments/decompiler scaffolding; uses still need individual evidence-based classification.
- All above are source/object/static checks, not whole-program semantic equivalence or runtime validation. The diagnostic DLL is not a loadable `.asi`; game testing remains open.
