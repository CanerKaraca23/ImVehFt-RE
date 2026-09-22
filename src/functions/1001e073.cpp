#include <cstdint>

extern "C" int __cdecl _ValidateRead(
    void* param_1,
    std::uint32_t )
{
    return static_cast<std::uint32_t>(param_1 != nullptr);
}