# Manual parity call-count recheck (2026-09-27)

This recheck compares each of the 13 `scope=call-count-only` entries in
`C:\Users\caner\OneDrive\Documents\ImVehFt\reports\re-agent\manual-parity-checks.md`
against the Ghidra assembly export and the target function block(s) in the
fresh x86 MSVC COFF objects under
`build/recheck/strict-all-post-raster-20260927`.

The same 13-symbol count was repeated against the parallel objects in
`build/obj` (`manual-parity-call-counts-buildobj-2026-09-27.json`): all 13
counts are identical between the two directories, although all 13 whole-object
SHA-256 values differ. Thus the two count discrepancies noted below are not
explained by merely selecting one of those local object directories; the
historical note must refer to another emitted body/configuration or a prior
counting basis, which is not yet identified.

The first two generated count reports used an incorrect function-boundary
parser and are retained for audit history, but must not be cited. The corrected
report is `manual-parity-call-counts-v2-2026-09-27.json`. The parser keeps MSVC
`$` local labels inside a function, handles decorated CRT symbol names, and
aggregates `FUN_1001bc9e`'s ABI wrapper with its `_impl` helper, as the existing
manual adjudication describes. It found all 13 targets with no symbol errors.
Each row includes the COFF object's SHA-256 and the Ghidra/COFF call counts.

| Address | Ghidra CALLs | Current COFF CALLs | Note |
|---|---:|---:|---|
| `1001a785` | 11 | 18 | Existing note compares Clang (10) and MSVC output; not the same toolchain count. |
| `100050e0` | 33 | 33 | Exact count match. |
| `10010ba1` | 8 | 9 | Existing note attributes the excess to merged paths/security-cookie instrumentation. |
| `100170d6` | 17 | 18 | Existing note explains a duplicated mutually exclusive cookie-check site. |
| `10010540` | 10 | 13 | Existing note explains split error/normal epilog and helper sites. |
| `1001bc9e` | 8 | 11 | Counts wrapper plus `_impl`, matching the documented representation. |
| `1001d591` | 31 | 30 | Target-frequency comparison explains the one-call delta: Ghidra calls `_inconsistency` four times; the candidate has three CALLs plus a tail `JMP` to `_inconsistency` after epilogue cleanup. Other direct targets/frequencies match. This is consistent with a tail-call codegen change; the old note's 32 count is not reproduced by either current object directory. |
| `100154dc` | 27 | 30 | Existing note's adjusted count is 28 after excluding two `memset` sites; raw count is 30. |
| `10010f59` | 27 | 32 | Existing note explains five additional mutually exclusive SEH epilog sites. |
| `100076d0` | 21 | 27 | Current COFF has seven `__security_check_cookie` call sites; removing them leaves 20 other calls. The COFF list has 10 indirect calls versus Ghidra's 11, consistent with one merged mutually-exclusive indirect tail, but exact target/path matching still matters. The separate conditional stack-slot semantic warning remains. |
| `100119f1` | 62 | 68 | Current target-frequency difference is exactly three extra `_isdigit` sites and three extra `__security_check_cookie` sites (candidate four, Ghidra one); the loop pairs and distinct return blocks are confirmed in the exact-object disassembly below. Other named call frequencies match. The old note's 66 count is not reproduced by either current object directory. |
| `10018120` | 2 | 2 | Exact count match. |
| `1001b9de` | 1 | 1 | Exact count match. |

The count-only waivers themselves remain narrow: a fresh ReAgent 0.4.0 parity
run (`parity-independent-continuation-2026-09-27.json`) reports 704 GREEN,
1 YELLOW, 0 RED across 705 functions, and the guard script confirms 13 scoped
waivers plus the retained `100076d0` semantic finding. A fresh independent
structural objective run reports 705 PASS / 0 FAIL / 0 UNKNOWN. Those outcomes
do not settle the three call-site accounting discrepancies above, prove
semantic equivalence, or establish link/game behavior.

The `1001d591` call-target histogram supports the count difference as a
tail-call transformation: the fourth Ghidra `_inconsistency` CALL corresponds
to the candidate's epilogue followed by a JMP to that same no-return helper.
For `100119f1`, the extra `_isdigit` sites form three loop pairs in this exact
object: `0xBB1/0xC23`, `0xCB8/0xD1D`, and `0xE12/0xE73`. Each pair tests at
the loop entry and repeat edge, matching one logical Ghidra test per loop. The
other three `_isdigit` sites are unpaired. Its four cookie checks are at
`0x10C`, `0x13DD`, `0x1403`, and `0x1427`; the latter three each precede a
distinct `RET`, while Ghidra has one shared cookie-check epilogue at
`0x100129EE`. These are mutually exclusive exits, accounting for three
duplicated static cookie sites. This exact-object control-flow evidence
accounts for the +6 raw `CALL` delta without claiming byte or runtime identity.

Next binary-side work should finish that exact-object CFG review for
`100119f1`, then reconcile `100076d0`'s indirect target/path inventory. A first
focused follow-up on `100076d0` found seven MSVC
`__security_check_cookie` call sites. Removing those leaves 20 other COFF call
sites, one fewer than Ghidra's 21; the indirect-call inventory likewise
differs by one, consistent with the documented mutually exclusive tail merge.
This plausible reconciliation does not prove exact call-target/path identity
or remove the independent stack-slot finding. No candidate source was changed
by this recheck. No original project build or in-game runtime test has been
verified.
