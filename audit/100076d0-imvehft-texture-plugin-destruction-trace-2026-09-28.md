# `100076d0` ImVehFt texture-plugin destruction trace

Date: 2026-09-28. Static cross-check of the hash-pinned original ASI and its
Ghidra exports, followed by inspection of the corresponding candidate TUs.
No candidate source or installed binary was modified.

## Registration and callback evidence

The source binary SHA-256 is
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
Disassembly at `0x10001850` calls `RwTextureRegisterPlugin` (`0x007f3bb0`)
with plugin size `0x10`, ID `0x5445584d` (`MEXT`), and callback addresses
`0x10001ad0`, `0x10001b00`, and `0x10001b30` (constructor, destructor, copy).
The registration routine is address-taken from `FUN_10001db0`; its process-
attach path passes it through the index-`0x0f` callback dispatcher. That path
queues a function pointer in the callback manager. The dispatcher’s table
target and the queue insertion were checked against the original `.text`
bytes and Ghidra exports. The exact subsequent queue-drain point is not
established by this bounded trace. The older installed runtime log does
report successful texture-map setup, but it is not a trace of this callback
or of a current session.

Ghidra export behavior for the callbacks:

- `0x10001ad0` initializes the 0x10-byte MEXT record: field `+0` to 1 and
  fields `+4`, `+8`, `+0xc` to 0.
- `0x10001b00` checks the record and, if its `+0xc` field is non-null, calls
  `RwTextureDestroy` (`0x007f3820`) on that owned texture; it then returns the
  record pointer. It has no reference to `DAT_1003c1fc` and no direct call to
  `0x100074d0` or `0x100076d0`.
- `0x10001b30` copies the first three fields. When the source `+0xc` field is
  non-null, it creates an owned texture through `0x007fb230`, applies the
  texture setup call at `0x007f37c0`, and stores the result in the destination
  record’s `+0xc` field.

The reconstructed `src/functions/10001ad0.cpp`, `10001b00.cpp`, and
`10001b30.cpp` retain those observed callback actions. The `10001b00` source
contains the same conditional nested `RwTextureDestroy` operation.

## Effect on the open `0x100076d0` question

This identifies one concrete callback on the texture-destroy path that was
previously treated only as an unknown indirect plugin-table callback. It can
cause a nested texture release, but the known ImVehFt destructor itself does
not directly update `DAT_1003c1fc` or invoke the vehicle-data callback. Its
constructor’s zeroing of the owned-texture slot is consistent with newly
created texture records not recursively owning another texture by default.

This narrows, but does not close, the finding. Other registered texture
callbacks, the live registry contents/order, and runtime behavior during the
nested release are not fully traced. No current gameplay run establishes
whether an external callback can re-enter the vehicle callback path before
`0x100076d0` rereads the global/stack slot. Keep callback/re-entry runtime
status **OPEN**; do not change the candidate on this evidence alone.
