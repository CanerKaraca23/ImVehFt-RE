# GTA dispatcher cross-check for `100076d0`

Date: 2026-09-27

The existing GTA SA Ghidra project was reopened headlessly with `-noanalysis`.
No PDB was searched or used.

## Direct references and call order

`gta-sa-xrefs-dispatcher-20260927.csv` records the queried references to
`0x4c8430`, `0x6d6617`, and `0x4c8c90`. The only direct incoming call to
dispatcher `0x4c8430` is at `0x6d662b` in `FUN_006d64f0`. That same function
calls the original target at the hook site `0x6d6617` immediately before
calling the dispatcher. This independently supports the ordinary call order;
it does not establish all-path behavior or the state of live callback tables.

## Dispatcher behavior

Fresh decompilation of `0x4c8430` shows it delegates to `0x749b70` with
callback `0x4c83e0`. `0x749b70` walks a linked list and invokes that callback
for each record until it returns zero. `0x4c83e0` checks a record flag and
dispatches one or two callbacks through `0x74c790`. The mod's patch at
`0x4c8415` replaces the immediate callback pointer `0x4c8220` with
`100076d0`.

Raw outputs: `gta-sa-dispatcher-4c8430-20260927.txt`,
`gta-sa-dispatch-helper-4c83e0-20260927.txt`,
`gta-sa-dispatch-helper-749b70-20260927.txt`, and
`gta-sa-xrefs-dispatcher-20260927.csv`.

## Conclusion

The ordinary dispatcher path is now more precisely explained. This still does
not determine whether nested RenderWare/plugin callbacks during `100076d0` can
re-enter the hook that writes `DAT_1003c1fc`. The candidate remains unchanged;
the stack-slot mismatch remains YELLOW pending stronger static or runtime
evidence.
