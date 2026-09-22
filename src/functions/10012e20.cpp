#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#pragma warning(disable:4733)
__declspec(naked) void __cdecl __SEH_prolog4(void)
{
    __asm {
        push 10012E90h
        push dword ptr fs:[0]
        mov eax, dword ptr [esp + 10h]
        mov dword ptr [esp + 10h], ebp
        lea ebp, [esp + 10h]
        sub esp, eax
        push ebx
        push esi
        push edi
        mov eax, 10029490h
        mov eax, dword ptr [eax]
        xor dword ptr [ebp - 4], eax
        xor eax, ebp
        push eax
        mov dword ptr [ebp - 18h], esp
        push dword ptr [ebp - 8]
        mov eax, dword ptr [ebp - 4]
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        mov dword ptr [ebp - 8], eax
        lea eax, [ebp - 10h]
        mov dword ptr fs:[0], eax
        ret
    }
}