# Current exact-object relayout investigation — 2026-09-30

This is a fresh layout/fixup inventory for the post-startup-edit 705-object set;
it supersedes earlier placement reports that used prior object hashes. No PE or
ASI was patched or installed.

## Fresh evidence

- Fresh exact-object diagnostic link succeeded with no unresolved linker errors.
  It has 19 stale `/ORDER` warnings and an oversized `SizeOfImage` of `0xE9000`
  (original `0x43000`); it is not a candidate. Its seven diagnostic-only
  `IVF_RELOC_TARGET_*` aliases all point to the same dummy `0x100DBF84`, so those
  addresses are explicitly unusable for final fixups. See
  `current-set-ghidra-cleanup-exact-diagnostic-link-2026-09-30.md`.
- Fresh fit and placement reports use the current 705 object hashes and the
  fresh diagnostic map. Of 705 entries, 560 bodies fit the bounded neighboring
  entry gap; linear instruction-boundary review reduces this to 288; four
  saved Ghidra interior references across three functions reduce it to a
  conservative **285 direct bodies / 420 thunk bodies**. All 705 diagnostic
  body targets are executable and rel32-reachable. This is static placement
  feasibility, not a proof that unknown/runtime references are absent.
- The 420 thunk payload has 82,548 body bytes, 2,086 referenced local `.rdata`
  bytes, and 87,691 combined bytes before file alignment. The COFF inventory
  has 2,850 fixups (1,580 DIR32, 1,270 REL32); 118 same-object `.rdata`
  sections require copying.
- Thunk windows have zero recorded Ghidra references to overwritten offsets
  1–4, but intersect 63 old `.text` HIGHLOW sites. Eight preserved old bodies
  have 92 saved static non-entry references after the five-byte patch window.
  These require final-image reconciliation.
- Historical note: the older report set described 421 appended roots / 284
  direct bodies and is not the current object placement. Its counts must not be
  carried forward. The current plan is 420 appended / 285 direct as listed
  below; the new v5 direct-target report is regenerated from those exact inputs.

## Follow-up target and callsite resolution

The previous paragraph is superseded by these fresh joins against the same
exact-object set:

- All 467 address-encoded symbols / 1,014 references in the complete appended
  body plus local-section closure map to original PE sections; none are
  unmapped. All 122 provider symbols / 177 references map to original preferred
  VAs, and the separate import-slot crosswalk matches 63/63 imported COFF
  symbols to the original IAT.
- The nine arithmetic calls now have an 82-byte bridge plan at provisional VA
  `0x1005A960`; the bridge calls the byte-identical original helper bodies at
  `0x1001DDA0` and `0x1001A900`. All nine caller REL32 fixups are in range.
  This plan is not applied. The previously recorded 100,209-case harness tests
  the bridge ABI/results against those helper bodies, excluding divide-by-zero
  and signed `INT64_MIN / -1`; it is not loader/game validation.
- A fresh API callsite plan covers 194 current `CALL rel32` sites (139 in-place,
  55 appended) through 21 exact `FF 25` IAT thunks; all displacements are in
  range at the bridge layout's API thunk offset. A fresh direct-body executable
  target audit accounts for 713/713 code relocation occurrences: 569 candidate
  entry targets, 139 exact API-thunk joins, and five same-object code-section
  targets; zero unresolved. This is address/fixup classification, not semantic
  proof. The v4 report had a stale “284 direct-body” scope caption despite its
  285-row contents; its generator now derives the count from the placement plan,
  the original script is backed up, and v5 has the corrected caption.
- Re-ran the appended-root local-section census using the exact 420-root
  payload, current relocation targets, and current root map. The fresh v2 report
  finds 16 referenced non-`.rdata` sections (`14 .xcode`, one `.data`, one
  `.bss`), 11,062 virtual bytes, and 222 section relocations. This payload was
  absent from the 87,691-byte code+root-`.rdata` census. Its 196 undefined
  external occurrences include 91 symbol/type pairs absent from the root-only
  symbol inventory; they require the full-closure maps, not guessed targets.
- Rebuilt the candidate-code HIGHLOW inventory from the current 285/420 plan:
  4,681 original sites reconciled, 954 removed from replaced byte ranges,
  805 in-place DIR32 sites, 1,583 appended body/root-`.rdata` sites, and 21
  original-IAT thunk sites produce a 6,136-site / 12,884-byte serialized
  baseline. It fits the original `.reloc` capacity; it is not written to the ASI.
