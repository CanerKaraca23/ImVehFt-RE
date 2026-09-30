#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __forcdecpt_l(char* buffer, _locale_t locale);
extern "C" void __cdecl __forcdecpt(char* _Buf)
{
    __forcdecpt_l(_Buf, (_locale_t)0x0);
    return;
}
