#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
extern "C" HANDLE DAT_10029f10;

extern "C" void __stdcall FUN_1001b29b()
{
    if ((DAT_10029f10 != (HANDLE)0xffffffff) &&
        (DAT_10029f10 != (HANDLE)0xfffffffe))
    {
        CloseHandle(DAT_10029f10);
    }
}