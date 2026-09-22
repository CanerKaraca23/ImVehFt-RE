#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
char* __fastcall FUN_10010258(int param_1)
{
    char* result = *reinterpret_cast<char**>(param_1 + 4);

    if (result == nullptr)
    {
        result = const_cast<char*>("Unknown exception");
    }

    return result;
}