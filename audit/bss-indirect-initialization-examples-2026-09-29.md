# Virtual-only `.data` xref follow-up (2026-09-29)

The 537 COFF relocation references in the zero-filled `.data` tail reduce to 147 original global addresses. The Ghidra xref join in `audit/bss-coff-target-ghidra-xrefs-fresh-425-2026-09-29.json` matches all 147 addresses, with 125 direct-write-xref targets and 22 lacking an explicit `WRITE`/`READ_WRITE` reference in the saved Ghidra export. The latter number is an xref-category gap, not proof that those globals are never written.

## Concrete indirect-write examples

- `0x1003A8C8` is a 0x200-byte module-path buffer: current candidate `src/functions/10001db0.cpp:26` passes it as the output buffer to `GetModuleFileNameA`; Ghidra lists the corresponding global references as `DATA`, not direct writes.
- `0x1003A6C8` is a 0x200-byte derived path buffer: `src/functions/10001e80.cpp:55` writes it via `strcpy_s` from the module-path buffer, then appends the effect-file path.
- `0x1003C520` is a CRT stream-pointer table. `src/functions/1001384b.cpp:75` allocates a stream block and writes it through `*stream_slot`; the table address is indexed, so Ghidra's references need not appear as direct stores to the base global.
- `0x1003D554` is read by `__cinit` as an optional three-argument callback (`src/functions/10012c05.cpp:52`); the candidate checks for null before calling it. The saved global-xref row shows reads/call usage but no direct write. This audit does not establish whether another runtime component ever supplies a non-null value.

These examples show why zero-filled BSS may be populated through pointer parameters, indexed stores, or external/runtime code despite no direct global write xref. The rest of the no-write set has not been exhaustively adjudicated. No PE bytes were changed and no runtime claim is made.
