# `100076d0` MEXT callback to GTA dispatch path

Date: 2026-09-29. Static cross-binary trace using Ghidra 12.1.3 headless, with
the exact GTA executable imported from an isolated copy and no adjacent PDB.
The imported executable SHA-256 is
`F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`; the
reference ImVehFt ASI SHA-256 is
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Static path now established

1. ImVehFt's DllMain process-attach path passes callback address `0x10001850`
   with jump-table index `0xF` to `FUN_1000a560`. The original jump table routes
   index 15 through `0x1000a5c9` to `FUN_1000b4e0`, which appends that callback
   to the vector rooted at `DAT_10037788`.
2. On first use, `FUN_1000b4e0` initializes manager `DAT_1003c3b8` via
   `FUN_1000b460`, with hook-site key `0x0053eca1` and the remaining four keys
   zero. `FUN_1000b460` pairs this nonzero key with stub `0x1000c8c0`.
3. Original `FUN_10009060` is a code-patching helper: it calls `VirtualProtect`,
   writes opcode `E8` at its address argument, and writes the relative call
   displacement to its target argument. Thus the registration above installs
   a call at GTA address `0x0053eca1` targeting `0x1000c8c0`.
4. In the unmodified, hash-pinned GTA image, `0x0053eca1` is entry 2 in the
   six-entry table at `0x0053ecdc`. Function `0x0053ec10` bounds its input at
   `0x26`, then tail-jumps through `0x004018ce`; that thunk loads a byte from
   `[input + 0x53ed08]` and jumps through the table. A fresh Ghidra read of the
   selector byte map confirms event selector `9` maps to table slot 2 and thus
   to `0x0053eca1`. Ghidra xrefs show calls to function `0x0053ec10` at
   `0x00619b6c` and `0x00619cae`; the dispatch thunk has a direct tail-jump
   caller at `0x0053ec1f`.
5. The address/name mapping is independently corroborated by the public
   `gta-reversed` source: `0x0053ec10` is `AppEventHandler`, whose
   `rsPLUGINATTACH` case calls `PluginAttach` at `0x0053d870`; the companion
   Plugin-SDK `RsEvent` enum assigns `rsPLUGINATTACH` value 9 for this game's
   event set. This matches the local selector-byte-map result. Thus the
   installed hook is on the RenderWare `rsPLUGINATTACH` route, not an
   unidentified generic event.
6. Stub `0x1000c8c0` jumps to `0x1000e960`. That dispatcher walks the manager's
   pre-handler list at `+0x18`, invokes its handler at `+0x4`, then walks its
   post-handler list at `+0x28`. The MEXT callback vector rooted at
   `DAT_10037788` is the manager's `+0x28` list. Therefore this path, rather
   than the sibling `0x1000c8f0 -> 0x1000ea80` route cited in the earlier
   queue-xref note, is the statically established dispatch route for this
   manager's registered `0x0053eca1` hook.

## What this resolves—and what it does not

The MEXT callback is not merely present in a queue with an unidentified
consumer: the binary-backed path identifies the GTA patch site, the
`rsPLUGINATTACH` handler route, installed stub, manager handler position, and
post-handler MEXT queue drain. A focused original-vs-candidate differential
for the actual dispatcher `0x1000e960` then passed five fresh x86 processes x
three cases each (15 pairs): normal traversal with a null pre-handler slot,
post-list extension by the central handler, and nested dispatcher re-entry;
callback order and return value matched in every case. The exact runner is
`scripts/test-1000e960-queue-reentry-differential.ps1`. Evidence hashes:

- Candidate source: `A33AC5B64EA205301287BCACC3CB2624D1FE8EA407C4477939F141E03DF06AA1`.
- Harness source: `BD42B91001AB065B80227FE255BC7047BA1432E8042DC2377AF6F0E9902DEEBA`.
- Candidate object: `6CED32D120190477E74A085D43BC36D6EF59E0B74A41996691AB596A2B184F6B`.
- Harness executable: `951979AB98FEAC3571B103C84ECC1D797B5CE58C0BE7BF86C691B3EF817F1685`.

This remains static plus a synthetic queue differential, not a live RenderWare
session. It does not show that a later nested `RwTextureDestroy` from MEXT's
texture-plugin destructor reaches this same hook, identify the actual
runtime handler/callback targets, or prove absence of re-entry into
`0x100076d0`. Keep that separate behavioral issue OPEN/YELLOW; do not change
the candidate based on this trace.

Ghidra run evidence is preserved in
`build/gta-hook-site-audit-20260929/query-3.log`; the isolated input copy is at
`build/gta-hook-site-audit-20260929/input/gta_sa.exe`. The reusable, PDB-free
headless query script is `scripts/ghidra_dump_gta_patch_site.java`. Its first
full analysis completed successfully; subsequent queries reused that project
with `-noanalysis`. External corroboration: [gta-reversed `AppEventHandler`]
(https://github.com/gta-reversed/gta-reversed/blob/master/source/app/app.cpp)
and [Plugin-SDK `RsEvent` enum]
(https://github.com/DK22Pac/plugin-sdk/blob/master/plugin_sa/game_sa/rw/skeleton.h).
No candidate source or original binary was modified.
