#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_10010756(void*);
struct FUN_1001032a_this { void* __thiscall invoke(std::uint8_t param_1); };
struct ExceptionStorage { void __thiscall tidy(); };

void* FUN_1001032a_this::invoke(std::uint8_t param_1)
{
    void* this_ = static_cast<void*>(this);
    *reinterpret_cast<void***>(this_) = reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022228));
    reinterpret_cast<ExceptionStorage*>(this_)->tidy();

    if ((param_1 & 1U) != 0U)
    {
        FUN_10010756(this_);
    }

    return this_;
}
