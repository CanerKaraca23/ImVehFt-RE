#include <cstdint>

extern "C" void __cdecl __local_unwind4(
    std::uint32_t* param_1,
    int param_2,
    std::uint32_t );

extern "C" void __fastcall _EH4_LocalUnwind(
    int param_1,
    std::uint32_t param_2,
    std::uint32_t ,
    std::uint32_t* param_4)
{
    __local_unwind4(param_4, param_1, param_2);
}
