# Installed GTA executable: selected hook-site compatibility probe

Date: 2026-09-27

This is a read-only static check of selected hard-coded patch sites in
`src/functions/10002210.cpp` against the installed
`C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe`.

## Input identity

- File size: 14,383,616 bytes
- SHA-256: `F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`
- PE image base: `0x00400000`; x86 PE

## Findings

The source contains 60 distinct protection-enable write spans in
`FUN_10002210` (paired with protection-restore calls). Mapping every span's
start and declared length through the PE section table found 59 fully within
`.text` and one fully within `.rdata`; none fall outside a file-backed PE
section. The `.rdata` span at `0x0085C5F4` currently contains pointer
`0x004C9680`, which resolves inside the executable image. This establishes
address mapping only, not that each original byte sequence is the intended
signature or that each replacement preserves behavior.

This inventory is reproducible with the standard-library-only checker:

```powershell
python scripts/audit-game-patch-spans.py --exe "C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe"
```

It emits JSON containing the file identity, each span's mapped section and
current bytes, and a nonzero exit code if any span is not file-backed.

Ghidra 12.1.3 was then run with `-noanalysis` and a bounded script that seeds
disassembly only at the 34 contiguous code-write groups (with four isolated
operand-only sites backed up to their known opcode byte). The resulting
[`gta-exe-ghidra-patch-sites-2026-09-27.csv`](gta-exe-ghidra-patch-sites-2026-09-27.csv)
classifies all 60 spans: 30 begin at an instruction under those seeds, 29 fall
inside a decoded instruction, and one has no instruction because it is the
`.rdata` pointer at `0x0085C5F4` (`0x004C9680`). All 34 bounded disassembly
commands succeeded. No whole-program auto-analysis was run for this result.
The instruction-boundary classification is conditional on the explicit seed
choices; it is a local decode check, not proof that each replacement preserves
the overwritten instruction sequence's behavior.

## ImVehFt hook destinations outside the 705-entry map

The `E8`/`E9` branch writes in `src/functions/10002210.cpp` resolve to 20
unique ImVehFt destinations. Eight destinations exactly match entries in
`audit/function-name-map.csv`; 12 do not. Bounded Ghidra 12.1.3 disassembly
and control-flow traversal was run on those 12 destinations in the original
`ImVehFt.asi` using `-noanalysis`. It visited 337 instructions across the 12
seeds, with no undecoded instructions and no target reaching the 800-instruction
cap. The detailed listing is
[`asi-hook-target-cfg-2026-09-27.csv`](asi-hook-target-cfg-2026-09-27.csv);
the direct branch inventory is
[`asi-hook-target-disassembly-2026-09-27.csv`](asi-hook-target-disassembly-2026-09-27.csv).
Relationships to already reconstructed candidate units are tracked in
[`hook-target-candidate-crosswalk-2026-09-27.csv`](hook-target-candidate-crosswalk-2026-09-27.csv).

These 12 addresses are not all ordinary standalone functions: several are
inline hook bodies that restore state and jump back into GTA code, while others
are helpers with `RET`. Ten register-indirect jump sites across eight target
blocks have unresolved ultimate destinations. The following destinations
have no exact start-address entry in the 705 candidate map:

`0x10004B10`, `0x10008780`, `0x10008830`, `0x10008940`, `0x10007F90`,
`0x10007F50`, `0x10007F70`, `0x10003E40`, `0x10003030`, `0x10003060`,
`0x10003080`, and `0x100031E0`.

The decoded behavior at these entrypoints is enough to classify their role,
but not yet enough to assert full equivalence:

| ImVehFt target | GTA patch site | Static role seen in the bounded listing | Remaining uncertainty |
|---|---|---|---|
| `0x10004B10` | `0x0053BFCC` (`CALL`) | Updates mode globals and returns on three paths | Caller/state conditions and exact candidate counterpart not reconciled |
| `0x10008780` | `0x005D5BC7` (`JMP`) | Initializes RenderWare-related globals, restores registers, jumps to `0x005D5BEA` | Indirect callees and complete object/resource behavior |
| `0x10008830` | `0x005D5C1E` (`JMP`) | Writes mode-specific structures and tail-jumps to `0x005D5C37` | Meaning/validity of each mode and indirect downstream behavior |
| `0x10008940` | `0x005D5AD1` (`JMP`) | Iterates a 16-slot resource table, clears/releases state, tail-jumps to `0x005D5AF6` | Indirect destructor targets and lifecycle behavior |
| `0x10007F90` | `0x006E198E` (`JMP`) | Vehicle-state/float checks; routes back to `0x006E19A1` or `0x006E19C8` | Pool/object validity and runtime path coverage |
| `0x10007F50` | `0x006E18DA` (`JMP`) | x87 compare/status shim; jumps back to `0x006E18EB` | Exact surrounding instruction/state contract |
| `0x10007F70` | `0x006E1A2D` (`JMP`) | Tests x87 status, conditionally calls `0x10003200`, jumps to `0x006E1A32` | Register/flag contract and runtime branch coverage |
| `0x10003E40` | `0x006FDED6` (`CALL`) | Pushes four constants and calls `0x007FB230`, then returns | Callee semantics and allocation/lifetime handling |
| `0x10003030` | `0x006AB350` (`JMP`) | Stores vehicle pointer, checks model through `0x10004A60`, routes back to GTA | Indirect tail destinations and exact hook-context contract |
| `0x10003060` | `0x006F3AED` (`CALL`) | Clears vehicle flag bit unless a model field equals `0xB`, then returns | Object-layout assumptions and caller coverage |
| `0x10003080` | `0x006F3973` (`CALL`) | Clears two vehicle flag masks unless a model field equals `0xB`, then returns | Object-layout assumptions and caller coverage |
| `0x100031E0` | `0x006E27E6` (`JMP`) | Saves vehicle pointer, calls `0x10003130`, jumps back to `0x006E27EB` | Register/flag contract and exact correspondence to candidate behavior |

### Three hook bodies with no equivalent candidate operation identified

A targeted source search and instruction-level comparison narrows the current
coverage gap. These are hook entrypoints in `.text`, not ordinary entries in
the 705 Ghidra-function export, and they must not be silently counted as
verified by the 705-function parity result:

| Hook body | Exact bounded behavior | Candidate-set comparison |
|---|---|---|
| `0x10007F50` | `FCOMP [0x1003C258]`; `FNSTSW AX`; copies status to `BX`; jumps to GTA `0x006E18EB` | No candidate source references `0x1003C258`; the x87/status handoff is not represented by a matching operation found in the 705 sources. |
| `0x10003060` | `PUSHAD`; saves incoming `ESI` to `0x1003BC2C`; unless `[ESI+0x594] == 0xB`, clears bit `0x10` at `[ESI+0x428]`; `POPAD; RET` | No candidate implements this conditional write. `10004bb0` and `100060d0` read the `+0x428` bit but do not perform this clear. |
| `0x10003080` | `PUSHAD`; saves incoming `ESI` to `0x1003BC2C`; unless `[ESI+0x594] == 0xB`, clears mask `0x18` at `[ESI+0x4A8]` and mask `0x40` at `[ESI+0x428]`; `POPAD; RET` | No candidate source references `0x1003BC2C` or `+0x4A8`; no equivalent pair of conditional clears was found. |

The evidence is bounded Ghidra CFG/decompilation plus a source search, not a
proof that these semantics are absent from every possible indirect path. It is
strong enough to keep full hook coverage open: the 705-function parity result
does not include or validate these three additional behaviors.

### Supplemental exact-byte reconstruction

All 12 bounded hook-target byte streams are now represented separately from
the 705 function TUs: three MSVC x86 naked routines in
[`src/hook_shims/x86_imvehft_hook_shims.cpp`](../src/hook_shims/x86_imvehft_hook_shims.cpp)
and nine additional targets in
[`src/hook_shims/x86_hook_targets_remaining.asm`](../src/hook_shims/x86_hook_targets_remaining.asm).
[`scripts/build-hook-shims.ps1`](../scripts/build-hook-shims.ps1) builds both
objects; [`scripts/verify-hook-shim-bytes.py`](../scripts/verify-hook-shim-bytes.py)
reads the Ghidra CFG CSV and COFF objects and requires exact byte-for-byte
equality with no code-section relocations. On 2026-09-27, all 12 targets
passed, covering 1,449/1,449 bytes. This verifies the bounded instruction
streams, not their image placement, installation, global-data mapping,
complete indirect destinations, or in-game behavior; the 705-source parity
count remains unchanged.

