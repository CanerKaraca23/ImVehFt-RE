# RenderWare engine-instance lifecycle follow-up for `100076d0`

Date: 2026-09-27. Goal: determine whether the indirect allocator and standard
function calls reached during GTA texture/raster destruction have statically
fixed targets. Evidence is from the installed GTA executable in Ghidra; no
PDB data or candidate source change was used.

## Engine-instance root and writers

A full Ghidra reference pass on `gta_sa.exe` found 2,020 references to the
global at `0x00C97B24`: 2,014 reads and six writes. The writes are in three
functions: `FUN_007F3170` (entry/setup at six recorded stores across the
functions), `FUN_007F2F70`, and `FUN_007F2F00`. The exact sites and owner
functions are in `gta-sa-rw-engine-instance-xrefs-2026-09-27.csv`.

Bounded Ghidra decompilation shows the instance is a pointer, not a fixed
callback struct embedded at the global's address:

- `FUN_007F3170` points it at the `.data` template at `0x00C979C8` before
  engine/device setup.
- `FUN_007F2F70` can allocate a `0x40000` block through the active allocator,
  copy `0x56` dwords from the template, and replace the global with that heap
  instance.
- `FUN_007F2F00` copies the active instance back to the template, restores the
  template pointer, and frees the heap copy.

The bounded instruction/decompilation records are
`gta-sa-rw-engine-instance-writers-2026-09-27.csv/.c`. The addresses
`0x00C979C8`, `0x00C97A24`, `0x00C97B10`, and `0x00C97B24` lie in the virtual
zero-fill tail of the executable's `.data` section (confirmed from the PE
section table); the loader therefore initializes those bytes to zero. The
runtime instance and callback slots are populated by initialization code,
not by file-backed initial pointer constants.
The offsets `RwGlobals.stdFunc[5] = +0x5c` and `RwGlobals.memoryFree = +0x148`
are asserted against the local historical SDK by
`scripts/probe-rwglobals-layout.cpp`.

## What initialization does and does not settle

The bounded init-chain trace shows `FUN_00801FD0` installs four memory
function entries at `+0x134..+0x140` from the supplied table (or game's
defaults). New call-path evidence resolves the separate `+0x144/+0x148` pair
for the observed GTA startup path:

- `RwGlobals` uses template base `0x00C979C8`; therefore the allocator and free
  callback template fields at `+0x144/+0x148` are absolute addresses
  `0x00C97B0C` and `0x00C97B10`.
- The only in-image direct caller of `FUN_007F3170` is `FUN_00619C90` at
  `0x00619C9E`. Its stack setup passes zero as `FUN_007F3170`'s second
  argument (read at callee entry as `[ESP+8]`), selecting writes of
  `0x00801C30` and `0x00801D50` to those template fields. The competing pair
  `0x007F3490/0x007F34B0` is the other mode branch and is not selected on this
  direct GTA startup path.
- `FUN_00745510` returns the table at `0x008D6228`, whose four entries are
  `0x0072F420` (malloc wrapper), `0x0072F430` (CRT `_free` wrapper),
  `0x0072F440`, and `0x0072F460` (calloc wrapper). `FUN_00801D50` implements
  the `RwFreeListFree`-style callback; when a freelist block becomes empty it
  returns that block through `RwGlobals.memoryFuncs[1]` at `+0x138`, i.e. the
  selected `_free` entry. The CRT `_free` path ends in its small-block heap
  routine or `HeapFree`; no ImVehFt callback/re-entry is visible in this
  statically traced path.
- `FUN_007F2F70` copies `0x56` dwords from the initialized template into the
  heap instance, covering both callback fields. This is why a register-based
  whole-program `+0x148` store scan missed the template writes: they are
  absolute stores to `0x00C97B0C/0x00C97B10`.

A fresh read-only bounded decompilation of the direct setup callee
`FUN_00801970` (three instructions) shows only `DAT_008e266c = param_1` and a
return; that call does not initialize `RwGlobals.stdFunc[5]`. Its summary and
pseudocode are `gta-sa-rwglobals-core-init-2026-09-27.csv/.c`. This excludes
one direct setup helper as the slot writer, not the other engine/device calls,
later initialization, or bulk/indirect writes; the actual `stdFunc[5]` writer
and runtime value remain unresolved.

