#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#pragma warning(disable:4733)
extern "C" __declspec(naked) void __stdcall _JumpToContinuation(
    void*,
    void*)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ecx
        push ebx
        mov eax, dword ptr [ebp + 0ch]
        add eax, 0ch
        mov dword ptr [ebp - 4], eax
        mov ebx, dword ptr fs:[0]
        mov eax, dword ptr [ebx]
        mov dword ptr fs:[0], eax
        mov eax, dword ptr [ebp + 8]
        mov ebx, dword ptr [ebp + 0ch]
        mov ebp, dword ptr [ebp - 4]
        mov esp, dword ptr [ebx - 4]
        jmp eax
    }
}
