# `1001023b` ret-8 caller integration follow-up — 2026-09-29

## Caller mismatch and repair

After correcting callee `1001023b` to clean 8 stack bytes, inspection of its
current caller candidate `10010893.cpp` found that it still called the method
with only one explicit parameter. That would have left the callee cleaning
four bytes that the caller had not pushed. The caller candidate is now backed
up as
`src/functions/10010893.cpp.pre-1001023b-ret8-caller-fix-20260929.bak` and
passes the second, currently unused argument as `1u`, matching Ghidra.

Ghidra `ghidra_exports/10010893.json` at `0x100108d3` pushes `1`; at
`0x100108d5` it computes the message-pointer address; at `0x100108d8` it pushes
that pointer; then it sets ECX to the global object and calls `0x1001023b`.
The target export confirms that the callee reads the first stack value,
ignores the second, and returns with `RET 8` (`0x10010255`). The candidate's
fresh caller COFF disassembly now has the same two pushes in the same order,
ECX setup, and helper call. The candidate callee COFF disassembly ends in
`C2 08 00` (`ret 8`). The function-name-map signature was updated to include
the inferred unused second stack argument; the raw Ghidra export remains
unchanged and records its decompiler omission.

## Focused differential on the final full-set object

The exact `1001023b.obj` produced by the final 705-unit strict build was
retested against the original binary: ten fresh x86 processes, 128 cases each
(1,280 paired calls), zero mismatches. The naked invocation wrapper measured
zero ESP delta for both paths while checking vtable, payload, flag byte, and
untouched neighboring bytes.

- Original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- `1001023b.cpp` SHA-256:
  `879A941C3ECD47BC474AD4D87BB79F57EC7421C1F055320C608E9AC54CB6F63B`
- `10010893.cpp` SHA-256:
  `CF53DEA92ECADA52FFD7668F69A1E5D61ADBF536B442CA02B9BA6EECCB85387C`
- Final full-set `1001023b.obj` SHA-256:
  `2EEE2F8CF6CA44559C383F01C5F9F906B6D7C4CCBD3E696EFC67EE9BE011A890`
- Final full-set `10010893.obj` SHA-256:
  `52B8682C80A1E6920F1D2175AB98D385F13695DC902ED3E2FC0AABCC5359A4A3`
- Harness source SHA-256:
  `23BA4247EAD06A6BB80BAB79A9C8A33BC3A596AE536587C31EB0AE284A598F08`
- Harness executable SHA-256:
  `4D83EDE8A2839779122EDE0D798B00A27A6DE682DBAFD399C2500356C9437F85`
- Runner: `scripts/test-1001023b-original-binary-differential.ps1`

## Final current-source checks after both edits

- Strict MSVC 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: 705/705;
  `build/strict-xcode-nogs-o1-after-1001023b-caller-fix-20260929.json`.
- Independent ReAgent objective: 705 PASS / 0 FAIL / 0 UNKNOWN;
  `audit/objective-independent-after-1001023b-caller-fix-2026-09-29.json`.
- ReAgent 0.4.0 parity: 705 GREEN / 0 YELLOW / 0 RED;
  `build/parity-after-1001023b-caller-fix-20260929.json`.
- Call-count adjudication: 13 scoped call-count-only waivers retained; the
  `100076d0` callback/re-entry risk is still reported.
- Independent Ghidra-vs-COFF scoped call-count audit: 13/13 entries, zero
  audit errors on the final post-caller-fix objects;
  `audit/manual-parity-call-counts-after-1001023b-caller-fix-2026-09-29.json`.
- Both current 705-row source manifests have zero source/hash mismatches.

The objective and parity green results did not detect the missing cleanup
argument; the defect was found by comparing Ghidra RET/caller stack behavior
and compiled COFF ABI. Those full-set checks remain structural, not semantic.

## Remaining boundary

The focused helper/caller ABI is now covered, but this does not validate
production PE placement/relocations/imports, the complete allocator failure
and thrown-exception runtime in-game, other functions' semantics, or live GTA
behavior. No production ASI or original project/build recipe has been
established.
