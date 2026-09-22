#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall __alloca_probe()
{
    __asm {
        mov     ecx, esp
        sub     ecx, eax
        sbb     edx, edx
        not     edx
        and     ecx, edx

        lea     edx, [esp - 4]
        and     edx, 0FFFFF000h

    probe_loop:
        cmp     ecx, edx
        jae     probe_done
        sub     edx, 400h
        jmp     probe_loop

    probe_done:
        mov     eax, [esp]
        mov     [ecx], eax
        ret
    }
}