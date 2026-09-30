# Relocation provider and 705-object link recheck (2026-09-28)

## Corrected investigation

The first `public-symbol-aliases` provider was generated without the prior
`candidate-internal-image-address-literals-v2-2026-09-27.csv` inventory. It had
782 rather than 896 unique `IVF_RELOC_TARGET_*` labels and its diagnostic link
failed with 124 unresolved symbols. That provider is incomplete and rejected.

The initial claim that the restored-inventory provider had 60 unexpected
relocations was also a verification-command error: the rerun omitted
`--unmapped-target-disassembly`, which supplies mappings for reconstructed
noncandidate code stubs. With all verifier inputs supplied, the current
provider passes **1,521/1,521** original data/code pointer fixups, with zero
mismatches, including 80 reconstructed local-code pointer sites and all 22
Ghidra-checked startup thunk sequences.

Parsing the 79 linker diagnostics from the baseline link yielded exact external
symbol aliases for original `.rdata`/`.data` addresses. Those aliases plus 11
additional data-address labels discovered by the next link attempt were added
to the provider. The resulting `reloc-aware-dat-provider-705-private-rtlunwind-v2`
object also passes 1,521/1,521 fixups (zero mismatches).

## RtlUnwind collision and all-candidate diagnostic link

Candidate `1001b2b2` defined `_RtlUnwind@16`, colliding with the KERNEL32
import thunk. Its recovered body remains the same single indirect jump; only
its local symbol was made unique (`_ImVehFt_Recovered_RtlUnwind@16`) and a
linker alternate name maps the undecorated IAT reference to KERNEL32's
canonical import. A preserved pre-edit copy is
`src/functions/1001b2b2.cpp.pre-unique-rtlunwind-linkage-20260928.bak`.
The original ASI bytes at `0x1001B2B2` are `FF 25 B8 20 02 10`, which jump
through the Ghidra-confirmed IAT slot `0x100220B8`. The strict COFF object
contains `FF 25 00 00 00 00` plus a `DIR32` relocation at operand offset 2 to
`__imp__RtlUnwind`; after link this is the same indirect-IAT-jump operation,
with the alternate-name directive resolving the import spelling.

Fresh strict compile: **705/705** (`build/strict-all-private-rtlunwind-v2-20260928.json`).
ReAgent structural objective: **705 PASS / 0 FAIL / 0 UNKNOWN**
(`audit/objective-post-private-rtlunwind-2026-09-28.json`). ReAgent parity:
**705 GREEN / 0 YELLOW / 0 RED**
(`build/parity-post-private-rtlunwind-20260928.json`). These are source-level
and structural checks, not proof of runtime equivalence.

Normal x86 linker result: exit 0, no diagnostics, all **705 actual candidate
object files** included. Output is
`build/link-probe/strict-704-historical-sdk/ImVehFt-all-705-candidates-link-not-ASI.dll`
(724,480 bytes) with map file alongside it. `dumpbin` confirms x86 GUI DLL and
KERNEL32 `RtlUnwind` import; the map includes the private recovered thunk.

## Why this link is not an ASI

Fresh `dumpbin /headers` measurements show the diagnostic PE does not preserve
the original image layout:

| PE property | Installed 2014 ASI | 705-object diagnostic DLL |
|---|---:|---:|
| Image base | `0x10000000` | `0x10000000` |
| Entry point VA | `0x100111B3` | `0x10011430` |
| Image end VA | `0x10042FFF` | `0x100B5FFF` |
| `.text` virtual size | `0x2027B` | `0x8447B` |
| `.rdata` virtual size | `0x6F44` | `0x1226C` |
| `.data` virtual size | `0x1455C` | `0x16268` |
| `.reloc` virtual size | `0x3F44` | `0x4A70` |

Both files import `d3dx9_43.dll`, `USER32.dll`, and `KERNEL32.dll`, but that
overlap does not establish ABI or startup equivalence. The rewritten image has
a different entrypoint VA, a much larger `.text`, and does not reconstruct the
original preferred-VA hook and code layout. Therefore its successful link is
only proof that the recovered objects and current diagnostic providers can be
resolved together; it is not safe to load in GTA SA.

## Limits / do not load

This is still a diagnostic DLL assembled with synthetic data/runtime providers,
not a production `.asi`. The original PE's complete `.text` HIGHLOW relocation
set, faithful section and hook layout, production startup/CRT/import behavior,
and in-game execution have not been established. Do not rename or load this
DLL. No game/runtime validation has been performed.

## Reproduction artifacts

- Provider: `build/recheck/reloc-aware-dat-provider-705-private-rtlunwind-v2-20260928.asm/.obj`
- Provider manifest: `audit/reloc-aware-dat-provider-705-private-rtlunwind-v2-2026-09-28.json`
- Exact aliases reconstructed from baseline link diagnostics: `audit/unresolved-pe-data-symbol-aliases-reconstructed-20260928.csv`
- Full 705-object link response/log: `build/link-probe/strict-704-historical-sdk/strict-705-link-all-candidate-objects-20260928.rsp/.log`
- Link map and diagnostic DLL: `build/link-probe/strict-704-historical-sdk/ImVehFt-all-705-candidates-link-not-ASI.map/.dll`
