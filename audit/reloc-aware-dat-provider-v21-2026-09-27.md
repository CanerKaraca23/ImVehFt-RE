# Relocation-aware provider v21 (2026-09-27)

## Result

Added exact byte-template reconstructions for the remaining catch/filter fragments at `0x1001cee8`, `0x1001d0ff`, and `0x1001d108`, plus the six-byte entry prefix at `0x1001d18f`. The original bytes and all original data/candidate-code call destinations were checked before generation. The `0x1001d0ff` call targets the local reconstructed `0x1001cee8` entry; the `0x1001d18f` prefix is followed by a non-flag-changing near jump to candidate entry `0x1001d195` to preserve its original fall-through when emitted out of line. The verifier checks the local relative call destination, tail JMP opcode, COFF relocation, and candidate symbol.

Provider v21 reduces unresolved code-pointer sites from four to **one**: `0x1001ce94`, an SEH cleanup continuation that branches into the interior of the `0x1001ce0c` candidate. Mapping it to the function entry would change behavior, so it remains unresolved pending an exact continuation representation.

Independent COFF verification passes **1,520/1,520** data/code pointer fixups, zero mismatches; 1,322 data-to-data, 119 candidate-code, 79 reconstructed local-code pointer sites, 125 generated `.text` relocations, 22/22 startup thunks, and 177/177 state-table bytes. Artifacts: `build/recheck/reloc-aware-dat-provider-v21-20260927.asm` and `.obj`; manifest: `audit/reloc-aware-dat-provider-v21-2026-09-27.json`.

Fresh 705-function checks were also rerun against the unchanged candidate TU set: VS2022 x86 strict compile **705/705** (`build/strict-v21-20260927.json`), independent ReAgent structural objective **705 PASS / 0 FAIL / 0 UNKNOWN** (`audit/objective-independent-v21-2026-09-27.json`), and ReAgent parity **704 GREEN / 1 YELLOW / 0 RED** (`build/parity-v21-20260927.json`). The one yellow is `0x100076d0`; scoped call-count waiver audit passes 13 checks and explicitly retains its semantic warning (`scripts/audit-reagent-callcount-adjudications.py`). These checks do not establish semantic/runtime equivalence.

This is not a loadable `.asi`: 3,160 original `.text` HIGHLOW relocations, full PE image/hook layout, production imports/link, the remaining continuation, and game/runtime validation remain open. Candidate C++ units were not changed in the provider pass; the compile/objective/parity gates were nevertheless freshly rerun as noted above.
