#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using _onexit_t = void (__cdecl*)();

extern _onexit_t __cdecl __onexit(_onexit_t);

int __cdecl _atexit(_onexit_t param_1)
{
    _onexit_t p_Var1 = __onexit(param_1);
    return (p_Var1 != nullptr) - 1;
}