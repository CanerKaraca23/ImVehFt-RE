# Fresh Ghidra recheck of `FUN_100076d0`

Date: 2026-09-27. Input: the supplied `ImVehFt.asi`, re-imported into a
temporary Ghidra 12.1.3 project. The checks used `-noanalysis` and a bounded
control-flow traversal; this is not original source recovery or runtime proof.

## Bounded decompilation

`GhidraBoundedDecompileSeeds.java` followed the CFG from `0x100076d0` with a
2,000-instruction cap. It reached 761 instructions / 2,174 bytes and the
decompiler completed. The output independently confirms that the initial read
of `DAT_1003c1fc` guards the only early initialization of the context-derived
stack local `iStack_c`. Later paths reread the global and use that stack local.

- [`100076d0-bounded-cfg-2026-09-27.csv`](100076d0-bounded-cfg-2026-09-27.csv)
- [`100076d0-bounded-cfg-2026-09-27.c`](100076d0-bounded-cfg-2026-09-27.c)

## Dispatch and remaining uncertainty

A separate direct-call survey reached four entries and 117 instructions to
depth 2, recording four direct edges, including calls to `0x10009360` and
`0x10001fb0`. It does not resolve callback targets selected through runtime
data. The main CFG also calls the GTA texture callback at `0x74dbc0` on several
material-name branches before later context checks. The independent GTA trace
[`texture-callback-call-audit-2026-09-27.csv`](texture-callback-call-audit-2026-09-27.csv)
shows that this route reaches RenderWare destruction and a registry-dispatched
callback (`CALL [ESI+0x24]`).

The separate ImVehFt MEXT registration fragment has no incoming static
reference, so its own three MEXT callbacks are not proven active. Callbacks
registered by other loaded modules and their runtime effects remain
unresolved. Thus the fresh pass confirms the conditional-stack-store mismatch
and a callback-dispatch route, but does not prove that a null-to-nonnull
re-entry occurs.

No candidate source was changed. Keep the zero initialization and the ReAgent
YELLOW finding: removing the initializer would introduce a C++
indeterminate-value read, while retaining it is a real emitted-code difference
if the unproven re-entry occurs. Resolve the callback/runtime invariant or
find a controlled machine-level representation before changing this candidate
or clearing the warning.

## Evidence correction (2026-09-27)

The statement above that ImVehFt's MEXT registration lacked a loader route is
superseded by `rw-registry-trace-2026-09-27.md`: DllMain registers callback
`0x10001850` through the internal dispatcher at index `0x0f`, and the installed
ImVehFt log records the matching `Attaching texture maps plugin...` and
`Finished (96).` messages (log timestamp 2026-09-11). This proves historical
execution evidence, not latest-session/live-registry state. Also, the five
register-indirect calls in the yellow window do not share one target: four
call `RwTextureDestroy` (`0x74dbc0`), and the fifth calls
`RwTexDictionaryFindNamedTexture` (`0x7f39f0`). Only the former callback path
retains the re-entry uncertainty. The source remains unchanged and the YELLOW
finding remains open.

## Reproduction

```powershell
& "C:\Users\caner\Downloads\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat" `
  "$env:TEMP" ImVehFtYellowAudit `
  -import "C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi" `
  -noanalysis -scriptPath "scripts" `
  -postScript GhidraBoundedDecompileSeeds.java `
  "audit/100076d0-bounded-cfg-2026-09-27.csv" `
  "audit/100076d0-bounded-cfg-2026-09-27.c" 2000 0x100076d0 `
  -deleteProject
```
