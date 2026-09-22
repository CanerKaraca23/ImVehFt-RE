#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __stdcall FUN_10009580(void);

extern "C" __declspec(naked) void __stdcall thunk_FUN_10009580(void)
{
    __asm {
        jmp FUN_10009580
    }
}
