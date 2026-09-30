# `100076d0` `stdFunc[5]` plugin-callback follow-up (2026-09-27)

## Scope

This is a read-only follow-up against the existing GTA SA Ghidra project. It
uses the game executable's instructions and Ghidra analysis only; no PDB or
candidate source was used. The purpose was to test whether the plugin
registration callbacks associated with `FUN_007F3170` directly initialize
`RwGlobals.stdFunc[5]` at template address `0x00C97A24` (`RwGlobals` base
`0x00C979C8`, offset `+0x5c`).

## Method and result

`GhidraBoundedDecompileSeeds.java` was run on the existing `raster_audit`
project with `-noanalysis -readOnly`. It completed bounded decompilation for
all 28 requested callback entrypoints (14 registration pairs); the headless
log reports `seeds=28 bounded_functions_decompiled=28`, then explicitly
discarded changes to the read-only program. Reproduction command:

```powershell
& 'C:\Users\caner\Downloads\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat' `
  'C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_project_raster_audit' raster_audit `
  -process gta_sa.exe -noanalysis -readOnly `
  -scriptPath 'C:\Users\caner\OneDrive\Documents\ImVehFt\_repo_update\ImVehFt-RE-publish2\scripts' `
  -postScript GhidraBoundedDecompileSeeds.java `
  'C:\Users\caner\OneDrive\Documents\ImVehFt\_repo_update\ImVehFt-RE-publish2\audit\gta-sa-plugin-callback-init-bounded-2026-09-27.csv' `
  'C:\Users\caner\OneDrive\Documents\ImVehFt\_repo_update\ImVehFt-RE-publish2\audit\gta-sa-plugin-callback-init-bounded-2026-09-27.c' `
  1800 `
  0x008087d0 0x00808810 0x007ede90 0x007ede20 0x0080aa40 0x0080aa50 `
  0x007f16c0 0x007f1660 0x007efef0 0x007eff70 0x007ec780 0x007ec7e0 `
  0x007ee110 0x007ee0b0 0x00802280 0x008024e0 0x007fb370 0x007fb310 `
  0x007f3ea0 0x007f3d00 0x00807c40 0x00807c60 0x0080a780 0x0080a7e0 `
  0x007efe20 0x007efde0 0x00807c90 0x00807d80
```

Artifacts:

- `gta-sa-plugin-callback-init-bounded-2026-09-27.csv` — all 28 seeds report
  completed bounded decompilation.
- `gta-sa-plugin-callback-init-bounded-2026-09-27.c` — temporary Ghidra
  pseudocode, not recovered original source.

The registration path provides a stronger bound for those dynamic offsets.
`FUN_007F3170` passes the callback pairs to `FUN_008084A0` together with
per-plugin extension sizes. The 32-bit value at `0x008E2298` is `0x158`; the
first field of that registry is therefore initialized to `0x158` (the end of
the 0x158-byte `RwGlobals` core template). `FUN_008084A0` computes the next
cursor as `align4(size) + *registry`, saves the old cursor as the plugin
offset, then advances the cursor. Consequently each registered callback's
`param_2` is a plugin-extension offset at or beyond `0x158`, not the core
`+0x5c` slot. This classifies the `RwGlobals + param_2` writes in callbacks
such as `FUN_007FB370` as extension data, not as a possible write to
`stdFunc[5]`.

The 16-byte memory snapshots used to establish the initial cursor are in
`gta-sa-plugin-registry-globals-bytes-2026-09-27.csv`, produced by
`GhidraReadOnlyMemoryBytes.java` in read-only mode. The snapshot also shows
the static template bytes at `0x00C97A24` are zero; that is only the on-disk
initial value, not evidence of its eventual runtime value. No callback body
contains a direct store naming `0x00C97A24` or a literal `RwGlobals + 0x5c`
assignment. This excludes the traced registry extension callbacks as the
writer, but does not rule out a core engine initializer, a different
initialization mechanism, external code, or bulk/indirect writes.

## Whole-listing store-candidate triage

The whole-listing `+0x5c` syntactic scan found 567 stores. Context and
prologue review classified 336 as `ESP`-relative and 92 as `EBP`-relative in
18 functions whose entry sequence establishes `EBP` from the stack pointer
(`MOV EBP,ESP` or `LEA EBP,[ESP-negative]`). The remaining 139 candidates
have a non-stack-looking base: 134 general-register-relative stores and five
`EBP`-relative stores in non-frame functions. They belong to 97 defined
functions, with five additional candidate instructions outside defined
functions.

