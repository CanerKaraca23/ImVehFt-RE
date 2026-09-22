#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __unlock_file2(int _Index, void* _File);

extern "C" void __stdcall FUN_10013ebb()
{
    int unaff_ESI;
    __asm mov unaff_ESI, esi
    extern void* DAT_1003c520;

    __unlock_file2(
        unaff_ESI,
        static_cast<void**>(DAT_1003c520)[unaff_ESI]);
}