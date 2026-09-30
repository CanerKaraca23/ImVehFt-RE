from __future__ import annotations

import importlib.util
from pathlib import Path
import unittest


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "generate-candidate-comdat-order.py"
SPEC = importlib.util.spec_from_file_location("candidate_comdat_order", SCRIPT)
assert SPEC is not None and SPEC.loader is not None
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)


class CandidateEntryMatchTests(unittest.TestCase):
    def test_auto_ghidra_name_matches_msvc_uppercase_stdcall_symbol(self) -> None:
        self.assertTrue(MODULE.is_candidate_entry("_FUN_10014D65@0", "FUN_10014d65"))

    def test_auto_ghidra_name_matches_case_insensitive_fastcall_symbol(self) -> None:
        self.assertTrue(MODULE.is_candidate_entry("@FUN_10014D6E@4", "FUN_10014d6e"))

    def test_auto_ghidra_name_matches_existing_exact_symbol(self) -> None:
        self.assertTrue(MODULE.is_candidate_entry("FUN_10001010", "FUN_10001010"))

    def test_generated_bridge_symbols_are_not_mistaken_for_entry(self) -> None:
        self.assertFalse(MODULE.is_candidate_entry("_FUN_10014D65_impl", "FUN_10014d65"))
        self.assertFalse(MODULE.is_candidate_entry("_FUN_10014D65_call_bridge", "FUN_10014d65"))

    def test_this_invoke_alias_is_bound_to_its_exact_auto_label_address(self) -> None:
        symbol = "?invoke@FUN_100101a5_this@@QAEPAXPAX@Z"
        self.assertTrue(MODULE.is_address_bound_cpp_entry_alias(symbol, "FUN_100101a5"))
        self.assertFalse(MODULE.is_address_bound_cpp_entry_alias(symbol, "FUN_100101f2"))
        self.assertFalse(MODULE.is_address_bound_cpp_entry_alias(symbol, "__CRT_INIT_12"))

    def test_public_coff_fun_label_is_bound_to_exact_target_address(self) -> None:
        self.assertTrue(MODULE.is_address_named_coff_alias("_FUN_1001E085", 0x1001E085))
        self.assertFalse(MODULE.is_address_named_coff_alias("_FUN_1001E085", 0x1001E5D6))
        self.assertFalse(MODULE.is_address_named_coff_alias("_FUN_1001E085_impl", 0x1001E085))

    def test_stdcall_source_identifier_alias_tracks_ghidra_at_name(self) -> None:
        self.assertTrue(
            MODULE.is_stdcall_name_sanitization_alias(
                "___CRT_INIT_12@12",
                "__CRT_INIT@12",
                "undefined4 __stdcall __CRT_INIT@12(uint32_t, int, int)",
            )
        )
        self.assertTrue(
            MODULE.is_stdcall_name_sanitization_alias(
                "_Catch_All_1001d057@0",
                "Catch_All@1001d057",
                "undefined __stdcall Catch_All@1001d057(void)",
            )
        )
        self.assertFalse(
            MODULE.is_stdcall_name_sanitization_alias(
                "___CRT_INIT_12@12", "__CRT_INIT@12", "int __cdecl __CRT_INIT@12(void)"
            )
        )

    def test_verified_recovered_rtlunwind_thunk_alias_is_exact(self) -> None:
        self.assertTrue(
            MODULE.is_verified_recovered_import_thunk_alias(
                "_ImVehFt_Recovered_RtlUnwind@16",
                "RtlUnwind",
                "void __stdcall RtlUnwind(PVOID, PVOID, PEXCEPTION_RECORD, PVOID)",
            )
        )
        self.assertFalse(
            MODULE.is_verified_recovered_import_thunk_alias(
                "_ImVehFt_Recovered_RtlUnwind@16", "RtlUnwind",
                "void __cdecl RtlUnwind(void)",
            )
        )
        self.assertFalse(
            MODULE.is_verified_recovered_import_thunk_alias(
                "_ImVehFt_Recovered_RtlUnwind@16", "AnotherFunction",
                "void __stdcall AnotherFunction(void)",
            )
        )

    def test_named_cpp_entry_matching_remains_case_sensitive(self) -> None:
        self.assertTrue(MODULE.is_candidate_entry("?__CRT_INIT_12@", "__CRT_INIT_12"))
        self.assertFalse(MODULE.is_candidate_entry("?__crt_init_12@", "__CRT_INIT_12"))


if __name__ == "__main__":
    unittest.main()
