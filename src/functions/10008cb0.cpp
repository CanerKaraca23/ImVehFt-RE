#include <cstddef>
#include <cstdint>

using Callback = std::uint32_t(__cdecl*)(std::uint32_t, std::uint32_t);

using PTR_0072FB30_t = char*(__cdecl*)(std::uint32_t);
using PTR_007F0DC0_t = void(__cdecl*)(
    std::uint32_t,
    Callback,
    std::uint32_t);
using PTR_007F1200_t = void(__cdecl*)(
    std::uint32_t,
    std::uintptr_t,
    std::uint32_t);
extern "C" int __cdecl strncmp(const char*, const char*, std::size_t);

extern "C" std::uint32_t __cdecl FUN_10008cb0(
    std::uint32_t param_1,
    std::uint32_t param_2
)
{
    const auto PTR_0072FB30 = reinterpret_cast<PTR_0072FB30_t>(
        static_cast<std::uintptr_t>(0x0072fb30));
    const auto PTR_007F0DC0 = reinterpret_cast<PTR_007F0DC0_t>(
        static_cast<std::uintptr_t>(0x007f0dc0));
    const auto PTR_007F1200 = reinterpret_cast<PTR_007F1200_t>(
        static_cast<std::uintptr_t>(0x007f1200));

    if (strncmp(PTR_0072FB30(param_1), "extra", 5) != 0)
    {
        if (strncmp(PTR_0072FB30(param_1), "movspoiler", 10) != 0)
        {
            PTR_007F0DC0(param_1, FUN_10008cb0, param_2);
            PTR_007F1200(param_1, 0x4C7700, param_2);
        }
    }

    return param_1;
}
