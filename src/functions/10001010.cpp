#include "imvehft_image_aliases.hpp"
#include <exception>

extern "C" void __fastcall FUN_1001031f(std::exception* param_1);
extern "C" void __cdecl FUN_10010756(void* param_1);

struct FUN_10001010_this
{
    void* __thiscall FUN_10001010(unsigned char param_1);
};

void* FUN_10001010_this::FUN_10001010(unsigned char param_1)
{
    *reinterpret_cast<void***>(this) = reinterpret_cast<void**>(
        static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022250));
    FUN_1001031f(reinterpret_cast<std::exception*>(this));
    if ((param_1 & 1u) != 0u)
    {
        FUN_10010756(this);
    }
    return this;
}
