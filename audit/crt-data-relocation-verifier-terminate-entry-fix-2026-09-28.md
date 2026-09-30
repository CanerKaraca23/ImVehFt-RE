# CRT/data relocation verifier: terminate entry disambiguation

Date: 2026-09-28. Target ImVehFt image SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Issue and evidence

The current CRT/data relocation verification stopped while resolving the
`REL32` target `0x10017DDE`: the address-named object also exports two naked
SEH helper functions at COFF value zero, so the verifier's former
"exactly one public function" assumption was false for this translation unit.
This is not evidence of a bad relocation or bad candidate implementation.

Ghidra's owner inventory identifies `0x10017DDE` as `terminate` and the
symbol inventory records the decorated entry `?terminate@@YAXXZ` at that
address. The verifier now accepts a preferred public entry only when that
exact name is present among the object's value-zero public text symbols; all
other ambiguous objects continue to fail closed. A pre-edit script backup is
`scripts/verify-coff-dat-relocation-provider.py.pre-terminate-entry-disambiguation-20260928.bak`.

## Fresh rerun

The verifier passes against the current provider object and fresh 705-object
directory:

- Expected and verified data relocation fixup sites: `1521 / 1521`.
- Generated `.text` code relocations: `150`.
- Original startup thunk instruction sequences: `22 / 22`.
- CRT state-table callback byte crosswalk: `177 / 177`.
- Mismatches: `0`.

This is relocation-record and source-byte evidence only. It does not prove
candidate semantic equivalence, original PE section/RVA layout, a production
ASI, hook installation/startup correctness, or runtime/game behavior. The
latest diagnostic DLL remains unsuitable for loading: it is `0xC4000` bytes
of image size versus `0x43000` for the original, and `FUN_100076d0` is linked
at `0x10008D20` instead of `0x100076D0`.
