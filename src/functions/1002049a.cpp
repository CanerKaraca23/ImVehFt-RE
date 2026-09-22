#include <cstdint>

// MSVC's inline assembler cannot encode FLD m80fp at an absolute address
// without adding a segment prefix. Emit the original DB /5 absolute forms.
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
        _emit 0DBh
        _emit 02Dh
        _emit 0DCh
        _emit 096h
        _emit 003h
        _emit 010h
        fistp dword ptr [ebp + 8]
        wait

    skip_integer_rounding:
        test cl, 08h
        jz skip_status_capture
        fstsw ax
        _emit 0DBh
        _emit 02Dh
        _emit 0DCh
        _emit 096h
        _emit 003h
        _emit 010h
        fstp qword ptr [ebp - 8]
        wait
        fstsw ax

    skip_status_capture:
        test cl, 10h
        jz skip_secondary_constant
        _emit 0DBh
        _emit 02Dh
        _emit 0E8h
        _emit 096h
        _emit 003h
        _emit 010h
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