# `1000ea80` callback-queue dispatcher differential

Compared the candidate `FUN_1000ea80` object against the hash-pinned original ImVehFt ASI at its preferred base. The harness populates the manager fields Ghidra identifies at offsets `+0x10`, `+0x18/+0x1c`, and `+0x28/+0x2c`; callbacks are test functions in the harness image. The reference ASI hash is checked by the runner before execution.

## Results

Five fresh x86 process executions passed three cases each (15 original-versus-candidate comparisons total):

1. Normal traversal with a null first-list callback slot: return `0xfeed1234`, five callbacks, matching order.
2. Middle callback extends the second-list end pointer: return `0xfeed1234`, four callbacks, matching order. This checks that the dispatcher reads the second-list bounds after the middle callback.
3. Nested dispatcher re-entry from a first-list callback: return `0xfeed1234`, eight callbacks, matching order.

Evidence hashes:

- Original ASI: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate object: `F1038CA97F6277A26184A49DCD566BB6FCAA10FDB0141F40BA18F58BA7968D05`.
- Harness source: `212FA4C41048741D24D4D0F7839321FB21D3EFA5D31BE16485C2D9ABA8AEA171`.
- Harness executable: `87B408EB152F0EE1F085729D57297E83B0E2910A81645B054886DEC683D039B0`.

Re-run with `scripts/test-1000ea80-queue-reentry-differential.ps1`.

## Limits

This verifies the dispatcher function's callback ordering, dynamic second-list bounds, return propagation, and synthetic nested re-entry against the original machine code. It does not reproduce the live GTA/RenderWare plugin registry, establish which runtime event dispatches the callback, or prove actual MEXT/driver re-entry into `100076d0`; that behavioral finding remains OPEN. No candidate source change was made in this follow-up.
