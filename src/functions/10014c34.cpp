#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_10017cd2(int param_1);

// This address is a shared CRT cleanup fragment: it inherits the caller's EBP
// frame and must restore that frame's saved ESI after releasing lock 12.
extern "C" __declspec(naked) void __stdcall FUN_10014c34(void)
{
    __asm {
        push 0ch
        call FUN_10017cd2
        pop ecx
        mov esi, dword ptr [ebp - 1ch]
        ret
    }
}
