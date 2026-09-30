# Candidate correction: `FUN_100076d0` fixed-address texture globals

Date: 2026-09-24  
Reference image: `ImVehFt.asi`, SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Evidence and change

The local Ghidra listing for `100076d0` accesses the 32-bit slots at `0x00B4E47C`, `0x00B4E68C`, and `0x00B4E690` directly: it checks/loads the first slot at `0x10007758`, `0x1000778d`, and `0x100077a9`, loads the second at `0x10007a24` and compares it at `0x10007a34`, and loads the third at `0x10007d6f`. The historical/local Plugin-SDK `CVehicleModelInfo.cpp` names these `ms_pRemapTexture`, `ms_pLightsTexture`, and `ms_pLightsOnTexture`, respectively, each a `RwTexture*` global.

The candidate previously modeled these executable globals as external symbols. `src/functions/100076d0.cpp` now reads each from its actual fixed address through a typed `RwTexture**` slot. This avoids requiring a linker-exported C++ symbol for memory owned by the running GTA executable. Existing logic and branch behavior were otherwise retained. This establishes address/type correspondence, not full semantic equivalence.

## Validation performed

- MSVC 2022 x86, C++20, `/O2`: the full set compiled and archived, **705/705**.
- MSVC 2022 x86 `/O2 /W4 /WX /MT`: the three currently corrected translation units passed; the other 702 were unchanged from the prior complete strict audit.
- ReAgent 0.4.0 targeted parity: **3 green / 0 red** for `10003ba0`, `10003e60`, and `100076d0`.
- ReAgent 0.4.0 objective verifier: **3/3 pass**, no structural failures.
- The `100076d0` object disassembly contains direct reads from the three expected addresses, consistent with the corresponding Ghidra accesses.
- The current diagnostic full-set link has **201 unique unresolved externals** and produced no DLL. It is not the original production project/link.

## Remaining warning and limits

The parity report records a scoped, manually adjudicated call-count heuristic for `100076d0`: optimized control flow merges mutually exclusive lookup tails. An earlier C4701 note concerned `local_c`; the current candidate avoids that warning by initializing the local to zero, but this is not a proven fidelity-preserving fix. Ghidra assembly initializes stack slot `[EBP-8]` only on the entry path guarded by `DAT_1003c1fc != 0` (`0x100076df` through `0x1000770e`), then re-reads that global at `0x10007c4b` before consuming `[EBP-8]` at `0x10007c54`. The candidate set also contains a writer to this global in `100074d0.cpp`. This makes a changed-between-checks state a plausible hazard; the inspected listing does not establish that such a transition is reachable during this function.

The aggregate 705/705 ReAgent totals refer to a prior source snapshot; only these three corrected candidates were rerun in the targeted ReAgent checks. No complete plugin link or GTA in-game validation has been performed. The work is therefore not 705/705 semantically or dynamically verified, and does not establish a byte-identical reconstruction of the author's source.

## Re-audit finding (2026-09-26)

A fresh `/O2` object disassembly confirms that the current candidate emits an unconditional zero store to its local stack slot (`mov dword ptr [esp+14h],0` at object offset `0x25`). In the Ghidra listing, the corresponding `[EBP-8]` slot is written only on the entry path where `DAT_1003c1fc` is nonzero (`0x100076df..0x1000770e`); later, the function rereads `DAT_1003c1fc` at `0x10007c4b` and consumes `[EBP-8]` at `0x10007c54`. If that global transitions from zero to nonzero during the function, the candidate's zero-initialized behavior differs from the binary's prior stack contents. Whether that transition can happen is not established by the current call-graph evidence. The candidate source is unchanged; this unresolved discrepancy is reported as YELLOW in the latest 705-function parity run, not as GREEN. Do not remove the initializer blindly: that would reintroduce C++ uninitialized-read/undefined-behavior concerns without proving the runtime invariant.

## Dispatch-path re-audit (2026-09-26)

Static tracing of the local GTA SA executable narrowed the earlier uncertainty for the ordinary dispatch path. The plugin installs candidate `100074d0` as a CALL hook at GTA address `0x6d6617`; the original instruction is preceded by `push esi`, and the candidate writes its argument to `DAT_1003c1fc` before returning. The next relevant original call at `0x6d662b` enters the callback dispatcher at `0x4c8430`, which passes callback address `0x4c83e0`. At `0x4c8415`, however, the patch does not replace a CALL instruction: it replaces the four-byte immediate of the `push imm32` instruction beginning at `0x4c8414`, changing the pushed callback pointer to `100076d0`; the following helper call at `0x4c841a` handles that callback. The scanned executable `.text` contains one direct caller of `0x4c8430`, at `0x6d662b`, and the callback address reference is at `0x4c843b`. This supports a nonzero-at-entry context for the identified ordinary path, assuming the vehicle argument in `ESI` is valid. Selected local executable byte checks are recorded in `game-executable-hook-compat-2026-09-27.md`; they are not a full hook-site or runtime compatibility pass.

