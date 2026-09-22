#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern char* DAT_1003c25c;
extern int _DAT_1003c260;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_100013e0(void)
{
    int* piVar1;
    int* piVar2;

    piVar2 = *reinterpret_cast<int**>(DAT_1003c25c);
    *reinterpret_cast<int**>(DAT_1003c25c) =
        reinterpret_cast<int*>(DAT_1003c25c);
    reinterpret_cast<int*>(DAT_1003c25c)[1] =
        static_cast<int>(reinterpret_cast<std::uintptr_t>(DAT_1003c25c));
    _DAT_1003c260 = 0;

    if (piVar2 != reinterpret_cast<int*>(DAT_1003c25c))
    {
        do
        {
            piVar1 = reinterpret_cast<int*>(*piVar2);
            FUN_10010756(piVar2);
            piVar2 = piVar1;
        }
        while (piVar1 != reinterpret_cast<int*>(DAT_1003c25c));
    }

    FUN_10010756(DAT_1003c25c);
}