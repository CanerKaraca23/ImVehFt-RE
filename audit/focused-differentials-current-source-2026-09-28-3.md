# Focused original-binary differentials on current sources

Date: 2026-09-28. These tests were run after the fresh 705-unit compile
recorded in `build/strict-705-live-20260928-3.json`. They use the exact
hash-pinned installed `ImVehFt.asi` reference
(`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`). No
candidate source was edited during the tests.

## Results

- `10006be0`: current source SHA-256
  `92B16BE2BB33C4A79E12E78FF34D3BB7D267C3F3B9EC7BB30C89D7A14A70BAF8`.
  Fresh original-binary differential matched **32,720/32,720** observations,
  with zero semantic/output/side-effect mismatches. Coverage includes directed
  edges, 4,096 deterministic variations, 21,600 finite downstream-tail cases,
  and 4,096 IEEE-boundary tail cases. There were 1,354 reported x87
  condition-code-only differences; these are explicitly excluded from the
  semantic-match count and are not represented as full machine-state identity.
  External game/effect APIs are controlled stubs. Executable:
  `build/abi-harness/10006be0-current-source-live-20260928-3/10006be0-original-binary-differential.exe`
  (SHA-256 `8A912419424065C61846646C7B0E49FB9D50E6641E1CA823F0F8CD7E275700B1`).
- `10007030`: current source SHA-256
  `DC18EBD109BC51AB3D9BE95E294DC8186E8B472A16870D87E34CF7B700337A15`.
  The current candidate matched the original in **4/4** directed cases:
  direct corona, alpha above/below threshold, and suppressed mode. The test
  confirms the reviewed transform ABI and overlapping stack aliases for these
  cases; GTA math/corona callees remain stubs, and the matrix input is identity.
  Executable:
  `build/abi-harness/10007030-current-source-live-20260928-3/10007030-stack-overlay-differential.exe`
  (SHA-256 `F4EEA561F81E70FE67DEE8F396FEF9E5CA773CA4819F3302007363F5FD6D47FB`).
- `1001ba40`: current source SHA-256
  `973DD0053E4680B0185F3C5695109B9DA0A328A7B5C5D31C97324FD8E7FBDBE4`.
  A fresh harness matched **12,000,264/12,000,264** original-vs-candidate
  cases, including 22 directed inputs and 1,000,000 deterministic random bit
  patterns for every mode/x87-rounding-control pair. Executable:
  `build/abi-harness/1001ba40-current-source-live-20260928-3/1001ba40-original-binary-differential.exe`
  (SHA-256 `E652AC231650B830DC582315363C9899126C4B312D506F8397F8C6059A1938CA`).

## Scope boundary

These differentials strengthen evidence for these three functions only. They
do not establish equivalence for all 705 units. In particular, the external
GTA/RenderWare helpers used by `10006be0`/`10007030` remain modeled, and the
live callback/re-entry, production PE layout, integration, and gameplay gaps
listed in `audit/current-source-revalidation-2026-09-28-3.md` remain open.
