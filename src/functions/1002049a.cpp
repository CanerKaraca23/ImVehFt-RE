#include <cstdint>

extern "C" std::uint32_t DAT_100396d8;

extern "C" __declspec(naked) void __cdecl FUN_1002049a(std::uint32_t)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ecx
        push ecx
        mov cl, byte ptr [ebp + 8]

        test cl, 01h
        jz skip_integer_rounding
        fld tbyte ptr [DAT_100396d8 + 4]
        fistp dword ptr [ebp + 8]
        wait

    skip_integer_rounding:
        test cl, 08h
        jz skip_status_capture
        fstsw ax
        fld tbyte ptr [DAT_100396d8 + 4]
        fstp qword ptr [ebp - 8]
        wait
        fstsw ax

    skip_status_capture:
        test cl, 10h
        jz skip_secondary_constant
        fld tbyte ptr [DAT_100396d8 + 10h]
        fstp qword ptr [ebp - 8]
        wait

    skip_secondary_constant:
        test cl, 04h
        jz skip_divide
        fldz
        fld1
        fdivrp st(1), st(0)
        fstp st(0)
        wait

    skip_divide:
        test cl, 20h
        jz finish
        fldpi
        fstp qword ptr [ebp - 8]
        wait

    finish:
        leave
        ret
    }
}
