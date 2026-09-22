#include <cstddef>
#include <cstdint>

using Callback = std::uint32_t(__cdecl*)(std::uint32_t, std::uint32_t);

extern char* (__cdecl* PTR_0072FB30)(std::uint32_t);
extern void (__cdecl* PTR_007F0DC0)(
    std::uint32_t,
    Callback,
    std::uint32_t
);
extern void (__cdecl* PTR_007F1200)(
    std::uint32_t,
    std::uintptr_t,
    std::uint32_t
);
extern int __cdecl strncmp(const char*, const char*, std::size_t);

extern "C" std::uint32_t __cdecl FUN_10008cb0(
    std::uint32_t param_1,
    std::uint32_t param_2
)
{
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