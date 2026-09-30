# Current appended-body external target resolution — 2026-09-30

Joined the current 422-thunk fixup inventory to the pinned original PE,
current 705-entry placement, current Ghidra function map, GTA SA text map,
saved callback maps, and the exact provider alias inventories.

## Address / call-target accounting

Of the 1,504 undefined-external fixup occurrences in the 422 appended candidate
bodies, **1,495 now have an original preferred-base address or an explicit
generated call-thunk target plan**:

| Evidence-backed target group | Occurrences |
| --- | ---: |
| Address-bearing original `.data` / `.rdata` aliases | 952 |
| Original imported-function IAT slots | 116 |
| API `CALL rel32` sites routed through verified FF25 thunks | 57 |
| Original callback labels retained outside candidate patches | 95 |
| Provider/runtime-data aliases crosswalked to original PE VAs | 150 |
| Callback dispatchers retained at their original VAs | 5 |
| Candidate entry targets routed by the current placement plan | 103 |
| External GTA `.text` targets | 17 |
| **Still unresolved static-CRT arithmetic calls** | **9** |

The 21 API thunks are verified as exact `FF 25 imm32` bodies; a separate
all-705-object plan covers all 196 API calls (139 in-place and 57 appended).
Current helper-overlay audit checks 70 JMP labels, 25 callback-entry labels,
and five 75-byte dispatchers: no helper/helper or helper/candidate overlap,
and all five dispatcher HIGHLOW operand sites remain in the expanded
6,136-site relocation table.

## Remaining issue and scope

The nine unresolved occurrences are four `__alldiv`, four `__allrem`, and one
`__aulldiv` call in the CRT-derived `1001bee6` and `10014003` candidates. The
current diagnostic link maps these to MSVC static-CRT objects; the diagnostic
addresses are not used as final targets. A byte-prefix scan of the three
diagnostic helper bodies did not find exact matches in original `.text`, so no
original-VA alias is asserted for them.

Machine-readable evidence:

- `audit/appended-thunk-address-encoded-original-pe-current-2026-09-30.json`
- `audit/appended-thunk-provider-original-addresses-current-2026-09-30.json`
- `audit/appended-thunk-code-target-classes-current-2026-09-30.json`
- `audit/callback-label-preservation-current-placement-2026-09-30.json`
- `audit/callback-helper-overlay-current-placement-2026-09-30.json`
- `audit/current-api-call-rel32-patch-plan-2026-09-30.json`

These are target inventories and deterministic patch plans, not applied fixups.
No candidate/PE bytes were patched; no final PE/ASI, loader test, or GTA
runtime validation has been produced.
