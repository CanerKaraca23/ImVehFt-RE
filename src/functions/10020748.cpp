#include <bit>
#include <cstdint>

extern "C" long double __cdecl __set_exp(std::uint64_t param_1, short param_2)
{
    const std::uint16_t high_word = static_cast<std::uint16_t>(
        (param_2 + 0x3FE) * 0x10 |
        (static_cast<std::uint16_t>(param_1 >> 48) & 0x800FU));

    const std::uint64_t bits =
        (static_cast<std::uint64_t>(high_word) << 48) |
        (param_1 & 0x0000FFFFFFFFFFFFULL);

    const double local_c = std::bit_cast<double>(bits);
    return static_cast<long double>(local_c);
}