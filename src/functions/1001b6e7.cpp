#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) std::uint32_t __cdecl
FID_conflict____CxxFrameHandler3(void)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        push ebx
        push esi
        push edi
        cld
        mov dword ptr [ebp - 4], eax
        xor eax, eax
        push eax
        push eax
        push eax
        push dword ptr [ebp - 4]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        push dword ptr [ebp + 8]
        mov eax, 1001D923h
        call eax
        add esp, 20h
        mov dword ptr [ebp - 8], eax
        pop edi
        pop esi
        pop ebx
        mov eax, dword ptr [ebp - 8]
        mov esp, ebp
        pop ebp
        ret
    }
}