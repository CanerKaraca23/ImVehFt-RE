#!/usr/bin/env python3
"""Check Ghidra-exported callee reachability before __cinit."""

from __future__ import annotations

import argparse
import json
from collections import deque
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_EXPORTS = ROOT.parents[1] / "ghidra_exports"
DEFAULT_OUTPUT = ROOT / "audit/asi-crt-preinit-direct-call-audit-2026-09-27.json"
STARTUP_ROOTS = [
    "10016d12",  # __heap_init
    "10014fa7",  # __mtinit
    "10016cc6",  # __RTC_Initialize
    "10016d30",  # __heap_term (failure cleanup)
    "10016c2f",  # ___crtGetEnvironmentStringsA
    "100132f6",  # __ioinit
    "10016b74",  # __setargv
    "100168fe",  # command-line setup
    "1001353b",  # __ioterm (failure cleanup)
    "10014c86",  # __mtterm (failure cleanup)
    "10012df2",  # __cexit (failure cleanup)
    "10011032",  # CRT cleanup helper
    "10014c52",  # ___set_flsgetvalue
    "10012a3a",  # __calloc_crt
]
TARGETS = {"100119f1": "__input_l", "100154dc": "__output_l"}


def load_graph(directory: Path) -> tuple[dict[str, dict], set[str]]:
    nodes: dict[str, dict] = {}
    for path in directory.glob("*.json"):
        try:
            item = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError):
            continue
        address = item.get("address")
        if address:
            nodes[str(address).lower()] = item
    missing: set[str] = set()
    for item in nodes.values():
        for callee in item.get("callees", []):
            address = str(callee.get("addr", "")).lower()
            if address and not address.startswith("external:") and address not in nodes:
                missing.add(address)
    return nodes, missing


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--exports", type=Path, default=DEFAULT_EXPORTS)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()
    nodes, missing = load_graph(args.exports)

    previous: dict[str, str | None] = {}
    queue: deque[str] = deque()
    for root in STARTUP_ROOTS:
        if root in nodes and root not in previous:
            previous[root] = None
            queue.append(root)

    while queue:
        address = queue.popleft()
        for callee in nodes[address].get("callees", []):
            target = str(callee.get("addr", "")).lower()
            if target in nodes and target not in previous:
                previous[target] = address
                queue.append(target)

    paths: dict[str, list[dict[str, str]] | None] = {}
    for address, name in TARGETS.items():
        if address not in previous:
            paths[address] = None
            continue
        chain: list[str] = []
        current: str | None = address
        while current is not None:
            chain.append(current)
            current = previous[current]
        chain.reverse()
        paths[address] = [
            {"address": item, "name": str(nodes[item].get("name", ""))}
            for item in chain
        ]

    report = {
        "date": "2026-09-27",
        "ghidra_export_directory": str(args.exports),
        "exported_function_count": len(nodes),
        "startup_initialization_and_failure_cleanup_roots": STARTUP_ROOTS,
        "reachable_exported_function_count": len(previous),
        "targets": TARGETS,
        "resolved_callee_paths": paths,
        "unresolved_non_external_callee_addresses_in_export_set": sorted(missing),
        "scope_limit": (
            "All callee references represented in Ghidra JSON exports are traversed, "
            "including computed-call targets Ghidra resolves. A missing path does "
            "not exclude unresolved indirect calls, callbacks, unexported functions, "
            "or runtime behavior."
        ),
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"Reachable exported functions: {len(previous)}; "
        f"unexported non-external callee addresses: {len(missing)}; "
        f"report: {args.output}"
    )
    for address, path in paths.items():
        if path is None:
            print(f"NO RESOLVED CALLEE PATH to {address} ({TARGETS[address]})")
        else:
            print(f"RESOLVED CALLEE PATH to {address}: " + " -> ".join(x["address"] for x in path))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
