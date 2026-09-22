#include <cstdint>

using VoidCallback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();

extern std::int32_t DAT_1003c3b0;

std::uint32_t __stdcall FUN_1000e720()
{
    const std::uintptr_t context =
        static_cast<std::uintptr_t>(DAT_1003c3b0);

    auto* end_18 = *reinterpret_cast<std::uint32_t**>(context + 0x1c);

    for (auto* current_18 =
             *reinterpret_cast<std::uint32_t**>(context + 0x18);
         current_18 != end_18;
         current_18 += 1)
    {
        if (*current_18 != 0U)
        {
            reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*current_18))();
        }
    }

    const auto callback =
        *reinterpret_cast<ReturnCallback*>(context + 0x14);

    const std::uint32_t result =
        callback == nullptr ? 0U : callback();

    auto* end_28 = *reinterpret_cast<std::uint32_t**>(context + 0x2c);

    for (auto* current_28 =
             *reinterpret_cast<std::uint32_t**>(context + 0x28);
         current_28 != end_28;
         current_28 += 1)
    {
        if (*current_28 != 0U)
        {
            reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*current_28))();
        }
    }

    return result;
}