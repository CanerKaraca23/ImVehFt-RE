#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
extern "C" HANDLE DAT_10029f10;

extern "C" void __cdecl ___initconout()
{
    DAT_10029f10 = CreateFileW(
        L"CONOUT$",
        0x40000000,
        3,
        nullptr,
        3,
        0,
        nullptr);
}