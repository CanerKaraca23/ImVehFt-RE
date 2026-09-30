# `__ValidateImageBase` in-place PE patch and differential probe

Date: 2026-09-28. This is a one-function integration-mechanism test, not a
705-function build or a production/game test. The original ASI was read-only
throughout; a distinct `.bin` copy was emitted under `build/pe-layout-probe`.

## Ghidra and placement evidence

- Read-only Ghidra 12.1.3 decompilation of hash-pinned `ImVehFt.asi` identifies
  `__ValidateImageBase` at `0x10018090`; its body ends at `0x100180C4`. The
  decompilation validates the DOS signature, PE signature at `e_lfanew`, and
  PE32 optional-header magic `0x10B`.
- The strict x86 object exports `___ValidateImageBase` as a 43-byte executable
  `.xcode` COMDAT with **zero COFF relocations**. The next mapped candidate
  begins at `0x100180D0`, leaving a 64-byte entry gap.
- Ghidra incoming-reference queries covered every byte of the original
  function body. The only references into the body beyond its entry are
  internal branches whose sources are within the replaced 43-byte range; no
  external reference targets the remaining original tail. The original PE
  `.text` HIGHLOW inventory has zero fixup fields overlapping the patch.

## Artifact and validation

- Probe: `build/pe-layout-probe/validate-image-base-single-function-probe-not-asi.bin`
- Probe SHA-256: `425A6250BC2F97B11A471F26D288D96E3379BFCA1E67B00CCEBCAEA6469E0C50`
- Machine report: `audit/validate-image-base-single-function-patch-probe-2026-09-28.json`
- A separate MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness mapped both the
  original ASI and this patched probe with `SEC_IMAGE`, then called the
  function at RVA `0x18090` in each mapping. The original function and
  candidate matched **5 named cases** (including valid PE32, bad DOS/PE
  signatures, PE32+ rejection, and a second safe `e_lfanew`) and **100,000
  deterministic bounded randomized buffers**.
- Harness executable SHA-256:
  `A075EBAA80D6678A9238E1A6A349D4019BC500532389A3FFE01A7E38295995A5`.
- Independent `pefile` parsing verified PE32/i386, all five original sections
  and all 16 data-directory entries unchanged, unchanged entry point and file
  length, and differences restricted to the candidate's original `.text`
  location (`0x17491..0x174BB`, 42 changed bytes within a 43-byte body).

## Limits

The harness does not invoke DLL initialization, imports, TLS/CRT startup,
installer hooks, or GTA. It proves only that this bounded, relocation-free
function can be placed and compared in a copy of the original image. It does
not establish semantic fidelity for this function on inputs outside the
tested domain or validate the other 704 candidates. The `.bin` is deliberately
not named or represented as a loadable ASI. No candidate source was edited.

Reproduce the differential run from the repository root with
`scripts/test-validate-image-base-inplace-probe.ps1`; it creates a fresh,
timestamped harness output directory and refuses to overwrite an existing one.
