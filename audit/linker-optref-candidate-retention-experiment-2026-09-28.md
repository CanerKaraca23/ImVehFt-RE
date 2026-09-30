# `/OPT:REF` candidate-retention link experiment

Date: 2026-09-28. Reference ASI SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Why the experiment was run

The original diagnostic link used `/OPT:NOREF`. Its full `.text` reached
`0x849e1`, but that included hundreds of unused MSVC/UCRT COMDAT functions.
The raw `.text*` contributions in the 705 candidate COFF objects total
`0x21e0c` (798 code sections), versus reference `.text` virtual size
`0x2027b`. This object-byte total is a useful size bound, not a semantic or
linked-layout equivalence claim.

## Results

1. A fresh `/OPT:REF` link completed and reduced `SizeOfImage` from `0xC4000`
   to `0x68000`, `.text` from `0x849e1` to `0x2e5bc`, and output file size from
   782,336 to 406,016 bytes. However, its map retained code-public entries
   from only 568 of the 705 candidate objects; `FUN_100076d0` was dead-stripped.
2. An initial attempt to root every code-looking symbol parsed from the old
   link map failed closed with 19 unresolved symbols. It had treated some
   internal/static function symbols as externally visible. No DLL from that
   attempt was produced.
3. The relink helper now reads COFF symbol tables and roots only external
   symbols in `.text*` sections. It found 746 distinct public code symbols
   across all 705 candidate objects. The resulting `/OPT:REF` diagnostic link
   succeeds and its map contains code-public entries from all 705 objects.
   Output: `build/link-probe/strict-704-historical-sdk/ImVehFt-optref-keep-public-candidates-diagnostic-not-ASI.dll`
   SHA-256: `987BDB0DFE608A7E08BCFC50962C2C962C46EF3F9ECC07E8526E9FFFFA5E28B1`.

The third image has PE32 base `0x10000000`, `SizeOfImage = 0x71000`,
`.text = 0x36dac`, `.rdata = 0xed7c`, `.data = 0x24164`, and file size
444,416 bytes. Address placement remains wrong: `FUN_100076d0` is still at
`0x10008D20` instead of `0x100076D0`; `FUN_10021267` is at `0x10024070`
instead of `0x10021267`. The linked entrypoint is `0x100114D0`, not the
reference entrypoint `0x100111B3`.

## Interpretation and limits

This is a useful reduction of unused runtime code while retaining the full
705-object candidate set. It does **not** produce a game-loadable ASI. The
image still exceeds the reference image size `0x43000`, has displaced code
and data, and uses a diagnostic entrypoint/startup recipe. No candidate C++
source changed in this experiment; the relink helper backup is
`scripts/relink-current-candidate-diagnostic.ps1.pre-coff-public-code-roots-20260928.bak`.
The output must not be installed or loaded. Semantic/runtime/game validation
remains open.
