#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using _onexit_t = void (__cdecl*)();

extern "C" void __stdcall FUN_10012b9c();
extern _onexit_t __cdecl __onexit_nolock(_onexit_t);
extern "C" void __stdcall FUN_10010523();

_onexit_t __cdecl __onexit(_onexit_t _Func)
{
    FUN_10012b9c();

    _onexit_t p_Var1 = __onexit_nolock(_Func);

    FUN_10010523();

    return p_Var1;
}