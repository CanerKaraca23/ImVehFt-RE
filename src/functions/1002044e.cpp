#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int __stdcall __statfp(void)
{
    short in_FPUStatusWord;

    __asm
    {
        fstsw in_FPUStatusWord
    }

    return static_cast<int>(in_FPUStatusWord);
}