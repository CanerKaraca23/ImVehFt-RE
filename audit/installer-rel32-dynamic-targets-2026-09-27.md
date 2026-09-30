# Dynamic installer `CALL/JMP rel32` targets

Date: 2026-09-27. `FUN_10002210` used 22 preferred-image displacement constants
for GTA patch sites. With an ordinary relocated link, those values still
pointed at the original ImVehFt virtual addresses, not the newly linked
functions or hook bodies.

## Change

The installer now declares 20 C-linkage `IVF_INSTALL_TARGET_*` wrapper labels
and computes every branch displacement as the linked wrapper address minus the
address after the five-byte `CALL`/`JMP`. The installer still writes the
original opcode and preserves each existing `VirtualProtect` sequence. Each
MASM wrapper is a one-instruction tail jump, so it does not add a stack frame or
change incoming argument/register state. There are 8 candidate-function
destinations and 12 supplemental hook-shim destinations. The 0x004c8415
function-pointer patch is separate and continues to use `&FUN_100076d0`.

The pre-edit installer is preserved as
`src/functions/10002210.cpp.pre-relocatable-hook-targets-20260927.bak`.
`scripts/generate-installer-target-thunks.py` derives wrappers reproducibly
from the preserved inventory in
`audit/installer-rel32-target-inventory-2026-09-27.md`; its generated target
map is `audit/installer-target-thunks-2026-09-27.json`.

## Verification

- Fresh VS2022 x86 strict compile of the full source set: **705/705 pass**,
  `/O2 /W4 /WX /MT`; see `build/strict-installer-rel32-dynamic-20260927.json`.
- Fresh independent ReAgent structural objective: **705 PASS / 0 FAIL / 0
  UNKNOWN**; see `audit/objective-installer-rel32-dynamic-2026-09-27.json`.
- Fresh ReAgent 0.4.0 parity: **704 GREEN / 1 YELLOW / 0 RED**; the sole
  warning remains `100076d0` and concerns unresolved indirect/reentrant
  runtime behavior, not this installer edit. See
  `build/parity-installer-rel32-dynamic-20260927.json`.
- The installer COFF object contains all 20 expected external wrapper
  references; the assembled wrapper object contains 20 `REL32` relocations to
  the mapped candidate/shim symbols. MASM assembly succeeded.

## Limits

The shim and provider objects have not yet been fully linked into a production
PE with the reconstructed image layout. At this checkpoint, installer globals
were still fixed-address operands; the follow-up section below records their
later conversion to provider aliases. Broader `.text`/data relocation,
CRT/import, loader and hook-site integration work remains open. No new `.asi`
was produced, loaded or tested in GTA. These checks do not prove semantic
equivalence or runtime readiness.

## Follow-up: installer data/global addresses

The installer also referenced 13 ImVehFt globals and path buffers by preferred
VA (`0x1003a6c7` through `0x1003c248`). The provider generator now accepts
repeatable `--public-data-address` options and emits both undecorated MASM
labels and underscore-decorated x86 C aliases at the exact original `.data`
offsets. `FUN_10002210` now uses those symbols instead of hard-coded pointers;
its backup is
`src/functions/10002210.cpp.pre-relocatable-installer-globals-20260927.bak`.

The resulting provider object assembles and independently verifies **1,521 /
1,521** expected COFF relocation sites with zero mismatches, including all 13
new public C aliases. Fresh whole-set results after both installer changes:
strict compile **705/705**, ReAgent objective **705 PASS / 0 FAIL / 0 UNKNOWN**,
and parity **704 GREEN / 1 YELLOW / 0 RED**. The sole yellow remains `100076d0`;
the call-count-only waiver guard confirms its semantic warning remains visible.
The 705 source hashes match the manifest.

This closes only these installer operands. The provider and thunks are not yet
linked into a complete original-layout PE; `.text` HIGHLOW relocations,
remaining loader/CRT/import work and runtime/game validation are open. No `.asi`
was emitted or loaded.

## Newly inventoried source literals

A read-only scan of the 705 candidate TUs against the original PE section table
found **323 occurrences / 278 unique original-image VAs** embedded in source:
176 `.text`, 42 `.rdata`, and 105 `.data` occurrences. Only 28 unique literal
addresses exactly match a function entry in the current function map; the
other 250 may be data, interior code labels, or unclassified references and
must be adjudicated individually. This inventory does not assume every literal
is erroneous, but it shows that converting the installer alone has not removed
all preferred-base assumptions from candidate source. See
[`candidate-internal-image-address-literals-v2-2026-09-27.json`](candidate-internal-image-address-literals-v2-2026-09-27.json),
the per-use [CSV](candidate-internal-image-address-literals-v2-2026-09-27.csv),
and [`scripts/inventory-candidate-internal-image-literals.py`](../scripts/inventory-candidate-internal-image-literals.py).
