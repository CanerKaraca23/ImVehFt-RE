#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_10010756(void*);
extern "C" void __fastcall FUN_1001031f(void*);
struct FUN_1001020f_this { void* __thiscall invoke(unsigned char param_1); };

void* FUN_1001020f_this::invoke(unsigned char param_1)
{
    void* this_ = static_cast<void*>(this);
    FUN_1001031f(this_);

    if ((param_1 & 1) != 0)
    {
        FUN_10010756(this_);
    }

    return this_;
}