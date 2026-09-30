#include "imvehft_image_aliases.hpp"
#include <exception>
struct ExceptionStorage { ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other); };

struct FUN_1001d906_this { void* __thiscall invoke(std::exception* param_1); };

void* FUN_1001d906_this::invoke(std::exception* param_1)
{
    void* self = static_cast<void*>(this);
    reinterpret_cast<ExceptionStorage*>(self)->copy_construct(
        reinterpret_cast<ExceptionStorage*>(param_1));

    *reinterpret_cast<void***>(self) =
        reinterpret_cast<void**>(IVF_IMAGE_ADDRESS_100261E8);

    return self;
}
