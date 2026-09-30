# Appended-section PE header capacity check

Date: 2026-09-28. Read the PE32 headers of the SHA-pinned original ASI and
current 705-object diagnostic link without modifying either binary.

## Measured values

- Original image: 5 section headers; section table ends at file offset
  `0x2A8`; first raw section begins at `0x400`.
- Header slack: `0x158` bytes = 344 bytes, enough for **8** additional 40-byte
  section headers (320 bytes), leaving 24 bytes.
- The prior append-layout hypothesis needs 6 new section records
  (`.xcode`, support code, support read-only data, support data, FP table, and
  a consolidated relocation section): 240 bytes. Thus section-header capacity
  is not the current blocker; 2 additional slots remain after this proposal.
- Original image base is `0x10000000`; section/file alignments are `0x1000` /
  `0x200`; original `SizeOfImage` is `0x43000`.
- Diagnostic has 7 sections and `SizeOfImage=0x93000`; it is still explicitly
  diagnostic-only. The proposed appended addresses from
  `audit/append-code-after-original-image-layout-2026-09-28.md` are arithmetic
  placements, not emitted sections.

## Scope and next gates

This only establishes that enough header-table room exists to describe the
proposed extra sections. It does not prove section characteristics, raw-file
offsets, virtual placement, import/TLS/CRT directory behavior, relocation
merging, fixed-address callbacks, loader acceptance, or runtime correctness.
No ASI or diagnostic image was patched. The next PE-layout implementation
must emit only to a new artifact path, preserve the original file, and verify
all original sections/RVAs plus the appended sections and merged relocation
directory with an independent PE parser before any loader test.
