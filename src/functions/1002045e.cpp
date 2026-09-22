#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) int __stdcall __clrfp(void)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ecx
        fnstsw word ptr [ebp - 4]
        fnclex
        movsx eax, word ptr [ebp - 4]
        leave
        ret
    }
}
