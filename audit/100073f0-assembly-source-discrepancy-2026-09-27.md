# Ghidra-driven x87 corrections: `1001b380` and `100073f0`

Date: 2026-09-27. No PDB lookup was performed. The original candidate files
were backed up before editing; see the matching `.pre-ghidra-exact-x87-20260927.bak`
files beside each source.

## Corrections made

`src/functions/1001b380.cpp` had modeled the incoming x87 value as a C++ local
and used `FSTP`, which popped `ST(0)`. The target at
`ghidra_exports/1001b380.json` uses `FST qword ptr [ESP]` (non-popping), calls
the conversion/error helper and sine path, and returns with the x87 result
still live. The candidate is now a naked MSVC x86 routine preserving that
control flow and x87 stack behavior.

`src/functions/100073f0.cpp` had expressed the trig wrappers as ordinary C++
`long double` calls. That obscured the live `ST(0)` input and omitted the
target's initial computation using `0x10024eb8` and `0x10024e70`. It is now a
naked x86 assembly transcription of the Ghidra listing. Its compiled COFF
disassembly has the same instruction sequence and length (`0xd9` bytes) as
the listing; relocations remain for the three globals and two internal
helper calls. The final call to the fixed game address `0x00707390` remains
an unresolved integration constraint, not a standalone link/runtime proof.

## Verification after the edits

- MSVC 2022 x86 `/O2 /W4 /WX /MT`: fresh full-set compile, 705/705 passed;
  report `build/strict-all-exact-x87-full-20260927.json`.
- ReAgent objective verifier: 705 PASS / 0 FAIL / 0 UNKNOWN;
  report `audit/objective-independent-exact-x87-full-2026-09-27.json`.
- ReAgent parity: 704 GREEN / 1 YELLOW / 0 RED; both corrected routines are
  GREEN in this heuristic report. The one yellow remains `100076d0`;
  report `build/parity-exact-x87-full-2026-09-27.json`.
- The first implementation draft of `100073f0` failed MSVC inline-assembler
  operand syntax. It was corrected before the successful object build; this
  is not an unresolved source error.

These checks establish successful translation-unit compilation and, for
`100073f0`, close instruction-sequence correspondence to the exported
assembly. They do not establish a linked production plugin, whole-set
semantic equivalence, correct fixed-address integration, or in-game
behavior.

## Still open: `10006be0`

The assembly around `0x10006d89`-`0x10006dea` prepares many stack values,
including reads from `0x10024f10` and `0x10024f28`, before the call to
`0x006fc580`. The current candidate models that call as a one-`int`
function-pointer invocation, and the Ghidra decompiler also simplifies the
call. The local 2014 Plugin-SDK snapshot (`_sdk_history/snapshot-2014-04-27/
src/sdk/game_sa/CCoronas.cpp`) identifies `0x006fc580` as
`CCoronas::RegisterCorona` with 21 four-byte stack arguments. The original
assembly's `ADD ESP,0x54` is exactly 84 bytes, corroborating that signature.
The former candidate call was therefore materially incomplete. The source now
declares the 21-argument `RegisterCorona` signature and supplies the stack
arguments for both the mode-2 path and the helper-alpha paths. The strict MSVC
x86 compile of `10006be0.cpp` succeeds. This closes the one-argument-call
defect, but is not a semantic validation of the full routine.

There is a second input-flow mismatch. Ghidra saves entry `EAX` to `EBX` at
`0x10006bef`, later uses that saved value while building the corona ID and
attachment arguments, and the target's cdecl stack has an additional value
at `[EBP+0x34]` that is used during argument preparation. The candidate
instead captures `EAX` after calling `0x0059c790`, and declares only 11 stack
parameters. Cross-function evidence resolves the caller side: Ghidra's
`10005860` listing explicitly sets `EAX` from its own `[EBP+8]` before
calling `10006be0`, pushes 12 stack words, and cleans `0x30` bytes after the
call. The twelfth word is the float loaded from the item at `+0x14`. The
current candidate `10005860.cpp` calls with 11 arguments; its independent
MSVC `/O2` object cleans `0x2c` bytes and does not set `EAX` to the caller's
`param_1` before the call. So both the callee's register/stack contract and
the caller's outgoing state differ from Ghidra.

For the `RegisterCorona` call blocks (`10006d1f`-`10006d7a`,
`10006d89`-`10006de8`, and the helper path at `10006df7`-`10006e8b`), reverse
stack order against the SDK signature gives this argument crosswalk:

