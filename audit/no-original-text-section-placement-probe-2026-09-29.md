# Candidate-code placement without copied original `.text` — 2026-09-29

## Diagnostic experiment

Using the single-provider 705-object response, removed only
`original_text_entry.obj` from a newly generated response file. This does not
edit or delete the pinned ASI or any source file. Link exit code was 0; three
obsolete `/ORDER` symbol warnings remain.

Output:
`build/link-probe/entry-exact-nogs-o1-single-provider-alias-probe-20260929/ImVehFt-entry-xcode-single-provider-no-original-text-not-ASI.dll`

- SHA-256: `1EE9B0EE4D14CCCA24A9FB4795B65F4E1044C5114BDD0FF50DC08D45CC581AF5`
- Size: 422,912 bytes.
- Candidate `.xcode`: RVA `0x1000`, extent `0x1E69D`, ending at `0x1F69C`.
- Linker/runtime `.text`: RVA `0x20000`, extent `0x13D9C`.
- `.rdata`: RVA `0x34000`, not the original `0x22000`.
- `.data`: RVA `0x43000`, not the original `0x29000`.
- PE entry point: RVA `0xE112`; original entry point: RVA `0x111B3`.

Removing the copied original text lets the candidate code blob begin within the
original `.text` span, but does not prove function-by-function address fidelity:
the map puts the recovered `entry` symbol at RVA `0xE112`, not its original
address. The remaining linked `.text` body (including provider/runtime code)
extends into the original data range and displaces `.rdata`/`.data`. This
output is not installable and must not be loaded.

## Conclusion

Two independent layout contributors are now measured: the copied original
`.text` object delayed `.xcode` to RVA `0x22000`; after removing that object,
candidate code starts at `0x1000` but the extra `.text` body and enlarged
`.rdata` still shift the original data sections. The aggregate diagnostic
linker ordering does not reproduce the original per-function VAs, entrypoint,
section layout, relocations, or startup. Production PE/GTA validation remains
unavailable; no original file or candidate C++ function source changed.
