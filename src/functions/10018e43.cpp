#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int __cdecl __mbsnbcmp_l(
    unsigned char* _Str1,
    unsigned char* _Str2,
    size_t _MaxCount,
    _locale_t _Locale);

extern "C" int __cdecl __mbsnbcmp(
    unsigned char* _Str1,
    unsigned char* _Str2,
    size_t _MaxCount)
{
    int iVar1 = __mbsnbcmp_l(_Str1, _Str2, _MaxCount, (_locale_t)0x0);
    return iVar1;
}