#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#pragma warning(disable:4733)
extern "C" __declspec(naked) void __stdcall __SEH_epilog4(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 10h]
        mov dword ptr fs:[0], ecx
        pop ecx
        pop edi
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        push ecx
        ret
    }
}
