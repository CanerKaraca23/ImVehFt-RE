# Current 705 validation rerun

Checked 2026-09-28 against the current `src/functions` tree. No candidate C++
source was edited during this rerun.

## Fresh structural checks

- Independent ReAgent objective audit:
  `audit/objective-independent-current-2026-09-28.json` — **705 PASS, 0 FAIL,
  0 UNKNOWN**. Its 705 source hashes match the current
  `audit/function-name-map.csv` hashes exactly (0 mismatches).
- ReAgent 0.4.0 parity with the local Ghidra JSON backend and the current
  manual/semantic rule files:
  `build/parity-current-ghidra-recheck-20260928.json` — **705 GREEN, 0 YELLOW,
  0 RED**. The address/name manifest used for this run is
  `build/reagent-parity-targets-current-20260928.csv`. This is a local static
  parity result, not proof of semantic equivalence or runtime behavior.
- A source-only parity run without Ghidra data yielded **650 GREEN, 55 YELLOW,
  0 RED**; all 55 warnings were ReAgent's short-body heuristic (3–5 lines).
  This explains why the backend-enabled rerun is necessary to reproduce the
  all-green verdict; short bodies were not manually relabeled green here.
- The most recent strict MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` run remains
  `build/strict-xcode-705-v2-20260929.json`: **705 compiled, 0 failed**. It
  compiled the exact candidate-source set, forced to a separate `.xcode`
  section. The object-equivalence audit says the forced-section build changes
  section naming, not candidate code bytes or runtime relocations.

## Reproduction scope and remaining gates

The ReAgent parity command used `--skip-ghidra` only for the separately
reported source-only comparison; the 705-green rerun used the local
`ghidra-json` export backend and made no model/API calls. The local ReAgent
checkout/config is modified and the check is not an upstream pristine run.

The two semantic findings (`0x100076d0`, `0x10006be0`) and real
RenderWare/GTA callback behavior are still open. The `.xcode` DLL remains a
diagnostic artifact: no final ASI PE with original sections/relocations and
entry patches has been validated, and no reconstructed candidate has been
loaded in GTA. Thus these 705 green results are necessary structural evidence,
not completion of the 705-function reverse-engineering objective.
