# Diagnostic-link code-layout measurement

Date: 2026-09-28. Reference ASI SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Measurement

Inspected the latest link map:
`build/link-probe/strict-704-historical-sdk/ImVehFt-relocatable-hook-shims-diagnostic-not-ASI.map`.
Its output code contributions are `.text$mn = 0x84315` and `.text$x = 0x6cc`,
for `0x849e1` total bytes before PE section alignment. The original ASI `.text`
virtual size is `0x2027b`. This first comparison is the *whole linked image*,
including statically linked MSVC runtime code, not only the 705 candidate
translation units. A fresh read-only COFF inventory of the 705 candidate
objects sums their raw `.text*` sections to `0x21e0c` bytes (705 objects, 798
code sections), about 1.05 times the reference `.text`; therefore the 4.15x
figure must not be attributed to candidate code alone.

The link map confirms concrete address drift: `_FUN_100076d0` is at
`0x10008D20` instead of `0x100076D0` (delta `+0x1650`); `_FUN_10021267` is at
`0x10024450` (delta `+0x31E9`). The input response is already ordered by
address-named candidate object, so the positive drift is not fixed by input
order alone. A follow-up `/OPT:REF` link removed much of the unused CRT COMDAT
code, but dropped 137 candidate object entry symbols; a second `/OPT:REF` link
rooted all 746 externally visible candidate code symbols (covering all 705
objects), but still had `FUN_100076d0` at `0x10008D20` and `FUN_10021267` at
`0x10024070`. That link's `.text` is `0x36dac` and `SizeOfImage` is `0x71000`.
The latter is a materially better size probe, not a viable ASI. Candidate
sections alone exceed the reference `.text` by about 5.4%, before support
code, so direct one-to-one placement of every byte within the old code
interval is not available. A production layout must account for moved
implementations, stable entry thunks, all internal absolute references, hook
entrypoints, code/data ranges, and overlaps. This report does not claim that
such a PE has been produced.

## Decision / validation boundary

Do not load the diagnostic DLL. Its successful resolution is still useful as
symbol/relocation evidence, but its code layout and PE image size are not
compatible with the reference image. The 705/705 compile, structural
objective, and parity checks remain source/static evidence only; they do not
prove the current linked code can safely replace the original module.