A read-only owner scan found direct references to the `RwEngineInstance`
root in eight of those 97 functions. A separate incoming-reference pass
covered 467 references to non-stack candidate owners; seven candidate owners
had at least one immediate caller body that also referenced the root. The
union is nine owners, all reviewed from full-function decompilation and
callsite evidence:

- `FUN_00749C50`, `FUN_0074C310`, `FUN_0074CA90`, `FUN_0074CCC0`,
  `FUN_0074D190`, `FUN_0074D6D0`, and `FUN_0074F760` use `+0x5c` within their
  separately allocated/managed RenderWare objects, not at the
  `RwEngineInstance` base. Their direct global references are allocator/free
  operations or other engine services.
- `FUN_0075E310` writes an engine-instance-relative field at
  `DAT_00C9BC60 + 0x5c`. The registered callback `FUN_00807C40` assigns its
  `param_2` to `DAT_00C9BC60`; its registration uses a `0x60`-byte extension,
  whose returned offset starts at or above `0x158`. Thus this is plugin
  extension data, not core `stdFunc[5]`.
- `FUN_007F0360` stores `0x20003` at its argument base `+0x5c`, but its
  immediate caller `FUN_007F0410` allocates a `0x3000e`-tagged object through
  `RwGlobals.memoryAlloc` and passes that object to the initializer.

A further incoming call/jump graph walk to depth three found direct root-xref
ancestors for 13 candidate owners total. It added four owners beyond the
direct/one-hop set above: three at depth two and one at depth three. Full
decompilation and wider instruction context classify their stores as:

- `FUN_004F0000` writes `[EDI+0x5c]` in a subobject with its own vtable; the
  routine also traverses `param_1` fields beyond `+0x43fc`, incompatible with
  the `0x158`-byte `RwGlobals` core object. Its ancestor's RenderWare state
  calls are separate operations, not evidence that this `EDI` base is the
  engine instance.
- `FUN_0053D0B0` writes `param_1+0x5c+i*4` as one element of a four-item
  state array, alongside sibling arrays/fields at `+0x4c`, `+0x68`, `+0x6c`,
  and `+0x9c+i*0x20`. The higher ancestor's engine-state calls do not pass a
  demonstrated `RwGlobals` pointer into this routine.
- `FUN_00576B70` writes a byte flag at `param_1+0x5c` alongside gameplay
  state bytes such as `+0x32`, `+0x33`, `+0x5f`, `+0x60`, and `+0xea`; the
  depth-three ancestor relationship is only a call-graph relation.
- `FUN_00722230` writes a 16-bit field at `param_1+0x5c` among object fields
  at `+0x54`, `+0x58..+0x6c`. Its caller chain performs render-state calls
  separately; those global references do not establish pointer flow to the
  object being initialized.

The walk therefore raises the count of root-related call-graph candidates
from nine to thirteen, but it does not find a core-slot writer or prove that
any ancestor passes the engine-instance pointer. The other 84 of the 97
defined non-stack-looking owner functions have no direct root xref in their
own body or a call/jump ancestor within three levels in this database; five
additional candidate instructions remain outside any defined function.
Multi-hop flows through data references, indirect calls, aliases, or deeper
callers are not excluded.

Reproducible artifacts are `gta-sa-rw-stdFunc5-slot-writer-candidates-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-writer-candidate-contexts-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-ebp-frame-classification-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-owner-global-xref-rank-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-candidate-callers-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-eight-owner-review-2026-09-27.c`,
`gta-sa-rw-stdFunc5-rootcaller-review-2026-09-27.c`, and
`gta-sa-rw-stdFunc5-followup-global-xrefs-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-ancestor-xref-trace-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-multihop-review-2026-09-27.c`,
`gta-sa-rw-stdFunc5-writer-candidate-contexts-wide-2026-09-27.csv`, and
`gta-sa-rw-stdFunc5-top-unclassified-owners-2026-09-27.c`. The supporting
scripts are `GhidraFindFieldStores.java`, `GhidraStoreCandidateContexts.java`,
`GhidraClassifyEbpFieldStores.java`, `GhidraRankFieldStoreOwners.java`,
`GhidraCandidateStoreCallers.java`, `GhidraTraceFieldStoreAncestors.java`,
and `GhidraInspectFunctionAddresses.java`.

