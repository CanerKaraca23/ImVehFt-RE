# `100110bd` root implementation follow-up — 2026-09-29

## Why the previous structural red was genuine but representation-driven

Ghidra's pinned-original export identifies `100110bd` as a non-thunk,
three-argument `__fastcall` routine. Its x86 entry receives two arguments in
ECX/EDX and leaves the third caller-pushed argument on the stack; Ghidra's
function ends in plain `RET`. The prior candidate represented the function as
a 5-byte naked tail-jump plus a separately named `_impl`. The focused runtime
test showed the ABI could match, but both structural analyzers only inspected
the tiny entry source body and correctly reported a call/control-flow
mismatch.

The source now places the two-register-argument implementation directly in the
address-mapped `___DllMainCRTStartup` function. It reads the preserved third
argument at `[EBP+8]`, as before, and emits a plain `RET`. A COFF
`/alternatename` directive aliases the historical three-argument decorated
entry symbol to the emitted two-argument symbol; the existing `100111b3`
caller still pushes the third argument, calls the three-argument name, then
removes that argument itself. The Ghidra-exported three-parameter signature,
register/stack contract, cleanup, branch structure, and call ordering are not
waived or hidden.

The prior files were preserved before editing:

- `src/functions/100110bd.cpp.pre-root-impl-red-recheck-20260929.bak`
- `src/functions/100111b3.cpp.pre-root-impl-red-recheck-20260929.bak`

## Fresh evidence

- Exact current-source strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`
  build: **705/705**, report
  `build/strict-xcode-nogs-o1-100110bd-root-impl-20260929.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  report `audit/objective-independent-100110bd-root-impl-2026-09-29.json`.
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**, report
  `build/parity-100110bd-root-impl-20260929.json`; `100110bd` has no findings.
- Fresh COFF disassembly/symbol inspection confirms the candidate body is
  rooted at the implementation and both decorated names resolve to the same
  address. The caller object is still the previously verified `100111b3`;
  a full 705-object diagnostic relink with the new `100110bd` object completed
  without `/FORCE` or unresolved external errors:
  `build/link-probe/100110bd-root-impl-clean-link-20260929/`.
- The hash-pinned-original differential was rebuilt with the new object and
  run in **five fresh x86 processes**. Each process matched 256 direct calls,
  256 full `100111b3` entry calls, and 128 controlled startup-branch cases;
  all return values, call order/arguments, and ESP deltas matched. Direct-call
  ESP delta remained `-4`; full-entry delta remained `0`.
- Candidate object SHA-256:
  `C95B718C5CF1F52B68DAF22AC975B7AA7576B5696FEBA1E06F8C5C3D8F196D42`.
- Harness executable SHA-256:
  `BE24566FC2ECDFC7BF6C3B4050AD4F9997D1E7E125DD48D3A7021C6635A1E5F7`.
- The two 705-row SHA-256 manifests were refreshed after the source change;
  the previous manifests were backed up by `scripts/refresh-source-manifests.py`.

## Scope limits

This closes the previous **structural analyzer finding** for `100110bd`; it
does not validate real CRT/plugin side effects in a live process or all
exception/unwind and thread-notification behavior. The full link remains a
diagnostic DLL, not a production `.asi`. Its PE sections still do not reproduce
the original addresses/data bytes; `.data`/relocations/imports/hooks and GTA
runtime integration remain to be reconstructed and checked. The 705/705
automated reports are structural gates, not a claim that all 705 functions
have full semantic differential coverage.
