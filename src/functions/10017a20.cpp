#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>

extern "C" int __cdecl __isleadbyte_l(int _C, _locale_t _Locale);

extern "C" int __cdecl _isleadbyte(int _C)
{
    int iVar1;

    iVar1 = __isleadbyte_l(_C, static_cast<_locale_t>(nullptr));
    return iVar1;
}