# `10006be0` x87 condition-code observability audit

The original-vs-candidate harness reports 1,354 cases per run where only x87 condition-code bits (C0/C1/C2/C3) differ. This follow-up checks whether the original's direct caller consumes those returned bits.

## Evidence

- The pinned Ghidra export lists one direct caller for `FUN_10006be0`: `FUN_10005860` (`CALL 0x10006be0` at `0x10005b1b`). A scan of the individual function-export JSON `callers` fields found no other direct caller.
- After the call, `FUN_10005860` executes `ADD ESP,0x30` and integer loads/increments/comparisons through the loop. It then calls `FUN_100060d0` at `0x10005b4b`; no `FNSTSW/FSTSW`, x87 conditional jump, or status-to-integer transfer occurs in that caller interval.
- `FUN_100060d0` first calls `FUN_10009360`, whose exported assembly contains integer/control-flow operations only. Four early `param_1+0x594` cases branch directly to its epilogue without consulting x87 status. Other paths execute `FLDZ; FCOM [ESI+0x4a0]; FNSTSW AX` at `0x1000612f-0x10006137`. `FCOM` establishes the comparison condition bits that are then read; stale C0/C1/C2/C3 from `FUN_10006be0` are not the values being tested.

## Conclusion and limit

The observed x87 condition-code-only differences are not consumed by the known direct caller before the caller either returns or performs its own comparison/status read. They remain a CPU-state non-identity if `FUN_10006be0` is invoked in isolation, but are not a demonstrated gameplay/return-side-effect mismatch on the known call chain. This resolves that specific caller-observability question only; the broader `10006be0` finding remains open for other edge cases and live GTA/RenderWare behavior. Source is unchanged; current candidate SHA-256 remains `92B16BE2BB33C4A79E12E78FF34D3BB7D267C3F3B9EC7BB30C89D7A14A70BAF8`.

## Fresh differential rerun

On 2026-09-29, rebuilt and ran `scripts/test-10006be0-original-binary-differential.ps1` against the same pinned ASI and current candidate source. One fresh process matched **32,720/32,720** semantic/output observations with zero mismatches; the existing **1,354** C0/C1/C2/C3-only differences recurred. Harness executable SHA-256: `3FBE2BC3A5B344AF3B43F744B0C972432CD674CD9445DCE84162FB311B94B090` at `build/abi-harness/10006be0-x87-caller-audit-20260929/`. This reconfirms the existing differential result on the current source; it does not broaden to the live game runtime.
