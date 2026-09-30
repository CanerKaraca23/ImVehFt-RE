#include <exception>
#include "imvehft_image_aliases.hpp"

struct ExceptionStorage
{
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other);
};

struct FUN_100014a0_this
{
    void* __thiscall FUN_100014a0(std::exception* source);
};

void* FUN_100014a0_this::FUN_100014a0(std::exception* source)
{
    reinterpret_cast<ExceptionStorage*>(this)->copy_construct(
        reinterpret_cast<ExceptionStorage*>(source));
    *reinterpret_cast<void***>(this) = reinterpret_cast<void**>(
        static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022250));
    return this;
}
