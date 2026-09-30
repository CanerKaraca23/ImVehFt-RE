# Focused `0x100076d0` harness rerun

Date: 2026-09-28. Rebuilt the PE32 harness with MSVC x86 and reran the
candidate-object scenarios in ten fresh processes against the hash-pinned
original ASI.

## Evidence

- Candidate source SHA-256:
  `149AE0C88160BA6DFDBDF6097853373074DEC2133BC5ADF066EB6DD8A84EEEAD`;
  this matches the `100076d0` row in `audit/source-sha256.csv`.
- Candidate object SHA-256:
  `A227D6163003883A003FD20606F571E8482552252F8AB261C7903BA116DDCB4E`.
- Harness SHA-256:
  `047D148ADA941AFEAD4E6562E1793AA0C6C7700B26C0D534AD4A3FCD444D7CEC`.
- Result: **10/10** fresh processes passed the documented synthetic
  model-info selector, callback, and controlled-re-entry cases.
- Reference ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The fresh build attempt using the separate `strict-xcode-705-v2-20260929`
object was rejected by this harness because its fixed-operand count assumptions
did not match that object's generated code. No source or object was changed by
that failed attempt. The successful rerun therefore uses the harness-designated
object and reproduces its recorded SHA exactly; it is not evidence about the
other object's operand layout.

## Scope limitation

These are controlled synthetic executions of the candidate object, with
fixed-address dependencies redirected to test stubs. They are not live GTA
RenderWare/plugin callbacks, do not establish actual callback-registry order or
external re-entry, and do not close the open semantic finding for
`0x100076d0`. No production `.asi` was built or loaded in-game.
