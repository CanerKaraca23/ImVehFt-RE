#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall __alloca_probe()
{
    __asm {
        push    ecx
        lea     ecx, [esp + 4]
        sub     ecx, eax
        sbb     eax, eax
        not     eax
        and     ecx, eax

        mov     eax, esp
        and     eax, 0FFFFF000h
    probe_loop:
        cmp     ecx, eax
        jb      probe_page
        mov     eax, ecx
        pop     ecx
        xchg    esp, eax
        mov     eax, [eax]
        mov     [esp], eax
        ret
    probe_page:
        sub     eax, 1000h
        test    dword ptr [eax], eax
        jmp     probe_loop
    }
}
