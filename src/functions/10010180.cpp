#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall FUN_10010180(void)
{
    __asm {
        push 0ffh
        push 0ffh
        push 0ffh
        push 0ffh
        mov eax, 07170c0h
        mov ecx, esi
        call eax
        mov eax, esi
        ret
    }
}
