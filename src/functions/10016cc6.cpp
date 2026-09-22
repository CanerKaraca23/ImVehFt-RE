#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall __RTC_Initialize(void)
{
    __asm
    {
        mov eax, 10028180h
        cmp eax, 10028180h
        ret
    }
}