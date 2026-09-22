#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __cdecl FUN_10010120(
    float,
    float)
{
    __asm {
        push ebp
        mov ebp, esp
        fld dword ptr [ebp + 0ch]
        sub esp, 8
        fstp dword ptr [esp + 4]
        mov eax, 053cc70h
        fld dword ptr [ebp + 8]
        fstp dword ptr [esp]
        call eax
        add esp, 8
        pop ebp
        ret
    }
}
