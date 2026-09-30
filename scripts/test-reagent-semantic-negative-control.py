#!/usr/bin/env python3
"""Reproduce a known ReAgent structural-checker semantic blind spot in memory."""

from __future__ import annotations

import dataclasses
import json
import sys
from pathlib import Path


ADDRESS = "10001010"
FUNCTION = "FUN_10001010"
GOOD_TOKEN = "IVF_IMAGE_ADDRESS_10022250"
MUTATED_TOKEN = "0"


def main() -> int:
    repo = Path(__file__).resolve().parents[1]
    owner = repo.parent.parent
    reagent_source = owner / "reagent" / "src"
    ghidra_export = owner / "ghidra_exports"
    config_path = repo / "build" / "re-agent-publish-config.yaml"
    if not reagent_source.is_dir() or not ghidra_export.is_dir():
        raise SystemExit("Expected local ReAgent source and Ghidra export directories.")
    sys.path.insert(0, str(reagent_source))

    from re_agent.backend.exports import GhidraExportsBackend
    from re_agent.config.loader import load_config
    from re_agent.core.models import FunctionTarget, HookEntry
    from re_agent.parity.engine import fetch_ghidra_data, score_single
    from re_agent.parity.rules import read_manual_checks, read_semantic_rules
    from re_agent.parity.source_indexer import SourceIndexer
    from re_agent.utils.address import normalize_address
    from re_agent.utils.text import strip_comments
    from re_agent.verification.objective import verify_candidate

    config = load_config(config_path)
    backend = GhidraExportsBackend(str(ghidra_export))
    source_index = SourceIndexer(repo / "src" / "functions", config.project_profile)
    source = source_index.find_in_candidate_translation_unit(ADDRESS, FUNCTION)
    if source is None:
        raise SystemExit(f"Could not resolve candidate {ADDRESS} in its named translation unit.")
    current_file = Path(source.path).read_text(encoding="utf-8")
    if current_file.count(GOOD_TOKEN) != 1:
        raise SystemExit(f"Expected exactly one {GOOD_TOKEN} use in {source.path}.")
    if read_manual_checks(Path(config.parity.manual_checks_file)).get(normalize_address(ADDRESS)):
        raise SystemExit(f"Candidate {ADDRESS} has a manual parity entry; choose an unoverridden target.")

    mutated_file = current_file.replace(GOOD_TOKEN, MUTATED_TOKEN, 1)
    mutated_body = source.body.replace(GOOD_TOKEN, MUTATED_TOKEN, 1)
    mutated_source = dataclasses.replace(
        source,
        body=mutated_body,
        body_no_comments=strip_comments(mutated_body),
    )
    target = FunctionTarget(
        address="0x" + ADDRESS,
        class_name="",
        function_name=FUNCTION,
    )
    hook = HookEntry(
        class_path="",
        fn_name=FUNCTION,
        address="0x" + ADDRESS,
        reversed=True,
        locked=False,
        is_virtual=False,
    )
    ghidra_data = fetch_ghidra_data(hook.address, backend)
    semantic_rules = read_semantic_rules(Path(config.parity.semantic_rules_file))

    result: dict[str, object] = {
        "address": "0x" + ADDRESS,
        "mutation": f"replace {GOOD_TOKEN} with {MUTATED_TOKEN} in memory only",
        "source_file_modified": False,
        "ghidra_decompile_ok": ghidra_data.decompile_ok,
        "ghidra_asm_ok": ghidra_data.asm_ok,
        "ghidra_instruction_count": ghidra_data.asm_instruction_count,
        "ghidra_call_count": ghidra_data.asm_call_count,
        "objective": {},
        "parity": {},
    }
    objective = result["objective"]
    parity = result["parity"]
    assert isinstance(objective, dict) and isinstance(parity, dict)

    for label, candidate in (("current", current_file), ("negative_control", mutated_file)):
        verdict = verify_candidate(
            candidate,
            target,
            backend,
            call_count_tolerance=config.orchestrator.objective_call_count_tolerance,
            control_flow_tolerance=config.orchestrator.objective_control_flow_tolerance,
        )
        objective[label] = {"verdict": verdict.verdict.value, "findings": verdict.findings}

    for label, candidate, source_match in (
        ("current", current_file, source),
        ("negative_control", mutated_file, mutated_source),
    ):
        status, findings = score_single(
            hook,
            source_match,
            ghidra_data,
            config.parity,
            semantic_rules,
            source_file_text=candidate,
        )
        parity[label] = {
            "status": status.value,
            "findings": [{"level": finding.level, "reason": finding.reason} for finding in findings],
        }

    reproduced = (
        objective["current"]["verdict"] == "PASS"
        and objective["negative_control"]["verdict"] == "PASS"
        and parity["current"]["status"] == "green"
        and parity["negative_control"]["status"] == "green"
    )
    result["known_semantic_blind_spot_reproduced"] = reproduced
    print(json.dumps(result, indent=2))
    # Exit 0 means the known blind spot was reproduced: the intentionally wrong
    # pointer value was not distinguished by either structural gate.
    return 0 if reproduced else 1


if __name__ == "__main__":
    raise SystemExit(main())
