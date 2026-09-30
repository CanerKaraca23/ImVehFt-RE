# Current source/SDK and diagnostic-link readiness (2026-09-29)

## Input availability

- The current publish checkout contains no `.sln`, `.vcxproj`, `.vcproj`,
  `CMakeLists.txt`, `.dsp`, or `.dsw` build descriptor.
- The installed `.ImVehFt` mod folder has the original and ImVehFtFix `.asi`
  files, logs, and resources, but no C/C++ source or project files. The target
  original and installed copies are each 247,296 bytes and have SHA-256
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
  `ImVehFtFix.asi` remains separate and out of scope.
- `C:\Users\caner\Downloads\SA Plugin SDK` is absent. The local historical
  SDK worktree is commit `888a67c1587ece1053a05f0cb6219a0c6c4dad0a`
  (`2014-04-27`, `Update CObject.h`) and includes a 1,379,326-byte
  `Plugin2014.lib` built locally in 2026. Its worktree has an existing modified
  `CallbackResetDevice.hpp` and an untracked build directory; neither was
  changed. The separate `plugin-sdk-sa` checkout is at
  `b55e89b336a81448c1aa1a5b188431c9845ebaa9` and has no tracked modifications.
- SDK availability is not evidence of the exact SDK or settings used by the
  original mod. The original ImVehFt project/source and build configuration
  remain unavailable.

## Current-object diagnostic link

### Latest replay (2026-09-29)

Ghidra signatures/assembly and current COFF symbol tables identified several
candidate-to-candidate C++ helpers that were incorrectly declared `extern
"C"` or had mismatched return/parameter types. Corrections were made to the
exception-constructor caller, EH handler/type-match/catch-object/unwind
callers, and the related x86 pointer conversions. Fresh strict compile,
independent objective verification, and ReAgent parity remain green at
**705/705**, **705 PASS**, and **705 GREEN**. Source manifests were refreshed;
each edited source has a pre-edit `.bak` copy.

Using the same 705-object diagnostic response family and support objects, the
current LNK1120 unresolved-symbol count decreased from **62 → 55 → 51 → 50 →
49 → 47** across successive fresh replays. The final response/log are
`build/link-probe/entry-exact-nogs-o1-linkage-reconcile-v3-20260929/` and use
the objects in
`build/recheck/strict-xcode-nogs-o1-linkage-reconcile-v3-20260929/`.
The link still fails and no DLL was emitted. The latest independent objective
and parity reports are
`audit/objective-linkage-reconcile-v3-2026-09-29.json` and
`build/parity-linkage-reconcile-v3-2026-09-29.json`; the final strict report is
`build/strict-xcode-nogs-o1-linkage-reconcile-v3-20260929.json`.

The remaining 47 distinct undefined-symbol names are inventoried in
`build/link-probe/entry-exact-nogs-o1-linkage-reconcile-v3-20260929/unresolved-lines.txt`.
They include unresolved CRT/file-I/O/math helpers, x86 SEH prolog/epilog
helpers, legacy initialization/runtime helpers, and several remaining
candidate-to-candidate declarations requiring Ghidra/signature review. The
current link response is still a diagnostic compatibility probe, not a
production linker recipe.

### Follow-up: remove stale forced roots and correct `__ctrlfp` call ABI (13:03 local)

The float-linkage response inherited two obsolete `/INCLUDE` roots:
`?__fload_withFB@@YIIIH@Z` (the current candidate defines
`@__fload_withFB@8`) and `?fputs@@YAHPADPAUFILE@@@Z` (current `_iobuf` type
identity differs). A preserved response copy with only those stale roots
removed reduced LNK1120 from 22 to **20**; this made no source change and did
not produce a DLL. The original response was retained unchanged.

Ghidra assembly for `0x1001defe` then provided a concrete candidate correction:
the `0x1002046f` call is preceded by `PUSH 0xffff` and `PUSH [EBP-0x88]`
(the saved control word), and the caller cleans eight stack bytes. The callee
at `0x1002046f` reads arguments at `[EBP+8]` and `[EBP+0xc]`, updates the x87
control word, and executes a plain `RET`. Corrected `src/functions/1001defe.cpp`
to declare/call the two-argument `__cdecl __ctrlfp(0xffff, local_98)`, matching
the current `0x1002046f` implementation and the original call sequence. A
pre-edit source backup is `src/functions/1001defe.cpp.pre-ctrlfp-abi-20260929.bak`.

Fresh whole-set gates pass: strict x86 `/O1 /GS-` compile **705/705**,
independent structural objective **705 PASS / 0 FAIL / 0 UNKNOWN**, and ReAgent
parity **705 GREEN / 0 YELLOW / 0 RED**. The regenerated caller object now
references `___ctrlfp` (instead of the nonexistent `___ctrlfp@0`). A fresh
705-object diagnostic link drops from 20 to **19 unresolved externals**; it
still fails and emits no DLL. Reports and response/log are
`build/strict-xcode-nogs-o1-ctrlfp-abi-20260929.json`,
`audit/objective-ctrlfp-abi-2026-09-29.json`,
`build/parity-ctrlfp-abi-2026-09-29.json`, and
`build/link-probe/entry-exact-nogs-o1-ctrlfp-abi-20260929/`. The two source
manifests were refreshed with separate pre-edit backups. Structural gates do
not prove semantic equivalence; no `.asi` or GTA runtime validation exists.

### Follow-up: EH4 prolog and `_atexit` linkage (13:14 local)

