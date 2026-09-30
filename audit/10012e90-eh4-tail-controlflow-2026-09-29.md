# `10012e90` EH4 cookie and tail-control-flow follow-up

## Change

Compared `src/functions/10012e90.cpp` against the pinned original's Ghidra export at `C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\10012e90.json` and the original `ImVehFt.asi` hash `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The Ghidra listing shows three checker pairs: entry at `0x10012ec4/0x10012ed4`, common return at `0x10012f47/0x10012f57`, and handler-transfer path at `0x10012fdd/0x10012fed`. Cookie values use the decoded EH4 scope-table header offsets; the GS check is conditional on its offset not being `-2`, while the EH cookie is always checked. The candidate now represents those formulas and emits six `@__security_check_cookie@4` COFF call relocations in both focused `/GS-` and default `/GS` objects.

The listing also shows a negative filter result branching to the common return-cookie block, not returning directly. After `_EH4_TransferToHandler`, control continues through the tail unwind test on `param_2`'s `try_level`, and then reaches the common return-cookie block. The candidate was adjusted to preserve those paths and pass `param_2` as the unwind frame. The previous candidate was preserved as `src/functions/10012e90.cpp.pre-tail-unwind-controlflow-20260929.bak`; the earlier cookie-pair edit is preserved in `src/functions/10012e90.cpp.pre-scope-cookie-pair-20260929.bak`.

## Validation

- Focused MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` compile passed with both `/GS-` and default `/GS`.
- Fresh complete strict compile: `build/strict-xcode-nogs-eh4tail-final-20260929.json` and `build/strict-xcode-gs-eh4tail-final-20260929.json`, each 705/705.
- Fresh independent objective audit: `audit/objective-independent-eh4tail-final-2026-09-29.json`, 705 PASS / 0 FAIL / 0 UNKNOWN.
- Fresh local ReAgent 0.4.0 parity: `build/parity-eh4tail-final-2026-09-29.json`, 705 GREEN / 0 YELLOW / 0 RED.
- Fresh static checker-call reconciliation: `audit/gs-callsite-reconciliation-eh4tail-final-2026-09-29.json`. The target function now matches Ghidra at 6 calls in either object mode. Whole-set totals remain different: Ghidra 29 calls / 24 functions; `/GS-` 38 call relocations / 17 functions; default `/GS` 97 call relocations / 51 functions plus 49 compiler-cookie relocations.

## Limits / remaining work

The results above establish compilation, configured objective checks, structural ReAgent parity, and this function's checker-call count. They do **not** establish full instruction/path equivalence, whole-set exception semantics, correct process-wide cookie initialization, a production-compatible linked image, or GTA gameplay behavior. Other per-function call-site mismatches remain. The supplied `.ImVehFt` directory contains mod assets/configuration rather than C++ source, and `C:\Users\caner\Downloads\SA Plugin SDK` was not present at verification time. No production `.asi` was generated or installed, no game test was run, and nothing was pushed.
