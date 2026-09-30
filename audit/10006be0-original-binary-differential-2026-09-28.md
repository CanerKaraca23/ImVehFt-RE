# `10006be0` targeted original-binary differential

Date: 2026-09-28

## Findings and correction

Ghidra export `ghidra_exports/10006be0.json` identifies the x87 value passed to
`FUN_1001ba40` and the corona-call stack arguments. The candidate's first
scaled-alpha path used `fld dword ptr [local_14]`. MSVC x86 disassembly showed
that `local_14` is a pointer stored at `[EBP-0x100]`; this instruction loaded
the pointer bits as a float. It now explicitly loads the pointed-to float.

The type-3/type-4 corona call also used the mutated `param_8` after calculating
alpha. In the original, the corona argument was already copied to the call
stack before the alpha helper call. The candidate now passes the saved
`original_corona_radius` to preserve that value. The candidate source was
backed up before each edit; the final pre-radius-edit snapshot is
`src/functions/10006be0.cpp.pre-original-corona-radius-20260928.bak`.

An early helper-entry probe produced invalid evidence because it clobbered
EAX/flags and compared non-equivalent parameter stack slots. That probe is not
used for the result below; helper interception is opt-in (`--trace-alpha`),
and the default differential path calls both implementations' helpers
directly.

## Verification

- Original binary SHA-256 pinned to
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Targeted differential: 2,928 directed cases per process across 3
  helper-global modes, 5 corona modes, 15 intensity edge values (including
  both sides of the alpha thresholds, infinities, and NaN), 4 alpha values,
  and 4 x87 rounding-control words; plus 4,096 deterministic input variations
  of the frame matrices, mode flags, radii, IDs, colors, and intensity. The
  latter exercises both direct matrix-copy and parent-matrix branches. The
  synthetic matrix stub writes exactly 16 DWORDs (64 bytes), enforced by a
  compile-time assertion. **Five fresh processes: 35,120/35,120 paired
  executions matched; zero mismatches.** Latest harness executable SHA-256:
  `987CB697053F7FFE99243B8613DC5B84D7FD527741C2B6FB120BA78D9D4B5B6F` at
  `build/abi-harness/10006be0-expanded-inputs-bounded-matrix-20260928/`.
  External game/API calls were replaced with controlled stubs. The later
  world/effect tail (`param_10 > 0`) remains outside this harness, as do live
  GTA/RenderWare and production-ASI validation.
- Fresh MSVC 14.44 x86 `/O2 /W4 /WX /MT /arch:IA32` compile: **705/705**;
  report `build/strict-all-10006be0-fix-20260928.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  report `audit/objective-independent-10006be0-x87-radius-fix-2026-09-28.json`.
- ReAgent 0.4.0 structural parity: **705 GREEN / 0 YELLOW / 0 RED**;
  report `build/parity-10006be0-fix-20260928.json`. The scoped call-count
  guard passes **13/13** and retains its semantic caveat.
- Both 705-row source manifests were backed up and refreshed; the objective
  run above used the refreshed manifest. `git diff --check` passed (only
  existing CRLF normalization warnings).

## Boundary

This repairs and increases evidence for one candidate only. Green parity,
compile, and objective results remain structural checks for the wider set.
There is still no production `.asi`, original build project/recipe, or live
in-game validation; other candidates and the global PE layout remain open.

## Tail-path follow-up (2026-09-28)

The previously excluded `param_10 > 0` path was added to the original-binary
harness. Direct comparison against the Ghidra assembly exposed a real source
translation error: the target performs three x87 rounds (param6, param5,
param4), forwards the param5 and param4 result bytes in ECX/EDX respectively,
and mutates the saved param8 stack slot only after its outgoing value has
already been pushed. The candidate had omitted the third round and forwarded
the wrong register bytes. These source errors are corrected; backup:
`src/functions/10006be0.cpp.pre-render-effect-channel-abi-20260928.bak`.

After that correction the harness passed its directed base set and 288 tail
cases, then exposed the target's mode-3 read of `[EBP-0x18]`: assembly confirms
the slot is only written on non-mode-3 branches, but mode 3 consumes it in an
`FMUL`. To preserve that observed stack behavior, the candidate entry bridge
now mirrors the original `sub esp,0xec` and saved-register prolog, captures the
untouched slot at the same `[EBP-0x18]` offset, and passes it to the translated
implementation. This is intentional stack-state emulation, not initialization
of the original undefined value. The implementation backup is
`src/functions/10006be0.cpp.pre-raw-local18-stack-capture-20260928.bak`.

Latest targeted run: `build/abi-harness/10006be0-tail-raw-local-capture-20260928/`;
**28,624/28,624** original-vs-candidate observations matched, including all
21,600 downstream-tail cases. Five additional fresh processes independently
repeated 28,624/28,624 each; together with the initial process, six fresh
processes produced **171,744 matched pairs**, zero mismatches. The harness
SHA-256 is `C256491B70A0E667A5A3DE3DD4DBD66F22C5DE0E166E5936D13989578B451897`.
Current `10006be0.cpp` SHA-256:
`C28A9A6DA0DD9C874C48843472CE17380C006F76C6D2FBD29EA354360B3DF772`.
The test patches external GTA/API calls to controlled stubs; this does not prove
live RenderWare/GTA behavior. The current source was then validated with a
fresh strict MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` compile (**705/705**), report
`build/strict-all-10006be0-tail-verified-20260928.json`,
independent objective (**705 PASS / 0 FAIL / 0 UNKNOWN**), current-source
ReAgent parity (**705 GREEN / 0 YELLOW / 0 RED**), and the scoped call-count
guard (**13/13**, still call-count-only). Both 705-row source manifests were
backed up and refreshed; an independent reread found zero source/hash
mismatches. A fresh full 705-object diagnostic link also succeeded; the PE32
DLL SHA-256 is
`8BE1F6AB1BCD32EF4099FD1C155225FA9927D9C7A46B58AF6E1A3A3D8F15850B` and it is
explicitly **not an ASI**. Candidate entry placement remains displaced
(`FUN_10006be0` at `0x10007320`, original `0x10006be0`; `FUN_100076d0` at
`0x10008d40`, original `0x100076d0`). No real GTA/RenderWare/gameplay run or
production PE is established.

