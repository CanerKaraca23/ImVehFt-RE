#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __stdcall __cfltcvt_init();
extern "C" void __cdecl __setdefaultprecision();

extern "C" void __cdecl __fpmath(int param_1)
{
    __cfltcvt_init();

    if (param_1 != 0)
    {
        __setdefaultprecision();
    }

    __asm
    {
        fnclex
    }
}
