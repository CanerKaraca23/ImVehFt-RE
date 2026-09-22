#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int DAT_10039a84;

extern "C" int __cdecl __tolower_l(int _C, _locale_t _Locale);

extern "C" int __cdecl _tolower(int _C)
{
    if (DAT_10039a84 == 0) {
        if (static_cast<unsigned int>(_C) - 0x41U < 0x1AU) {
            return _C + 0x20;
        }
    } else {
        _C = __tolower_l(_C, static_cast<_locale_t>(0x0));
    }

    return _C;
}