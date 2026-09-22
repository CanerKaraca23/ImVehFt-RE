#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl doexit(int code, int quick, int return_status);

extern "C" __declspec(noreturn) void __cdecl __exit(int _Code)
{
    doexit(_Code, 1, 0);
}