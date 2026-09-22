#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
extern "C" HANDLE DAT_10039b90;

extern "C" void __cdecl __heap_term(void)
{
    HeapDestroy(DAT_10039b90);
    DAT_10039b90 = static_cast<HANDLE>(0x0);
}