"""Evidence-backed micro-stubs for non-entry .text pointer targets.

Each body is reconstructed from its original x86 bytes. Fixups are (offset,
kind, original target VA), where kind is REL32 or DIR32. Candidate calls are
resolved to the matching address-named COFF object by the generator/verifier.
"""

from __future__ import annotations

from typing import Any


STUBS: list[dict[str, Any]] = []


def add(targets: tuple[int, ...], label: str, asm: tuple[str, ...], body: str,
        fixups: tuple[tuple[int, str, int], ...] = (),
        tail_jump: int | None = None,
        blocks: tuple[dict[str, Any], ...] = (),
        local_labels: dict[int, str] | None = None) -> None:
    STUBS.append({
        "targets": targets,
        "label": label,
        "asm": asm,
        "body": bytes.fromhex(body),
        "fixups": fixups,
        "tail_jump": tail_jump,
        "blocks": blocks,
        "local_labels": local_labels or {},
    })


# Naked jump/context shims and exception filter results.
add((0x100101A0,), "IVF_LOCAL_JUMP_100101A0", ("jmp {CODE_1001031F}",),
    "E9 00 00 00 00", ((1, "REL32", 0x1001031F),))
add((0x1001CD2C,), "IVF_LOCAL_CONTEXT_1001CD2C",
    ("mov DWORD PTR [ecx], OFFSET IVF_RELOC_TARGET_100261E8", "jmp {CODE_1001031F}"),
    "C7 01 00 00 00 00 E9 00 00 00 00",
    ((2, "DIR32", 0x100261E8), (7, "REL32", 0x1001031F)))
add((0x10017DFE, 0x10017E4E, 0x1001D376, 0x1001D40F), "IVF_SEH_RETURN_ONE",
    ("xor eax, eax", "inc eax", "ret"), "33 C0 40 C3")
add((0x1001CF70,), "IVF_SEH_RETURN_EBP_ARGC_NONZERO",
    ("xor eax, eax", "cmp BYTE PTR [ebp + 0Ch], al", "setne al", "ret"),
    "33 C0 38 45 0C 0F 95 C0 C3")


def wrapper(target: int, label: str, asm: tuple[str, ...], body: str,
            call_offset: int, callee: int) -> None:
    add((target,), label, asm, body, ((call_offset, "REL32", callee),))


for target, label in ((0x1001066D, "IVF_LOCK_WRAPPER_1001066D"),
                      (0x10010888, "IVF_LOCK_WRAPPER_10010888")):
    wrapper(target, label,
        ("mov esi, DWORD PTR [ebp + 8]", "push esi", "call {CODE_10013169}", "pop ecx", "ret"),
        "8B 75 08 56 E8 00 00 00 00 59 C3", 5, 0x10013169)

wrapper(0x10010A0E, "IVF_LOCK_WRAPPER_10010A0E",
    ("mov edi, DWORD PTR [ebp + 0Ch]", "push edi", "call {CODE_10013169}", "pop ecx", "ret"),
    "8B 7D 0C 57 E8 00 00 00 00 59 C3", 5, 0x10013169)

