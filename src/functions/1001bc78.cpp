#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
void __cdecl __forcdecpt(char* _Buf)
{
    using ForceDecimalPointLocale = void (__cdecl*)(char*, _locale_t);
    reinterpret_cast<ForceDecimalPointLocale>(0x1001baeb)(
        _Buf, (_locale_t)0x0);
    return;
}