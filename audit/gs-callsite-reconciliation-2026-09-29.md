# Original/modern stack-cookie call-site reconciliation (2026-09-29)

## Scope

Compared the saved Ghidra assembly for all 705 target functions with actual COFF relocation references in two fresh MSVC 14.44 x86 object sets built from the current sources: the default-GS build and the `/GS-` experiment. The reproducible inventory is `scripts/audit-gs-callsite-reconciliation.py`; its machine-readable output is `audit/gs-callsite-reconciliation-2026-09-29.json`.

This is a static call-site inventory. Call-count equality does not prove path or semantic equivalence; unequal counts can result from compiler tail duplication/merging, hidden cookie checks, or missing behavior and require instruction/path review.

## Whole-set totals

| Evidence | Check calls/sites | Functions containing checks | Compiler-cookie global relocations |
|---|---:|---:|---:|
| Original Ghidra assembly | 29 | 24 | n/a |
| MSVC 14.44 default `/GS` objects | 93 | 51 | 49 |
| MSVC 14.44 `/GS-` objects | 34 | 17 | 0 |

Neither global flag reproduces the original call-site inventory as a whole. Default `/GS` adds modern-toolchain checks and references a compiler cookie that the legacy checker does not use. `/GS-` removes those generated checks, including some present in original CRT/EH functions. The choice must be made per function or with exact assembly/ABI-compatible cookie mapping, guided by original evidence—not by the 705/705 compile result.

## Per-function raw-count differences

Only functions whose original and `/GS-` raw call counts differ are listed. `default-GS` is shown to expose the modern compiler expansion, not as proof of equivalent paths.

| Address | Original Ghidra | `/GS-` COFF | Default `/GS` COFF |
|---|---:|---:|---:|
| `10011724` | 1 | 0 | 1 |
| `100119f1` | 1 | 0 | 4 |
| `10012e90` | 6 | 2 | 2 |
| `100142b6` | 1 | 2 | 2 |
| `100154dc` | 1 | 2 | 2 |
| `10019c86` | 1 | 0 | 3 |
| `10019eb3` | 1 | 0 | 0 |
| `1001b827` | 1 | 0 | 0 |
| `1001bdff` | 1 | 3 | 2 |
| `1001c35f` | 1 | 4 | 2 |
| `1001c420` | 1 | 4 | 2 |
| `1001da5c` | 1 | 3 | 2 |
| `1001db04` | 1 | 3 | 2 |
| `1001e085` | 1 | 2 | 2 |
| `1001e5d6` | 1 | 2 | 2 |
| `1001eb27` | 1 | 0 | 2 |
| `1001f203` | 1 | 0 | 3 |

The other 688 functions have equal raw `@__security_check_cookie@4` call counts between Ghidra assembly and the `/GS-` object set. This is only count parity, not semantic equivalence.

## Priority finding: `10012e90` (`__except_handler4`)

Ghidra export `ghidra_exports/10012e90.json` contains six injected calls to `0x100172d5`, in three paired regions: `0x10012ec4/0x10012ed4`, `0x10012f47/0x10012f57`, and `0x10012fdd/0x10012fed`. The current `/GS-` candidate object has two checker relocations at object offsets `0x10b` and `0x137`; its source explicitly checks one `encoded_cookie` value along return paths. The original assembly checks additional values derived from the decoded scope table and frame base. This mismatch is not cleared by the parity GREEN signal or by the count-only checks. Exact per-path cookie semantics and exception-frame corruption behavior remain OPEN and should be investigated before calling the handler runtime-ready.

The binary-backed `1001b71d` correction now matches its original assembly byte-for-byte modulo two relocations; its check call is not among the unresolved rows above.

## Decision/status

Keep both build variants as separate experiments. Do not designate `/GS-` as the production build flag yet, and do not accept default `/GS` as runtime-safe. Next evidence should establish the original compiler-cookie initialization/mapping and reconstruct/compare the listed CRT/EH checks, starting with `10012e90`. No ASI or game-runtime validation was performed by this audit.
