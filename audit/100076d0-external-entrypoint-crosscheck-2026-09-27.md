# External entrypoint cross-check for `100076d0`

Date: 2026-09-27. This follow-up checks whether installed plugins can enter
the patched callback at `0x4c8415` without first traversing the vehicle-context
setter hook at `0x6d6617`. It uses the exact installed GTA SA executable and
installed ASI/DLL images; it is static analysis, not a live ModLoader session.

## GTA-side Ghidra xrefs

Ghidra 12.1.3 queried the existing auto-analyzed `gta_sa.exe` project in
headless `-noanalysis` mode. Incoming xrefs show:

- `0x4c8430` has one incoming code reference, the call at `0x6d662b` inside
  `FUN_006d64f0`.
- `0x6d64f0` has one incoming code reference, the call at `0x5532a9` inside
  `FUN_00553260`.
- `0x4c83e0` has one incoming reference: the callback address supplied by
  `FUN_004c8430` at `0x4c843a`. That callback contains the patched instruction
  at `0x4c8414..0x4c8419`, whose original target is `0x4c8220`.
- `0x6d6617` is the call site to the setter target (`0x4c8c90`) immediately
  before `0x6d662b` calls `0x4c8430`.

The reference inventory is `gta-sa-entry-xrefs-20260927.csv`; the existing
vehicle-parent and dispatcher listings are
`gta-sa-vehicle-callback-parent-553260-20260927.txt` and
`gta-sa-dispatcher-crosscheck-2026-09-27.md`.

## Installed-module address hits, decoded

The earlier raw-address scan exposed real references to GTA functions; these
were disassembled instead of treating address-byte hits as calls:

| Module | Ghidra/disassembly finding | Relation to the setter/callback |
| --- | --- | --- |
| `samp.dll` | Four register-indirect calls to `0x553260` (`0x1009F923`, `0x1009F9C7`, `0x1009F9DC`, `0x100A8B79`). The same image has a patch routine that writes `RET` (`0xC3`) to the first byte of `0x6D64F0` at `0x100A3E91`. | Calls to `0x553260` use its normal vehicle-state gate and, when they reach `0x6D64F0`, the hook at `0x6D6617` precedes the dispatcher. If the SA-MP patch runs, it short-circuits `0x6D64F0` instead; it does not jump directly into `0x4C8430`/`0x4C83E0`. Its live order relative to other installers is unknown. |
| `ModelExtras.asi` | Thunk at `0x1000B600`: `mov eax,0x6D64F0; jmp eax`. | Enters the beginning of the GTA function; it does not target the callback address. If the function proceeds, it encounters the setter hook before the dispatcher. |
| `ProperShaders.asi` | Calls `0x553260` at `0x100236B8` and through `EDI` at `0x100237E0`. | Both enter the normal parent function; the parent invokes `0x6D64F0` only under its `state & 7 == 2` branch. |
| `SkyGfx Deferred` and `SkyGfx Remix` | Each has a tail-jump thunk to `0x553260` (`0x1003B360` and `0x100030E0`). | Same parent-function gate and setter path. |
| `SilentPatchSA.asi` | Contains a code immediate `0x4C83E0` at `0x10001504`, which at first looked like a callback registration. | Full Ghidra analysis shows its initializer packages `(0x4C83E0, length, ...)` into a pattern object. `FUN_10007D70` calls `FUN_100083F0` to build the pattern and `FUN_10006EA0` to scan/compare bytes; `0x4C83E0` is signature-scan input, not a call target or callback registration. Decompilations: `silentpatch-init-100014a0-20260927.txt`, `silentpatch-helper-10007d70-20260927.txt`, `silentpatch-helper-100083f0-20260927.txt`, `silentpatch-helper-10006ea0-20260927.txt`, and `silentpatch-helper-100082c0-20260927.txt`. |

The SilentPatch import was analyzed in a temporary Ghidra project with the
PDB analyzers disabled by `GhidraDisablePdbAnalyzers.java`. Its SHA-256 is
`908E1D12E36BA809A8CE584BE0BD29239349968259A5DE593F9B0CC71DBB352B`.

## Cross-module direct-call sweep

`dumpbin /disasm` scanned 64 installed non-backup `.asi`/`.dll` files for
immediate `CALL` instructions to `0x4c83e0`, `0x4c8220`, `0x4c8430`,
`0x749b70`, and `0x74c790`; none were found. The follow-up raw-byte scan found
no third-party address literal for `0x4c8430`, `0x4c8220`, or `0x6d6617`.
Other raw hits are the decoded `0x553260`/`0x6d64f0` parent/thunk routes above,
ImVehFt's own installer references, and SilentPatch's pattern input. This is
not proof against computed pointers, unscanned/late-loaded code, or live
callback behavior.

## Effect on the open finding

This closes one static gap: the apparent SilentPatch `0x4c83e0` reference is
not an alternate callback registration, and the discovered installed-module
code routes enter the parent/vehicle function rather than calling the patched
callback directly. The known static route to `0x100076d0` therefore crosses
the context setter first, unless another runtime hook changes control flow.

Do not remove the `local_c` initializer or promote the parity warning yet.
Texture/raster destruction still reaches live registry callbacks, allocator
functions, a RenderWare device callback, and COM `Release`; their concrete
runtime targets, load order, and re-entry behavior were not observed. The game
was not running. Keep `0x100076d0` YELLOW pending runtime/integrated-plugin
evidence; candidate source remains unchanged.
