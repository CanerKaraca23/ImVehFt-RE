#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __unlock_fhandle(int _FileHandle);

extern "C" __declspec(naked) void __stdcall FUN_10019b2f(void)
{
    __asm
    {
        push ebx
        call __unlock_fhandle
        add  esp, 4
        ret
    }
}