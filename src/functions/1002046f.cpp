#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) int __cdecl __ctrlfp(
    unsigned int ,
    unsigned int )
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ecx
        fstcw word ptr [ebp - 4]
        mov eax, dword ptr [ebp + 0ch]
        mov ecx, dword ptr [ebp + 8]
        and ecx, dword ptr [ebp + 0ch]
        not eax
        and ax, word ptr [ebp - 4]
        or ax, cx
        movzx eax, ax
        mov dword ptr [ebp + 0ch], eax
        fldcw word ptr [ebp + 0ch]
        movsx eax, word ptr [ebp - 4]
        leave
        ret
    }
}
