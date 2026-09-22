#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall __shift(void)
{
    __asm {
        push esi
        mov esi, eax
        test edi, edi
        jz done
        push esi
        mov eax, 10011650h
        call eax
        inc eax
        push eax
        push esi
        add esi, edi
        push esi
        mov eax, 100111E0h
        call eax
        add esp, 10h
    done:
        pop esi
        ret
    }
}