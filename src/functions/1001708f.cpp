#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" unsigned int DAT_10029d30;

extern "C" unsigned int __cdecl __set_abort_behavior(
    unsigned int _Flags,
    unsigned int _Mask)
{
    unsigned int uVar1 = DAT_10029d30;

    DAT_10029d30 =
        (~_Mask & DAT_10029d30) |
        (_Flags & _Mask);

    return uVar1;
}