# Original-entry patch cross-evidence audit

Date: 2026-09-28. Joined the hash-pinned original-image relocation overlap
report to the Ghidra instruction-unit export, Ghidra entry-byte xrefs, and the
705-entry function map. The reproducible join is
`scripts/audit-entry-patch-cross-evidence.py`; its machine-readable output is
`audit/entry-patch-cross-evidence-current-2026-09-28.json` (SHA-256
`1137DD0DD44A7DDAC3EEC91C236061FC09DB56C392A1CC685B6A8F740B070999`).

## Findings

- All **97/97** original `.text` HIGHLOW fields intersecting proposed 5-byte
  entry thunks join to Ghidra `InstructionDB` code units. This confirms that
  they overlap decoded instruction bytes; it does not establish that a final
  patch/image handles their fixups correctly.
- The 705-entry map has exactly two gaps shorter than five bytes:
  `0x10018F94`→`0x10018F97` and `0x1002044B`→`0x1002044E`, each 3 bytes.
- The only non-data Ghidra references into the first five bytes of mapped
  entries land at offset `+3` in those two gaps. Both are direct calls to the
  adjacent function starts. The separate relay-layout probe models short
  entry jumps and relays at `0x10018F9C` and `0x10020453`; those addresses have
  not been emitted or runtime-tested.

## Remaining implementation gates

A production image builder must suppress any original base-relocation records
whose 4-byte fixup fields overlap bytes replaced by an entry branch, preserve
or correctly redirect the two adjacent-entry direct calls, merge all
candidate and original relocations, and independently validate the emitted
PE's sections, imports, TLS/CRT initialization, exception metadata, and
entrypoint. This audit emits no PE and does not establish semantic equivalence,
loader success, or GTA behavior. No candidate C++ source was changed for this
audit.
