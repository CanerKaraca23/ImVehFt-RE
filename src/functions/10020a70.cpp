#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __stdcall FUN_100013e0(void);

extern "C" __declspec(naked) void __stdcall thunk_FUN_100013e0(void)
{
    __asm {
        jmp FUN_100013e0
    }
}
