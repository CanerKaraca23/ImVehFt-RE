#include <cstdint>

extern "C" std::uint32_t __cdecl FUN_1001ca18(
    std::uint32_t ,
    std::uint32_t param_2)
{
    if ((param_2 & 0x7FF00000U) != 0x7FF00000U)
    {
        return param_2 & 0x7FF00000U;
    }

    return param_2;
}