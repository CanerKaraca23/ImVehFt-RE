#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using undefined4 = std::uint32_t;
using undefined = unsigned char;
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined8 = std::uint64_t;
struct localeinfo_struct;

errno_t __cdecl __cftoe(
    double* _Value,
    char* _Buf,
    size_t _SizeInBytes,
    int _Dec,
    int _Caps)
{
    using CftoeLocale = errno_t (__cdecl*)(
        undefined4*, char*, size_t, int, int, localeinfo_struct*);
    return reinterpret_cast<CftoeLocale>(0x1001bdff)(
        reinterpret_cast<undefined4*>(_Value),
        _Buf,
        _SizeInBytes,
        _Dec,
        _Caps,
        reinterpret_cast<localeinfo_struct*>(0x0));
}