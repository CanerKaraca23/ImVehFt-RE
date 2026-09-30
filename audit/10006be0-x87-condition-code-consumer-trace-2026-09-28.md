# `10006be0` x87 condition-code consumer trace

Date: 2026-09-28

This checks the remaining C0/C1/C2/C3-only observations from the targeted
original-binary differential. The Ghidra export used is
`ghidra_exports/10006be0.json` (SHA-256
`C565BAF19B714A9CE32655AD421F3F5182076CC9F7FAD13BCA4D571953A58AFF`) for the
hash-pinned original ImVehFt image.

## Observed call chain

Ghidra lists one direct caller of `FUN_10006be0`: `FUN_10005860`. That caller
has one caller, `FUN_100074D0`; Ghidra records `FUN_100074D0` as a data
reference from `FUN_10002210` (callback registration), not a direct call.

- At `0x10005B1B`, `FUN_10005860` calls `FUN_10006BE0`. It then performs
  integer-only cleanup/index operations and calls `FUN_100060D0`; its Ghidra
  assembly contains no `FNSTSW`/`FSTSW` read.
- `FUN_100060D0` has five `FNSTSW AX` sites. In each path, an `FCOM` or
  `FCOMP` immediately establishes fresh x87 condition codes before the status
  word is read. It does not consume the incoming `FUN_10006BE0` condition
  codes.
- After `FUN_10005860` returns to `FUN_100074D0` at `0x100076B8`, the latter
  performs integer stack/register cleanup and returns at `0x100076C6`; its
  Ghidra assembly contains no x87-status read.
- `FUN_10002210` installs `0x100074D0` as a callback value. The actual
  external callback invoker and its post-callback machine-state use are not
  present in this internal call chain.

## Conclusion and boundary

This trace found no in-module consumer of the condition codes before they are
overwritten on the analyzed paths. That supports treating the C0/C1/C2/C3
differences as non-semantic for this plugin-internal path, but does not make
the original and candidate full machine states identical. The external
callback caller is not covered by these Ghidra exports or the synthetic
harness, so live GTA/RenderWare behavior remains open.

The differential still reports the raw difference: 1,354 condition-code-only
cases in each 32,720-pair run, with no other recorded observation mismatch.
No candidate source or installed ASI was changed by this trace; no in-game
test was run.