The setup/decompilation artifacts are
`gta-sa-rw-engine-instance-writers-2026-09-27.csv/.c`,
`gta-sa-rw-memory-callback-default-xrefs-2026-09-27.csv`,
`gta-sa-rw-memory-callback-init-caller-2026-09-27.csv/.c`,
`gta-sa-rw-engine-callback-init-context-2026-09-27.csv`,
`gta-sa-rw-default-memory-function-table-2026-09-27.csv`,
`gta-sa-rw-default-memory-functions-2026-09-27.csv/.c`, and
`gta-sa-rw-crt-free-unlock-2026-09-27.csv/.c`. The older setup excerpts remain
in `gta-sa-rw-init-chain-2026-09-27.csv/.c` and
`gta-sa-rw-device-setup-2026-09-27.csv/.c`.

Bounded code confirms that the `+0x148` callback is invoked by GTA's
texture/raster destroy paths and by arena cleanup in `FUN_008020F0`; its
installed target is now statically identified as `FUN_00801D50` on the
observed startup path. The `+0x5c` call remains an unresolved, runtime-selected
`stdFunc[5]` entry and may still have external/plugin initialization or
re-entry behavior. The D3D swap-chain destructor path separately reaches
`IUnknown::Release`; neither its static classification nor the callback trace
observes the live process state.

An additional bounded instruction scan used
`scripts/GhidraScanRwGlobalsOffsets.java` on the 421 distinct function owners
from the full xref set. It visited 58,314 CFG instructions and emitted 280 raw
`+0x5c`/`+0x148` displacement hits; these are candidates, not 280 proven
`RwGlobals` accesses, because the scan does not track register provenance.
The two `CALL [register+0x5c]` hits were then disambiguated: `0x007FB03A` in
`RwRasterDestroy` uses the `RwGlobals` pointer and is the `stdFunc[5]` call in
the path reached from `100076d0`; `0x004CB90B` is a different object's vtable
call through `*_DAT_00C97C28`, not `RwGlobals`. This classification is
supported by `gta-sa-rw-other-stdcall-4cb7c0-2026-09-27.c`. In the destruction
path, the `+0x148` calls at `0x007FB04E` and `0x007F3889` remain indirect
`memoryFree` calls; the scan did not identify a static function-pointer store
that resolves their target. Raw hits are in
`gta-sa-rw-global-offset-uses-2026-09-27.csv`.

## Disambiguation of apparent `+0x5c` stores

A second bounded, binary-only pass decompiled six functions containing raw
`[register+0x5c]` stores that could otherwise be mistaken for writes to the
engine-instance standard-function slot. All six bounded CFGs completed; the
outputs are `gta-sa-offset-store-context-2026-09-27.csv/.c`. They do not write
through the `RwGlobals` base. The functions operate on separate heap/object
bases: `0x749c50` allocates and initializes an object whose `+0x5c` field is
later consumed by `0x74ca90`/`0x74c310`; `0x74d190` reads a stream into that
object family; and `0x74ccc0`/`0x74d6d0` destroy the object's owned buffer and
object. The pseudocode shows the base parameter or allocated object explicitly
(`param_1 + 0x5c`, `puVar1 + 0x5c`, or `iVar4 + 0x5c`), whereas the actual GTA
memory-function call uses `_DAT_00c97b24 + 0x138` (the engine-instance base).
That is the second entry in `RwGlobals.memoryFuncs`, not the distinct
`RwGlobals.memoryFree` field at `+0x148`. This removes these raw displacement
stores from the candidate `stdFunc[5]` writer set; it does not prove there are
no stores via bulk copies, aliases, or other initialization paths.

## Memory-function setup and startup-path `memoryFree` resolution

A further bounded trace followed the successful setup path from
`FUN_007F3170` into `FUN_00801FD0`, `FUN_00804140`, `FUN_008082E0`, and
`FUN_008084A0`. The reproducible output is
`gta-sa-rw-engine-memory-init-2026-09-27.csv/.c` (all six requested CFGs
decompiled within the 1,000-instruction cap). `FUN_00801FD0` writes the four
`RwGlobals.memoryFuncs` entries at `+0x134..+0x140`, either from its supplied
four-function table or from GTA's defaults. `FUN_008084A0` then calls the
`+0x144` allocator and releases a temporary index array through `+0x138`;
these are distinct from `memoryFree` at `+0x148`. The other inspected setup
routines write their listed engine/device fields but do not assign `+0x5c`,
`+0x144`, or `+0x148`.

This bounds the known initialization path. The separate `+0x144/+0x148`
template pair is installed by the caller path described above; the observed
startup argument selects `0x00801C30/0x00801D50`, and the latter reaches the
CRT `_free` wrapper through `memoryFuncs[1]`. This resolves the target for
that statically observed startup path, not the live process or every possible
external/plugin override. The destructor calls at `0x007FB04E` and
`0x007F3889` remain indirect at the call site; possible re-entry on other
paths is not proven or excluded.

