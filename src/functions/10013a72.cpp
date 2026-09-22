#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __fastcall _EH4_CallFilterFunc(
    void* ,
    void* )
{
    __asm {
        push ebp
        push esi
        push edi
        push ebx
        mov ebp, edx
        xor eax, eax
        xor ebx, ebx
        xor edx, edx
        xor esi, esi
        xor edi, edi
        call ecx
        pop ebx
        pop edi
        pop esi
        pop ebp
        ret
    }
}
