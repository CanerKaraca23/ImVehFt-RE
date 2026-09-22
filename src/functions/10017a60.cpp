#include <bit>
#include <cstdint>

extern "C" long long __stdcall __allmul(
    std::uint32_t param_1,
    std::int32_t param_2,
    std::uint32_t param_3,
    std::int32_t param_4)
{
    const std::uint64_t product =
        static_cast<std::uint64_t>(param_1) *
        static_cast<std::uint64_t>(param_3);

    if (param_4 == 0 && param_2 == 0)
    {
        return std::bit_cast<long long>(product);
    }

    std::uint32_t high = static_cast<std::uint32_t>(product >> 0x20);
    high += static_cast<std::uint32_t>(param_2) * param_3;
    high += param_1 * static_cast<std::uint32_t>(param_4);

    const std::uint64_t result =
        (static_cast<std::uint64_t>(high) << 0x20) |
        static_cast<std::uint32_t>(product);

    return std::bit_cast<long long>(result);
}