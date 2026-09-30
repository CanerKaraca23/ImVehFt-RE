# Address-ordered COMDAT link experiment

Date: 2026-09-28. Reference ASI SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Method

MSVC compiles the candidate function bodies into separate `.text$mn` COMDATs.
Microsoft documents `/ORDER:@file` as the linker mechanism for ordering such
COMDAT functions, with the important limitation that static functions cannot
be ordered by symbol name. The new generator reads COFF symbol tables and the
Ghidra address/name/signature map to prioritize one exact public COMDAT per
address, then includes the remaining public candidate code symbols in source
address order. It found 705 candidate objects and 746 unique public code
symbols: 676 entries matched the Ghidra name/signature rule, and the other 29
were inferred from the sole public `.text*` symbol in their address-named
object. There were no unresolved/ambiguous entry selections; the 29 inferred
selections are explicitly weaker than name/signature matches.

The order file and machine-readable selection audit are:

- `build/recheck/candidate-comdat-order-v9-20260928.order`
- `audit/candidate-comdat-order-v9-2026-09-28.json`

## Link result

Linked all 705 candidate objects with `/OPT:REF`, 746 COFF-derived `/INCLUDE`
roots, and `/ORDER:@candidate-comdat-order-v9-20260928.order`:

- DLL: `build/link-probe/strict-704-historical-sdk/ImVehFt-optref-comdat-order-v4-diagnostic-not-ASI.dll`
- SHA-256: `89E9690E4C4D6AD0D0CAB87F11DF7B189CD62D45FFFC9F39272408C903018F24`
- PE32 base: `0x10000000`; `SizeOfImage = 0x71000`; file size `444416` bytes.
- Map contains candidate code entries from all 705 address-named objects.
- 705/705 selected public candidate root symbols are present in the map; 676
  are name/signature matched and 29 use the unique-public-symbol inference.

For those same 705 selected roots, address deltas (linked VA minus reference
VA) changed as follows compared with the preceding `/OPT:NOREF` diagnostic
link:

| Metric | `/OPT:NOREF` | `/OPT:REF` + `/ORDER` |
|---|---:|---:|
| Exact original RVAs | 3/705 | 3/705 |
| Mean absolute drift | 4,341 bytes | 2,468 bytes |
| Median absolute drift | 2,816 bytes | 2,592 bytes |
| 90th percentile absolute drift | 9,202 bytes | 3,835 bytes |
| Maximum positive drift | `+0x939E` | `+0x1C3E` |

Examples: `FUN_100076d0` moved from `0x10008D20` to `0x10007EF0` (still
`+0x820` from its reference VA); `FUN_10021267` moved from `0x10024450` to
`0x10022E00` (still `+0x1B99`). The link entrypoint is `0x100106A0`, not the
reference `0x100111B3`; the image is `0x71000`, not the reference `0x43000`.

## Validation boundary

This is measurable progress in code placement, not completion. The linked
image still has incorrect function RVAs, startup entrypoint, image extent, and
data layout. It is a diagnostic DLL, **not a loadable ASI**; do not install or
run it in GTA. No new candidate C++ changes were made, so the earlier
705/705 strict compile and objective/parity results remain the latest
candidate-source checks; they were not rerun for this linker-only experiment.
No production startup/installer or game/runtime validation is claimed.

The relink helper has pre-change copies at
`scripts/relink-current-candidate-diagnostic.ps1.pre-coff-public-code-roots-20260928.bak`
and `scripts/relink-current-candidate-diagnostic.ps1.pre-comdat-order-20260928.bak`.
