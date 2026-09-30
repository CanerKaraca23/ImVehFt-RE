# x87 code-generation and vector-storage follow-up

Date: 2026-09-28. Exact target: `ImVehFt.asi`, SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Findings and candidate corrections

The normal MSVC x86 strict profile passed, but object disassembly showed that
some newly corrected binary64 expressions became SSE2 instructions, while
Ghidra's exact-target assembly used x87. An isolated `/arch:IA32` compile of
the affected TUs emitted x87 qword operations for the inspected constants.
The strict compiler harness now has an opt-in `-UseIa32FloatingPoint` mode;
this is a diagnostic compatibility profile, not evidence of the original
project's precise compiler switches.

Stack inspection found that several candidate functions modeled adjacent
three-float vectors as independent scalar locals, then passed the first local's
address to opaque transform/render functions. The optimizer removed updates
to the third scalar because the C++ source did not express a three-element
object. The candidates now use actual contiguous `float[3]` storage in
`10003400`, `10003660`, `10005b60`, `10005d30`, and `10005ef0`. The regenerated
x87 objects retain the Ghidra-indicated `0x10024fd0`, `0x10024f48`, and
`0x10024eb0` operations. Additional widths were corrected at `0x10024fb0`
and `0x10024f08`.

Backups for the candidate files are preserved with suffix
`.pre-double-constant-width-batch-20260928.bak`; the source manifests were
refreshed and separately backed up.

## Fresh checks

- Targeted x86 `/O2 /W4 /WX /MT /arch:IA32` compile: all changed TUs pass.
- Full x86 `/arch:IA32` strict compile: **705/705**, report
  `../build/strict-all-ia32-x87-final-20260928.json`.
- Independent objective scanner: **705 PASS / 0 FAIL / 0 UNKNOWN**, report
  `objective-ia32-x87-final-2026-09-28.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**, report
  `../build/parity-ia32-x87-final-20260928.json`.
- Fresh all-object diagnostic link: succeeded to
  `../build/link-probe/strict-704-historical-sdk/ImVehFt-ia32-x87-final-diagnostic-not-ASI.dll`
  (782,336 bytes). This artifact is not a loadable ASI.
- Source manifest: 705 entries, zero current hash mismatches.

## Follow-up: implicit x87 alpha input in `10007030`

The two previously missing constants were traced through the exact target
assembly and the `FUN_1001ba40` helper. The helper consumes its primary numeric
input from x87 ST(0), not from an explicit C++ parameter. At `10007030`, the
target selects either binary64 `0x10024f18` or `local_18 * binary64
0x10024f20` using the `FCOM`/`FNSTSW`/`TEST AH,0x41` condition, then preserves
that value in ST(0) while arranging other callback arguments. The candidate
now reproduces that comparison, both qword operations, and the helper call's
ECX/EDX plus implicit ST(0) input in inline x86 assembly.

Evidence and checks for this follow-up:

- Preserved source backup:
  `src/functions/10007030.cpp.pre-implicit-x87-alpha-fix-20260928.bak`.
- Fresh MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` object disassembly contains the
  conditional qword multiply/load and calls `FUN_1001ba40` with ST(0) live;
  targeted compile passed.
- Fresh full strict compile: **705/705**,
  `../build/strict-all-implicit-x87-alpha-20260928.json`.
- Independent objective scan: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  `objective-implicit-x87-alpha-2026-09-28.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**,
  `../build/parity-implicit-x87-alpha-20260928.json`.
- Fresh 705-object diagnostic link succeeds to
  `../build/link-probe/strict-704-historical-sdk/ImVehFt-implicit-x87-alpha-diagnostic-not-ASI.dll`.
- Both 705-row source manifests were refreshed with a separate backup suffix.

This closes the identified static source/object operand gap; it does not prove
complete semantic equivalence. No original production project/complete
matching SDK build or gameplay test is available. The diagnostic DLL is not a
loadable ASI. Compile, object inspection, objective labels, parity, and
diagnostic linking are not runtime proof.

No original production project/complete matching SDK build or gameplay test is
available. Compile, source/object inspection, objective labels, parity, and a
diagnostic link are not proof of complete function equivalence or runtime
correctness.
