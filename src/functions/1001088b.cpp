#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __unlock_file(FILE*);
void __stdcall FUN_1001088b(void)
{
    FILE* unaff_ESI;
    __asm mov unaff_ESI, esi
    __unlock_file(unaff_ESI);
}