The next fresh linker replay exposed mixed linkage around `0x10012e20`:
after its definition was corrected to the original C symbol `___SEH_prolog4`,
four callers still requested a C++-mangled version. Corrected only those four
declarations (`10010678`, `1001384b`, `10017dde`, `100189f5`) to C linkage;
the naked EH4 body and stack ABI were unchanged. The next 705-object replay
resolved the EH4 prolog symbol completely.

The six remaining `__atexit` caller errors mapped to Ghidra function
`0x10010529` (`_atexit`). Its candidate definition had C++ linkage while the
callers and original COFF symbol require C linkage. Corrected the definition
to `extern "C"`; the fresh object exports `__atexit`. A legacy MASM startup
provider still calls its old C++-mangled `_atexit` symbol, so only the
diagnostic response adds an explicit `/alternatename` to the verified C
candidate symbol. With that compatibility mapping, LNK1120 is now **17**.

After these source changes, strict compile is **705/705**, independent
objective verification **705 PASS / 0 FAIL / 0 UNKNOWN**, and parity **705
GREEN / 0 YELLOW / 0 RED**. Source manifests were refreshed with new backups.
The diagnostic link still fails and emits no DLL. Its current response/log are
under `build/link-probe/entry-exact-nogs-o1-atexit-linkage-20260929/` (`link-v3.log`);
the 17 unresolved symbols are mostly legacy CRT floating-point/runtime
helpers plus a couple candidate-to-candidate identities. These results do not
establish semantic/runtime equivalence, a production `.asi`, or a successful
GTA test.

### Follow-up: legacy float CRT symbols and math-helper boundary (13:34 local)

The next linker pass exposed a cluster of internal C++-mangled candidates for
Ghidra-identified Visual Studio CRT routines. Restored C linkage on
`__cfltcvt`, `__cfltcvt_l`, `__fassign`, `__fassign_l`, `__cftoe`, `__cftoe_l`,
`__cftoa_l`, `__cftof_l`, and `__cftog_l`; renamed the two duplicate
`FID_conflict:__atoflt_l` bodies with address-qualified C names matching their
call sites; and aligned `__math_exit` / `__startOneArgErrorHandling` formal
fastcall signatures with Ghidra's 20-byte and 24-byte decorations. Also
corrected the `0x1001f203` CRT formatter export to the Ghidra `$I10_OUTPUT`
symbol. Every changed source was backed up before editing.

The refreshed full-set checks remain strict compile **705/705**, independent
objective **705 PASS / 0 FAIL / 0 UNKNOWN**, and ReAgent parity **705 GREEN / 0
YELLOW / 0 RED**. In a copied diagnostic response, two stale forced roots
were removed and explicit aliases bridge the legacy MASM `_atexit` startup
provider and the compiler-specific alloca probe decoration. The diagnostic
link count fell **17 → 2**; there is still no DLL. The remaining unresolved
names are `_FUN_1001c60e` and
`?FUN_1001b3cf@ReagentMathError@@QAEOXZ`. Ghidra's original `0x1001c60e`
tail path is a direct jump to `0x1001b3cf`, while the current reconstructed
C++ math-helper boundary implies a class-method call; the entry uses XMM0 and
preserved register/stack state, so adding a name-only alias would not establish
the needed ABI or semantics. These two are intentionally left for a focused
original-vs-candidate call-boundary analysis. The fresh response/log and
current objects are under
`build/link-probe/entry-exact-nogs-o1-legacy-crt-symbols-20260929/` and
`build/recheck/strict-xcode-nogs-o1-legacy-crt-symbols-20260929/`. No
production `.asi` or GTA run exists.

An earlier unresolved-data extraction that reported 1,082 aliases was based
on a polluted linker log containing duplicate-definition diagnostics. Treat
that extraction as rejected and do not use it to generate a provider. The
current link replay above uses the smaller clean extraction/provider already
identified in the v1 response. The old 178/111/110 counts below describe prior
stages and are not the current result.

Replayed the saved full-candidate entry-link response using the freshly built
current strict x86 object set (`build/strict-xcode-nogs-o1-cinit-stdcall-20260929.json`,
705/705). The prior response's address provider and supplemental link objects
are old artifacts, so this is a compatibility diagnostic, not a production
link recipe.

- With that support set, the current 705-object link ended with LNK1120 and
  178 unresolved externals; no DLL was produced.
- Adding the current 82-address alias provider and current callback-vftable
  crosswalk provider reduced the unresolved count to 111.
- Mapping the remaining `_thunk_FUN_100013e0` decoration reduced it to 110.
  Adding the existing CRT-data alias provider did not reduce it further.
- The final response file/log are in
  `build/link-probe/entry-exact-nogs-o1-cinit-stdcall-crt-alias-provider-20260929/`.
  The linker produced no DLL, and no output was loaded into the game.

The remaining errors include address-backed data/global labels, CRT/runtime
helpers, and other candidate/shim names. The added vftable crosswalk eliminated
the missing callback-manager vftable symbols in this probe. Before drawing a
conclusion from the remaining count, the data provider, CRT compatibility
objects, and supplemental thunks must be regenerated/reconciled against the
current 705 object set. The historical successful diagnostic DLL is based on
an older candidate/object-provider combination and does not prove this current
set links.

## Readiness

Current source-level gates remain strict x86 compile **705/705**, independent
ReAgent objective **705 PASS / 0 FAIL / 0 UNKNOWN**, and ReAgent parity **705
GREEN / 0 YELLOW / 0 RED**. They do not prove full semantic equivalence. With
the original source/project missing and the current-object diagnostic link
still failing, production `.asi` generation, correct original PE layout, and
GTA runtime/gameplay validation remain open. The original ASI was not modified.
