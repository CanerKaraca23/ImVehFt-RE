#include <cstdint>

__declspec(naked) std::uint32_t __fastcall __fload_withFB(std::uint32_t, int)
{
    __asm
    {
        mov eax, dword ptr [edx + 4]
        and eax, 0x7ff00000
        cmp eax, 0x7ff00000
        jz special_value
        fld qword ptr [edx]
        ret

    special_value:
        mov eax, dword ptr [edx + 4]
        sub esp, 0x0a
        or eax, 0x7fff0000
        mov dword ptr [esp + 6], eax
        mov eax, dword ptr [edx + 4]
        mov ecx, dword ptr [edx]
        shld eax, ecx, 0x0b
        shl ecx, 0x0b
        mov dword ptr [esp + 4], eax
        mov dword ptr [esp], ecx
        fld tbyte ptr [esp]
        add esp, 0x0a
        test eax, 0
        mov eax, dword ptr [edx + 4]
        ret
    }
}
