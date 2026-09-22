#include <cstdio>

extern "C" void __cdecl __unlock_file(FILE*);

extern "C" __declspec(naked) void __stdcall FUN_1001072a()
{
    __asm {
        push dword ptr [ebp + 8]
        call __unlock_file
        pop ecx
        ret
    }
}