To look for a direct assignment, the bounded displacement scan was expanded
to `+0x134`, `+0x138`, `+0x13c`, `+0x140`, `+0x144`, and `+0x148` across the
421 functions referencing the engine-instance root. The reproducible output
is `gta-sa-rw-memory-callback-offset-uses-2026-09-27.csv`: 57,791 instructions
visited and 585 raw hits. The 69 `+0x144` and 95 `+0x148` hits are mostly
indirect calls, not assignments. The only matching `MOV` destinations at
`+0x144/+0x148` in this bounded owner set are `[ESP+offset]` locals in
`FUN_007C51D0`; the engine-rooted writes at `+0x134..+0x140` are the four
assignments in `FUN_00801FD0`. This shows that the bounded register-relative
scan does not independently reveal the absolute template-store initialization
of the `+0x148` target. It does not rule out additional writes through callees,
aliases, or bulk copies on other paths.
The expanded scan is reproducible with `GhidraScanRwGlobalsOffsets.java`
followed by the offsets `5c 134 138 13c 140 144 148`; omitting the optional
offsets retains the original `+0x5c/+0x148` scan.

As an additional false-positive check, a read-only sweep of all 1,410,635
instructions in the existing GTA Ghidra listing found 70 syntactic writes to
`[register+0x144]`/`[register+0x148]`. Candidates are preserved in
`gta-sa-rw-memory-slot-writer-candidates-2026-09-27.csv`; the scan deliberately
does not infer register provenance. A second reproducible read-only Ghidra pass
now records five instructions on either side of every candidate, candidate
instruction references, and references to any containing function entry in
`gta-sa-rw-memory-slot-candidate-contexts-2026-09-27.csv` (70 candidates,
770 listing rows). This contextual sweep refines, but does not close, the
classification:

- 26 stores use `[ESP+offset]`, so those exact writes are stack-relative locals,
  not stores through the `RwGlobals` instance pointer.
- The other 44 use a general register as the base. Sixty-five of the 70
  instructions belong to 37 Ghidra function bodies; the remaining five are
  inside executable `.text` but outside a defined function body. Their exact
  listing windows are preserved, and the ownerless rows are not silently
  treated as functions or discarded.
- All 37 containing functions have bounded full-function decompilation in
  `gta-sa-rw-memory-slot-all-context-2026-09-27.c`. Only `FUN_007C51D0` has
  direct references to the named `DAT_00C97B24` root in that decompilation; its
  two candidate writes are the `[ESP+0x148]` and `[ESP+0x144]` stack locals
  above. This is useful negative evidence, not proof against passing the
  instance pointer as an argument or copying callback fields indirectly.

Full-function context for reviewed non-stack groups shows they target other
state: `FUN_00720930` indexes records
from the table at `0x00C79AA8` (record stride `0x158`); `FUN_007A0301`
allocates `0x800`-byte shader/program work arrays in its argument object;
`FUN_007AA21B`/`FUN_007AAF82` use object fields and a device vtable; and
`FUN_007D61A0` reads/writes image pixel buffers. Context artifacts are
`gta-sa-rw-memory-slot-writer-xrefs-2026-09-27.csv/.c` and
`gta-sa-rw-memory-slot-7d-xrefs-2026-09-27.csv` plus
`gta-sa-rw-memory-slot-7d-context-2026-09-27.c`. The five-instruction windows
are generated by `scripts/GhidraStoreCandidateContexts.java` against the
existing full-analysis GTA project using `-readOnly -noanalysis`. These reviewed
groups are false positives for `RwGlobals`; base provenance for the remaining
non-stack writes, especially the four ownerless non-stack rows, still needs
resolution. This scan still cannot prove the absence of an indirect or bulk
assignment.

## Immediate-caller cross-check for the 37 owners

To test whether any candidate owner is directly called from a function that
also reads the `RwEngineInstance` pointer, a further read-only Ghidra pass
enumerated references to the 37 owner entries and checked each defined caller
body for xrefs to `0x00C97B24`. The full per-reference listing context is in
`gta-sa-rw-memory-slot-candidate-callers-2026-09-27.csv`, generated by
`scripts/GhidraCandidateStoreCallers.java`.

- The 37 owners have 137 incoming references: 134 call references, one
  unconditional jump, and two data references. Two owners have no incoming
  reference in this Ghidra database.
- Of the 135 code references, five originate outside a defined caller function;
  the other 130 are associated with defined caller bodies. None of those
  defined caller bodies has a direct xref to `0x00C97B24`.
- The two data references are not call sites. The five unowned code references
  remain uncertain even though their saved local instruction windows show no
  literal reference to the engine-instance global.

