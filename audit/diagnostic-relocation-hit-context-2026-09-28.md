# Context classification of diagnostic relocation-move hits

Date: 2026-09-28

Inputs: the `diagnostic-not-ASI.dll` and `.map` named in
`diagnostic-relocation-move-coverage-2026-09-28.json`, the pinned original
`ImVehFt.asi`, and the existing reconstructed assembly sources. This follow-up
classifies hit context; it does not patch or emit an image.

## Code-section candidates

Of the 31 bytewise DWORD hits in executable `.xcode`/support `.text`, Capstone
32-bit linear disassembly identified 14 whose exact four bytes form a decoded
instruction immediate or absolute displacement. All 14 values fall in the
*original* ASI's still-preserved `.rdata`/`.data` VA ranges, not in an appended
candidate section in the intended final layout. They must therefore remain
pointing at the original VAs when those original data sections are retained;
adding the diagnostic-section move delta to these values would be wrong.

| Diagnostic operand VA | Encoded target VA | Reconstructed function/object context |
| ---: | ---: | --- |
| `0x100315F6` | `0x10029C0C` | `FUN_10011032`, `10011032.obj` |
| `0x100338DE` | `0x10029490` | `__SEH_prolog4`, `10012e20.obj` |
| `0x10037E11`, `0x10037E16` | `0x10028180` | `___RTC_Initialize`, `10016cc6.obj` |
| `0x10037E21`, `0x10037E26` | `0x10028188` | `FUN_10016CEC`, `10016cec.obj` |
| `0x1003E7D0` | `0x100258E0` | `FUN_1001C9BC`, `1001c9bc.obj` |
| `0x10040018` | `0x10029490` | `__EH_prolog3_catch`, `1001e03d.obj` |
| `0x10043131`, `0x10043143` | `0x100396DC` | `FUN_1002049A`, `1002049a.obj` |
| `0x10043155` | `0x100396E8` | `FUN_1002049A`, `1002049a.obj` |
| `0x10043E52` | `0x100399E0` | `FUN_10021267`, `10021267.obj` |
| `0x10043E56` | `0x10022250` | `FUN_10021267`, `10021267.obj` |
| `0x10043E5B` | `0x100399E0` | `FUN_10021267`, `10021267.obj` |

The source corroborates this distinction: `src/functions/10011032.cpp` embeds
the old-image data VA `0x10029C0C`; `src/functions/10021267.cpp` emits the
original data VAs `0x100399E0` and `0x10022250`. The pinned reference section
table places those targets in original `.data` or `.rdata`. These are fixed
image-address references, not references to the diagnostic link's accidental
overlapping `.xcode` mapping.

The other 17 executable-section DWORD matches did not begin a four-byte
immediate/displacement field. Fourteen fell within decoded instructions but
inside opcodes or shorter/non-address operand fields. Three support-runtime
sites initially missed by section-start linear sweep were decoded from their
link-map function starts:

| DWORD scan site | Containing instruction | Why it is not a 32-bit pointer operand |
| ---: | --- | --- |
| `0x100586DB` | `0x100586DA: jns 0x100586FC` | 1-byte relative branch displacement |
| `0x10058DE3` | `0x10058DE2: je 0x10058DE9` | 1-byte relative branch displacement |
| `0x10059762` | `0x10059761: je 0x10059791` | 1-byte relative branch displacement |

Therefore none of the 17 remaining byte-pattern hits is a decoded 32-bit
absolute immediate/displacement operand. They are scan-window coincidences,
not evidence of live pointers.

## Data-section candidates and provenance

The 147 raw `.data` hits resolve by nearest public symbol/object in the link
map as follows:

| Object provenance | Count | Interpretation |
| --- | ---: | --- |
| `internal_data_alias_probe.obj` | 89 | Diagnostic alias-probe data; values resolve to original `.data`/`.rdata` VAs. Not production candidate data. |
| `internal_rdata_alias_probe.obj` | 8 | Diagnostic alias-probe data; values resolve to original `.data`/`.rdata` VAs. Not production candidate data. |
| `exception_abi_probe.obj` | 44 | Diagnostic vtable/function-pointer entries aimed at candidate bodies in the current `.xcode`; if this probe is retained after moving code, its entries need rebasing. The link response shows it comes from the historical buildcheck probe directory, not a candidate function object. |
| Reloc-aware DAT provider / PNG provider | 6 | All six match original `.data` raw bytes exactly at the corresponding source VAs; they are copied original bytes, not move fixups. |

This explains why the earlier 182-count must not be treated as 182 confirmed
production fixups. The 97 alias-probe hits (89 + 8) are diagnostic fixtures,
and the 44 exception ABI vtable entries are also supplied by a probe object.
The current response file is an experiment assembled from a historical
704-candidate buildcheck directory plus current 705 candidate objects; it is
not a production source/link recipe. The six provider hits were further
checked against the original `.data` bytes: each window is byte-identical at
its source VA, including all three PNG-provider matches.

The six byte comparisons are reproducible with
`scripts/verify-diagnostic-provider-hit-byte-inheritance.py`; it pins the
original ASI SHA-256 and verifies all six source-VA/object-offset pairs. The
run returned six PASS results.

## Updated move decision

The HIGHLOW table plus this context is still not a full rebase proof. It does,
however, narrow the work:

1. Preserve original `.rdata`/`.data` VAs and leave reconstructed fixed-image
   address operands targeting those sections unchanged.
2. Exclude the diagnostic alias probes from any production-equivalent link.
3. If the exception ABI probe is used for further layout tests, explicitly
   rebase its candidate-function vtable entries; do not silently retain them.
4. Exclude the six proven original-data byte matches from move fixups.
5. Rebuild and audit imports, entrypoint/CRT setup, and the combined base
   relocation directory before any PE can be called loadable.

No source candidates or installed ASI were modified. No final ASI or GTA test
was produced.
