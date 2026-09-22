#include <cstdint>

extern std::uint32_t DAT_1003c398;

using VoidCallback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();

std::uint32_t __stdcall FUN_1000dac0()
{
    const std::uint32_t instance = DAT_1003c398;

    auto* end = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(instance) + 0x1C);

    for (auto* current = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(instance) + 0x18);
         current != end;
         ++current)
    {
        if (*current != 0U)
        {
            (*reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*current)))();
        }
    }

    std::uint32_t result;

    auto callback = *reinterpret_cast<ReturnCallback*>(
        static_cast<std::uintptr_t>(instance) + 0x08);

    if (callback == nullptr)
    {
        result = 0U;
    }
    else
    {
        result = callback();
    }

    end = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(instance) + 0x2C);

    for (auto* current = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(instance) + 0x28);
         current != end;
         ++current)
    {
        if (*current != 0U)
        {
            (*reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*current)))();
        }
    }

    return result;
}