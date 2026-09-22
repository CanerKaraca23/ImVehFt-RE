#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __stdcall FUN_10012ba5();

extern "C" __declspec(naked) void __stdcall FUN_10010523(void)
{
    __asm {
        call FUN_10012ba5
        ret
    }
}
