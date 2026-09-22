#include <cstdint>

extern "C" void __cdecl __raise_exc_ex(
    std::uint32_t*, std::uint32_t*, std::uint32_t, int,
    std::uint32_t*, std::uint32_t*, int);

extern "C" void __cdecl __raise_exc(
    std::uint32_t* param_1,
    std::uint32_t* param_2,
    std::uint32_t param_3,
    int param_4,
    std::uint32_t* param_5,
    std::uint32_t* param_6)
{
    __raise_exc_ex(
        param_1,
        param_2,
        param_3,
        param_4,
        param_5,
        param_6,
        0);
}