This classifies 13 direct-through-depth-three root-related matches; it does
not prove the remaining 84 owner functions or five ownerless non-stack-looking
instructions cannot receive an aliased engine pointer through a longer path.
The saved caller inventory contains 41 incoming call references whose caller
body directly references the root across all syntactic candidates; the
non-stack-looking subset was filtered for the figures above. Therefore
absence of a literal global xref is negative evidence only, not proof of no
alias or indirect flow.

## Address-taken/data-reference follow-up

To cover one gap in that call/jump-only walk, incoming references were also
queried for the 84 remaining defined owners. The inventory contains 14 `DATA`
references across ten owners (plus ordinary call/jump references). Twelve
references originate in data blocks such as function-pointer/vtable tables;
two are code-side address uses/passes. A data reference is not itself proof
that a callback is invoked with `RwGlobals`, so each of the ten owners was
decompiled and its relevant `+0x5c` field interpreted in its local object
context.

The reviewed routines are `FUN_004C75E0`, `FUN_004C95C0`, `FUN_004C9890`,
`FUN_0063C670`, `FUN_0063C770`, `FUN_0063C840`, `FUN_0063DC20`,
`FUN_00644470`, `FUN_0066D050`, and `FUN_00671800`. Their surrounding fields,
constructor/vtable setup, method signatures, and call behavior identify
class/object state rather than the `RwGlobals` core slot. For example,
`FUN_004C75E0` installs `PTR_FUN_0085C5C8` as the object's vptr and clears
`param_1[0x17]` (byte offset `+0x5c`); `FUN_004C95C0` writes a pointer to
`this+0x5c`, and `FUN_004C9890` reads/clears that member. The `FUN_0063...`
and later methods likewise manipulate object flags or state alongside
nearby class fields. This is evidence about the meaning of these ten stores,
not proof that every possible indirect call/data alias in the executable has
been resolved.

Artifacts: `gta-sa-rw-stdFunc5-data-ref-owners-2026-09-27.csv` records the
incoming data/call references, and
`gta-sa-rw-stdFunc5-data-ref-owners-2026-09-27.c` contains the bounded
decompilations. With these ten owners classified as non-core object fields,
74 of the original 97 defined owners and five ownerless instructions still
lacked full base-pointer provenance at that point. A subsequent read-only
inspection of the five ownerless addresses found:

- `0x004A641E` is part of a contiguous sequence assigning adjacent fields
  through `[EAX+0x58]` and `[EAX+0x5c]`; it is consistent with a structure
  initializer, not a standalone engine-global slot write.
- `0x004F11BA` is immediately after a `RET` at `0x004F11B9`; the only
  incoming reference reported for the following epilogue is a conditional
  jump to `0x004F11C1`, skipping this instruction. Treat the apparent store
  as unreachable/overlapped code, not an executed writer.
- `0x0068B172` and `0x0068B56F` access `[EDI+0x5c]` amid object cleanup and
  member-state operations; local listing context supports object fields, not
  the `RwGlobals` base.
- `0x005C5187` indexes `[EBP + EBX*4 + 0x5c]` and immediately reads the same
  indexed slot. Its base provenance was unresolved in the initial pass; a
  later expanded listing traces EBP to `[ESI+0x15c]`, an object-owned table.

The initial read-only address inspection artifact is
`gta-sa-rw-stdFunc5-ownerless-review-2026-09-27.csv`; surrounding listing
windows are preserved in `gta-sa-rw-stdFunc5-writer-candidate-contexts-wide-2026-09-27.csv`.
At that stage the conservative set was 74 defined owners plus this one
ownerless candidate; the expanded follow-up below resolves the latter.
The actual `stdFunc[5]` writer/value and all-path callback/re-entry behavior
remain unresolved; retain YELLOW.

## Deeper call-ancestor follow-up (depths 4–6)

The call/jump ancestor walk was extended from depth 3 to depth 6 using the
same root `0x00C97B24`. It found 15 additional owner/path rows at depths 4–6,
covering 15 distinct candidate owners. This is only a prioritization signal:
the graph records static call/jump ancestry and does not establish argument
or alias flow. All 15 functions were decompiled and their store instructions
matched to the saved listing contexts.

Fourteen local contexts support non-core interpretations:

- `FUN_004AA6C0`, `FUN_004E8290`, `FUN_004EFE50`, `FUN_0051A746`,
  `FUN_0055F4C9`, and `FUN_0055F870` write narrow fields or structured output
  members amid neighboring fields/initialization; they do not name the core
  global or show a passed `RwGlobals` base.
