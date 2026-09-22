#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl _free(void*);

extern "C" void __cdecl FUN_10010756(void* param_1)
{
    _free(param_1);
}