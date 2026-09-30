#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct FUN_100101a5_this { void* __thiscall invoke(void* param_1); };
struct ExceptionStorage
{
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other);
};

void* FUN_100101a5_this::invoke(void* param_1)
{
    reinterpret_cast<ExceptionStorage*>(this)->copy_construct(
        reinterpret_cast<ExceptionStorage*>(param_1));
    *reinterpret_cast<void***>(this) =
        reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022210));
    return this;
}
