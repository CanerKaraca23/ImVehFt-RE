#include <cstdint>

extern "C" long double __fastcall __startOneArgErrorHandling(
    std::uint32_t param_1,
    int param_2,
    std::uint16_t param_3,
    std::uint32_t param_4,
    std::uint32_t param_5,
    std::uint32_t param_6);

extern "C" __declspec(naked) void __cdecl __math_exit()
{
    __asm
    {
        mov ax, word ptr [esp]
        cmp ax, 027Fh
        je already_default
        test ax, 020h
        je restore_control_word
        fstsw ax
        test ax, 020h
        je restore_control_word
        mov eax, 8
        call __startOneArgErrorHandling
        pop edx
        ret

    restore_control_word:
        fldcw word ptr [esp]

    already_default:
        pop edx
        ret
    }
}
