#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#include <cstdarg>
#include <cstdio>
#pragma warning(disable:4996)
#include <cstdarg>
#include <cstdio>


extern "C" int __cdecl FUN_10014206(char*, std::size_t, char*, va_list);

extern "C" int __cdecl fputs(
    const char* string,
    FILE* stream);

extern char DAT_1003a6c4;
extern FILE* DAT_1003a6c0;

extern "C" void __cdecl FUN_100014c0(char* param_1, ...)
{
    char local_204[512];

    if (DAT_1003a6c4 != '\0')
    {
        va_list arguments;
        va_start(arguments, param_1);

        FUN_10014206(
            local_204,
            0x200,
            param_1,
            arguments);

        va_end(arguments);

        fputs(local_204, DAT_1003a6c0);
        fputs("\n", DAT_1003a6c0);
    }
}