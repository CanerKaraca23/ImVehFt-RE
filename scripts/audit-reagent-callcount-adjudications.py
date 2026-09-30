#!/usr/bin/env python3
"""Guard the parity report against broadening scoped call-count waivers."""

from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
EXPECTED_FUNCTIONS = 705
EXPECTED_STATUSES = {"green": 705, "yellow": 0, "red": 0, "unknown": 0}
EXPECTED_MANUAL_CHECKS = 13
OPEN_RISK_ADDRESS = "0x100076d0"
OPEN_RISK_MARKER = "indirect RenderWare callback/re-entry behavior remains untested."


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "report",
        nargs="?",
        type=Path,
        default=ROOT / "build/parity-live-current-20260928.json",
        help="ReAgent parity JSON report (default: latest 2026-09-28 current-source run)",
    )
    args = parser.parse_args()
    report = json.loads(args.report.read_text(encoding="utf-8"))
    results = report.get("results", [])
    errors: list[str] = []

    addresses = [item.get("address", "").lower() for item in results]
    if len(results) != EXPECTED_FUNCTIONS:
        errors.append(f"expected {EXPECTED_FUNCTIONS} results, found {len(results)}")
    if len(set(addresses)) != len(addresses):
        errors.append("duplicate function addresses found")

    counts = Counter(item.get("status", "unknown").lower() for item in results)
    for status, expected in EXPECTED_STATUSES.items():
        if counts[status] != expected:
            errors.append(f"expected {expected} {status}, found {counts[status]}")

    manual_checks: list[tuple[str, str]] = []
    open_risk_retained = False
    for item in results:
        address = item.get("address", "<missing-address>").lower()
        for finding in item.get("findings", []):
            reason = finding.get("reason", "")
            if address == OPEN_RISK_ADDRESS and OPEN_RISK_MARKER in reason:
                open_risk_retained = True
            if "Scoped manual check:" not in reason:
                continue
            manual_checks.append((address, reason))
            if "scope=call-count-only" not in reason:
                errors.append(f"{address}: manual check is not explicitly call-count-only")
            if "Suppress only" not in reason:
                errors.append(f"{address}: manual check does not limit the suppression scope")

    if len(manual_checks) != EXPECTED_MANUAL_CHECKS:
        errors.append(
            f"expected {EXPECTED_MANUAL_CHECKS} scoped manual checks, found {len(manual_checks)}"
        )
    if not open_risk_retained:
        errors.append(
            f"the {OPEN_RISK_ADDRESS} callback/re-entry limitation is missing from its finding"
        )

    print(
        f"results={len(results)} statuses="
        f"{counts['green']} green/{counts['yellow']} yellow/"
        f"{counts['red']} red/{counts['unknown']} unknown; "
        f"scoped_callcount_checks={len(manual_checks)}"
    )
    if errors:
        for error in errors:
            print(f"FAIL {error}")
        return 1
    print(
        "PASS all waivers are call-count-only; the resolved source-pattern warning is absent; "
        "the 100076d0 callback/re-entry limitation remains explicit"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