## IEEE-boundary and code-generation follow-up (2026-09-28)

The tail-path differential was extended with 4,096 deterministic IEEE-754
boundary cases per process across the world/effect input, scene value, and the
otherwise-uninitialized mode-3 `[EBP-0x18]` slot. The test harness seeds that
slot to the same selected bit pattern before each original and candidate call;
the values include signed zero, subnormals, finite extremes, infinities, and
quiet NaN. It compares arguments, writes, call counts, x87 exception/control/
tag state and MXCSR. It separately counts x87 condition-code-only differences
(C0/C1/C2/C3), which are not part of the callback return contract; these are
reported, not silently described as bit-identical machine state.

This exposed and corrected two concrete translation artifacts:

1. The implementation copied the raw stack slot through a C++ `float`, and
   MSVC emitted `FLD`/`FSTP` unconditionally. A denormal seed therefore set
   x87 DE on paths where the original had not read the slot. The bridge still
   captures the exact raw word, but the implementation now copies it using an
   integer store; the float load occurs only when the original mode-3 tail
   consumes the slot. The optimized object confirms an integer move for this
   raw-slot assignment.
2. The world/effect expression previously kept `param_10 - fVar1` at x87
   extended precision through the multiplication. Ghidra's original listing
   and fresh MSVC disassembly show the adjusted value first stored as a 32-bit
   float, then reloaded and multiplied by the raw local. The candidate now
   emits `FSUB`, `FSTP m32`, `FLD m32`, `FMUL m32`, `FSTP m32`, and passes the
   rounded parameter onward. This fixed a reproducible one-ULP mismatch at
   extreme inputs under directed rounding.

Five fresh PE32 test processes, each with **32,720** original-vs-candidate
paired calls, match all compared semantic outputs and side effects: **163,600
paired calls, 0 non-condition-code mismatches**. Each process had 1,354 cases
where only x87 condition codes differed; exception flags, control word, x87
tag, MXCSR, callback/effect arguments and counts, and other recorded writes
matched. Harness SHA-256:
`E12603B240A8275A6D85A73DBFF73247B97B1EEAA42CF4F7BABFED3B44D0FCC1`.
Candidate source SHA-256:
`92B16BE2BB33C4A79E12E78FF34D3BB7D267C3F3B9EC7BB30C89D7A14A70BAF8`.
The source change has a preserved pre-edit backup adjacent to the candidate.

Fresh full-set checks after these edits: strict MSVC x86 `/O2 /W4 /WX /MT
/arch:IA32` compile **705/705**; independent objective **705 PASS / 0 FAIL / 0
UNKNOWN**; local modified ReAgent 0.4.0 parity **705 GREEN / 0 YELLOW / 0 RED**;
13 scoped manual checks remain call-count-only. A fresh 705-object diagnostic
DLL link succeeds (SHA-256
`CC1D373096E3BDB84438551B8E18EE8C5840B9C8EDCEF4578DF5EBD2E00913E2`) and
rechecks all 705 code-entry targets with the same 429 direct-body / 275
in-range-thunk feasibility. It is **not** a loadable ASI: entry VAs remain
displaced, and PE data/relocation layout, startup/installer integration, live
GTA/RenderWare callbacks and gameplay remain unverified.

## Reproducible rerun (2026-09-28 16:16 local)

Rebuilt the focused harness from the current candidate and ran it in six fresh
PE32 processes against the hash-pinned original ASI. Each process matched
32,720/32,720 compared observations, for **196,320 paired calls and zero
semantic/output/side-effect mismatches**. Coverage includes the finite
`param_10 > 0` effect/world tail, 4,096 deterministic variations, and 4,096
IEEE-boundary tail cases per process. Each run again reported 1,354
x87-condition-code-only differences; these are not claimed as full CPU-state
identity.

Current source SHA-256 is
`92B16BE2BB33C4A79E12E78FF34D3BB7D267C3F3B9EC7BB30C89D7A14A70BAF8`, matching
the 10006be0 row in `audit/source-sha256.csv` and the source hash recorded in
the independent objective report. Harness source SHA-256 is
`2FF5A653F1CA126E2BD5478C7E2B90509A567E5AC6CC8FCC1C390082BE41086A`; freshly
built executable SHA-256 is
`BD2A5E03AFC8DE6C9E70FD61A690EC94467109365368CF00B026306572D1DCBE`. The
reference ASI remains SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The same-source whole-set reports still show strict MSVC compile 705/705,
independent structural objective 705 PASS / 0 FAIL / 0 UNKNOWN, and local
modified ReAgent 0.4.0 structural parity 705 GREEN / 0 YELLOW / 0 RED. These
are not 705-function semantic or in-game validation. Production PE/ASI
relocation/layout, loader and installer integration, and live GTA/RenderWare
behavior remain open.
