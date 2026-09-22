#include <cstdint>


#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int DAT_10039a84;
extern "C" const std::uint8_t* PTR_DAT_10029bf8;

extern "C" int __cdecl __isxdigit_l(int _C, _locale_t _Locale);

extern "C" int __cdecl _isxdigit(int _C)
{
    if (DAT_10039a84 == 0) {
        return *reinterpret_cast<const std::uint16_t*>(
                   PTR_DAT_10029bf8 + _C * 2) &
               0x80;
    }

    return __isxdigit_l(_C, static_cast<_locale_t>(nullptr));
}