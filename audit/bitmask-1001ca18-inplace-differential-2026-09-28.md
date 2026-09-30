# `FUN_1001ca18` bit-mask differential

Date: 2026-09-28. This is a bounded function comparison, not a production ASI
or GTA runtime test.

- Ghidra's decompilation and the candidate both return the input's
  `0x7FF00000` exponent field unless all exponent bits are set, in which case
  they return the entire input word. The first argument is unused.
- Candidate body: 21 bytes, zero COFF relocations, no original HIGHLOW
  overlap, and fits the next-entry gap. Capstone decoded all seven
  instructions; its direct branch remains inside the candidate. Full-span
  Ghidra xrefs cover 24 byte-target rows and show no external reference into
  the overwritten interior.
- Probe:
  `build/pe-layout-probe/bitmask-1001ca18-probe-not-asi.bin`, SHA-256
  `AE175BBC51DD905F1D7A5B139BB72175BEB082BCB683EE7DAC8D3E88F7436A31`.
  It changes 18 bytes, all within the function body.
- Strict MSVC x86 `/O2 /W4 /WX /MT /GS /arch:IA32` harness compared original
  and probe as `SEC_IMAGE`. **12 named bit patterns**, including finite,
  subnormal, infinity/NaN exponent encodings and sign variants, plus **100,000
  deterministic randomized argument pairs passed**.
- Harness SHA-256:
  `CB6C38AA54E3998ECACF52CF6308F55378733056FE5A96D898ACBF5AE521E4EF`.

This confirms the tested 32-bit input domain only; it does not validate other
functions or image/game integration.
