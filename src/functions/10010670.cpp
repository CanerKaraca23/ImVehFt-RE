#include <cstdio>

extern "C" void __cdecl __unlock_file(std::FILE* file);

extern "C" void __stdcall FUN_10010670()
{
    __asm
    {
        push esi
        call __unlock_file
        add  esp, 4
    }
}