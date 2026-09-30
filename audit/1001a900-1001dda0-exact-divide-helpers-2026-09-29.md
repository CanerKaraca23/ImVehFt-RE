# Exact 32-bit divide helper reconstruction — 2026-09-29

## Changes

Replaced the C++ 64-bit `/` and `%` implementations in `src/functions/1001a900.cpp`
and `src/functions/1001dda0.cpp` with the corresponding x86 instruction
sequences exported by Ghidra. The original source files are preserved as:

- `src/functions/1001a900.cpp.pre-exact-ghidra-asm-20260929.bak`
- `src/functions/1001dda0.cpp.pre-exact-ghidra-asm-20260929.bak`

These routines are Visual Studio 2010 CRT helpers (`__aulldvrm` and
`__alldvrm`). The C++ arithmetic could lower back into CRT divide helpers;
the exact assembly avoids that self-dependency.

## Byte-level evidence

The pinned reference image is `ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.
With strict x86 MSVC `/O1 /W4 /WX /MT /arch:IA32 /GS-`, the `.xcode`
contribution begins with byte-identical original bodies and has no COFF
relocations:

| Entry | Original body | Exact candidate prefix SHA-256 | Result |
|---|---:|---|---|
| `0x1001a900` | `0x93` bytes | `7E91DC134EB3D5834CA6F2F9AC14E1269BDD84709152B5A9929D01A7A496CD90` | exact |
| `0x1001dda0` | `0xDD` bytes | `BC30361FAED120822FA3D848387AA19E521F0D6AF2E1244D92F34B43842D637F` | exact |

Each object contribution is two bytes longer (`10 00`) due to compiler
alignment after the function body; those bytes are outside the original body.

## Whole-set checks

- `build/strict-xcode-nogs-o1-exact-divide-20260929.json`: **705/705** strict
  x86 translation units compile.
- `audit/objective-independent-exact-divide-2026-09-29.json`: **705 PASS / 0
  FAIL / 0 UNKNOWN** under ReAgent's structural objective verifier.
- `build/parity-exact-divide-20260929.json`: **705 GREEN / 0 YELLOW / 0 RED**
  under ReAgent parity.
- `audit/source-sha256.csv`: all **705/705** current source hashes and byte
  counts match. The prior manifests are preserved with suffix
  `.pre-exact-divide-asm-20260929.bak`.

These are source/object/parity gates, not whole-plugin semantic or game-runtime
proof.

## Follow-up: private `_tolower` linkage and mapped differential

Ghidra export `ghidra_exports/10015237.json` identifies `_tolower`'s only caller
as `0x1001baeb` (`__forcdecpt_l`), with two call sites. Renamed the candidate
definition to the private C symbol `ImVehFt_tolower_10015237` and redirected
those two source calls. Backups are preserved beside both sources with suffix
`.pre-private-tolower-linkage-20260929.bak`. This keeps the reverse-engineered
candidate body in the diagnostic image while leaving the UCRT's own
`__tolower` symbol available for UCRT internals.

After this change, refreshed both 705-row source manifests (with backups) and
reran the whole-set gates:

- `build/strict-xcode-nogs-o1-private-tolower-20260929.json`: **705/705**
  strict x86 compile.
- `audit/objective-independent-private-tolower-2026-09-29.json`: **705 PASS / 0
  FAIL / 0 UNKNOWN**.
- `build/parity-private-tolower-20260929.json`: **705 GREEN / 0 YELLOW / 0 RED**.
- Current `audit/source-sha256.csv`: **705/705** hashes and byte counts match.

A fresh link of all 705 current objects now succeeds without `/FORCE`; output
is `build/link-probe/private-tolower-20260929/ImVehFt-current-boundary-check-not-ASI.dll`
(SHA-256 `8B79957C9CF581F1F9660373CD514DB914E74F2BF301EEA24D0DA66D78603949`).
The map places the private candidate at `0x1001d9b6` and the UCRT `__tolower`
at `0x10020116`, with no duplicate-symbol error. Link output still contains
stale `/ORDER` LNK4037 warnings, and this diagnostic image has a six-section
layout (`.xcode`, `.text`, `.rdata`, `.data`, `.fptable`, `.reloc`); it is
not the original plugin image.

`tests/runtime_10015237_private_link_differential.cpp` loads both the original
ASI and this diagnostic DLL without initialization, sets each image's
`DAT_10039a84` equivalent to zero, and compares **500,041/500,041** inputs
bit-exactly, including ASCII boundaries, signed-edge values and a fixed-seed
random set. This proves only the zero-locale-flag `_tolower` path and its
mapped-code execution. It does not test the locale-enabled call path, DllMain,
plugin startup, hooks, or GTA gameplay. No production PE/ASI exists. The
2014-era SDK snapshot is available, but the original ImVehFt project/build
configuration is not; full image relocation, startup integration, and
end-to-end game validation remain open. See
`audit/source-and-sdk-availability-2026-09-29.md`.

## Mapped runtime differential for the divide helpers

Added `tests/runtime_divide_helpers_mapped_differential.cpp`, built as an x86
standalone harness at `build/abi-harness/divide-helpers-20260929/harness.exe`.
It maps the pinned original ASI and the successful diagnostic DLL using
`DONT_RESOLVE_DLL_REFERENCES`, then directly invokes original entries
`0x1001a900`/`0x1001dda0` and current diagnostic-map entries
`0x100172a5`/`0x10019b4d`.

Result: **250,169 input pairs** (169 cross-product boundary cases plus 250,000
fixed-seed xorshift cases) matched for both unsigned and signed helpers. The
harness checks quotient and remainder register pairs, exact caller stack
balance for each invocation, and preservation of ESI/EDI/EBP. Zero divisors
are replaced with one because the helpers intentionally fault on divide by
zero. Both images are loaded without initialization; this is focused helper
evidence, not DLL startup or gameplay validation.
