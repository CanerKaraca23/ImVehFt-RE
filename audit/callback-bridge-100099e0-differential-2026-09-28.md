# `FUN_100099e0` callback/ECX differential

Date: 2026-09-28. This validates one exact function body, not a production ASI
or GTA runtime.

- Ghidra locates `FUN_100099e0` at `0x100099E0`; the strict x86 object has a
  13-byte `.xcode` body with zero COFF relocations, and all 13 bytes match the
  original ASI at the same VA exactly. Object SHA-256:
  `23DFF0EE27584CDE537903AF9D130D510705C65D54D77B83983F6953FB026F6B`.
- The isolated probe therefore has the same whole-file SHA-256 as the original
  (`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`); it
  remains separately named as a probe and was not used as a mod.
- The harness mapped both PEs as `SEC_IMAGE`, supplied a controlled x86
  `__fastcall` callback, and checked that each implementation invoked it once
  with the receiver value passed through ECX. **8 named and 100,000
  deterministic randomized calls passed.**
- Harness SHA-256:
  `75D00A134DFDC5E484B81C92DB06AA245A3CAC99C255A9BB3B568913E4C84EBA`.

The test validates the observed callback/receiver ABI over its tested inputs.
It does not validate the callback's GTA implementation, mod initialization,
other entry points, or game behavior.
