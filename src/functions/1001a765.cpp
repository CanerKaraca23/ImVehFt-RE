#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __unlock_fhandle(int _Filehandle);

extern "C" void __stdcall FUN_1001a765(int _FileHandle)
{
    __unlock_fhandle(_FileHandle);
}