#include "imvehft_image_aliases.hpp"
#include <cstdint>

struct FUN_1001023b_this
{
    void __thiscall invoke(
        const std::uint32_t* param_1,
        std::uint32_t unused_stack_param);
};

void FUN_1001023b_this::invoke(
    const std::uint32_t* param_1,
    std::uint32_t unused_stack_param)
{
    (void)unused_stack_param;
    void* this_ptr = static_cast<void*>(this);
    *reinterpret_cast<void***>(this_ptr) = reinterpret_cast<void**>(
        static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022228));
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 4) = *param_1;
    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 8) = 0;
}
