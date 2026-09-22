#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __fastcall FUN_1000a560(int)
{
    __asm {
        jmp dword ptr [ecx * 4 + 01000a618h]
    }
}
