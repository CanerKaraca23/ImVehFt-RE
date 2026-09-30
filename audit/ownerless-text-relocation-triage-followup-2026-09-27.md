# Ownerless `.text` relocation triage follow-up

Date: 2026-09-27. Rechecked the 200 original `.text` HIGHLOW source sites
whose containing instruction has no Ghidra function owner, using
`audit/asi-text-highlow-ownerless-instruction-sites-2026-09-27.csv` and the
current `scripts/reloc_local_code_stubs.py` inventory.

The previous hook-CFG crosswalk accounts for 128 of the 200 instruction sites;
72 remained outside that specific crosswalk. The five sites at `0x1000caa3`,
`0x1000caf3`, `0x1000cb43`, `0x1000cb93`, and `0x1000cbe3` are now each
represented in the five exact-byte callback-dispatch templates. The current
provider object defines their five symbols and the freshly compiled
`1000bca0.obj` has matching DIR32 relocations to those symbols.

This leaves 67 sites outside both the previous hook-CFG crosswalk and the
simple local-stub fixup list. They are distributed across 10 address clusters
after removing the five callback sites (64-byte clustering heuristic, not
function boundaries). The CSV shows several distinct families: the
`0x10013025` CRT `_initterm_e` state-table body, CRT/startup and registration
code around `0x10020848`–`0x10020a60`, an entry shim at `0x10001000`, and
smaller ranges near `0x10001859`, `0x100030b1`, `0x100104cd`, `0x10014c49`,
`0x1001704e`, and `0x1001c5e2`. These must not all be treated as missing
candidate-function work: candidate TUs naturally emit their own linkable
references, while CRT/helper fragments require provider-specific proof.

The generated provider v26 independently verifies 1,521/1,521 original
`.rdata`/`.data` fixups and the callback templates, but that result is not a
site-by-site disposition of the 3,160 original `.text` HIGHLOW records.
Remaining work is to map the 67 addresses to candidate object relocations,
dedicated CRT/helper templates, or genuinely uncovered executable/data
fragments. Do not infer `.asi` readiness from this inventory.
