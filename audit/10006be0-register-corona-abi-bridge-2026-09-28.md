# `10006be0` RegisterCorona entry ABI bridge

Date: 2026-09-28. Target ImVehFt image SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Discrepancy and binary evidence

The Ghidra listing in `ghidra_exports/10006be0.json` saves entry `EAX` to
`EBX` at `0x10006bef`. The caller listing
`ghidra_exports/10005860.json` sets `EAX` to its entity/context value before
the shared call at `0x10005b1b`, pushes 12 four-byte arguments, then cleans
`0x30` bytes. In the callee, `[EBP+0x34]` is the twelfth stack argument and is
read at `0x10006d1c`/`0x10006e4e`. Thus the original ABI is entry context in
EAX plus 12 cdecl stack arguments.

Before this correction, the candidate represented the context as a
thirteenth C++ stack argument. Its reconstructed caller passed that value
explicitly, preserving the intended value flow within the candidate sources,
but the function boundary did not match the binary ABI.

## Correction

`src/functions/10006be0.cpp` now exports a naked 12-argument entry bridge. It
saves incoming EAX and forwards the 12 original stack words plus that captured
context to the C++ implementation. A separate caller bridge accepts the
reconstruction's 13 explicit C++ arguments, loads the thirteenth into EAX,
pushes the other 12 in reverse order, and calls the ABI-correct entry. The
three reconstructed calls in `10005860` use this caller bridge.

Backups made before the edit:

- `src/functions/10006be0.cpp.pre-register-corona-abi-bridge-20260928.bak`
- `src/functions/10005860.cpp.pre-register-corona-abi-bridge-20260928.bak`

The fresh `/O2 /W4 /WX /MT /arch:IA32` object disassembly confirms the entry
bridge stores EAX, forwards offsets `[EBP+0x34]` through `[EBP+8]` and the
saved register context, then removes `0x34` bytes of implementation arguments.
The caller bridge loads its 13th explicit argument from `[EBP+0x38]`, forwards
the 12 stack words, calls the entry, and removes `0x30` bytes. `10005860.obj`
references the bridge symbol. This is direct object/ABI evidence, not a
complete byte-for-byte match of the target function body.

## Fresh checks

- Full strict MSVC x86 IA32 compile: **705/705**,
  `build/strict-all-register-corona-abi-bridge-20260928.json`.
- Independent ReAgent objective check: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  `audit/objective-register-corona-abi-bridge-2026-09-28.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**,
  `build/parity-register-corona-abi-bridge-20260928.json`.
- Scoped manual call-count audit: **13 checks / 13 results / 0 errors** against
  the fresh object directory,
  `audit/manual-parity-register-corona-abi-bridge-2026-09-28.json`. This does
  not validate the RegisterCorona argument values or runtime behavior.
- A diagnostic link of the fresh 705 candidate objects plus the existing
  support objects succeeded. Its PE32 image has base `0x10000000` and image
  size `0xC4000`; the map places `_FUN_10005860` at `0x10005EC0`,
  `_FUN_10006be0` at `0x10007320`, and its implementation at `0x100073A0`.
  These do not preserve the original entry VAs, so the artifact
  `build/link-probe/strict-704-historical-sdk/ImVehFt-register-corona-abi-bridge-diagnostic-not-ASI.dll`
  is **not loadable as the target ASI**. Its SHA-256 is
  `05691337BE18DB8CFB24ED31DD15C3DB6A06D6904E81281D3A1DEB9F229449ED`.
- Source hash/name manifests refreshed for all 705 sources, with pre-edit
  manifest copies preserved using the same backup suffix.

These checks and the bridge disassembly do not establish full function
semantic equivalence, a production PE/ASI, or game/runtime behavior. The
current original build recipe and runtime prerequisites remain unavailable;
no gameplay test is claimed.
