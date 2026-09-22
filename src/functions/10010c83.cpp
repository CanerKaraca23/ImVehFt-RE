#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern int DAT_10039a84;
extern "C" int __cdecl _strnicmp_l(char*, char*, std::size_t, _locale_t);
extern "C" int __cdecl ___ascii_strnicmp(char*, char*, std::size_t);

int __cdecl _strnicmp(char* _Str1, char* _Str2, std::size_t _MaxCount)
{
    int* piVar1;
    int iVar2;

    if (DAT_10039a84 != 0)
    {
        iVar2 = _strnicmp_l(_Str1, _Str2, _MaxCount, (_locale_t)0x0);
        return iVar2;
    }

    if (((_Str1 != (char*)0x0) && (_Str2 != (char*)0x0)) &&
        (_MaxCount < 0x80000000))
    {
        iVar2 = ___ascii_strnicmp(_Str1, _Str2, _MaxCount);
        return iVar2;
    }

    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_1001189f();
    return 0x7fffffff;
}