#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct FUN_100101f2_this { void* __thiscall invoke(void* param_1); };
struct ExceptionStorage { ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other); };

void* FUN_100101f2_this::invoke(void* param_1)
{
    reinterpret_cast<ExceptionStorage*>(this)->copy_construct(
        reinterpret_cast<ExceptionStorage*>(param_1));
    *reinterpret_cast<void***>(this) =
        reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_1002221C));
    return this;
}
