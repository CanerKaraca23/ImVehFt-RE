#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __unlock_file(FILE*);
extern "C" void __stdcall FUN_10010a11(void)
{
    FILE* unaff_EDI;
    __asm mov unaff_EDI, edi
    __unlock_file(unaff_EDI);
}