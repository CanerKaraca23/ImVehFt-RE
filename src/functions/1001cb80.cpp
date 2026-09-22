#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void FUN_1001cb9e(void);

extern "C" __declspec(naked) void __fastcall FUN_1001cb80(void* )
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        and esp, 0fffffff0h
        fstp qword ptr [esp]
        movq xmm0, qword ptr [esp]
        call FUN_1001cb9e
        leave
        ret
    }
}
