#include "imvehft_image_aliases.hpp"
#include <cstdint>

extern "C" void __fastcall FUN_1001031f(void* param_1);
extern "C" void __cdecl FUN_10010756(void* param_1);

struct FUN_1001cd37_this { void* __thiscall invoke(std::uint8_t param_1); };

void* FUN_1001cd37_this::invoke(std::uint8_t param_1)
{
    void* this_ptr = static_cast<void*>(this);
    *reinterpret_cast<void***>(this_ptr) = reinterpret_cast<void**>(
        static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_100261E8));

    FUN_1001031f(this_ptr);

    if ((param_1 & 1U) != 0U)
    {
        FUN_10010756(this_ptr);
    }

    return this_ptr;
}
