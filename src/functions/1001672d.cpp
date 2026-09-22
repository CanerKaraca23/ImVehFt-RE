#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __stdcall __unlock_fhandle(int);

extern "C" void __stdcall FUN_1001672d()
{
    int unaff_EBX;
    __asm mov unaff_EBX, ebx


    __unlock_fhandle(unaff_EBX);
}