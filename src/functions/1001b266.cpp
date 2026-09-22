#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) unsigned int __stdcall __alloca_probe_8()
{
    __asm {
        mov     ecx, 4
        sub     ecx, eax
        and     ecx, 7

        add     eax, ecx
        sbb     edx, edx
        or      eax, edx

        ret
    }
}