# Single-provider alias link probe — 2026-09-29

## Change and reproducibility

The clean-signature 705-object response was relinked after adding 149 exact
external data aliases directly to a *copy* of the existing IA32 relocation
provider COFF symbol table: 82 current link aliases, 21 callback-vtable
crosswalk aliases, and 46 CRT data aliases. The new helper
`scripts/add-coff-external-data-aliases.py` resolves every alias through the
pinned original PE's `.data`/`.rdata` RVA map and appends COFF external symbol
records without changing section bytes or the input object. The input provider
and original ASI were not modified.

- Input provider SHA-256: `A762ED761DEAD500A782856642D21ACC33C6D65092A7F73F82C3B46E80B8595E`
- Alias-augmented provider SHA-256: `DCD1A99305EF1E4F2739C8285A1BEAB5FA48E7D3EE68A6C3700DB129DF9BBBAB`
- Alias inventory count: 149 distinct symbols; some symbols intentionally share an address.
- COFF `.data` raw size: `0x1455C` before and after; `.rdata`: `0x7000` before and after.
- The linker map resolves every alias name, but preceding linker contributions
  still shift their final output offsets (for example original `.data+0x1D0`
  becomes output `.data+0x204`; original `.rdata+0x2208` becomes output
  `.rdata+0x3028`). The names therefore resolve, but output addresses are not
  original-image addresses.

`scripts/prepare-single-data-provider-link-probe.py` replaces the original
provider in the fresh 705-object response and retains the CRT alias directive
object while omitting the three redundant full-section alias providers. The
link succeeded (exit 0) with only three stale `/ORDER` warnings for obsolete
symbol spellings. Diagnostic DLL SHA-256:
`4695F6F853B3548F85A14E268E0C58E7C669700FD5D52F9E0A4DE8C355A321CF`;
size 555,008 bytes versus 890,880 bytes in the four-copy diagnostic. This is
an improvement in diagnostic link construction, not source or runtime proof.

## Remaining layout blocker

The single-provider image is still not loadable and is not an ASI. Its
`.xcode` occupies RVA `0x22000`, colliding with the original `.rdata` RVA
`0x22000`; output `.rdata` is at `0x55000` and `.data` at `0x64000`, rather
than original `0x22000` and `0x29000`. The copied original entry-text section
occupies RVA `0x1000` through `0x213FF`, leaving candidate code emitted as a
separate `.xcode` section. The provider-consolidation change removes duplicate
data storage but does not map recovered code bodies back onto their original
function addresses or solve complete PE relocation/startup behavior.

No candidate C++ function source, pinned original ASI, installed mod, or game
state was changed. Do not rename, install, or load this diagnostic DLL.
