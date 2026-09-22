#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
[[noreturn]] void __cdecl terminate(void)
{
    using terminate_handler = void (__cdecl*)();

    struct _tiddata
    {
        terminate_handler _terminate;
    };

    using getptd_function = _tiddata* (__cdecl*)();
    using abort_function = void (__cdecl*)();
    using seh_prolog_function = void (__cdecl*)();

    reinterpret_cast<seh_prolog_function>(0x10012e20)();

    _tiddata* p_Var1 =
        reinterpret_cast<getptd_function>(0x10014df0)();

    if (p_Var1->_terminate != nullptr) {
        (*p_Var1->_terminate)();
    }

    reinterpret_cast<abort_function>(0x1001705c)();
}