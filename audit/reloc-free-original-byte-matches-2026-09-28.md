# Relocation-free candidate byte comparison

Date: 2026-09-28. The audit compared each complete strict x86 `.xcode` body
against the hash-pinned original at its original VA, limited to candidates that
fit their mapped entry gap, contain zero COFF relocations, and overlap no
original `.text` HIGHLOW fixup.

This initial snapshot has been superseded after exact-byte repairs to both
stack-probe helpers. The fresh scoped rerun now covers 27 candidates, of which
16 are byte-identical and 11 differ. `0x1001b220` is newly byte-identical;
`0x1001b266` is omitted from the zero-relocation subset because its single
REL32 is resolved separately and its fixed-address body is also byte-identical.
See [`reloc-free-original-byte-matches-alloca-probe8-fix-2026-09-28.json`](reloc-free-original-byte-matches-alloca-probe8-fix-2026-09-28.json)
and [`alloca-probe-original-byte-repair-2026-09-28.md`](alloca-probe-original-byte-repair-2026-09-28.md).

- Scope: **28** of the 705 candidates.
- Complete body bytes identical: **15**.
- Complete body bytes differ: **13**.
- Original `ImVehFt.asi` SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Machine-readable per-byte-digest and mismatch-offset report:
  [`reloc-free-original-byte-matches-2026-09-28.json`](reloc-free-original-byte-matches-2026-09-28.json).

Exact bodies are `0x100099e0`, `0x10010120`, `0x10010140`, `0x10010170`,
`0x10010180`, `0x10012e65`, `0x10013a72`, `0x10018f94`, `0x1001b65a`,
`0x1001b68c`, `0x1001c9a5`, `0x1001c9d5`, `0x1002044b`, `0x1002045e`, and
`0x1002046f`.

Whole-body byte identity is strong evidence that those function bodies match
the original machine code at the original address. It does not validate a new
PE layout, changed data/globals, imports, startup, hook interactions, or GTA
runtime. The 13 differing bodies need function-specific control-flow and
behavior checks; byte inequality alone does not imply semantic mismatch.
