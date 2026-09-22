#include <cstddef>

#include <corecrt.h>
#include <cstdint>
using uint = std::uint32_t;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" std::size_t __cdecl _wcslen(wchar_t* _Str)
{
    wchar_t wVar1;
    wchar_t* pwVar2;

    pwVar2 = _Str;
    do {
        wVar1 = *pwVar2;
        pwVar2 = pwVar2 + 1;
    } while (wVar1 != L'\0');

    return ((static_cast<int>(reinterpret_cast<std::uintptr_t>(pwVar2)) -
             static_cast<int>(reinterpret_cast<std::uintptr_t>(_Str))) >>
            1) -
           1;
}