#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __fastcall FUN_1001031f(void*);

extern "C" __declspec(naked) void __stdcall FUN_10021267(void)
{
    __asm {
        // MSVC's inline assembler rejects an absolute-memory/immediate MOV;
        // emit the exact C7 05 absolute-address encoding shown by Ghidra.
        _emit 0C7h
        _emit 005h
        _emit 0E0h
        _emit 099h
        _emit 003h
        _emit 010h
        _emit 050h
        _emit 022h
        _emit 002h
        _emit 010h
        mov ecx, 100399E0h
        jmp FUN_1001031f
    }
}