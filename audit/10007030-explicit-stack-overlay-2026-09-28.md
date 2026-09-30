# `10007030` explicit stack-overlay correction

## Superseding correction (2026-09-28)

The four-case harness result documented below is **superseded and must not be
treated as behavioral validation**. A new review of the original call-site
assembly and archived 2014 Plugin-SDK found that `0x40FE60` is
`VectorSub(CVector const& from, CVector const& what)`, returning a `CVector`
by value. In the original call at `0x10007095`–`0x100070a5`, the hidden
structure-result pointer is `[EBP-0x18]`, the first vector argument is
`param_3`, and the second vector argument is `[EBP-0x40]`. The latter is a
read-only vector overlapping the final 16 bytes of the copied matrix; it is
not an output buffer. The candidate previously sent `[EBP-0x1c]` as the
result pointer, while its old harness stub wrote synthetic words into
`[EBP-0x40]`.

Corrected the candidate call to use `[EBP-0x18]` as the result buffer and
`param_3` / `[EBP-0x40]` as vector inputs. The archived SDK also identifies
`0x7F2070` as `RwMatrixInvert(out, in)`, not matrix multiplication. Its test
callback is currently constrained to identity-matrix input and copies that
matrix; the `0x59C790` test callback applies the SDK-documented `Multiply3x3`
basis formula. An initial corrected run yielded 3 matches / 1 mismatch because
the harness reused x87 state between separately invoked original and candidate
calls. Resetting the x87 environment before each invocation eliminated that
harness-only divergence. A fresh corrected four-case run now matches all four
scenarios (direct corona; alpha above/below threshold; suppressed mode), using
the exact original ASI hash. This supports the caller's selected ABI, stack
aliases, control flow, and outputs under these controlled callee models; it is
not full-function equivalence because GTA vector/matrix/corona callees remain
stubbed and the focused matrix input is identity-only. `10007030` is partially
validated, not fully verified or gameplay-tested.

Attempted to replace the mocked GTA math callbacks by mapping the installed
`gta_sa.exe` into the x86 harness at its preferred base. The executable is
PE32/x86, image base `0x00400000`, size `0x01177000`, SHA-256
`F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`, and has
relocations stripped. The harness could not reserve its preferred image range:
`VirtualAlloc` failed with Win32 error 487, and `VirtualQuery` showed existing
committed regions across that address interval. Rebasing is not safe without
relocations. The mapped-game experiment was discarded; the controlled harness
was restored and rerun, again matching 4/4. This does not count as game
validation. No `gta_sa.exe` process was running during the check.

Read-only Capstone disassembly of this exact-hash GTA executable independently
confirms the helper instruction behavior: `0x40FE60` reads its two vector
pointers from `[ESP+8]` and `[ESP+0xC]`, writes the hidden result pointer at
`[ESP+4]`, performs three x87 subtractions, and returns with plain `RET`;
`0x59C910` uses `ECX` as its vector and has an x87 normalize path; `0x59C790`
reads result/matrix/vector from the expected stack arguments, computes the
three basis products, and returns with plain `RET`. `0x7F2070` additionally
reads `RwEngineInstance` globals at `0xC97B24` and `0xC979BC` before selecting
matrix paths, so it is not a context-free pure callback. This supports the
ABI interpretation but does not replace running those engine functions inside
an initialized GTA process.

Evidence: Ghidra export
`C:/Users/caner/OneDrive/Documents/ImVehFt/ghidra_exports/10007030.json`,
archived SDK `src/sdk/game_sa/common.cpp` and `RenderWare.h`, and current test
source `tests/runtime_10007030_stack_overlay_differential.cpp`.

The checks and claims below record the prior state only; their four-case
callback model was incorrect. Current-source checks are recorded above and in
`audit/status.json`.

