#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __cropzeros_l(char* _Buf, _locale_t _Locale);

void __cdecl __cropzeros(char* _Buf)
{
    __cropzeros_l(_Buf, (_locale_t)0x0);
    return;
}