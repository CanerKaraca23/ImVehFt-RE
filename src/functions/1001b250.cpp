#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>

extern "C" void __stdcall __alloca_probe(void);

extern "C" __declspec(naked) unsigned int __stdcall __alloca_probe_16()
{
    __asm {
        push ecx
        lea ecx, [esp + 8]
        sub ecx, eax
        and ecx, 0Fh
        add eax, ecx
        sbb ecx, ecx
        or eax, ecx
        pop ecx
        jmp __alloca_probe
    }
}
