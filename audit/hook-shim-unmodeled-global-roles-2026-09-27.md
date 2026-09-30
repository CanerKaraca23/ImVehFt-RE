# Ghidra triage of 13 hook-shim globals absent from candidate source text

Date: 2026-09-27. Scope: the 13 `.data` addresses used by supplemental hook
bodies that have no candidate global name and no literal-address or Ghidra-alias
hit in any of the current 705 `src/functions/*.cpp` files. The Ghidra label,
code-unit text, global xrefs, and startup bytes are joined in
[`hook-shim-data-snapshot-2026-09-27.csv`](hook-shim-data-snapshot-2026-09-27.csv).
The table records only what the machine instructions establish; descriptive
roles are intentionally not promoted to recovered semantic names or C++ types.

| Address | Ghidra code unit / startup | Observed access in bounded hook code | Safe conclusion |
|---|---|---|---|
| `0x10037508` | `undefined2 FFFFh` | In `10004B10`: one 16-bit read, then three 16-bit writes. | Mutable 16-bit state initialized to `0xFFFF`; semantic meaning unknown. |
| `0x1003BBB8` | `undefined4 0`; zero-filled | `10008780` passes its address to a helper and later loads a dword from it. | Four-byte global cell whose address and value are both consumed; pointee/type unknown. |
| `0x1003BC10` | `undefined4 0`; zero-filled | `10008780` passes its address to a helper and later loads a dword from it. | Four-byte global cell; semantic meaning unknown. |
| `0x1003BC14` | one zero-filled dword | `100031E0` stores ESI; no read is present in the recorded whole-program xref set. | A 32-bit saved value is written, but its consumer/lifetime is unresolved. |
| `0x1003BC28` | `undefined4 0`; zero-filled | `10008780` passes its address to a helper and later loads a dword from it. | Four-byte global cell; semantic meaning unknown. |
| `0x1003BC2C` | `undefined4 0`; zero-filled | Three hook entries store ESI; two paths read the saved dword. | Shared 32-bit ESI snapshot. Pointer-like use is plausible, not proven as a declared pointer type. |
| `0x1003BD84` | `undefined4 0`; zero-filled | `10007F90` stores EAX returned by `FUN_10008E00`; later dereferences `[value+0x28]` and a byte at `+0x325`. | The returned value is used as a base address in this path; exact structure/type unresolved. |
| `0x1003BD88` | `undefined4 0`; zero-filled | `10007F90` saves ESI and reloads it for object-field access, including `+0x460`. | Saved ESI/context base; semantic object type unresolved. |
| `0x1003BD94` | `undefined4 0`; zero-filled | `10008780` stores EAX returned by the `0x7FB230` call and later reloads/passes it. | Four-byte call result retained across later calls; semantic type unresolved. |
| `0x1003C1F0` | `undefined4 0`; zero-filled | `10008780` stores a call result; `10008830` overwrites it from EAX; multiple hook paths reload it and use it in indexed table stores. | Shared four-byte context/value, with write sites in two shims; exact producer/consumer contract unresolved. |
| `0x1003C200` | `undefined4 0`; zero-filled | `10008780` saves EAX from the `0x7CF9B0` call, reloads it, and passes it to subsequent calls. | Four-byte helper result used as an argument/base; semantic type unresolved. |
| `0x1003C204` | `undefined4 0`; zero-filled | `10008780` passes its address to a helper, then loads and passes the stored dword. | Four-byte global cell; exact ownership and pointee type unresolved. |
| `0x1003C258` | undefined 32-bit float; zero-filled | `10007F50` performs `FCOMP` against this address. | Read as a 32-bit floating value by this hook; producer and semantic meaning unresolved. |

## Consequence

All 13 are real default-labeled Ghidra data symbols, not merely a missing-name
formatting issue: the current candidate source text has no direct address or
alias occurrence for any of them. The xrefs provide partial access roles, but
do not establish the full state lifetime, function ownership, or all runtime
readers/writers. `0x1003BC14` is especially incomplete because the recorded
module xrefs show a write without a corresponding read. Do not define dummy
globals or assign semantic names solely from these hook slices. A relocatable
plugin must preserve/map this state block and verify every consumer, or prove
the corresponding original routines can be rebuilt without those shims.

The status is therefore still: hook-target code is byte-recovered, but these
13 state cells are not represented by the 705 candidate sources; shim/global
integration and runtime tests remain incomplete. No candidate source was
changed by this triage.

## PE data-section relocation impact

Parsing the input ASI's PE32 section headers and base-relocation directory
shows `.data` at RVA `0x29000`, virtual size `0x1455C`, raw size `0x10A00`.
Thus its final `0x3B5C` bytes are loader-zero-filled; 29 of the 30 referenced
`.data` cells fall in this virtual tail, and the one raw-backed referenced
cell is `0x10037508` with initial word `0xFFFF`. This agrees with the byte
snapshot and explains why a file-offset-only dump would miss most of this
state.

The original PE's relocation directory contains 4,708 entries: 4,681
`HIGHLOW` relocations whose stored values point inside the original image, and
27 `ABSOLUTE` padding entries. Of those `HIGHLOW` entries, 274 patch sites are
in `.data` (3,160 in `.text` and 1,247 in `.rdata`). A future rebuild that
copies or moves the original data state must preserve/recompute those
data-section pointer fixups as well as the 139 shim instruction operands;
the shim fixup manifest alone is not a complete PE relocation solution.
Counts come from the input ASI's PE section table and base-relocation blocks,
with values checked against the original image range. Reproduce them with
[`inspect-asi-base-relocations.py`](../scripts/inspect-asi-base-relocations.py)
and [`asi-base-relocations-2026-09-27.json`](asi-base-relocations-2026-09-27.json).
No image was modified.
