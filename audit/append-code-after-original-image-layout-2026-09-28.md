# Append candidate code after the preserved original image

Date: 2026-09-28

## Finding

The `original-entry-xcode-layout` diagnostic places its `.entry` contribution
at the original `.text` start and its `.xcode` contribution at `0x10022000`.
That address is also the original `.rdata` start, so that diagnostic layout
cannot preserve the original data addresses.

PE header and section-table values were reread from the hash-pinned original
`ImVehFt.asi` and the current diagnostic DLL:

| Image / section | VA | Virtual size | End (exclusive) |
| --- | ---: | ---: | ---: |
| Original `.text` | `0x10001000` | `0x2027B` | `0x1002127B` |
| Original `.rdata` | `0x10022000` | `0x6F44` | `0x10028F44` |
| Original `.data` | `0x10029000` | `0x1455C` | `0x1003D55C` |
| Original `.rsrc` | `0x1003E000` | `0x2B8` | `0x1003E2B8` |
| Original `.reloc` | `0x1003F000` | `0x3F44` | `0x10042F44` |
| Original `SizeOfImage` boundary | `0x10043000` | — | — |
| Diagnostic `.xcode` | `0x10022000` | `0x230D5` | `0x100450D5` |

The original image uses image base `0x10000000`, section alignment `0x1000`,
and file alignment `0x200`. The exact original `.text` raw bytes were separately
compared to the diagnostic `.entry` raw bytes and matched (`0x20400` bytes;
SHA-256 `BD691CB790F42EBB2ADBEE6D9761B7D03E46093C28DEC59C719845B342DB4CF7`).

If the diagnostic support sections are appended in their current order after
the original `SizeOfImage`, simple `0x1000`-aligned arithmetic gives this
non-overlapping *hypothetical* extension:

| Appended section | Proposed VA | Virtual size | End (exclusive) |
| --- | ---: | ---: | ---: |
| `.xcode` | `0x10043000` | `0x230D5` | `0x100660D5` |
| support `.text` | `0x10067000` | `0x13D1C` | `0x1007AD1C` |
| support `.rdata` | `0x1007B000` | `0xEDA4` | `0x10089DA4` |
| support `.data` | `0x1008A000` | `0x24164` | `0x100AE164` |
| `.fptable` | `0x100AF000` | `0x80` | `0x100AF080` |
| support `.reloc` | `0x100B0000` | `0x3494` | `0x100B3494` |

The resulting aligned `SizeOfImage` would be `0xB4000`. This confirms there is
address-space room; it does not prove that moving the diagnostic sections and
updating all absolute references/relocation-directory RVAs is correct.

## Layout direction

The next layout experiment should preserve original `.text`, `.rdata`, `.data`,
`.rsrc`, and `.reloc` at their original RVAs, then append reconstructed
executable and support sections at or after `0x10043000`. This removes the
proven `.xcode`/`.rdata` RVA collision without shrinking the requested
705-function scope. The first appended executable range can be section-aligned
at `0x10043000`; the present candidate code virtual size (`0x230D5`) fits there
as a distinct section.

## Gates still required

This is a placement hypothesis, not a completed PE transformation or a
loadable ASI. The new link must demonstrate all of the following before any
stub patching or runtime attempt:

1. Original non-code section contents and original RVAs are preserved, with
   `.data` zero-fill/virtual tail handled correctly.
2. Every candidate and support section has a unique, non-overlapping RVA;
   all 705 entry branches resolve to executable candidate bodies.
3. The final base-relocation directory correctly covers moved/appended code
   and data references, while original relocation semantics remain intact.
4. Imports, CRT/static initialization, PE directories, and the ASI loader's
   expected DLL characteristics are understood and verified.
5. Only after static PE verification should controlled loader/GTA testing be
   considered; candidate compile/parity checks do not prove runtime behavior.

No production candidate source or installed ASI was modified by this audit.
