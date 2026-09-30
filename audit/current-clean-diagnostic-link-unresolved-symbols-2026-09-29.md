# Probe-free diagnostic link failure — 2026-09-29

## Experiment

Started from `build/recheck/entry-xcode-exact-20260929.rsp`, remapped all 705
candidate objects to the fresh `/O1 /GS-` build, and removed four historical
test/probe objects: `exception_abi_probe.obj`, `crt_abi_alias_probe.obj`,
`internal_data_alias_probe.obj`, and `internal_rdata_alias_probe.obj`.
Response-file generation is reproducible with
`scripts/filter-link-response-for-layout-probe.py`; the generated response is
`build/recheck/entry-xcode-nogs-o1-clean-active-20260929.rsp`.

The linker failed, reporting **283 LNK2019/LNK2001 diagnostics for 185 unique
unresolved symbols**. Full output:
`build/link-probe/entry-exact-nogs-o1-clean-active-20260929/clean-link-unresolved-20260929.log`.
No linked DLL was emitted by this failed attempt.

## What the result means

The earlier successful original-entry-template diagnostic link depends on
those four removed objects. The two internal alias probes contain `/ALTERNATENAME`
directives that redirect numerous original-address data symbols to synthetic
`_reagent_probe_*` labels. The CRT alias object is also primarily `.drectve`
aliases, while the exception probe contributes vtable data and test ABI
symbols. They are useful diagnostic scaffolding, but their successful link is
not evidence that production data/exception support has been integrated.

Unresolved names include callback-manager vtables, `PTR_vftable_*` and
`PTR_DAT_*` data aliases, exception ABI symbols, and CRT/SEH routines. They
need to be mapped to exact original section bytes/symbols or to Ghidra-backed
candidate implementations; blindly restoring the probes would preserve the
same unresolved production-integrity question.

## Current gate

This experiment made no candidate-source or original-ASI changes. It narrows
the next link task to building real definitions/aliases for the unresolved
symbols, while retaining the preserved original section layout and resolving
the appended-code/base-relocation problem. There is still no production `.asi`
and no GTA load/gameplay validation.