wrapper(0x10013972, "IVF_LOCK_WRAPPER_10013972",
    ("mov edi, DWORD PTR [ebp - 1Ch]", "push 1", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "8B 7D E4 6A 01 E8 00 00 00 00 59 C3", 6, 0x10017CD2)

for target, label in ((0x10013D2D, "IVF_UNLOCK_WRAPPER_10013D2D"),
                      (0x1001672A, "IVF_UNLOCK_WRAPPER_1001672A"),
                      (0x10019B2C, "IVF_UNLOCK_WRAPPER_10019B2C"),
                      (0x10019C05, "IVF_UNLOCK_WRAPPER_10019C05")):
    wrapper(target, label,
        ("mov ebx, DWORD PTR [ebp + 8]", "push ebx", "call {CODE_100191A6}", "pop ecx", "ret"),
        "8B 5D 08 53 E8 00 00 00 00 59 C3", 5, 0x100191A6)

wrapper(0x100144DE, "IVF_LOCK_WRAPPER_100144DE",
    ("mov esi, DWORD PTR [ebp - 1Ch]", "push 0Dh", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "8B 75 E4 6A 0D E8 00 00 00 00 59 C3", 6, 0x10017CD2)
wrapper(0x10014D5F, "IVF_LOCK_WRAPPER_10014D5F",
    ("xor edi, edi", "inc edi", "mov esi, DWORD PTR [ebp + 8]", "push 0Dh", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "33 FF 47 8B 75 08 6A 0D E8 00 00 00 00 59 C3", 9, 0x10017CD2)
wrapper(0x10014F21, "IVF_LOCK_WRAPPER_10014F21",
    ("mov esi, DWORD PTR [ebp + 8]", "push 0Dh", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "8B 75 08 6A 0D E8 00 00 00 00 59 C3", 6, 0x10017CD2)
wrapper(0x10014F2D, "IVF_LOCK_WRAPPER_10014F2D",
    ("mov esi, DWORD PTR [ebp + 8]", "push 0Ch", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "8B 75 08 6A 0C E8 00 00 00 00 59 C3", 6, 0x10017CD2)
wrapper(0x10019198, "IVF_LOCK_WRAPPER_10019198",
    ("xor ebx, ebx", "mov edi, DWORD PTR [ebp + 8]", "push 0Ah", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "33 DB 8B 7D 08 6A 0A E8 00 00 00 00 59 C3", 8, 0x10017CD2)
wrapper(0x10019299, "IVF_LOCK_WRAPPER_10019299",
    ("mov edi, DWORD PTR [ebp - 28h]", "mov esi, DWORD PTR [ebp - 20h]", "push 0Ah", "call {CODE_10017CD2}", "pop ecx", "ret"),
    "8B 7D D8 8B 75 E0 6A 0A E8 00 00 00 00 59 C3", 9, 0x10017CD2)

# Additional byte-verified code-pointer targets. These bodies are short
# compiler-generated helpers/SEH fragments; external references are explicit
# relocations so the provider can be placed independently of the source ASI.
add((0x10011030,), "IVF_LOCAL_HELPER_10011030",
    ("xor edi, edi", "cmp DWORD PTR [ebp + 10h], edi", "jne IVF_11030_done",
     "cmp DWORD PTR [IVF_RELOC_TARGET_10029C0C], -1", "je IVF_11030_done",
     "call {CODE_10014C86}", "IVF_11030_done:", "ret"),
    "33 FF 39 7D 10 75 0E 83 3D 00 00 00 00 FF 74 05 E8 00 00 00 00 C3",
    ((9, "DIR32", 0x10029C0C), (17, "REL32", 0x10014C86)))
add((0x10011190,), "IVF_LOCAL_HELPER_10011190",
    ("mov eax, DWORD PTR [ebp - 14h]", "mov ecx, DWORD PTR [eax]",
     "mov ecx, DWORD PTR [ecx]", "push eax", "push ecx",
     "call {CODE_10016E8E}", "pop ecx", "pop ecx", "ret"),
    "8B 45 EC 8B 08 8B 09 50 51 E8 00 00 00 00 59 59 C3",
    ((10, "REL32", 0x10016E8E),))
add((0x100111A1,), "IVF_LOCAL_SEH_EPILOG_100111A1",
    ("mov esp, DWORD PTR [ebp - 18h]", "mov DWORD PTR [ebp - 4], -2",
     "xor eax, eax", "call {CODE_10012E65}", "ret"),
    "8B 65 E8 C7 45 FC FE FF FF FF 33 C0 E8 00 00 00 00 C3",
    ((13, "REL32", 0x10012E65),))
add((0x10013EB6,), "IVF_LOCAL_UNLOCK_FILE2_10013EB6",
    ("xor edi, edi", "mov esi, DWORD PTR [ebp - 20h]",
     "mov eax, DWORD PTR [IVF_RELOC_TARGET_1003C520]",
     "push DWORD PTR [eax + esi*4]", "push esi", "call {CODE_100131A5}",
     "pop ecx", "pop ecx", "ret"),
    "33 FF 8B 75 E0 A1 00 00 00 00 FF 34 B0 56 E8 00 00 00 00 59 59 C3",
    ((6, "DIR32", 0x1003C520), (15, "REL32", 0x100131A5)))
add((0x10017E02,), "IVF_LOCAL_SEH_ABORT_10017E02",
    ("mov esp, DWORD PTR [ebp - 18h]", "mov DWORD PTR [ebp - 4], -2",
     "call {CODE_1001705C}", "call {CODE_10012E65}", "ret"),
    "8B 65 E8 C7 45 FC FE FF FF FF E8 00 00 00 00 E8 00 00 00 00 C3",
    ((11, "REL32", 0x1001705C), (16, "REL32", 0x10012E65)))
add((0x10017E52,), "IVF_LOCAL_SEH_TERMINATE_10017E52",
    ("mov esp, DWORD PTR [ebp - 18h]", "mov DWORD PTR [ebp - 4], -2",
     "call {CODE_10017DDE}", "int 3"),
    "8B 65 E8 C7 45 FC FE FF FF FF E8 00 00 00 00 CC",
    ((11, "REL32", 0x10017DDE),))
wrapper(0x10018036, "IVF_LOCAL_COND_UNLOCK_10018036",
    ("mov ebx, DWORD PTR [ebp + 8]", "mov edi, DWORD PTR [ebp - 28h]",
     "cmp DWORD PTR [ebp - 1Ch], 0", "je IVF_18036_done", "push 0",
     "call {CODE_10017CD2}", "pop ecx", "IVF_18036_done:", "ret"),
    "8B 5D 08 8B 7D D8 83 7D E4 00 74 08 6A 00 E8 00 00 00 00 59 C3",
    15, 0x10017CD2)
add((0x100181AB,), "IVF_LOCAL_SEH_ACCESS_VIOLATION_FILTER_100181AB",
    ("mov eax, DWORD PTR [ebp - 14h]", "mov ecx, DWORD PTR [eax]",
     "xor edx, edx", "cmp DWORD PTR [ecx], 0C0000005h", "sete dl",
     "mov eax, edx", "ret"),
    "8B 45 EC 8B 08 33 D2 81 39 05 00 00 C0 0F 94 C2 8B C2 C3")
add((0x100181BE,), "IVF_LOCAL_SEH_EPILOG_100181BE",
    ("mov esp, DWORD PTR [ebp - 18h]", "mov DWORD PTR [ebp - 4], -2",
     "xor eax, eax", "mov ecx, DWORD PTR [ebp - 10h]",
     "DB 064h, 089h, 00Dh, 0, 0, 0, 0", "pop ecx", "pop edi", "pop esi",
     "pop ebx", "mov esp, ebp", "pop ebp", "ret"),
    "8B 65 E8 C7 45 FC FE FF FF FF 33 C0 8B 4D F0 64 89 0D 00 00 00 00 59 5F 5E 5B 8B E5 5D C3")
wrapper(0x1001CE8A, "IVF_LOCAL_FRAME_UNWIND_FILTER_1001CE8A",
    ("push DWORD PTR [ebp - 14h]", "call {CODE_1001CDBD}", "pop ecx", "ret"),
    "FF 75 EC E8 00 00 00 00 59 C3", 4, 0x1001CDBD)
add((0x1001CEC8,), "IVF_LOCAL_THREAD_EXCEPTION_COUNT_1001CEC8",
    ("mov ebx, DWORD PTR [ebp + 8]", "mov esi, DWORD PTR [ebp - 1Ch]",
     "call {CODE_10014DF0}", "cmp DWORD PTR [eax + 90h], 0",
     "jle IVF_1CEC8_done", "call {CODE_10014DF0}",
     "dec DWORD PTR [eax + 90h]", "IVF_1CEC8_done:", "ret"),
    "8B 5D 08 8B 75 E4 E8 00 00 00 00 83 B8 90 00 00 00 00 7E 0B E8 00 00 00 00 FF 88 90 00 00 00 C3",
    ((7, "REL32", 0x10014DF0), (21, "REL32", 0x10014DF0)))
add((0x1001CF79,), "IVF_LOCAL_SEH_TERMINATE_1001CF79",
    ("mov esp, DWORD PTR [ebp - 18h]", "call {CODE_10017DDE}", "int 3"),
    "8B 65 E8 E8 00 00 00 00 CC", ((4, "REL32", 0x10017DDE),))
add((0x1001D37A,), "IVF_LOCAL_SEH_TERMINATE_RETURN_1001D37A",
    ("mov esp, DWORD PTR [ebp - 18h]", "call {CODE_10017DDE}", "xor eax, eax",
     "call {CODE_10012E65}", "ret"),
    "8B 65 E8 E8 00 00 00 00 33 C0 E8 00 00 00 00 C3",
    ((4, "REL32", 0x10017DDE), (11, "REL32", 0x10012E65)))
add((0x1001D413,), "IVF_LOCAL_SEH_TERMINATE_1001D413",
    ("mov esp, DWORD PTR [ebp - 18h]", "call {CODE_10017DDE}", "int 3"),
    "8B 65 E8 E8 00 00 00 00 CC", ((4, "REL32", 0x10017DDE),))
add((0x1002051F,), "IVF_LOCAL_SEH_FLOAT_EXCEPTION_FILTER_1002051F",
    ("mov eax, DWORD PTR [ebp - 14h]", "mov eax, DWORD PTR [eax]",
     "mov eax, DWORD PTR [eax]", "cmp eax, 0C0000005h",
     "je IVF_2051F_yes", "cmp eax, 0C000001Dh", "je IVF_2051F_yes",
     "xor eax, eax", "ret", "IVF_2051F_yes:", "xor eax, eax", "inc eax", "ret"),
    "8B 45 EC 8B 00 8B 00 3D 05 00 00 C0 74 0A 3D 1D 00 00 C0 74 03 33 C0 C3 33 C0 40 C3")
add((0x1002053B,), "IVF_LOCAL_SEH_FLOAT_EPILOG_1002053B",
    ("mov esp, DWORD PTR [ebp - 18h]",
     "and DWORD PTR [IVF_RELOC_TARGET_100396F4], 0",
     "and DWORD PTR [ebp + 8], 0FFFFFFBFh", "DB 0Fh, 0AEh, 55h, 08h",
     "mov DWORD PTR [ebp - 4], -2", "jmp IVF_2053B_tail",
     "and DWORD PTR [ebp + 8], 0FFFFFFBFh", "DB 0Fh, 0AEh, 55h, 08h",
     "IVF_2053B_tail:", "call {CODE_10012E65}", "ret"),
    "8B 65 E8 83 25 00 00 00 00 00 83 65 08 BF 0F AE 55 08 C7 45 FC FE FF FF FF EB 08 83 65 08 BF 0F AE 55 08 E8 00 00 00 00 C3",
    ((5, "DIR32", 0x100396F4), (36, "REL32", 0x10012E65)))

add((0x10018A86,), "IVF_LOCAL_BITFIELD_UNLOCK_10018A86",
    ("xor edi, edi", "mov esi, DWORD PTR [ebp + 18h]",
     "cmp DWORD PTR [ebp - 1Ch], edi", "je IVF_18A86_done",
     "cmp DWORD PTR [ebp - 20h], edi", "je IVF_18A86_unlock",
     "mov eax, DWORD PTR [esi]", "mov ecx, eax", "sar ecx, 5",
     "and eax, 1Fh", "shl eax, 6",
     "mov ecx, DWORD PTR [ecx*4 + IVF_RELOC_TARGET_1003C420]",
     "lea eax, [ecx + eax + 4]", "and BYTE PTR [eax], 0FEh",
     "IVF_18A86_unlock:", "push DWORD PTR [esi]", "call {CODE_100191A6}",
     "pop ecx", "IVF_18A86_done:", "ret"),
    "33 FF 8B 75 18 39 7D E4 74 28 39 7D E0 74 1B 8B 06 8B C8 C1 F9 05 83 E0 1F C1 E0 06 8B 0C 8D 00 00 00 00 8D 44 01 04 80 20 FE FF 36 E8 00 00 00 00 59 C3",
    ((31, "DIR32", 0x1003C420), (45, "REL32", 0x100191A6)))

# Recreate the local C++ exception-filter entry that is called from a thunk.
# This stub must precede its caller so the local target symbol is available.
add((0x1001CEE8,), "IVF_LOCAL_EXCEPTION_FILTER_1001CEE8",
    ("mov eax, DWORD PTR [eax]", "cmp DWORD PTR [eax], 0E06D7363h",
     "jne IVF_1CEE8_no", "cmp DWORD PTR [eax + 10h], 3",
     "jne IVF_1CEE8_no", "mov ecx, DWORD PTR [eax + 14h]",
     "cmp ecx, 19930520h", "je IVF_1CEE8_yes",
     "cmp ecx, 19930521h", "je IVF_1CEE8_yes",
     "cmp ecx, 19930522h", "jne IVF_1CEE8_no",
     "IVF_1CEE8_yes:", "cmp DWORD PTR [eax + 1Ch], 0",
     "jne IVF_1CEE8_no", "call {CODE_10014DF0}", "xor ecx, ecx",
     "inc ecx", "mov DWORD PTR [eax + 20Ch], ecx", "mov eax, ecx",
     "ret", "IVF_1CEE8_no:", "xor eax, eax", "ret"),
    "8B 00 81 38 63 73 6D E0 75 38 83 78 10 03 75 32 8B 48 14 81 F9 20 05 93 19 74 10 81 F9 21 05 93 19 74 08 81 F9 22 05 93 19 75 17 83 78 1C 00 75 11 E8 00 00 00 00 33 C9 41 89 88 0C 02 00 00 8B C1 C3 33 C0 C3",
    ((50, "REL32", 0x10014DF0),))
add((0x1001D0FF,), "IVF_LOCAL_EXCEPTION_FILTER_THUNK_1001D0FF",
    ("mov eax, DWORD PTR [ebp - 14h]",
     "call {CODE_1001CEE8}", "ret"),
    "8B 45 EC E8 00 00 00 00 C3", ((4, "REL32", 0x1001CEE8),))

add((0x1001D108,), "IVF_LOCAL_CATCH_HANDLER_1001D108",
    ("mov esp, DWORD PTR [ebp - 18h]", "call {CODE_10014DF0}",
     "and DWORD PTR [eax + 20Ch], 0", "mov esi, DWORD PTR [ebp + 14h]",
     "mov edi, DWORD PTR [ebp + 0Ch]", "cmp DWORD PTR [esi + 4], 80h",
     "jg IVF_D108_wide", "movsx ecx, BYTE PTR [edi + 8]",
     "jmp IVF_D108_char_ready", "IVF_D108_wide:",
     "mov ecx, DWORD PTR [edi + 8]", "IVF_D108_char_ready:",
     "mov ebx, DWORD PTR [esi + 10h]", "and DWORD PTR [ebp - 20h], 0",
     "IVF_D108_loop:", "mov eax, DWORD PTR [ebp - 20h]",
     "cmp eax, DWORD PTR [esi + 0Ch]", "jae IVF_D108_unwind",
     "imul eax, eax, 14h", "mov edx, DWORD PTR [eax + ebx + 4]",
     "cmp ecx, edx", "jle IVF_D108_next", "cmp ecx, DWORD PTR [eax + ebx + 8]",
     "jg IVF_D108_next", "mov eax, DWORD PTR [esi + 8]",
     "mov ecx, DWORD PTR [eax + edx*8 + 8]", "IVF_D108_unwind:",
     "push ecx", "push esi", "push 0", "push edi", "call {CODE_1001CE0C}",
     "add esp, 10h", "and DWORD PTR [ebp - 1Ch], 0",
     "and DWORD PTR [ebp - 4], 0", "mov esi, DWORD PTR [ebp + 8]",
     "mov DWORD PTR [ebp - 4], -2", "mov DWORD PTR [ebp + 10h], 0",
     "call {CODE_1001D195}", "mov eax, DWORD PTR [ebp - 1Ch]",
     "call {CODE_10012E65}", "ret", "IVF_D108_next:",
     "inc DWORD PTR [ebp - 20h]", "jmp IVF_D108_loop"),
    "8B 65 E8 E8 00 00 00 00 83 A0 0C 02 00 00 00 8B 75 14 8B 7D 0C 81 7E 04 80 00 00 00 7F 06 0F BE 4F 08 EB 03 8B 4F 08 8B 5E 10 83 65 E0 00 8B 45 E0 3B 46 0C 73 18 6B C0 14 8B 54 18 04 3B CA 7E 41 3B 4C 18 08 7F 3B 8B 46 08 8B 4C D0 08 51 56 6A 00 57 E8 00 00 00 00 83 C4 10 83 65 E4 00 83 65 FC 00 8B 75 08 C7 45 FC FE FF FF FF C7 45 10 00 00 00 00 E8 00 00 00 00 8B 45 E4 E8 00 00 00 00 C3 FF 45 E0 EB A7",
    ((4, "REL32", 0x10014DF0), (84, "REL32", 0x1001CE0C),
     (117, "REL32", 0x1001D195), (125, "REL32", 0x10012E65)))

# Exact six-byte prefix falls through to the existing candidate entry. The
# diagnostic provider adds a non-mutating jump tail to preserve that flow.
add((0x1001D18F,), "IVF_LOCAL_CATCH_HANDLER_PREFIX_1001D18F",
    ("mov edi, DWORD PTR [ebp + 0Ch]", "mov esi, DWORD PTR [ebp + 8]"),
    "8B 7D 0C 8B 75 08", tail_jump=0x1001D195)

# Exact 0x4b-byte callback-dispatch bodies installed dynamically by
# FUN_1000bca0. Their only per-body difference is the callback slot at EBX+4..+14.
# Ghidra listing, xrefs, and the original PE confirm each entry and its operands.
for target, slot in (
    (0x1000CAA0, 0x04),
    (0x1000CAF0, 0x08),
    (0x1000CB40, 0x0C),
    (0x1000CB90, 0x10),
    (0x1000CBE0, 0x14),
):
    suffix = f"{target:08X}"
    loop_label = f"IVF_PLUGIN_CALLBACK_{suffix}_LOOP"
    callback_label = f"IVF_PLUGIN_CALLBACK_{suffix}_SLOT"
    failed_label = f"IVF_PLUGIN_CALLBACK_{suffix}_FAILED"
    slot_operand = f"0{slot:X}h"
    # C-linkage x86 symbols emitted by MSVC carry a leading underscore.
    add((target,), f"_IVF_PLUGIN_CALLBACK_DISPATCH_{suffix}",
        (
            "push ebx",
            "mov ebx, DWORD PTR [IVF_RELOC_TARGET_1003C3CC]",
            "push esi",
            "mov esi, DWORD PTR [ebx + 18h]",
            "push edi",
            "mov edi, DWORD PTR [ebx + 1Ch]",
            "cmp esi, edi",
            f"je {callback_label}",
            f"{loop_label}:",
            "mov eax, DWORD PTR [esi]",
            "test eax, eax",
            f"je {loop_label}_NEXT",
            "call eax",
            f"{loop_label}_NEXT:",
            "add esi, 4",
            "cmp esi, edi",
            f"jne {loop_label}",
            f"{callback_label}:",
            f"mov eax, DWORD PTR [ebx + {slot_operand}]",
            "test eax, eax",
            f"je {failed_label}",
            "call eax",
            "mov esi, eax",
            "lea eax, [ebx + 28h]",
            "call {CODE_100099F0}",
            "pop edi",
            "mov eax, esi",
            "pop esi",
            "pop ebx",
            "ret",
            f"{failed_label}:",
            "lea eax, [ebx + 28h]",
            "xor esi, esi",
            "call {CODE_100099F0}",
            "pop edi",
            "mov eax, esi",
            "pop esi",
            "pop ebx",
            "ret",
        ),
        "53 8B 1D 00 00 00 00 56 8B 73 18 57 8B 7B 1C 3B F7 74 0F "
        "8B 06 85 C0 74 02 FF D0 83 C6 04 3B F7 75 F1 "
        f"8B 43 {slot:02X} 85 C0 74 12 FF D0 8B F0 8D 43 28 "
        "E8 00 00 00 00 5F 8B C6 5E 5B C3 8D 43 28 33 F6 "
        "E8 00 00 00 00 5F 8B C6 5E 5B C3",
        ((3, "DIR32", 0x1003C3CC), (0x31, "REL32", 0x100099F0),
         (0x41, "REL32", 0x100099F0)))

# C++ EH funclets referenced by the registration record in FUN_10008000 and
# CRT exception metadata. These are code fragments outside Ghidra function
# bodies. Preserve their exact x86 instructions, relocating FuncInfo pointers
# and transferring to the candidate CRT handlers by relative COFF relocations.
add((0x10020848,), "_IVF_EH_HANDLER_10020848",
    ("mov eax, OFFSET IVF_RELOC_TARGET_10028620", "jmp {CODE_1001B6E7}"),
    "B8 00 00 00 00 E9 00 00 00 00",
    ((1, "DIR32", 0x10028620), (6, "REL32", 0x1001B6E7)))

add((0x10020852,), "_IVF_EH_HANDLER_10020852",
    ("mov edx, DWORD PTR [esp + 8]", "lea eax, [edx + 0Ch]",
     "mov ecx, DWORD PTR [edx - 14h]", "xor ecx, eax",
     "call {CODE_100172D5}", "mov eax, OFFSET IVF_RELOC_TARGET_100286C0",
     "jmp {CODE_1001B6E7}"),
    "8B 54 24 08 8D 42 0C 8B 4A EC 33 C8 E8 00 00 00 00 "
    "B8 00 00 00 00 E9 00 00 00 00",
    ((13, "REL32", 0x100172D5), (18, "DIR32", 0x100286C0),
     (23, "REL32", 0x1001B6E7)))


# The 0x1001ce94 SEH continuation re-enters an interior block of
# ___FrameUnwindToState. Recreate the exact cleanup continuation and the
# relevant loop/epilog blocks out-of-line rather than jumping to the function
# entry (which would repeat its prologue and change stack semantics).
add((0x1001CE94,), "IVF_LOCAL_FRAME_UNWIND_SEH_CONTINUATION_1001CE94",
    ("mov esp, DWORD PTR [ebp - 18h]", "and DWORD PTR [ebp - 4], 0",
     "mov edi, DWORD PTR [ebp + 10h]", "mov ebx, DWORD PTR [ebp + 8]",
     "mov esi, DWORD PTR [ebp - 20h]", "mov DWORD PTR [ebp - 1Ch], esi",
     "jmp SHORT IVF_1CE42_LOOP"),
    "8B 65 E8 83 65 FC 00 8B 7D 10 8B 5D 08 8B 75 E0 89 75 E4 EB 00",
    ((20, "REL8", 0x1001CE42),),
    blocks=(
        {"source_va": 0x1001CE42, "label": "IVF_1CE42_LOOP", "asm": ("cmp esi, DWORD PTR [ebp + 14h]", "je SHORT IVF_1CEA9_CLEANUP", "cmp esi, -1", "jle SHORT IVF_1CE51_TERMINATE", "cmp esi, DWORD PTR [edi + 4]", "jl SHORT IVF_1CE56_LOAD", "IVF_1CE51_TERMINATE:", "call {CODE_10017E2A}", "IVF_1CE56_LOAD:", "mov eax, esi", "mov ecx, DWORD PTR [edi + 8]", "mov esi, DWORD PTR [ecx + eax*8]", "mov DWORD PTR [ebp - 20h], esi", "mov DWORD PTR [ebp - 4], 1", "cmp DWORD PTR [ecx + eax*8 + 4], 0", "je SHORT IVF_1CE84_CLEAR", "mov DWORD PTR [ebx + 8], esi", "push 103h", "push ebx", "mov ecx, DWORD PTR [edi + 8]", "push DWORD PTR [ecx + eax*8 + 4]", "call {CODE_1001DA10}", "IVF_1CE84_CLEAR:", "and DWORD PTR [ebp - 4], 0", "jmp SHORT IVF_1CEA4_CONVERGE"), "body": bytes.fromhex("3B 75 14 74 00 83 FE FF 7E 00 3B 77 04 7C 00 E8 00 00 00 00 8B C6 8B 4F 08 8B 34 C1 89 75 E0 C7 45 FC 01 00 00 00 83 7C C1 04 00 74 00 89 73 08 68 03 01 00 00 53 8B 4F 08 FF 74 C1 04 E8 00 00 00 00 83 65 FC 00 EB 00"), "fixups": ((4, "REL8", 0x1001CEA9), (9, "REL8", 0x1001CE51), (14, "REL8", 0x1001CE56), (16, "REL32", 0x10017E2A), (44, "REL8", 0x1001CE84), (62, "REL32", 0x1001DA10), (71, "REL8", 0x1001CEA4))},
        {"source_va": 0x1001CEA4, "label": "IVF_1CEA4_CONVERGE", "asm": ("mov DWORD PTR [ebp - 1Ch], esi", "jmp SHORT IVF_1CE42_LOOP"), "body": bytes.fromhex("89 75 E4 EB 00"), "fixups": ((4, "REL8", 0x1001CE42),)},
        {"source_va": 0x1001CEA9, "label": "IVF_1CEA9_CLEANUP", "asm": ("mov DWORD PTR [ebp - 4], -2", "call {CODE_1001CECE}", "cmp esi, DWORD PTR [ebp + 14h]", "je SHORT IVF_1CEBF_EPILOG", "call {CODE_10017E2A}"), "body": bytes.fromhex("C7 45 FC FE FF FF FF E8 00 00 00 00 3B 75 14 74 00 E8 00 00 00 00"), "fixups": ((8, "REL32", 0x1001CECE), (16, "REL8", 0x1001CEBF), (18, "REL32", 0x10017E2A))},
        {"source_va": 0x1001CEBF, "label": "IVF_1CEBF_EPILOG", "asm": ("mov DWORD PTR [ebx + 8], esi", "call {CODE_10012E65}", "ret"), "body": bytes.fromhex("89 73 08 E8 00 00 00 00 C3"), "fixups": ((4, "REL32", 0x10012E65),)},
    ))
