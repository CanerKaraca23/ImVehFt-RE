#include <cstdint>
#include <cstdio>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This ABI harness must be built with MSVC for x86."
#endif

extern "C" std::uint32_t g_error_status = 0;
extern "C" std::uint32_t g_slot_param4 = 0;
extern "C" std::uint32_t g_slot_param5 = 0;
extern "C" std::uint32_t g_slot_param6 = 0;
extern "C" std::uint32_t g_slot_param7 = 0;
extern "C" std::uint32_t g_slot_param8 = 0;
extern "C" std::uint64_t g_input_bits = 0x400A000000000000ULL; // 3.25
extern "C" std::uint64_t g_output_bits = 0;
extern "C" std::uint16_t g_stub_control_word = 0x0B7F;
extern "C" std::uint16_t g_after_control_word = 0;
extern "C" std::uint16_t g_after_status_word = 0;
extern "C" std::uint32_t g_stub_calls = 0;
extern "C" std::uint32_t g_layout_ok = 0;

extern long double __fastcall FUN_1001cb20(
    std::uint32_t, int, std::uint16_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);

extern "C" void __cdecl __87except(
    std::uint32_t error_code,
    std::uint32_t* argument_block,
    std::uint16_t* control_word_slot)
{
    ++g_stub_calls;
    g_layout_ok = error_code == 0x33333333 &&
        argument_block[0] == 0x11111111 &&
        argument_block[1] == 0x22222222 &&
        argument_block[2] == 0x44444444 &&
        argument_block[3] == 0x55555555 &&
        argument_block[4] == 0x66666666 &&
        argument_block[5] == 0x77777777 &&
        *reinterpret_cast<std::uint64_t*>(argument_block + 6) == g_input_bits &&
        reinterpret_cast<std::uintptr_t>(control_word_slot) -
            reinterpret_cast<std::uintptr_t>(argument_block) == 0x28 &&
        *control_word_slot == static_cast<std::uint16_t>(g_error_status);

    __asm {
        fldcw word ptr g_stub_control_word
    }
}

// Reference transcribed from Ghidra's 0x1001cb20 prologue and the common
// 0x1001cb40 tail at the start of __startOneArgErrorHandling.
extern "C" __declspec(naked) void call_ghidra_reference()
{
    __asm {
        push ebp
        mov ebp, esp
        add esp, -20h
        mov dword ptr [ebp - 20h], eax
        mov eax, dword ptr [ebp + 18h]
        mov dword ptr [ebp - 10h], eax
        mov eax, dword ptr [ebp + 1Ch]
        mov dword ptr [ebp - 0Ch], eax
        jmp reference_common_tail

    reference_common_tail:
        fstp qword ptr [ebp - 8]
        mov dword ptr [ebp - 1Ch], ecx
        mov eax, dword ptr [ebp + 10h]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ebp - 18h], eax
        mov dword ptr [ebp - 14h], ecx
        lea eax, [ebp + 8]
        lea ecx, [ebp - 20h]
        push eax
        push ecx
        push edx
        call __87except
        add esp, 0Ch
        fld qword ptr [ebp - 8]
        cmp word ptr [ebp + 8], 027Fh
        je reference_restore_frame
        fldcw word ptr [ebp + 8]

    reference_restore_frame:
        leave
        ret
    }
}

extern "C" __declspec(naked) void call_candidate()
{
    __asm {
        push ebp
        mov ebp, esp
        push 77777777h
        push 66666666h
        push 55555555h
        push 44444444h
        push dword ptr g_slot_param4
        push dword ptr g_error_status
        fld qword ptr g_input_bits
        mov eax, 11111111h
        mov ecx, 22222222h
        mov edx, 33333333h
        call FUN_1001cb20
        add esp, 18h
        fstp qword ptr g_output_bits
        fnstsw ax
        mov word ptr g_after_status_word, ax
        fnstcw word ptr g_after_control_word
        leave
        ret
    }
}

extern "C" __declspec(naked) void call_reference()
{
    __asm {
        push ebp
        mov ebp, esp
        push 77777777h
        push 66666666h
        push 55555555h
        push 44444444h
        push dword ptr g_slot_param4
        push dword ptr g_error_status
        fld qword ptr g_input_bits
        mov eax, 11111111h
        mov ecx, 22222222h
        mov edx, 33333333h
        call call_ghidra_reference
        add esp, 18h
        fstp qword ptr g_output_bits
        fnstsw ax
        mov word ptr g_after_status_word, ax
        fnstcw word ptr g_after_control_word
        leave
        ret
    }
}

static bool run_case(const char* label, void (*invoke)(), std::uint16_t status)
{
    g_error_status = status;
    g_stub_control_word = 0x0B7F;
    g_after_control_word = 0;
    g_after_status_word = 0;
    g_stub_calls = 0;
    g_layout_ok = 0;
    g_output_bits = 0;
    invoke();

    const std::uint16_t expected_control_word =
        status == 0x027F ? g_stub_control_word : status;
    const bool one_x87_value_returned_and_popped =
        ((g_after_status_word >> 11) & 7) == 0;
    const bool passed =
        g_stub_calls == 1 &&
        g_layout_ok == 1 &&
        g_output_bits == g_input_bits &&
        one_x87_value_returned_and_popped &&
        g_after_control_word == expected_control_word;

    std::printf(
        "%s status=%04X stub=%u frame=%u output=%016llX TOP=%u CW=%04X expected-CW=%04X %s\n",
        label,
        status,
        g_stub_calls,
        g_layout_ok,
        static_cast<unsigned long long>(g_output_bits),
        (g_after_status_word >> 11) & 7,
        g_after_control_word,
        expected_control_word,
        passed ? "PASS" : "FAIL");
    return passed;
}

int main()
{
    const bool reference_default = run_case("Ghidra-reference", call_reference, 0x027F);
    const bool reference_restore = run_case("Ghidra-reference", call_reference, 0x037F);
    const bool candidate_default = run_case("candidate", call_candidate, 0x027F);
    const bool candidate_restore = run_case("candidate", call_candidate, 0x037F);
    return reference_default && reference_restore && candidate_default && candidate_restore ? 0 : 1;
}
