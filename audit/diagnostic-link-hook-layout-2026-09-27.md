# Diagnostic DLL hook-address/layout verification

Date: 2026-09-27. This pass inspects, but does not execute or load, the
2026-09-26 diagnostic link:

`C:\Users\caner\OneDrive\Documents\ImVehFt\reports\re-agent\buildcheck\old-sdk-plugin-lib-probe-20260923\out-704-candidates-entrypoint-correctimport\ImVehFtLinkProbeCurrentCandidates.dll`

SHA-256: `09FE84F08AB2BA9C4030E7AAF282E44CD1C9BB993A41C1B7F9538E0255723CD3`.
Its matching map is `ImVehFtLinkProbeStaticAliases.map` in the same output
directory. The link did succeed with zero linker warnings/errors. This audit
shows that success does not make the DLL safe to install or run.

## Actual image layout versus the original ASI

`dumpbin /headers` reports PE32/x86, preferred image base `0x10000000`, image
size `0xA8000` (ending at `0x100A7FFF`), `.text` at
`0x10001000..0x1008417B`, and `.data` at `0x10091000..0x100A1A4B`. The original
ASI has the same preferred base but image size `0x43000`, `.text` ending at
`0x1002127A`, `.rdata` at `0x10022000`, and `.data` at `0x10029000`.

The diagnostic map confirms that candidate symbols are not placed at their
original entry VAs:

| Original symbol/address | Diagnostic map address |
| --- | --- |
| installer `FUN_10002210` | `0x100022D0` |
| `FUN_100074d0` | `0x10007C00` |
| `FUN_100076d0` | `0x10007F70` |
| candidate `DAT_1003c1fc` alias | `0x100A0500` |

The candidate C++ references to these globals are linked through diagnostic
aliases. Original absolute addresses embedded in the unchanged installer or
byte-exact hook assembly are not redirected by those aliases. Also, original
`.rdata`/`.data` addresses such as `0x100249xx` and `0x1003xxxx` now fall inside
the diagnostic DLL's expanded `.text` range.

## Hook target evidence

Ghidra 12.1.3 imported the diagnostic DLL with `-noanalysis` and ran
`GhidraModHookTargets.java` using the existing installer source. It decoded all
20 unique branch destinations from the installer: 20/20 disassembly commands
succeeded, but only 17/20 destinations begin at an instruction boundary in
this new image. The raw decoded output is
[`diagnostic-link-hook-targets-2026-09-27.csv`](diagnostic-link-hook-targets-2026-09-27.csv).
For example, the installer still branches to `0x10003060` and
`0x10003080`, while the diagnostic image decodes those locations as
`LEA EAX,[ESP+0x14]` and an instruction beginning three bytes after
`0x10003080`, respectively. These are not the original helper bodies.

As an independent byte check, I mapped each of the 12 supplemental Ghidra CFG
streams through the diagnostic PE section table and compared it with bytes at
the same original VA in the diagnostic DLL. **All 12/12 targets mismatch from
byte offset zero** (the original expected streams total 1,449 bytes). This is
consistent with the Ghidra disassembly: the link did not integrate or place
the supplemental bodies at their original destinations. The result is
reproducible from `audit/asi-hook-target-cfg-2026-09-27.csv`,
`audit/diagnostic-link-hook-targets-2026-09-27.csv`, and the DLL named above.

A separate full-analysis Ghidra import queried nine of the old destination
addresses for their containing function in the diagnostic image. It found
five containing functions, which further shows why retaining the preferred
base alone is insufficient:

| Old address queried | Function actually containing it in diagnostic DLL |
| --- | --- |
| `0x10003030`, `0x10003060`, `0x10003080`, `0x100031E0` | `FUN_100022D0`, body `0x100022D0..0x10003306` |
| `0x100074D0` | `FUN_10007280`, body `0x10007280..0x10007642` |
| `0x100076D0` | `FUN_10007670`, body `0x10007670..0x10007AB2` |
| `0x10007F50` | `FUN_10007C00`, body `0x10007C00..0x10007F6B` |
| `0x10007F70`, `0x10007F90` | `FUN_10007F70`, body `0x10007F70..0x10008852` |

The queried addresses at `0x10007F70`/`0x10007F90` therefore land in the
relocated candidate body, not the separately intended hook-target bodies.
The full-analysis query output is
[`diagnostic-link-target-functions-2026-09-27.csv`](diagnostic-link-target-functions-2026-09-27.csv),
with the bounded decompilation in the adjacent `.c` file. This query used
Ghidra's binary analysis; no PDB file or PDB-derived symbol data was used.

## Consequence

The diagnostic DLL is evidence that 704 candidate object modules and selected
runtime inputs can be linked under one VS2022 probe configuration. It is not a
loadable/game-valid reconstruction: it does not preserve the original function
entry layout, does not contain all 12 exact hook bodies at their expected
addresses, and its global aliases are at new VAs while fixed installer/hook
references still encode old VAs. Do not put it in the game directory or run
it. Runtime testing remains gated on resolving the image layout, installing
all hook bodies, and retargeting every branch/global reference; original
project/build inputs and game behavior are still unverified.
