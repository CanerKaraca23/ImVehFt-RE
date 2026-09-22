#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall FUN_10010140(
    unsigned int,
    unsigned int,
    unsigned int,
    unsigned int)
{
    __asm {
        push ebp
        mov ebp, esp
        fld dword ptr [ebp + 14h]
        sub esp, 10h
        fstp dword ptr [esp + 0ch]
        mov eax, 04041c0h
        fld dword ptr [ebp + 10h]
        mov ecx, esi
        fstp dword ptr [esp + 8]
        fld dword ptr [ebp + 0ch]
        fstp dword ptr [esp + 4]
        fld dword ptr [ebp + 8]
        fstp dword ptr [esp]
        call eax
        mov eax, esi
        pop ebp
        ret 10h
    }
}
