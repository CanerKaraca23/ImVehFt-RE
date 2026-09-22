#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) unsigned int __stdcall __alloca_probe_16()
{
    __asm {
        mov     ecx, 4
        sub     ecx, eax
        and     ecx, 0Fh

        add     eax, ecx
        sbb     edx, edx
        or      eax, edx

        ret
    }
}