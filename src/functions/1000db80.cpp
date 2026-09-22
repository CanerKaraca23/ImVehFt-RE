#include <cstdint>

std::uint32_t DAT_1003c398;

std::uint32_t __stdcall FUN_1000db80()
{
    const std::uintptr_t state =
        static_cast<std::uintptr_t>(DAT_1003c398);

    auto* first = *reinterpret_cast<std::uint32_t**>(state + 0x18);
    auto* last = *reinterpret_cast<std::uint32_t**>(state + 0x1C);

    for (auto* current = first; current != last; current += 1)
    {
        if (*current != 0U)
        {
            reinterpret_cast<void (*)()>(
                static_cast<std::uintptr_t>(*current))();
        }
    }

    const std::uint32_t result =
        *reinterpret_cast<std::uint32_t*>(state + 0x10) == 0U
            ? 0U
            : reinterpret_cast<std::uint32_t (*)()>(
                  static_cast<std::uintptr_t>(
                      *reinterpret_cast<std::uint32_t*>(state + 0x10)))();

    first = *reinterpret_cast<std::uint32_t**>(state + 0x28);
    last = *reinterpret_cast<std::uint32_t**>(state + 0x2C);

    for (auto* current = first; current != last; current += 1)
    {
        if (*current != 0U)
        {
            reinterpret_cast<void (*)()>(
                static_cast<std::uintptr_t>(*current))();
        }
    }

    return result;
}