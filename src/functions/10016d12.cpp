#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
extern "C" HANDLE DAT_10039b90;

extern "C" int __cdecl __heap_init(void)
{
    DAT_10039b90 = HeapCreate(0, 0x1000, 0);
    return static_cast<int>(DAT_10039b90 != static_cast<HANDLE>(0x0));
}