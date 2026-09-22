#include <cstdint>

extern std::uint32_t DAT_1003c398;

using VoidCallback = void(__cdecl*)();
using ReturnCallback = std::uint32_t(__cdecl*)();

std::uint32_t __stdcall FUN_1000da60()
{
    const std::uintptr_t base =
        static_cast<std::uintptr_t>(DAT_1003c398);

    auto* end_1 = *reinterpret_cast<std::uint32_t**>(base + 0x1C);
    for (auto* current = *reinterpret_cast<std::uint32_t**>(base + 0x18);
         current != end_1;
         ++current)
    {
        const auto callback =
            reinterpret_cast<VoidCallback>(*current);

        if (callback != nullptr)
            callback();
    }

    std::uint32_t result = 0;

    const auto returnCallback =
        *reinterpret_cast<ReturnCallback**>(base + 0x04);

    if (returnCallback != nullptr)
        result = (*returnCallback)();

    auto* end_2 = *reinterpret_cast<std::uint32_t**>(base + 0x2C);
    for (auto* current = *reinterpret_cast<std::uint32_t**>(base + 0x28);
         current != end_2;
         ++current)
    {
        const auto callback =
            reinterpret_cast<VoidCallback>(*current);

        if (callback != nullptr)
            callback();
    }

    return result;
}