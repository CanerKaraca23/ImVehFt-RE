# COMDAT candidate-entry name normalization

Date: 2026-09-28. Reviewed the 29 entries previously classified as
unique-public-symbol inferences in the candidate COMDAT ordering report.

## Finding and correction

Two auto-labeled Ghidra functions were false negatives caused solely by
hexadecimal case in MSVC x86 symbols:

- `10014d65`: Ghidra name `FUN_10014d65`; COFF symbol `_FUN_10014D65@0`.
  The candidate is `void __stdcall FUN_10014D65(void)`, and the Ghidra listing
  is `PUSH 0xd; CALL 0x10017cd2; POP ECX; RET`; candidate source makes the
  same call with `0xd`.
- `10014d6e`: Ghidra name `FUN_10014d6e`; COFF symbol `_FUN_10014D6E@0`.
  The Ghidra listing is the same wrapper with `0xc`; candidate source makes
  the corresponding call with `0xc`.

Updated only `is_candidate_entry` so automatic `FUN_<8-hex-address>` names
compare case-insensitively. Named library/C++ matching remains case-sensitive,
and generated `_impl`, `_call_bridge`, `_relocatable_entry`, and `_usercall`
symbols remain excluded. The C++ candidate bodies were not changed. A
pre-change helper backup is `scripts/generate-candidate-comdat-order.py.pre-
case-insensitive-fun-entry-20260928.bak`.

Five focused unit tests pass. Regenerating from the same 705 x86 objects
changes the audit classification from 676 matched / 29 inferred to
**678 matched / 27 inferred**, with zero ambiguous entries. The emitted 746-
symbol order file is byte-identical to v9 (SHA-256
`0EF433EE9456DB5A5596719ADEC4A345529F239E66F82637920C4420BD6FCAA9`), so the
already-successful v9 ordered diagnostic link remains applicable to exactly
the same ordering. New artifacts:

- `audit/candidate-comdat-order-v10-2026-09-28.json`
- `build/recheck/candidate-comdat-order-v10-20260928.order`
- `tests/test_candidate_comdat_order.py`

## Limits

This resolves a symbol-name classification bug, not the other 27 inferred
entries and not original RVA placement. It does not add semantic/runtime
proof or make the diagnostic DLL loadable as an ASI.
