#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

extern "C" int DAT_100399fc;

extern "C" int __cdecl __set_error_mode(int _Mode)
{
    int iVar1;
    int* piVar2;

    if (-1 < _Mode) {
        if (_Mode < 3) {
            iVar1 = DAT_100399fc;
            DAT_100399fc = _Mode;
            return iVar1;
        }

        if (_Mode == 3) {
            return DAT_100399fc;
        }
    }

    piVar2 = __errno();
    *piVar2 = 0x16;
    FUN_1001189f();

    return -1;
}