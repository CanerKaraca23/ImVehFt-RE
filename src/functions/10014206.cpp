#include <cstddef>
#include <cstdarg>

extern "C" int __cdecl FUN_1001415a(char*, std::size_t, const char*, _locale_t, va_list);


extern "C" int __cdecl FUN_10014206(
    char* _Dest,
    std::size_t _Count,
    const char* _Format,
    va_list _Args)
{
    int iVar1;

    iVar1 = FUN_1001415a(
        _Dest,
        _Count,
        _Format,
        (_locale_t)0x0,
        _Args);

    return iVar1;
}