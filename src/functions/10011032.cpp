#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall FUN_10011032(void)
{
    __asm {
        cmp dword ptr [ebp + 10h], edi
        jne done
        mov eax, 10029c0ch
        cmp dword ptr [eax], -1
        je done
        mov eax, 10014c86h
        call eax
    done:
        ret
    }
}