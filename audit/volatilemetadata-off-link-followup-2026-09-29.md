# `/volatileMetadata-` full-set follow-up — 2026-09-29

## Controlled candidate build

The isolated x86 MSVC 14.44 test showed that `/volatileMetadata-` is accepted.
For `10006be0`, the `.voltbl` section disappeared while the `.xcode` bytes,
flags, and relocations remained unchanged. A fresh strict `/O1 /GS-` build was
then made for all 705 translation units into
`build/recheck/strict-xcode-nogs-o1-volatilemetadata-off-20260929/`; report:
`build/strict-xcode-nogs-o1-volatilemetadata-off-20260929.json`.
Result: **705/705 compiled**.

`scripts/verify-volatile-metadata-code-equivalence.py` compared that set with
the exact-source `/O1 /GS-` baseline in
`build/recheck/strict-xcode-nogs-o1-1ae25-return-20260929/`. It confirmed
**705/705** preserve executable code bytes, flags, relocations, non-debug
runtime sections, and public symbols. `.voltbl` was removed from **29/705**
objects. Debug/checksum metadata was excluded from the comparison; no source
file was edited by this compiler-option experiment.

## Linker-map probe and limitation

A diagnostic relink using the saved response template and the new candidate
objects measured `.rdata$voltmd` at `0x8c` bytes, compared with `0x564` bytes
in the template's prior map: a reduction of `0x4d8`. The residual contribution
comes from support objects that were not rebuilt with `/volatileMetadata-`.
The map also retains `.rdata$zzzdbg` at `0x248` bytes.

The first relink attempt exposed stale `/INCLUDE` roots for `10001db0`,
`1001074b`, and `1001023b`, plus the old decorated `10009790` symbol in the
data provider. A fresh response file now roots the current candidate symbols
and aliases the provider's address-only `10009790` reference to the current
symbol. The resulting relink completed **without `/FORCE` and without any
unresolved external errors**:
`build/link-probe/volatile-metadata-off-clean2-20260929/ImVehFt-xcode-705-diagnostic-not-ASI.dll`
(SHA-256 `66BC2674EDFAA8D8852FCCD1C823D8A3B1D920C1FEFCFA273A22232ADF0D101C`).
Three LNK4037 warnings remain because the saved COMDAT order file names the
old decorated forms of `10001db0`, `1001023b`, and `1001074b`; those missing
order hints were ignored by the linker.

This successful link is still a diagnostic DLL, not an ASI. Its PE section
table places `.data` at RVA `0x43000`, not the original RVA `0x29000`, and it
does not preserve the original section bytes or hooks. Its `.xcode` and support
code layout also differs from the pinned mod. The clean link proves only that
the full candidate set and this provider/support set resolve under this test
recipe; it does not prove original PE placement or production readiness.

Microsoft documents `/volatileMetadata` as metadata for x86/x64 emulation on
ARM64 and documents the negative spelling; this switch is distinct from
`/volatile:iso` and `/volatile:ms`. The latter alter language memory-ordering
semantics and were not changed. Source: [Microsoft `/volatileMetadata`
reference](https://learn.microsoft.com/en-us/cpp/build/reference/volatile?view=msvc-170).

## Decision

Keep `/volatileMetadata-` as a promising build-layout experiment, not yet a
production build setting. Rebuild or replace the four stale support/provider
objects using current signatures, then repeat a clean full diagnostic link and
inspect every emitted PE section, data alias, relocation, import, entry point,
CRT/TLS path, and hook target. No output from this experiment should be loaded
in GTA or installed as the mod.
