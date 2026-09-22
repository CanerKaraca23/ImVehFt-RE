#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int __cdecl CPtoLCID(int param_1)
{
    if (param_1 == 0x3A4)
        return 0x411;

    if (param_1 == 0x3A8)
        return 0x804;

    if (param_1 == 0x3B5)
        return 0x412;

    if (param_1 != 0x3B6)
        return 0;

    return 0x404;
}