There is also a concrete relinking hazard. In candidate `10002210.cpp`, the
installer writes fixed `CALL rel32` immediates at GTA sites `0x006F3AED` and
`0x006F3973` (`0x0F90F56E` and `0x0F90F708`), which resolve to the original
ASI addresses `0x10003060` and `0x10003080`. A newly linked DLL cannot be
assumed to place replacement code at those old ASI VAs; its link map and
hook-target relocations must be verified before it is eligible for runtime
testing. The current diagnostic link is not that verification.

This establishes a scope gap in the current 705-entry index, not yet a proven
missing behavior in the reconstructed set: some blocks may be represented
through the hook installer or neighboring candidates. They must be reconciled
against their original call sites and existing candidates before adding any new
source unit. The earlier one-instruction temporary-function decompilation
summary (`hook-destination-recovery-2026-09-27.csv`) is only a success record
for starting decompilation and must not be read as full function-boundary
recovery. A newer pass synthesized temporary function bodies from each
bounded CFG and decompiled all 12/12; see
[`hook-cfg-function-recovery-2026-09-27.csv`](hook-cfg-function-recovery-2026-09-27.csv)
and [`hook-cfg-function-recovery-2026-09-27.c`](hook-cfg-function-recovery-2026-09-27.c).
Those are Ghidra pseudocode over bounded CFG bodies, not recovered original
source or authoritative function boundaries.

Reproduce the bounded traversal (run from the repository root):

```powershell
& "C:\Users\caner\Downloads\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat" `
  "$env:TEMP" ImVehFtHookCFG `
  -import "C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi" `
  -noanalysis -scriptPath "scripts" `
  -postScript GhidraHookTargetFlow.java "audit/asi-hook-target-cfg.csv" 800 `
  -deleteProject
```

The listing follows direct in-image conditional/unconditional branches and
fallthrough, but does not follow callees (except their return path) or resolve
register-indirect jumps. It is disassembly evidence, not source recovery,
semantic equivalence, or runtime validation.

The bounded Ghidra run can be repeated with a fresh project name and output path:

```powershell
& "C:\Users\caner\Downloads\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat" `
  "$env:TEMP" ImVehFtPatchSites `
  -import "C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe" `
  -noanalysis `
  -scriptPath "scripts" `
  -postScript GhidraPatchSpanListing.java `
  "src/functions/10002210.cpp" "audit/gta-exe-ghidra-patch-sites.csv" `
  -deleteProject -okToDelete
```

| Site | Original bytes / decoded context | Candidate patch operation | Result |
|---|---|---|---|
| `0x006D6617` | `E8 74 26 DF FF`; `call 0x004C8C90` | Keep `E8`, replace rel32 operand | Opcode/site shape matches the installed executable. The original callee is consistent with the current binary, but this does not establish every downstream behavior. |
| `0x004C8415` | `0x004C8414` is `68`; `push 0x004C8220` with its four-byte immediate at `0x004C8415`; followed by `push ecx; call 0x0074C790` | Replace the pushed immediate with `&FUN_100076d0` | The patch targets the immediate operand, not an instruction entrypoint. The required `push imm32` opcode is present. The pushed callback is passed through the following helper call. |
| `0x005B8FFD` | `E8 BE CB 01 00`; `call 0x005D5BC0` | Rewrite opcode and rel32 operand | Existing `E8` call-site form matches; the replacement destination and behavioral equivalence need separate validation. |

The disassembly was decoded from the installed executable after mapping PE virtual
addresses to file offsets. No binary was modified or executed.

## Scope and limitations

The 60-span pass verifies file-backed mapping and provides bounded instruction
decoding; the table above gives extra-readable context for three key sites. It
does not verify every hard-coded patch's expected precondition or semantics,
full game-version compatibility, ASI initialization, or in-game behavior. It
does not establish that the installed Steam-distributed
1.00 executable is identical to every canonical US 1.0 executable targeted by
2014-era plugins. A complete compatibility gate still needs a systematic audit
of all patch spans against a precisely identified supported executable and an
in-game test with the reconstructed plugin. PDB availability is unrelated to
this check and is not a prerequisite.
