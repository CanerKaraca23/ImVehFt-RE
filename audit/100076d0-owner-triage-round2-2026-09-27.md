# Remaining `stdFunc[5]` owner triage, round 2 (2026-09-27)

This read-only Ghidra pass starts from the 24 defined owners left after the
previous owner-triage report. Candidate `+0x5c` operations were matched to the
full-function decompilation and their object/array use. A matching displacement
alone is not evidence of a write to the fixed `RwGlobals.stdFunc[5]` slot at
`0x00C97A24`.

## Twenty-four owners reviewed (all 24 excluded from the global-slot writer set)

| Store instruction(s) | Function | Evidence from Ghidra decompilation |
|---|---|---|
| `00538cd8` | `00538bc0` | Entry `MOV EAX,ECX` and `ADD EAX,0x2c` establish the base from the function argument. A six-iteration loop advances EAX by `0x190`; on iteration `i=0..5`, the candidate address is `param_1 + 0x2c + i*0x190 + 0x5c`, ranging from `param_1+0x88` through `param_1+0x858`. The caller `00539da0` runs `_eh_vector_constructor_iterator_` with element size `0x28` and count `0x3c`, allocating/constructing `0x960` bytes before calling this initializer. Thus every store lands within that object-owned array, not the fixed global slot. Evidence: `gta-sa-rw-stdFunc5-owner-00538bc0-live-2026-09-27.txt` and `gta-sa-rw-stdFunc5-caller-00539da0-live-2026-09-27.txt`. |
| `005bc684` | `005bc533` | The predecessor listing shows `005bc520` saves `ECX` as `ESI` (`MOV ESI,ECX`) and sets `EBP=ESI+0x18`, then jumps through `00406e9a` to `005bc533`. The candidate block keeps ESI unchanged while initializing many fields of the same instance (`+0x27`, `+0x140`, `+0x5c`, `+0x954`, etc.); therefore `[ESI+0x5c]` is an object member. Evidence: `gta-sa-rw-stdFunc5-owner-005bc533-predecessor-listing-2026-09-27.txt`, `gta-sa-rw-stdFunc5-owner-005bc533-live-2026-09-27.txt`, and `gta-sa-rw-stdFunc5-caller-00406e9a-live-2026-09-27.txt`. |
| `005d2391` | `005d2330` | `__thiscall` copy/update routine copies fields from a source object (`param_2+0x4a0`) into the destination instance, including destination offset `+0x5c`, with adjacent fields copied together. |
| `0061bb34` | `0061bb10` | `__thiscall` object method treats `param_1+0x5c` as flags (`& 8`, `| 4`, `& 8`), passes the value to a task/behavior creation call, then stores its result at `param_1+8`; this is instance state. |
| `006429b1` | `006428c0` | `__thiscall` behavior method accesses a one-byte bitfield at `param_1+0x5c` (`& 1`, set/clear bit 0) while updating adjacent timer/animation values. |
| `00642d61`, `00642d7c`, `00642e3c`, `00642e59` | `00642ae0` | `__thiscall` behavior update repeatedly reads/sets/clears bits in a byte at `param_1+0x5c` (`& 2`, `| 2`, `& 0xfd`) alongside instance timers/flags. |
| `0066aa0a` | `0066a850` | `__thiscall` game-task routine tests and sets bit 0 of `param_1+0x5c`; the same instance owns adjacent vector/position fields used by the task logic. The separate `[ESP+0x5c]` store in this function is a stack local. |
| `0066ebfb` | `0066ebe0` | `__thiscall` state-machine step copies a value from instance `+0x58` to `+0x5c`; both are neighboring instance members and the function then evaluates adjacent state/float fields. |
| `006717dc` | `00671750` | `__thiscall` transform/behavior update clears instance `param_1+0x5c` only when a flag in `param_1+0x4c` is set, alongside clearing `+0x50`, `+0x54`, and `+0x58`. |
| `0068aa2b`, `0068aa5f`, `0068abaf` | `0068a9f0`, `0068aa50`, `0068aa70` | Water-ripple resource lifecycle: `0068a9f0` obtains the resource named `water_ripples` and stores its returned handle at instance `+0x5c`; `0068aa50` releases and zeros that handle; `0068aa70` consumes the instance state in ripple calculations. The writer and destructor form one object-owned handle lifecycle. |
| `0069491d` | `00694850` | Initializes a float/vector data block through `param_1`; `+0x5c` is element `param_1[0x17]` among contiguous geometric values, with later elements initialized and used as a shape/vertex-like array. |
| `006c2f55` | `006c2b90` | `__thiscall` computes model/vehicle geometry in a large output instance: writes surrounding float extents and normalized dimensions at `param_1[0x27..0x32]`; `+0x5c` is member `param_1[0x17]` in that same instance, not a fixed absolute address. |
| `006f9eee` | `006f9eb0` | Initializes a lookup/config record with sentinel `0xffffffff` values across consecutive members, including member `[0x17]`; nearby byte fields are cleared and base member zeroed. |
| `0076b58d` | `0076b567` | Initializes a parser/source object, clearing path/file-related members around offsets `+0x38..+0x70`, including `+0x5c`. |
| `0076b673`, `0076b70a` | `0076b60b` | Source-file loader uses `GetFullPathNameA`, allocates path buffers, stores them in the source object at `+0x5c`/`+0x60`, copies the resolved path, and passes the resulting handle and buffers to the source-opening callback. |
| `0076fafd` | `0076faeb` | Parser/assembler record initializer clears a run of pointer/count members including `[0x17]`; it is a small field reset routine, not a global callback writer. |
| `00770c5f`, `00770c7a`, `00770d0b`, `00770d52`, `00770d9f`, `00770ddc`, `00770e1f`, `00770e4c`, `00770eeb`, `00770f6e` | `00770859` | D3D shader-fragment assembler: the candidate increments occur in instruction/register validation and fragment-link diagnostics; decompilation refers to parser/instruction counters and register tokens, not a RenderWare callback table. |
| `00771251` | `0077107f` | D3D shader assembler/finalization routine; `+0x5c` contributes to accumulated parser/fixup counts used to size and build output tables. |
| `00771538` | `0077129f` | D3D shader assembler/debug-output routine; `+0x5c` contributes to parser/debug record counters while building shader output. |
| `00771834` | `00771724` | Shader register parser: the method parses register names (`v_`, `r_`, `c_`, `b_`, `i_`) and increments `param_1+0x5c` as the temporary-register index/count, then emits a register record. |
| `00789b3e`, `00789c04` | `00789a92`, `00789ba9` | Paired settings/configuration mapper routines store a looked-up setting handle at member `[0x17]` and copy it from an external settings record at offset `+0x5c`; neighboring values and owned arrays/capacities are managed as members of the same mapper instance. |

The exact instruction contexts and owner/caller mapping are in
`gta-sa-rw-stdFunc5-writer-candidate-contexts-wide-2026-09-27.csv` and
`gta-sa-rw-stdFunc5-residual-owners-2026-09-27.csv`; full-function decompilation
is in `gta-sa-rw-stdFunc5-residual-owners-2026-09-27.c`.

## Remaining candidates and limits

No defined owners remain unresolved in this 47-owner syntactic `+0x5c` scan:
the final two (`00538bc0`, `005bc533`) are now tied to object-owned arrays and
instance state by live Ghidra instruction/caller evidence. No source function
was edited. This closes this particular false-positive candidate inventory;
it does not prove there is no differently encoded alias or indirect writer.

This reduces the conservative defined-owner residual from 24 to 0. It does not
identify the live `RwGlobals.stdFunc[5]` writer/value or prove the full indirect
callback/re-entry behavior. Therefore `100076d0` stays YELLOW until those
runtime/all-path facts are established; this triage is not semantic or game
validation.
