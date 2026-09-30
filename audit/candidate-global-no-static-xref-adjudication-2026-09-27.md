# Candidate globals without exact Ghidra xrefs: bounded adjudication

Date: 2026-09-27. The source-vs-Ghidra address inventory found seven
candidate-used addresses with no exact-address symbol or incoming xref in the
existing analyzed Ghidra database. This review compares each with the target
function's assembly; a missing xref alone is not treated as a mismatch.

## `1001c60e` floating-point constants

The candidate names five interior qword values as doubles at `0x10025818`,
`0x10025828`, `0x10025838`, `0x10025848`, and `0x10025868`. Ghidra's assembly
for the same function uses 16-byte aligned vector-memory operands instead:

- `MOVAPD XMM6,xmmword ptr [0x10025820]` and
  `ADDPD XMM6,xmmword ptr [0x10025810]` read lanes covering offsets `+8`
  (`0x10025828`) and `+8` (`0x10025818`) respectively, as well as the two
  base qwords.
- `MOVAPD XMM5,xmmword ptr [0x10025840]` covers `0x10025848`.
- `MOVAPD XMM2,xmmword ptr [0x10025860]` covers `0x10025868`.

The five candidate addresses are therefore lane aliases inside Ghidra's
16-byte operands, not independently addressed memory operands. The lack of
exact-address xrefs is expected; it does not show those constants are missing
or misbased. Exact target instruction evidence is in
`ghidra_exports/1001c60e.json`; the corresponding candidate expressions are
in `src/functions/1001c60e.cpp`.

## `100170b0` runtime-error message table

Ghidra disassembly reads the value table with
`MOV EAX,dword ptr [EAX*0x8 + 0x10023094]` at `0x100170cd` and the key table
from `0x10023090` at `0x100170ba`. This is a register-indexed operand, so the
existing Ghidra xref database has no fixed `0x10023094` incoming reference.
The candidate expression `UNK_10023094[uVar1 * 2]` scales a 4-byte pointer by
two, yielding the same 8-byte record stride. The address and indexing form are
supported by the instruction listing; the complete table contents and all
return-value cases are not revalidated here.

## `10014566` multibyte-character table

Ghidra disassembly at `0x10014679` reads
`byte ptr [EAX + 0x100298cc]`; `EAX` is the loop index in the preceding
control flow. Candidate `DAT_100298cc[range_table]` expresses the same
byte-indexed lookup. As with the runtime-error table, the indexed operand is
not represented as a fixed-address xref by the current Ghidra reference
database. The base address and byte access are supported; this note is not a
full semantic validation of the surrounding routine.

## Result and limit

All seven exact-address xref gaps are accounted for by vector-lane aliases or
register-indexed memory operands in the original listing. No candidate source
change was made. This adjudication is limited to those seven references and
does not replace whole-function behavior checks or production-link/runtime
validation.
