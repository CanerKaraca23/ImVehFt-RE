#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
// Ghidra 12.1.3 shows a frameless SEH handler that reads the exception
// specification from the enclosing handler frame at [EBP+8].
extern "C" void __cdecl __getptd(void);
extern "C" __declspec(noreturn) void __stdcall __CxxThrowException_8(void*, void*);

extern "C" __declspec(naked) void __stdcall Catch_All_1001d057(void)
{
    __asm {
        call __getptd
        mov ecx, dword ptr [ebp + 8]
        push 0
        push 0
        mov dword ptr [eax + 94h], ecx
        call __CxxThrowException_8
    }
}