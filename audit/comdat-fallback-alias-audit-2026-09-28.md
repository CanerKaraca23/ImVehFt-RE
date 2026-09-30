# COFF entry alias audit

Date: 2026-09-28. Continued the review of COMDAT-order entries that do not
literally use the Ghidra function name. All counts refer to the same 705
address-named candidate objects and the same `function-name-map.csv`.

## Alias classes now recognized

- **678 literal name/signature matches.** Automatic `FUN_<address>` matching
  is case-insensitive only for hexadecimal spelling.
- **7 address-bound C++ aliases.** Their sole candidate public code symbol is
  `invoke@FUN_<exact-address>_this...`; each carries the exact target address.
- **4 address-named COFF aliases.** Symbols `_FUN_<exact-address>` identify
  the source target directly even when Ghidra gave it a CRT/FID label:
  `1001415a`, `10014206`, `1001e085`, and `1001e5d6`.
- **7 stdcall identifier-sanitization aliases.** Candidate source replaces
  Ghidra's `@` in the identifier with `_` (legal C++ spelling), while COFF
  retains the separate trailing stdcall `@N`. The matcher requires a
  `__stdcall` Ghidra signature and exact transformed name.
- **9 single-public-symbol inferences remain.** They are not relabeled as
  direct matches. The current generator report lists them individually.

The 8 focused matcher tests pass. The v13 report is
`audit/candidate-comdat-order-v13-2026-09-28.json`; the emitted list is
`build/recheck/candidate-comdat-order-v13-20260928.order`.
Totals reconcile to 705: 678 + 7 + 4 + 7 + 9, with zero ambiguous entries.
The 746-symbol order list has the same SHA-256 as v9
(`0EF433EE9456DB5A5596719ADEC4A345529F239E66F82637920C4420BD6FCAA9`). Thus
the previously successful v9 `/ORDER` link used byte-identical ordering; no
new link result is claimed for v13.

## Boundary

This audits which public COFF symbol is selected for placement. It does not
prove source semantics, original RVAs, private/static helper placement, full
image layout, startup correctness, or in-game behavior. The remaining nine
single-symbol inferences remain explicitly weaker than the address-bound
classes.
