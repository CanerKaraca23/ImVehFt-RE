#include <cstdint>

extern std::int32_t DAT_1003c390;

extern std::uint32_t __stdcall FUN_100096e0(
    std::int32_t param_1,
    std::int32_t param_2
);

// Calling convention of the indirect callbacks is unresolved by the evidence.
using Callback = void (*)();

std::uint32_t __stdcall FUN_1000d760()
{
    const std::int32_t base = DAT_1003c390;

    auto* end = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(base) + 0x48
    );

    for (auto* current = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(base) + 0x44);
         current != end;
         ++current)
    {
        if (*current != 0U)
        {
            reinterpret_cast<Callback>(*current)();
        }
    }

    const std::uint32_t result = FUN_100096e0(base + 4, 8);

    end = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(base) + 0x58
    );

    for (auto* current = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(base) + 0x54);
         current != end;
         ++current)
    {
        if (*current != 0U)
        {
            reinterpret_cast<Callback>(*current)();
        }
    }

    return result;
}