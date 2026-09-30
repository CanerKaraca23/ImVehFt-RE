# Ghidra cookie-callsite reconciliation: manual legacy cookies under `/O1 /GS-`

## Finding and source changes

The original inventory in `ghidra_exports/*.json` contains 29 calls to `0x100172d5` across 24 functions. The previous `/O2 /GS-` candidates emitted 38 checker-call relocations; the `/O1 /GS-` experiment emitted only 22, and default `/GS` variants added compiler-cookie references that are not interchangeable with this binary's legacy `DAT_10029490` cookie.

Ghidra callsites absent from the `/O1 /GS-` candidate were checked individually and restored in source:

| Address | Ghidra call | Reconstructed behavior |
| --- | --- | --- |
| `10011724` | `10011846` | Explicit legacy stack-cookie check at the common epilogue |
| `100119f1` | `100129ee` | Funnel source returns through the original common stack-cookie epilogue |
| `10019c86` | `10019e66` | Funnel early zero returns through the legacy stack-cookie epilogue |
| `10019eb3` | `10019f93` | Funnel early zero returns through the legacy stack-cookie epilogue |
| `1001b827` | `1001b838` | Validate EH registration cookie `*(param_2 + 8) XOR param_2` at entry; this is not a local GS-cookie check |
| `1001eb27` | `1001f1c9` | Funnel the invalid-locale return through the legacy stack-cookie epilogue |
| `1001f203` | `1001fab7` | Funnel all scalar returns through the legacy stack-cookie epilogue |

Each edited source had a pre-edit `.bak` copy. The EH4 correction is separately recorded in `audit/10012e90-eh4-tail-controlflow-2026-09-29.md`.

## Fresh validation

- Full current-source MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` compile: `build/strict-xcode-nogs-o1-manual-cookies-final2-20260929.json`, 705/705.
- Full Ghidra-vs-COFF inventory: `audit/gs-callsite-reconciliation-nogs-o1-manual-cookies-2026-09-29.json`; original 29 calls/24 functions and candidate 29/24. A per-function comparison reports zero call-count mismatches; candidate objects have zero compiler-cookie references.
- Independent objective verifier: `audit/objective-independent-nogs-o1-manual-cookies-2026-09-29.json`, 705 PASS / 0 FAIL / 0 UNKNOWN.
- ReAgent 0.4.0 parity: `build/parity-nogs-o1-manual-cookies-2026-09-29.json`, 705 GREEN / 0 YELLOW / 0 RED.

## Interpretation and remaining checks

Exact per-function call counts are stronger than the earlier aggregate-only match, but they do not prove that all 29 call instructions use the right arguments, execute on the right paths, or preserve all exception/stack semantics. The seven new callsites were located from Ghidra evidence and the cookie formulas were reviewed; they have not all received original-binary differential tests. `/O1 /GS-` is therefore a promising fidelity candidate, not yet a selected production build. The 705-target objective verifier and ReAgent parity remain structural gates.

The candidate still has no production-compatible rebuilt PE/ASI: code/data relocation integration, hook installation, startup/runtime compatibility, and GTA gameplay validation remain open. The supplied `.ImVehFt` directory is assets/configuration rather than original C++ source; `C:\Users\caner\Downloads\SA Plugin SDK` was absent on this check. No file was pushed.
