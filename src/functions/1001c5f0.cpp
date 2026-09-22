#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
// Ghidra 12.1.3 export: 0x1001c5f0..0x1001c607 (24 bytes).
// The incoming x87 value is rounded to binary64, then passed in XMM0;
// ECX (the fastcall object/this pointer) is intentionally preserved.
extern "C" void __cdecl FUN_1001c60e(void);

extern "C" __declspec(naked) void __fastcall FUN_1001c5f0(void*)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        and esp, 0fffffff0h
        fstp qword ptr [esp]
        movq xmm0, qword ptr [esp]
        call FUN_1001c60e
        leave
        ret
    }
}