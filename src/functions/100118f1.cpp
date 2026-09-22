#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int* __cdecl __errno(void)
{
    struct _tiddata
    {
        int _terrno;
    };

    using _ptiddata = _tiddata*;

    extern _ptiddata __cdecl __getptd_noexit(void);
    extern int DAT_100291c8;

    _ptiddata p_Var1 = __getptd_noexit();

    if (p_Var1 == nullptr)
    {
        return &DAT_100291c8;
    }

    return &p_Var1->_terrno;
}