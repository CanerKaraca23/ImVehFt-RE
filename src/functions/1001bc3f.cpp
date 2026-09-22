#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __fassign_l(int flag, char* argument, char* number, _locale_t param_4);

void __cdecl __fassign(int flag, char* argument, char* number)
{
    __fassign_l(flag, argument, number, (_locale_t)0x0);
    return;
}