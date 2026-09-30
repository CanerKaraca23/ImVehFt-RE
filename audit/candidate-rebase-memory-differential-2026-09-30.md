# Candidate rebase memory differential — 2026-09-30

## Result

The v5 candidate (`build/pe-layout-probe/ImVehFt-candidate-705-static-20260930-v5.asi`, SHA-256 `A0513334C7DE0D5E174FE417E19B886EB6882EFF70C41A3DA34B098476F6B2F4`) is **not validated**. A 32-bit Windows probe loaded it at a non-preferred base with `LoadLibraryExW(DONT_RESOLVE_DLL_REFERENCES)` after reserving its preferred base, and compared every HIGHLOW target in mapped memory against the relocation delta. Of 6,389 records, 3 produced bytes inconsistent with a single correct HIGHLOW relocation. No imports were resolved, DllMain was not called, and neither GTA nor a plugin loader was started.

| RVA | File DWORD | Expected at mapped base | Actual mapped DWORD | Interpretation |
|---|---:|---:|---:|---|
| `0x586A8` | `0x024F1005` | `0x5C821005` | `0x8F821005` | Stale provisional local-`.rdata` relocation site now falls in `.xcode` instruction bytes. |
| `0x586A9` | `0x10024F10` | `0x6A354F10` | `0x6A8F8210` | Actual local-`.rdata` DIR32 field; this RVA is misaligned relative to the preceding bogus record and the result is cumulatively corrupted. |
| `0x586AC` | `0x6A505010` | `0xC4835010` | `0xC483506A` | Stale provisional local-`.rdata` relocation site falls in instruction bytes. |

The previously audited `local_rdata_payload_map` identifies three object relocation fields, but its provisional flattened payload RVAs were carried into the final PE without translating them to the split `.xrdata` placement. The combined `.rdata` layout maps the current field sites to:

- `0x10010678`, object section 3, offset 24 → RVA `0x5C6A0`, target `_FUN_1001072a@0` (candidate body at original entry `0x1001072A`).
- `0x10017DDE`, object section 5, offset 20 → RVA `0x5C818`, target `_terminate_scope_filter`.
- `0x10017DDE`, object section 5, offset 24 → RVA `0x5C81C`, target `_terminate_scope_handler`.

The corresponding local `.rdata` object section contains two more DIR32 references to local `.xcode` helper sections, which were absent from the previous combined-xcode inventory. The object file independently yielded the exact four-byte filter and 16-byte landing-pad helpers. A follow-up repair placed these at `0x1005BB7B` and `0x1005BB7F`, resolved the landing pad's REL32 call to candidate `_abort` entry `0x1001705C`, patched the three `.xrdata` fields, and moved all three HIGHLOW sites to their final RVAs. The operation emits a separate v7 candidate, leaving v4/v5 intact.

The v7 PE section/header and payload checks pass (`audit/repaired-candidate-local-rdata-relocs-2026-09-30-v7.json`). A fresh 32-bit Windows nonpreferred-base probe maps v7 at `0x692D0000` (delta `0x592D0000`) and compares all **6,389** HIGHLOW DWORDs in mapped memory with the corresponding file value plus the loader delta: **0 mismatches** (`audit/candidate-rebase-memory-differential-v7-2026-09-30.json`). Imports remain unresolved; DllMain, plugin-loader initialization, GTA, and gameplay were not run. This is stronger evidence for relocation correctness, but not proof the candidate is a functioning or safe-to-install ASI.

## Scope caveat

The earlier PE parser, checksum, relocation-site-set union, preferred-base mapping, and thunk-overlap guard all passed, but none compared the OS loader's relocated bytes against expected field semantics at a non-preferred base. This differential is stronger and supersedes claims that v5's relocation table was validated. Original ASI hash remains pinned at `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`; it was not modified.