- `FUN_004E7F80`, `FUN_005EDF10`, `FUN_00601DA0`, and `FUN_0063C340` initialize
  objects by setting many adjacent fields; `FUN_0063C340` also installs the
  object's vptr before initializing its state.
- `FUN_0050A970` treats `+0x5c` as a per-object timestamp paired with a float
  timer field at `+300` and global tick `DAT_00B7CB84`.
- `FUN_005C7130` and `FUN_005C7420` write state words in a `0x150`-byte
  buffer allocated by `FUN_005C7590` through the owning object's allocator
  callback. The deeper ancestor route comes through `FUN_005D0820` and
  `FUN_005D0470`, which opens/reads a file and initializes this configuration
  buffer; it does not demonstrate passing the engine-instance pointer as the
  buffer base.
- `FUN_007AC82A` fills a table with code pointers and installs another code
  pointer at `+0x5c`, consistent with an object dispatch-table/state layout.

At this depth-6 review stage, `FUN_005FC4C0` was conservatively unresolved
because its listing began mid-flow and Ghidra showed `ESI`/`EDI` as unrecovered
register inputs. A later cross-block trace below recovers the base. The
original full listing is `gta-sa-rw-stdFunc5-owner-005fc4c0-listing-2026-09-27.txt`;
the flow xrefs are in `gta-sa-rw-stdFunc5-candidate-address-xrefs-2026-09-27.csv`.
These 14 classifications are recorded, with the
full decompilation, incoming-reference and path artifacts, in
`gta-sa-rw-stdFunc5-depth6-owners-2026-09-27.c`,
`gta-sa-rw-stdFunc5-depth6-owners-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-ancestor-xref-trace-depth6-2026-09-27.csv`, and
`gta-sa-rw-stdFunc5-renderstate-ancestors-2026-09-27.c`. After excluding the
14 locally classified false positives, 60 defined owners plus the one
ownerless indexed-store candidate remain unresolved. No candidate source was
changed. `stdFunc[5]` remains YELLOW.

## Extended call-ancestor follow-up (depths 7–9)

The same read-only static call/jump walk was extended to depth 9. It found
nine path rows at depths 7–9, representing eight new distinct owners; none
overlaps the ten owners reviewed through DATA references. Decompilation and
store-width/context comparison support excluding seven of the eight as core
pointer-slot writes:

- `FUN_004AA750` initializes a structured object with a 16-bit `+0x5c` field
  and adjacent state/size fields. `FUN_004EF680` copies that narrow field as
  part of a larger object copy.
- `FUN_004E9CAB` updates a state object field at `+0x5c` alongside fields at
  `+0x58`, `+0x68..+0x7c`, and `+0xe9/+0xea`; the decompiler's unrecovered
  register inputs make it unsuitable as standalone pointer-flow proof.
- `FUN_0050A160` and `FUN_0050E180` initialize many adjacent fields of a
  state structure; the latter's `+0x5c` store is one byte, not a function
  pointer.
- `FUN_0050A9F0` treats `+0x5c` as a per-object timestamp, paired with a
  dynamic subobject index and float state at `+0x12c`.
- `FUN_0067B4E7` installs a vptr and initializes many members of a newly
  constructed object; the candidate store is within that member layout.

`FUN_00517BF0` remains unresolved: the binary has two four-byte stores at
`[ESI+0x5c]`, but its decompile does not recover the relevant ESI provenance
or express those stores as an identified object field. Its deeper root-xref
ancestry alone is not enough to clear it. The decompilation/ref inventory is
`gta-sa-rw-stdFunc5-depth9-owners-2026-09-27.c/.csv`, and the depth-9 owner
paths are in `gta-sa-rw-stdFunc5-ancestor-xref-trace-depth9-2026-09-27.csv`.
The conservative remainder is now 53 defined owners plus one ownerless
indexed-store candidate. The actual `stdFunc[5]` writer/value remains
unidentified; keep `100076d0` YELLOW.

## Extended call-ancestor follow-up (depths 10–12)

The same `-noanalysis -readOnly` call/jump walk reached depth 12 with no
capped searches. It returned six new distinct owners beyond depth 9. Five
have local evidence inconsistent with a `RwGlobals.stdFunc[5]` pointer-slot
write:

