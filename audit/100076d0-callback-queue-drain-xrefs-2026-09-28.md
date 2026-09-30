# `0x100076d0` callback-queue drain xref trace

Date: 2026-09-28. Read-only/no-analysis Ghidra 12.1.3 inspection of the
existing `ImVehFt.asi` project. Original ASI SHA-256:
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Newly mapped static edges

The fresh incoming-reference query is in
`audit/100076d0-queue-drain-xrefs-20260928-queue-trace-rerun.csv`; companion
decompilation is in the adjacent `.c` file. Ghidra confirms these direct edges:

- `0x1000c8f0 -> 0x1000ea80`
- `0x1000c900 -> 0x1000eae0`
- `0x1000c8b0 -> 0x1000e900`
- `0x1000c8c0 -> 0x1000e960`
- `0x1000c8d0 -> 0x1000e9c0`
- `0x1000c8e0 -> 0x1000ea20`

The six `0x1000c8xx` addresses are callback stubs installed by methods such as
`FUN_1000b460`, which passes five callback addresses and five supplied handlers
through `FUN_1000c480`. `FUN_1000c480` resolves/patches each stub to call its
associated handler. The `0x1000ea80` family drains callback arrays around its
central handler call. In particular, `FUN_1000ea80` drains the list at manager
offset `+0x18`, invokes the handler at `+0x10` if present, then drains the list
at `+0x28`.

Earlier Ghidra evidence shows `FUN_1000b4e0` appending the MEXT callback
`0x10001850` into the vector rooted at `DAT_10037788`, which corresponds to the
manager's `+0x28` callback list. This links MEXT callback registration to a
known drain site, rather than leaving the callback consumer wholly unknown.

## Interpretation and remaining uncertainty

The callback is drained when the relevant callback-dispatch stub is invoked;
the static chain does **not** establish which real GTA/RenderWare event invokes
that stub, whether a nested `RwTextureDestroy` during the `0x10001b00` MEXT
destructor causes that dispatch, or whether any external plugin callback can
write `DAT_1003c1fc` or re-enter `0x100076d0`. No runtime registry/order trace
was acquired. Thus this is a narrower static call graph, not proof that the
open callback/re-entry scenario occurs or cannot occur. Keep the semantic
finding for `0x100076d0` **OPEN** and do not alter the candidate based on this
trace alone.
