# Supplemental hook-shim relocation integration blocker (2026-09-27)

The diagnostic link's post-link failure is not just a function-order problem. The twelve Ghidra-recovered hook bodies are emitted as original `DB`/`_emit` byte streams, but their internal plugin-image addresses remain preferred VAs when the bodies are linked at new DLL addresses.

Evidence and scope:

- `audit/hook-shim-fixups-2026-09-27.json` inventories **139 image-internal operand fixups** across 12 bodies: 123 absolute memory references, 11 rel32 calls to candidate functions, and 5 absolute pointer immediates. It also independently validates 42 branches whose targets stay inside their own body and therefore remain position-relative.
- The 11 candidate calls have five distinct entry targets: `0x10001730`, `0x10003130`, `0x10003200`, `0x10004a60`, and `0x10008e00`. These are all address-named translation units in the 705-member source set.
- The 123 absolute-memory fixups touch 45 unique plugin-image addresses. The final 418-address candidate DAT symbol inventory contains 15 of those addresses; the remaining 30 require explicit exported labels in the data provider (many are string/table slots, not currently referenced as typed C++ globals).
- Five pointer-immediate fixups are separately inventoried and must also be retargeted; their address set overlaps the absolute-memory target set.
- `audit/diagnostic-link-hook-layout-2026-09-27.md` reports all 12 body byte streams mismatch at offset zero in the diagnostic DLL. The DLL's preferred base is unchanged, but linker placement differs and its `.text` overlaps the original `.rdata`/`.data` preferred-VA ranges. Keeping the same image base cannot make these addresses valid.
- `scripts/generate-coff-dat-relocation-provider.py` emits synthetic `IVF_RELOC_TARGET_*` labels inside its data object, but currently does not mark those labels `PUBLIC`; the existing MASM shims preserve full raw bytes and therefore do not create COFF DIR32/REL32 relocations for the 139 operands.

## Relocatable shim-object prototype

Implemented `scripts/generate-relocatable-hook-shims.py` and
`scripts/verify-relocatable-hook-shims.py`. Using the fresh 705-object strict
build, the generator emits one MASM COFF object containing all 12 bodies. The
original instruction bytes are retained except for the address fields that
must be linker relocations. The independently inspected object has exactly
**139 relocations: 128 DIR32 data/pointer relocations and 11 REL32 candidate
function calls**. Its total text stream is exactly 1,449 bytes, including 556
relocation-field bytes; the verifier checks all 12 public body labels, all 893
non-relocation bytes, all relocation sites/types, and target symbol names.
Result: `PASS shims=12 instruction_stream_bytes=1449
verified_nonfixup_bytes=893 relocations=139 DIR32=128 REL32=11`.

Extended `scripts/generate-coff-dat-relocation-provider.py` with an optional
shim-fixup inventory input; its generated provider now exports all 46 unique
data-address aliases needed by those shim operands. A symbol-closure check
confirmed 46/46 shim data aliases are defined by that provider object. The
existing independent provider verifier still passes **1,441/1,441** data/code
relocation sites with zero mismatches after the alias exports. Candidate call
references resolve to the public symbols extracted from the fresh objects for
the five mapped entry targets.

Reproduction outputs are `build/recheck/relocatable-hook-shims-v1-20260927.asm`,
`build/recheck/relocatable-hook-shims-v1-20260927.obj`,
`audit/relocatable-hook-shims-v1-2026-09-27.json`, and
`build/recheck/reloc-aware-dat-provider-hook-shim-labels-20260927.asm/.obj`.

This is an object-level relocation improvement, not a completed production
link. The runtime installer still needs dynamic hook destinations/patches;
the original 3,160 `.text` HIGHLOW inventory, complete image/CRT integration,
and runtime checks remain separate open gates. No `.asi` was rebuilt or
loaded, so no game test is justified yet.