This makes a direct one-hop `RwGlobals` argument path to these candidate owners
less likely, but does not rule out a multi-hop parameter flow, an alias, a
bulk copy, or a callback reached through another object. It is not a proof that
all 44 non-stack writes target unrelated object fields. The allocator/free
callback pair is now explained by absolute template writes, but the unrelated
`stdFunc[5]` target and all-path re-entry invariant remain unresolved; retain
the `100076d0` YELLOW.

## Conclusion and limits

The `RwGlobals` instance is replaceable and runtime initialized. The exact
`memoryAlloc`/`memoryFree` pair and ordinary CRT deallocation path are now
resolved for the observed GTA startup path; no ImVehFt re-entry is visible in
that `memoryFree` chain. The `stdFunc[5]` target used during raster destruction
is still unresolved, and static evidence does not establish the invariant for
all callback/plugin paths. Keep the `100076d0` semantic warning YELLOW and do
not change its local initializer based on this partial evidence.

The bounded output `gta-sa-rw-init-chain-2026-09-27.c` includes one invalid
entry row for `0x007F5F60` whose synthesized function body begins at
`0x004C9AB0`; that row is an overlap artifact and is explicitly excluded from
all conclusions here. All other cited seeds in that file report bounded
decompilation, but remain temporary Ghidra pseudocode rather than source.

## Fresh direct-reference check for the template slot (2026-09-27)

Ghidra 12.1.3 was rerun in read-only/no-analysis mode against the existing GTA
project with `GhidraReadOnlyAddressSymbols.java` for `0x00C97A24` (the template
address of `RwGlobals.stdFunc[5]`) and `0x00C97B24` (`RwEngineInstance`). The
slot address is in `.data`, has no defined symbol or data unit, and has zero
incoming references in the saved reference database. The engine-instance
global has its expected `DAT_00C97B24` label and many incoming references.
The raw two-address result is
[`gta-sa-rwglobals-stdFunc5-live-xrefs-2026-09-27.csv`](gta-sa-rwglobals-stdFunc5-live-xrefs-2026-09-27.csv).

This only rules out a recorded direct reference to the template-slot address;
it does not resolve writes through a runtime `RwGlobals*`, aliases, structure
copies, or the live heap-instance value. It therefore adds no basis to clear
the `100076d0` YELLOW or alter the candidate initializer.

## Bulk-copy coverage follow-up (2026-09-27)

Because the immediate-displacement scan does not see string operations,
`scripts/GhidraRwGlobalsBulkCopyAudit.java` scans all 1,410,635 Ghidra listing
instructions for exact string-move/store mnemonics and index-register
operands. The refined scan found 2,466 string-memory operations total; 135
occur in 51 functions that directly reference an `RwEngineInstance`, template,
or slot root (`0x00C97B24`, `0x00C979C8`, `0x00C97A24`). The refined raw list is
[`gta-sa-rwglobals-string-copy-audit-2026-09-27.csv`](gta-sa-rwglobals-string-copy-audit-2026-09-27.csv).

Within that list, the three operations in the two explicit engine-instance
lifecycle functions are in `FUN_007F2F00` and `FUN_007F2F70`. Their fresh
bounded Ghidra decompilations show complete `0x56`-dword `RwGlobals` structure
copies: active heap instance back to the static template on engine close or
failure, and template to a new heap instance on open (with a restore copy on
failure). Those operations carry/preserve the existing `stdFunc[5]` field;
they do not show an independent callback target being installed. Pseudocode
is in `gta-sa-rwglobals-bulk-copy-owners-2026-09-27.c/.csv`.

The remaining 132 string operations in root-referencing functions are not
classified by this sweep as `stdFunc[5]` writes; the root xref alone does not
prove their destination. The earlier broad `MOVS*` screen
(`gta-sa-rwglobals-bulk-copy-audit-2026-09-27.csv`) over-counted similarly
named non-string instructions and is retained only as superseded raw output.
As an owner-level cross-check, intersecting the 51 refined string-operation
owners with the whole-listing `+0x5c` store inventory yields four functions
and five instructions: `0074CB67` and `0074F8FB` write `+0x5c` in separately
allocated RenderWare objects (the two allocation-backed false positives
already classified in the callback-followup report); `007597BD`, `00814C28`,
and `00814C36` address ESP-relative stack locals. This rules out those literal
`+0x5c` stores as `stdFunc[5]` writes, but does not prove the destination of
each string operation or exclude a bulk copy through an aliased pointer.
This refined scan still is not whole-program register/argument provenance: a
callee receiving an aliased `RwGlobals*` may not itself reference a root, and
bounded decompilation is not runtime observation. The `stdFunc[5]` writer/value
and callback re-entry behavior are still unresolved; retain the YELLOW.
