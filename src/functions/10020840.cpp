#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __stdcall FUN_10010170(void);

extern "C" __declspec(naked) void __stdcall Unwind_10020840(void)
{
    __asm {
        lea ecx, dword ptr [ebp - 10h]
        jmp FUN_10010170
    }
}
