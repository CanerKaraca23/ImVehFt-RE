#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl doexit(int code, int quick, int return_status);

extern "C" void __cdecl __cexit(void)
{
    doexit(0, 0, 1);
}