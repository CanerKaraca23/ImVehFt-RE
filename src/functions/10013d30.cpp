#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __unlock_fhandle(int _FileHandle);

extern "C" void __stdcall FUN_10013d30()
{
    int _FileHandle;

    __asm
    {
        mov _FileHandle, ebx
    }

    __unlock_fhandle(_FileHandle);
}