This is static control-flow evidence, not a complete proof: indirect dispatch, re-entrancy, exceptional paths, and runtime mutation were not exercised. The candidate's unconditional local initialization still differs from Ghidra's conditional stack write at the instruction level. The parity rule is therefore downgraded from RED to YELLOW (warning), not cleared to GREEN. Preserve the initializer: removing it would create C++ uninitialized-read concerns and is not justified by the current evidence. A fresh 705-function parity run is required to publish the updated aggregate count.

A repository-wide check further narrowed possible writers: among the 705 candidate sources, the only assignment to `DAT_1003c1fc` is in `100074d0.cpp`; among the Ghidra JSON exports, only `100074d0` (writer) and `100076d0` (reader) reference the global. Combined with the observed call ordering, this supports the ordinary-path invariant more strongly. A fresh GTA executable disassembly also traced the material-texture path from `0x74dbc0` to `0x7f3820`, then to `0x808740`/`0x7fb020`, where indirect object-table calls occur at `0x80875a`, `0x7fb03a`, and `0x7fb04e` (plus the indirect call at `0x7f3889`). Their runtime targets are not resolved; they could not be proven not to re-enter code that changes vehicle context. Therefore the ordinary-path invariant is supported, but all-path/reentrant stability and runtime behavior remain unproven; keep the YELLOW warning.

## Targeted callback/callee audit (2026-09-27)

To narrow the re-entry concern, Ghidra 12.1.3 `-noanalysis` was run against
the installed `gta_sa.exe` (SHA-256
`F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`). A
bounded CFG/direct-call survey followed the target callback at `0x74DBC0` and
its direct callees to depth 2: five code entries and 158 instructions were
visited, with four direct call edges and four indirect callback/allocator
sites. The chain is `0x74DBC0 -> 0x7F3820 -> {0x808740, 0x7FB020}`. Their
roles are identified from the 2014 SDK layout and bounded disassembly:
`0x7F3889` and `0x7FB04E` use `RwGlobals.memoryFree`, `0x80875A` invokes a
registered texture-plugin callback at record `+0x24`, and `0x7FB03A` invokes
`RwGlobals.stdFunc[5]`. These are not five unknown API targets; the unresolved
part is the live function pointer/callback behavior and possible re-entry.
The second callback used in
`100076d0`, `0x7F39F0`, has no direct call instruction in the bounded listing.
Raw image scanning found eight byte occurrences of the absolute address
`0x1003C1FC`. Mapping the ImVehFt PE `.text` raw offset to its image VA and
cross-checking the Ghidra listings identifies all eight as instructions: one
write at `0x10007682` in `100074d0`, and seven reads/compares in `100076d0`.
The per-reference mapping is in
[`1003c1fc-reference-map-2026-09-27.csv`](1003c1fc-reference-map-2026-09-27.csv).
No other literal direct writer exists in the scanned file. This does not
exclude writes through an alias or indirect target.

This strengthens the ordinary-path account: no direct call edge in the
surveyed texture callback chain reaches the writer hook, and the complete
literal-reference scan found no second direct writer. It still cannot observe
the live allocator/registry function pointers or prove their callback paths
cannot mutate vehicle context. Indirect alias writes and re-entrancy therefore remain unexcluded;
the stack-slot mismatch remains YELLOW, and `100076d0.cpp` is intentionally
unchanged. The raw bounded evidence is
[`texture-callback-call-audit-2026-09-27.csv`](texture-callback-call-audit-2026-09-27.csv).

### Indirect-call roles from SDK layout and bounded Ghidra pseudocode

The local historical Plugin-SDK `RenderWare.h` identifies `0x7F3820` as
`RwTextureDestroy`, `0x7FB020` as `RwRasterDestroy`, and `0xC97B24` as
`RwEngineInstance` (a `RwGlobals*`). Its 32-bit `RwGlobals` layout places
`memoryFree` at `+0x148` and `stdFunc[0]` at `+0x48`, so the call at
`0x7FB03A` through `RwGlobals+0x5C` selects `stdFunc[5]`. The two indirect
calls through `+0x148` (`0x7F3889` and `0x7FB04E`) therefore use the RenderWare
free-list callback field, not an unexplained arbitrary object vtable.
The offsets were independently checked by compiling
[`probe-rwglobals-layout.cpp`](../scripts/probe-rwglobals-layout.cpp) with
VS2022 x86 `/Zs` against the local 2014 SDK header; all five `offsetof`
assertions passed.

A separate bounded Ghidra decompilation of `0x7F3820`, `0x7FB020`, and
`0x808740` confirms that these are texture/raster destruction paths. However,
`0x808740` walks a runtime list rooted at `0x8E23CC`/`0x8E2518` and calls each
record's function pointer at offset `+0x24`. Those per-record callbacks are
not statically resolved by this pass. The other three indirect sites use the
RenderWare freelist allocator or `stdFunc[5]`; their configured function
pointers are not read from a live game process. See [`rw-destroy-targets-2026-09-27.c`](rw-destroy-targets-2026-09-27.c)
and [`rw-destroy-targets-2026-09-27.csv`](rw-destroy-targets-2026-09-27.csv).

