#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern int DAT_1003aacc;

extern "C" void __cdecl FUN_10001ad0(int param_1)
{
    int iVar1 = DAT_1003aacc;

    *reinterpret_cast<int*>(DAT_1003aacc + param_1) = 1;
    *reinterpret_cast<int*>(iVar1 + 4 + param_1) = 0;
    *reinterpret_cast<int*>(iVar1 + 8 + param_1) = 0;
    *reinterpret_cast<int*>(iVar1 + 0xc + param_1) = 0;
}