- Recomputed the 420-root same-object fixups together with the 285-direct
  local-section closure. The report joins 229 root-to-local fixups and 26
  closure-internal fixups; it inventories 128 closure DIR32 sites and adds the
  113 direct-closure HIGHLOW sites. The extended directory is 6,377 sites /
  13,400 bytes, round-trips exactly, and fits the 16,384-byte original section.
  The two additional literal sections add 10 bytes, and all recomputed REL32
  fixups fit. Undefined external values, PE writes, loader/startup, and game
  behavior remain unverified.
- Replanned the three cross-object `.xcode` helper sections against the new
  current bridge/direct layout: all 29 references join, all three helper
  relocations are in range, 77 helper bytes are placed, and `.rdata` does not
  shift again. Then generated a field-level manifest for all 420 appended
  bodies plus their copied local-section closure: **3,075/3,075 fields** have
  unique sites and computed targets (1,708 DIR32, 1,367 REL32), with every
  REL32 in range. This remains a provisional fixup plan, not fields written to
  objects or a PE; it does not validate target semantics, startup, or game
  behavior.
- Availability check: the previously named `Downloads\SA Plugin SDK` path is
  absent now; the supplied `.ImVehFt` mod folder contains the two ASIs/logs but
  no `.sln`, `.vcxproj`, `.cpp`, or headers. Thus an original project/SDK build
  and source-to-binary comparison are not currently possible from those paths.
- Two audited tools had stale assumptions about fixed 421/284 counts and
  diagnostic map target classes. Their originals are preserved as
  `scripts/plan-crt-original-helper-bridge-rel32-fixups.py.pre-dynamic-705-placement-20260930.bak`,
  `scripts/audit-inplace-candidate-local-section-closure.py.pre-dynamic-direct-count-20260930.bak`,
  `scripts/audit-inplace-direct-executable-targets.py.pre-api-reloc-class-independent-20260930.bak`,
  `scripts/audit-inplace-direct-executable-targets.py.pre-candidate-code-target-class-20260930.bak`,
  `scripts/audit-inplace-direct-executable-targets.py.pre-candidate-entry-crosswalk-20260930.bak`,
  and `scripts/audit-inplace-direct-executable-targets.py.pre-local-xcode-symbol-va-20260930.bak`.
  Re-runs are recorded separately below. Current local-section placement and
  the complete HIGHLOW table still require a unified regenerated layout.

## Reproducible reports

- `entry-slot-fit-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `entry-trampoline-feasibility-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `inplace-candidate-relocations-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `inplace-instruction-boundaries-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `inplace-interior-xrefs-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `placement-plan-conservative-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `thunk-entry-window-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `appended-thunk-relocation-targets-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `appended-thunk-payload-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `appended-thunk-link-map-resolution-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `appended-thunk-code-target-classes-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `appended-thunk-full-closure-link-map-resolution-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `full-closure-address-encoded-coff-targets-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `full-closure-provider-original-addresses-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `full-closure-original-import-crosswalk-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `crt-original-helper-bridge-rel32-fixups-ghidra-cleanup-exact-linkmap-2026-09-30.json`
- `current-api-callsite-rel32-fixups-ghidra-cleanup-exact-linkmap-2026-09-30-v2.json`
- `inplace-direct-executable-targets-ghidra-cleanup-exact-linkmap-v4-2026-09-30.json`
- `inplace-direct-executable-targets-ghidra-cleanup-exact-linkmap-v5-2026-09-30.json`
- `appended-thunk-local-section-closure-ghidra-cleanup-exact-linkmap-v2-2026-09-30.json`
- `all-705-candidate-code-relocation-directory-exact-285-420-2026-09-30.json`
- `appended-local-section-rva-shifts-exact-285-420-2026-09-30.json`
- `inplace-local-section-closure-exact-285-direct-2026-09-30.json`
- `appended-cross-object-code-sections-exact-285-420-2026-09-30.json`
- `appended-all-fixups-exact-285-420-2026-09-30.json`

The existing extended local-section / relocation reports are still based on
the older 421-root / 284-direct placement. They are historical, not valid for
the current 420/285 production plan. A fresh unified local-section layout and
HIGHLOW directory regeneration from current objects remains required.

## Gate

These reports make the current placement plan and remaining fixup classes
actionable, but do not establish a production PE. Exact original-VA target
resolution, API-thunk fixups, local/cross-object section closure, complete
relocation directory regeneration, PE structural checks, startup execution,
and isolated GTA/game validation remain open. Do not install the diagnostic
DLL or the known-crashing v7/v8 ASIs.
