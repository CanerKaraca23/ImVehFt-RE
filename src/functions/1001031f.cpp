#include "imvehft_image_aliases.hpp"
#include <cstdint>
struct ExceptionStorage { void __thiscall tidy(); };

extern "C" void __fastcall FUN_1001031f(void* param_1)
{
    *reinterpret_cast<void***>(param_1) =
        reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022228));

    reinterpret_cast<ExceptionStorage*>(param_1)->tidy();
}