The earlier search of 706 Ghidra exports and 705 candidate sources for direct
registration API references was incomplete: it did not recognize the
`MOV EAX, 0x7F3BB0; CALL EAX` sequence in `ImVehFt.asi`. Exact-binary Ghidra
inspection now confirms an indirect `RwTextureRegisterPlugin` call at
`0x1000187E`, passing callbacks `10001ad0`, `10001b00`, and `10001b30`. The
actual sequence starts at `0x10001850`; `0x10001863` is an interior address,
so the earlier check for a containing function at that address was not valid.
The installed ImVehFt log records `Attaching texture maps plugin...` followed
by `Finished (96).`, matching the logger sequence around this registration
call in the exact-hash binary. The log timestamp is 2026-09-11 20:42:40: strong
evidence of execution in that historical run, but not proof of latest-session
execution or current registry state. The PE has no export directory or TLS
callback table; the registration/dispatch route must be traced from the
correct function boundary. Other indirect
registrations and callbacks from loaded modules also remain possible. See
`rw-registry-trace-2026-09-27.md`.

This narrows the uncertainty to RenderWare's runtime callback/allocator
dispatch rather than ordinary direct control flow. The registered `+0x24`
callback list could still contain code that re-enters plugin logic; no static
or runtime proof currently excludes that. Keep the stack-state mismatch
YELLOW and the candidate unchanged.

## Compiled-object cross-check (2026-09-27)

Inspected the archived MSVC x86 `/O2` object listed for this translation unit
in `build/compile-report.json` (`build/obj/100076d0.obj`, SHA-256
`0A0BB9879F002CAA9B7519B7E5180365197894C668A6EFF25229D47689B5B27C`).
The COFF `.text$mn` section starts with the compiled `FUN_100076d0` body.
The generated code writes zero to one stack slot unconditionally at object
offset `0x25` (`mov dword ptr [esp + 0x14], 0`), then overwrites that slot
from the context-derived value only on the non-null path at offset `0x60`.
This independently confirms that the current C++ initializer survives the
compiler and that the object preserves both writes. The original Ghidra
listing has only the conditional write to `[EBP-8]` at `0x1000770e`.

This is not a byte-for-byte comparison: the object has compiler-generated
stack-cookie/prologue code, COFF relocations, and a different frame layout.
It does confirm that the YELLOW is a real emitted stack-state difference,
not merely ReAgent's source-level interpretation. It does not establish
whether an indirect callback can take the null-to-nonnull re-entry path at
runtime, so neither removing the initializer nor marking this finding green
is justified by this check.

## Later source/object correction (2026-09-28)

This current-source follow-up supersedes the older emitted-object/initializer
finding above; it is recorded in
[`100076d0-model-info-array-index-fix-2026-09-28.md`](100076d0-model-info-array-index-fix-2026-09-28.md).
The current candidate uses a naked entry bridge with the target-shaped frame
and routes the shared `[EBP-8]` slot through the implementation. A fresh
Ghidra/object review also found and fixed the missing model-info pointer
dereference and per-item `0x354 + index * 0x14` offset. Strict compile,
objective, parity, and a fresh full-object diagnostic link all pass after that
change. Live RenderWare callback/re-entry behavior remains unobserved; retain
that runtime uncertainty and do not infer semantic completion from green
structural gates.

## Ghidra stack-slot/control-flow detail (2026-09-27)

Re-read the exported Ghidra instruction listing for `100076d0.json` directly. At `0x100076d8` it loads `DAT_1003c1fc`; the branch at `0x100076e1` skips the only early write to `[EBP-8]` at `0x1000770e` when that context is null. Before the later context test at `0x10007c4b`, the function contains register-indirect calls at `0x10007861`, `0x100078ae`, `0x100078fc`, `0x1000794c`, and `0x10007a1b`. If any callback can re-enter the hooked path and set `DAT_1003c1fc` from null to non-null, control can pass the test at `0x10007c4b` and consume `[EBP-8]` at `0x10007c54` without the early write. The dynamic targets and re-entry behavior are unresolved, so this is a credible but not runtime-confirmed hazard. On a separate later path, Ghidra reuses `[EBP-8]` for a loop-derived index at `0x10007e22`; this reinforces that the stack slot is lifetime/path-sensitive rather than a simple always-valid context local.

The candidate source's zero initializer is therefore not a cosmetic compiler-warning fix: it changes the value observed if that null-to-non-null transition occurs. Removing it would, in turn, introduce a C++ indeterminate-value read and cannot be justified as a safe source-level correction without a controlled machine-code experiment. Keep the finding YELLOW and the candidate unchanged pending a stronger resolution; no new runtime claim is made here.
