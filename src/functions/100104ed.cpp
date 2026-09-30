#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using _onexit_t = void (__cdecl*)();

extern "C" void __stdcall FUN_10012b9c();
extern void* __cdecl __onexit_nolock(void*);
extern "C" void __stdcall FUN_10010523();

_onexit_t __cdecl __onexit(_onexit_t _Func)
{
    FUN_10012b9c();

    auto* const result = __onexit_nolock(reinterpret_cast<void*>(_Func));

    FUN_10010523();

    return reinterpret_cast<_onexit_t>(result);
}