| SDK argument(s) | Ghidra evidence |
| --- | --- |
| 1-2 | corona id is formed from the signed byte at `[EBP+0x10]`, `0xff00`, and saved entry `EAX` (`EBX`); saved entry `EAX` is also pushed as the entity pointer |
| 3-7 | bytes from `[EBP+0x14]`, `[EBP+0x18]`, `[EBP+0x1c]`, helper result `AL` (or the type-2 byte), then address `[EBP-0x38]` |
| 8 | incoming `param_8` on default and type-2 calls; type-3/type-4 calls use the computed float stored at `10006e4b` |
| 9 | `0x10024f10`, loaded at `10006d37` and stored at `10006d48` |
| 10-14 | constants `1, 0, 1, 0, 0` |
| 15 | constant `0` is moved from the x87 stack at `10006d32` |
| 16-18 | constants `0, 0x10024f28, 0` (`0x10024f28` is loaded at `10006cef` and stored at `10006d2a`) |
| 19-21 | extra stack float `[EBP+0x34]`, then constants `0, 0` |

The x87 stack trace from `FLD [EBP+0x24]` at `10006c9e` and the three call
blocks now ground the source-level callback arguments. This also exposed and
fixed a radius-flow error: the C++ model mutates `param_8` for helper rounding,
but the default/type-2 callback still uses the incoming radius; only the
type-3/type-4 callback uses the computed radius. The candidate captures the
helper's EAX result as alpha and passes the additional fade-speed argument.
The helper's own listing confirms it consumes `ST(0)` and returns the rounded
integer in `EAX`. The source now explicitly constructs this hidden argument at
all call sites. A fresh optimized MSVC object shows the default scaled branch's
`FLD [local14]`, `FILD [param7]`, `FADD ST(0),ST(0)`, `FMULP` sequence, the
unscaled branch's `FILD [param7]`, and the type-3/type-4 branch's `FLD [EBP+24]`
before calling `FUN_1001ba40`; these correspond to the Ghidra x87 inputs.
Remaining work is to compare the final emitted callback stack against the
Ghidra call setup for every path and verify x87 condition behavior including
unordered values. The argument count, radius split, and hidden-x87 inputs are
now represented, but the routine is not yet semantically verified.

The game executable cross-check resolves the consumer: `0x006FC580` substitutes
the type's texture and tail-jumps to `0x006FC180`; the latter reads all three
vector components even when an entity is attached, transforms them through the
entity matrix, and stores the components in the corona record. The vector local
is initialized through an overlapping bulk copy: on the fixed-length path,
the 16-dword object copy starts at `[EBP-0x68]`, and callback argument 7 points
to `[EBP-0x38]`, offset `0x30` into that copy (source dwords 12-14). The
attached-frame path calls `0x7F18B0` as
`RwMatrixMultiply(result, frame->modelling, frame->parent->modelling)`; it is
not a dynamic-length copy. The 2014 SDK header gives the matching RenderWare
API address and `RwFrame` offsets. The candidate had incorrectly modeled this
as `memcpy`, and has now been corrected to multiply by the parent modelling
matrix. `FUN_1001ba40` does not dereference its `ECX` context. A prior note
incorrectly called the vector uninitialized because it searched for direct
stores and missed the overlapping matrix copy. The candidate's compiled
buffer and callback pointer were also four bytes early; the source frame
offsets have now been corrected to match the Ghidra addresses.
Full game-side evidence is in
[`10006be0-register-corona-game-crosscheck-2026-09-27.md`](10006be0-register-corona-game-crosscheck-2026-09-27.md).

A test of capturing entry `EAX` in the first C++ inline-assembly
statement showed the compiler emits its security-cookie prologue first, so
that approach does not capture the incoming register; it was reverted and
preserved as `src/functions/10006be0.cpp.pre-incoming-eax-flow-20260927.bak`.
The source accepts the extra float and caller `param_1` as `param_12` and
`incoming_EAX`; all three `10005860` sites pass them. It also now represents
each `RegisterCorona` invocation with 21 typed arguments. This remains a
source-level reconstruction, not a byte-identical ABI wrapper. Compilation
only proves the translation unit builds; it does not establish equivalence.

The current fresh targeted evidence is: `/O2 /W4 /WX /MT` compile passed,
structural objective PASS, raw whole-set ReAgent parity GREEN for `10006be0`
(the run had 703 GREEN / 2 unadjudicated call-count YELLOW overall). These are
not semantic proof. The earlier “uninitialized vector” concern and the later
“dynamic copy length” theory were both incorrect. The fixed branch copies a
16-dword local modelling matrix; the attached branch composes that matrix with
its parent's using `RwMatrixMultiply`. Fresh Ghidra analysis of GTA's
`0x7F18B0`, the 2014 SDK declaration, and the candidate object's emitted
arguments agree. The corrected file compiled in the 705/705 strict run, passed
the structural objective check, and remained GREEN in the full-set parity run
(704 GREEN / 1 YELLOW overall). Full final-stack parity on each branch, x87
unordered/edge-case behavior, and in-game behavior remain open. The function
remains open.
