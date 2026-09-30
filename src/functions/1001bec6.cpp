#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using undefined = unsigned char;
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined8 = std::uint64_t;
extern "C" errno_t __cdecl __cftoe_l(
    std::uint32_t* value,
    char* buffer,
    std::size_t size_in_bytes,
    int precision,
    int caps,
    _locale_t locale);

extern "C" errno_t __cdecl __cftoe(
    double* _Value,
    char* _Buf,
    size_t _SizeInBytes,
    int _Dec,
    int _Caps)
{
    return __cftoe_l(
        reinterpret_cast<std::uint32_t*>(_Value),
        _Buf,
        _SizeInBytes,
        _Dec,
        _Caps,
        nullptr);
}
