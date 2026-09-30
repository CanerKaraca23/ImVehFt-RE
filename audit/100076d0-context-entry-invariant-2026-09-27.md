# `100076d0` context-at-entry invariant review

Date: 2026-09-27. This review checks the specific `DAT_1003c1fc` zero-to-
nonzero transition that could make the target's conditionally initialized
stack slot differ from the candidate's zero-initialized local. Evidence is
from the installed `ImVehFt.asi` and `gta_sa.exe` Ghidra databases and bounded
read-only Ghidra output. No PDB data or candidate source edits were used.

## Statically supported normal path

1. The GTA vehicle parent at `0x00553260` dereferences its vehicle argument
   immediately (`[ESI+0x36]`, then the object's vtable), and reaches
   `0x006d64f0` only for the vehicle state where `state & 7 == 2`.
2. The only recorded direct GTA caller of `0x006d64f0` is that parent call at
   `0x005532a9`. Calls to the parent from GTA are at `0x00553c52`,
   `0x00553cb8`, `0x00553d8f`, and `0x00732c48`; read-only decompilation
   classifies their containing functions as vehicle/model render/update paths.
   See [`gta-sa-parent-caller-functions-2026-09-27.c`](gta-sa-parent-caller-functions-2026-09-27.c)
   and its xref table.
3. In `0x006d64f0`, the hook site at `0x006d6617` receives the vehicle object
   pointer before the callback dispatcher call at `0x006d662b`. ImVehFt's
   patch redirects that setter call to `FUN_100074d0`; the candidate setter
   reads fields from `param_1` and stores `param_1` to `DAT_1003c1fc` before
   returning. A null vehicle pointer is not a viable execution of this path:
   both the GTA parent and setter dereference the object.
4. The GTA callback dispatcher at `0x004c8430` has one recorded direct caller,
   `0x006d662b`, and supplies the patched callback address for
   `FUN_100076d0`. Thus the known direct path writes a non-null context before
   `100076d0` enters. Decompilations of `0x004c8c90`, `0x004c8430`, and
   `0x004c83e0` are preserved in
   [`gta-sa-setter-and-dispatcher-review-2026-09-27.c`](gta-sa-setter-and-dispatcher-review-2026-09-27.c).

Under this known path, the entry guard that conditionally initializes
`100076d0`'s stack slot is taken. Consequently, the extra zero initialization
in the current candidate is overwritten before any intervening call, and a
later re-read of a context changed to another non-null vehicle does not create
the previously suspected zero-to-nonzero/uninitialized-slot case. This
substantially narrows the concrete semantic concern behind ReAgent's warning.

## Why this does not clear the warning

The proof is limited to recorded direct references and the current hook
patches. It cannot exclude computed callback targets, unscanned/late-loaded
modules, live code patching, or runtime control flow not represented in the
static xrefs. The reconstructed DLL is not integrated or loadable at the
original image addresses, and no candidate plugin/game session was
instrumented. The ReAgent parity warning is therefore retained as YELLOW; the
candidate's `local_c` initializer is not removed, because doing so would
reintroduce an uninitialized C++ read on any unmodeled zero-context route.

## Reproduction artifacts

- `gta-sa-parent-caller-functions-2026-09-27.c/.csv`: read-only Ghidra
  decompilation and incoming references for the three recorded GTA callers of
  `0x00553260`.
- `gta-sa-setter-and-dispatcher-review-2026-09-27.c/.csv`: read-only Ghidra
  decompilation and xrefs for `0x004c8c90`, `0x004c8430`, and `0x004c83e0`.
- `gta-sa-vehicle-callback-parent-553260-20260927.txt` and
  `gta-sa-100076d0-dispatch-caller-6d6617-20260927.txt`: instruction listings
  around the vehicle parent, setter hook, and callback dispatch.
- `1003c1fc-reference-map-2026-09-27.csv`: reference-binary literal reads and
  writer for the ImVehFt context global.
