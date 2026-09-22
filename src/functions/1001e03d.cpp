#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#pragma warning(disable:4733)
__declspec(naked) void __cdecl __EH_prolog3_catch(void)
{
    __asm {
        push eax
        push dword ptr fs:[0]
        lea eax, [esp + 0Ch]
        sub esp, dword ptr [esp + 0Ch]
        push ebx
        push esi
        push edi
        mov dword ptr [eax], ebp
        mov ebp, eax
        mov eax, 10029490h
        mov eax, dword ptr [eax]
        xor eax, ebp
        push eax
        mov dword ptr [ebp - 10h], esp
        push dword ptr [ebp - 4]
        mov dword ptr [ebp - 4], 0FFFFFFFFh
        lea eax, [ebp - 0Ch]
        mov dword ptr fs:[0], eax
        ret
    }
}