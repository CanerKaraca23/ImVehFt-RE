#include <cstdint>

extern "C" std::uint32_t DAT_1003a31c;
extern "C" std::uint32_t DAT_1003a320;
extern "C" std::uint32_t DAT_1003a324;
extern "C" std::uint32_t DAT_1003a328;

extern "C" void __cdecl __initp_misc_winsig(std::uint32_t param_1)
{
    DAT_1003a31c = param_1;
    DAT_1003a320 = param_1;
    DAT_1003a324 = param_1;
    DAT_1003a328 = param_1;
}