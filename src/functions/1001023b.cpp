#include <cstdint>

extern void** std_exception_vftable;

struct FUN_1001023b_this { void __thiscall invoke(const std::uint32_t* param_1); };

void FUN_1001023b_this::invoke(const std::uint32_t* param_1)
{
    void* this_ptr = static_cast<void*>(this);
    *reinterpret_cast<void***>(this_ptr) = std_exception_vftable;
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 4) = *param_1;
    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 8) = 0;
}