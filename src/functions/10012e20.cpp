#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#pragma warning(disable:4733)

extern "C" std::uint32_t __cdecl __except_handler4(
    void*,
    void*,
    std::uint32_t);
extern "C" std::uint32_t DAT_10029490;

extern "C" __declspec(naked) void __cdecl __SEH_prolog4(
    std::uint32_t,
    int)
{
    __asm {
        push OFFSET __except_handler4
        push dword ptr fs:[0]
        mov eax, dword ptr [esp + 10h]
        mov dword ptr [esp + 10h], ebp
        lea ebp, [esp + 10h]
        sub esp, eax
        push ebx
        push esi
        push edi
        mov eax, OFFSET DAT_10029490
        mov eax, dword ptr [eax]
        xor dword ptr [ebp - 4], eax
        xor eax, ebp
        push eax
        mov dword ptr [ebp - 18h], esp
        push dword ptr [ebp - 8]
        mov eax, dword ptr [ebp - 4]
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        mov dword ptr [ebp - 8], eax
        lea eax, [ebp - 10h]
        mov dword ptr fs:[0], eax
        ret
    }
}
