#include <cstdint>

extern void** std_bad_exception_vftable; // Unresolved linker/compiler vftable symbol.

extern "C" void __fastcall FUN_1001031f(void* param_1);
extern "C" void __cdecl FUN_10010756(void* param_1);

struct FUN_1001cd37_this { void* __thiscall invoke(std::uint8_t param_1); };

void* FUN_1001cd37_this::invoke(std::uint8_t param_1)
{
    void* this_ptr = static_cast<void*>(this);
    *reinterpret_cast<void***>(this_ptr) = std_bad_exception_vftable;

    FUN_1001031f(this_ptr);

    if ((param_1 & 1U) != 0U)
    {
        FUN_10010756(this_ptr);
    }

    return this_ptr;
}