- `FUN_004BDB80`, `FUN_004BE7D0`, and `FUN_004C2610` set individual bits in
  one-byte `+0x5c` fields (`OR byte ptr ..., 0x2/0x4`) while processing other
  object/state records. The access width and neighboring operations exclude
  a four-byte function-pointer slot.
- `FUN_0066A100` is an object constructor with a vptr and adjacent fields;
  its `+0x5c` operation is a byte-sized flag-mask update.
- `FUN_00681E70` is an object constructor that initializes fields at
  `+0x59..+0x5e` and `+0x6e`; its `+0x5c` store is one byte.

At the depth-12 stage, `FUN_01561CF0` remained unresolved because its long
ancestor chain did not reveal the destination. The later direct-caller trace
below resolves it as a nested record copy into a fixed object, so it is no
longer counted in the open set. The original depth-12 decompilation and
references are in
`gta-sa-rw-stdFunc5-depth12-owners-2026-09-27.c/.csv`, with paths in
`gta-sa-rw-stdFunc5-ancestor-xref-trace-depth12-2026-09-27.csv`. The
conservative remainder is 48 defined owners plus one ownerless indexed-store
candidate. `stdFunc[5]` remains unresolved; do not upgrade `100076d0` from
YELLOW.

## Extended call-ancestor follow-up (depths 13–20)

The same static caller walk was extended to depth 20. There were no capped
searches and no new owners after the single depth-13 result, `FUN_0050E49E`.
Its decompilation shows a no-argument helper operating through an unrecovered
`ESI` base, calling `FUN_0050A160` to initialize a separate state record, and
writing many fields through the ESI base up to offset `+0x230`. The
`+0x5c` store is within that much larger game-state structure, not evidence
of a write to the 0x158-byte `RwGlobals` core slot. The deep caller chain
still does not establish ESI as the engine-instance pointer. Its evidence is
saved in `gta-sa-rw-stdFunc5-depth15-owner-2026-09-27.c/.csv` and
`gta-sa-rw-stdFunc5-ancestor-xref-trace-depth15-2026-09-27.csv`; the
depth-20 rerun found no deeper additions and is recorded in
`gta-sa-rw-stdFunc5-ancestor-xref-trace-depth20-2026-09-27.csv`.

This leaves 47 defined owners plus one ownerless indexed-store candidate
without sufficient provenance. The actual writer/value remains unknown;
`100076d0` stays YELLOW.

## Conclusion

The traced plugin callbacks and the reviewed direct/deeper/address-taken
syntactic store matches do not write core `stdFunc[5]`; the actual writer and
runtime value remain unidentified. `100076d0` remains YELLOW. Continue tracing
the core RenderWare engine initialization and standard-function table setup,
including copies that could initialize `0x00C97A24`. No candidate source was
changed, and this pass does not establish live-process or in-game behavior.

## Residual-owner listing cross-check (2026-09-27)

A subsequent read-only cross-check of the existing residual decompilation
identified two false positives in the prior unresolved-owner count:

- `FUN_00517BF0`: the exact prologue contains `MOV ESI,ECX`, consistent with
  its `__thiscall` signature. The candidate stores at `[ESI+0x5c]` decompile
  as `param_1[0x17] = param_1[0x1c]`, among adjacent state members. This is
  an object field, not the global RenderWare table slot. The listing is
  `gta-sa-rw-stdFunc5-owner-00517bf0-listing-2026-09-27.txt`.
- `FUN_005B9390`: its entry instructions contain `MOV EBP,ECX`, so EBP is
  the `this` pointer rather than a conventional frame pointer. The candidate
  instruction at `0x005B9526` is `[EBP+0x5c]=EBX`; the decompile shows the
  constructor initializes a larger object with fields extending past
  `+0x110`. The prior stack/register heuristic had incorrectly left this as
  unresolved.

