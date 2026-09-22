#include <exception>

extern void* PTR_std_bad_alloc_vftable;
extern "C" void __fastcall FUN_1001031f(std::exception* param_1);
extern "C" void __cdecl FUN_10010756(void* param_1);

struct FUN_10001010_this
{
    void* __thiscall FUN_10001010(unsigned char param_1);
};

void* FUN_10001010_this::FUN_10001010(unsigned char param_1)
{
    *reinterpret_cast<void***>(this) =
        reinterpret_cast<void**>(PTR_std_bad_alloc_vftable);
    FUN_1001031f(reinterpret_cast<std::exception*>(this));
    if ((param_1 & 1u) != 0u)
    {
        FUN_10010756(this);
    }
    return this;
}