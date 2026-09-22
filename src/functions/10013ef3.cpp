#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int __cdecl flsall(int param_1);

extern "C" int __cdecl __flushall(void)
{
    int iVar1 = flsall(1);
    return iVar1;
}