Date: 2026-09-28. Reference binary: installed `ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Evidence and issue

The current Ghidra export is `C:/Users/caner/OneDrive/Documents/ImVehFt/ghidra_exports/10007030.json`.
Its original assembly shows two 16-dword matrix copies:

- At `0x10007072`–`0x10007082`, `ECX=0x10` and `REP MOVSD` writes the first
  matrix at `[EBP-0xb0]`.
- At `0x10007085`–`0x10007093`, `ECX=0x10` and `REP MOVSD` writes the second
  matrix at `[EBP-0x70]`.
- The later corona-position pointer is passed as `LEA EAX,[EBP-0x80]`,
  overlapping the last 16 bytes of the first matrix. The output scratch passed
  to `0x40fe60` starts at `[EBP-0x40]`, overlapping the last 16 bytes of the
  second matrix; that matrix is consumed beforehand by `0x7f2070`.

The candidate had declared each matrix as `uint32_t[12]` but its loops wrote 16
elements, invoking C++ out-of-bounds undefined behavior and leaving these
important stack-lifetime overlaps to compiler local placement. Replaced those
separate arrays/scratch arrays with one aligned `0xf0`-byte overlay and pointers
at offsets verified against the original assembly: first matrix `-0xb0`,
corona-position pointer `-0x80`, second matrix `-0x70`, and helper output
`-0x40`. The compiled entry also preserves the Ghidra-observed `0x59c790`
pointer relation: result and input at `-0x18`, matrix pointer at `-0xf0`
(relative separation `0xd8`). The alpha value is the following float at
`-0x14`, written by the transform output; the candidate now models it in the
same overlay. The post-transform x87 zero-stack setup (`FLDZ`) is also emitted
at the corresponding control-flow point. These placements preserve the
observed aliases without array-overrun UB.

An isolated 32-bit harness calls the exact installed ASI implementation and
the candidate with identical crafted arguments. Four controlled cases now
match: direct corona; alpha with transform output above and below the observed
`0.5` threshold; and the alpha-suppressed mode. It compares callback counts,
corona arguments, matrix data, alias contents, and the `0x59c790` relative
pointer geometry. The alpha-helper call forwards to the actual mapped original
`0x1001ba40`; setup, tick, matrix, transform, and corona callbacks are
deterministic stubs. The transform stub injects three chosen float words, so
this isolates the caller's branches but does not validate the real GTA
transform callback. A pre-fix negative control correctly mismatches the
transform-pointer delta and alpha result. This is bounded differential
evidence, not exhaustive function equivalence.

## Preservation and checks

Backups:

- `src/functions/10007030.cpp.pre-explicit-stack-overlay-20260928.bak`
  (pre-change SHA-256 `93D66D22946DDE961071DFF5C3A20EAACA6A8B0CAE977AABFD580D635D9C49E4`).
- `src/functions/10007030.cpp.pre-overlay-alignment-20260928.bak`
  (intermediate SHA-256 `F201ADE09448AD87A67FE36C035A6BF5FAF9C4BB90E3A84605DDFA48AC0B00EF`).
- Both 705-row manifests were backed up before each refresh using
  `.pre-stack-overlay-10007030-20260928.bak` and
  `.pre-stack-overlay-alignas-10007030-20260928.bak` suffixes; the final
  refresh is backed up with `.pre-callback-stack-alias-final-10007030-20260928.bak`.
- `src/functions/10007030.cpp.pre-callback-stack-alias-20260928.bak` preserves
  the source before the new pointer/alias/alpha corrections (SHA-256
  `F65C9E8EE0DC23B2F63BD95D5D173BFFBCF3ACBB1A5C4C736F425D5B295EEC04`).

The final source SHA-256 is
`08B963113ECE77EE3293F848413EB22761F02420208BF165A691531437003570`, matching
the refreshed manifest. The four-case harness source SHA-256 is
`8CD88A6D038809923CAA7317C8D1752F1363F2B75338C41C64BEB380E2FE0DA6`; its
executable SHA-256 is
`090DDA088ED7796B5679018A4D4DB485041AB1613C944BCD59EA1667B6BE90D3`.
Fresh whole-set checks against this source:

- Strict compile: **705/705**, `build/strict-stack-overlay-complete-10007030-20260928.json`.
- Independent structural objective: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  `audit/objective-stack-overlay-complete-10007030-2026-09-28.json`.
- Local modified ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**,
  `build/parity-stack-overlay-complete-10007030-20260928.json`.
- Full 705-object diagnostic link succeeded to
  `build/link-probe/strict-704-historical-sdk/ImVehFt-stack-overlay-complete-10007030-diagnostic-not-ASI.dll`
  (SHA-256 `901B658F2455420EED4B46F9DA537786ED8FB97A370CE333621FD214F81834FC`).
  `dumpbin` confirms PE32 x86 DLL, image base `0x10000000`, size `0xC4000`;
  it is explicitly **not** a loadable ASI.
- On this fresh link/map, the original-entry placement feasibility audit
  resolves **705/705** executable targets: 429 direct bodies fit, 275 require
  in-range 5-byte `E9 rel32` stubs (minimum gap 8 bytes). Report:
  `audit/entry-trampoline-feasibility-stack-overlay-complete-10007030-2026-09-28.json`.

## Limits

This is a Ghidra-backed stack-layout/undefined-behavior correction with four
bounded original-binary differential scenarios, not exhaustive whole-function
equivalence. Real GTA transform/corona effects remain unverified.
ReAgent/objective/compile green remain structural evidence. No production `.asi`, complete original
ImVehFt project/build recipe, or live GTA/RenderWare test is established. The
entry-placement audit proves only address feasibility; it emits no thunks and
does not restore original data/relocation layout, loader/installer startup, or
prove gameplay behavior.
