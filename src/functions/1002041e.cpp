#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int* __cdecl __errno(void);

extern "C" void __cdecl __set_errno_from_matherr(int param_1)
{
    if (param_1 == 1) {
        int* piVar1 = __errno();
        *piVar1 = 0x21;
    }
    else if ((1 < param_1) && (param_1 < 4)) {
        int* piVar1 = __errno();
        *piVar1 = 0x22;
        return;
    }

    return;
}