The copy-helper caller trace resolves the prior `FUN_01561CF0` uncertainty.
Ghidra xrefs show `FUN_01561CF0` is reached through thunk `0x0045C4B0`, called
only at `0x0156AE64` by copy routine `FUN_0156AE50`. At `0x015689FC`, the
initializer calls that copy routine with destination `0x00A430B0` and source
`0x00B7CD98`. The copy routine passes destination/source plus four bytes to
the helper, so helper `[param_1+0x5c]` is written to absolute address
`0x00A43110`, not `RwGlobals.stdFunc[5]` at `0x00C97A24`. The routine copies a
record within a larger object and is excluded from the residual.
Reproducible evidence: `gta-sa-rw-stdFunc5-owner-01561cf0-listing-2026-09-27.txt`,
`gta-sa-rw-stdFunc5-caller-0045c4b0-listing-2026-09-27.txt`,
`gta-sa-rw-stdFunc5-caller-0156ae50-listing-2026-09-27.txt`,
`gta-sa-rw-stdFunc5-caller-015689d0-listing-2026-09-27.txt`,
`gta-sa-rw-stdFunc5-struct-copy-xrefs-2026-09-27.csv`, and
`gta-sa-rw-stdFunc5-copy-ctor-path-xrefs-2026-09-27.csv`.

The remaining ownerless indexed-store candidate `0x005C5187` was then
re-examined with a 32-instruction Ghidra listing. The code loads the function's
object argument into ESI (`0x005C509B`), loads EBP from `[ESI+0x15c]`
(`0x005C509F`), and uses `[EBP+EBX*4+0x5c]` as one indexed entry in that
substructure's pointer table. On the null path, it calls the object's allocator
through `[ESI+4]` for `0x404` bytes, stores the returned pointer in that
indexed entry, then zero-initializes 0x404 bytes through the new pointer. This
is an object-owned allocation table, not the fixed `RwGlobals` slot. Ghidra's
address inventory shows the local branch into the candidate from `0x005C5175`
and no direct external reference to the store instruction. Evidence:
`gta-sa-rw-stdFunc5-ownerless-radius32-input-2026-09-27.csv`,
`gta-sa-rw-stdFunc5-ownerless-context-radius32-2026-09-27.csv`, and
`gta-sa-rw-stdFunc5-ownerless-block-xrefs-2026-09-27.csv`.

The `FUN_005FC4C0` base provenance is resolved by its cross-block control flow:
at `0x005FC4A5`, `MOV ESI,ECX` saves the method's object argument; the branch
at `0x005FC4BB` jumps to block `0x00403CAF`, which continues to the block at
`0x005FC4C0` and eventually the candidate store at `0x005FC586`. The prologue
at `0x005FC4A0` saves ESI and the shared tail restores it, confirming these
noncontiguous blocks are one logical method path. In the candidate region,
ESI remains the object base, EDI is initialized from `[ESI]` then advanced by
eight, and `[ESI+0x5c]` is compared/copied alongside the same value mirrored
to `[ESI+0xfc]` and `[ESI+0x23c]`. This is a member-state update, not a write
to the global `RwGlobals` table. Evidence is in
`gta-sa-rw-stdFunc5-parent-005fc4a0-listing-2026-09-27.txt` and
`gta-sa-rw-stdFunc5-005fc4c0-flow-xrefs-2026-09-27.csv`.

At this review stage, the conservative residual was **43 defined owners and
zero unresolved ownerless stores**: the original 47 defined owners minus the
four classified defined owners (`00517BF0`, `005B9390`, `01561CF0`, and
`005FC4C0`). The separate ownerless indexed-table candidate `005C5187` was
also classified and is not part of that defined-owner arithmetic. The true
`stdFunc[5]` writer/value remained unknown; no candidate source was changed
and `100076d0` remained YELLOW.

Follow-up triage then examined 19 additional residual owners and identified
their `+0x5c` stores as transform-array data, short/float/byte object fields,
class constructor members, a static record-array member, CRT exception/signal
TLS state, or keyboard mapping state. Evidence and exact instruction addresses
are recorded in `100076d0-owner-triage-2026-09-27.md`. The conservative
syntactic owner residual is now 24 defined owners and zero unresolved
ownerless stores. The runtime writer/value and all-path callback/re-entry
invariant remain unproven; `100076d0` remains YELLOW.

The subsequent round-two pass classified all 24 then-remaining owners as
object/task fields, resource/path handles, geometry data, parser counters, or
configuration records. Fresh read-only Ghidra runs resolved the final two:
`00538bc0` writes within a caller-constructed `0x960`-byte object array, and
`005bc533` inherits `ESI=this` across its predecessor jump before writing
`[ESI+0x5c]`. Evidence is in
`100076d0-owner-triage-round2-2026-09-27.md` and its referenced live listings.
The 47-owner syntactic residual is now zero; the separate ownerless candidate
was also resolved. This scan closure does not identify the runtime
`stdFunc[5]` writer/value or prove all-path callback re-entry; parity for
`100076d0` remains YELLOW.
