#include <cstdint>

extern std::uint32_t DAT_1003c39c;

using Callback = void(__cdecl*)();
using ReturnCallback = std::uint32_t(__cdecl*)();

std::uint32_t __stdcall FUN_1000ddc0()
{
    const std::uintptr_t base = DAT_1003c39c;

    auto* end = *reinterpret_cast<Callback**>(base + 0x1c);

    for (auto* current = *reinterpret_cast<Callback**>(base + 0x18);
         current != end;
         ++current)
    {
        if (*current != nullptr)
        {
            (*current)();
        }
    }

    std::uint32_t result = 0;

    const ReturnCallback callback =
        *reinterpret_cast<ReturnCallback*>(base + 0x14);

    if (callback != nullptr)
    {
        result = callback();
    }

    end = *reinterpret_cast<Callback**>(base + 0x2c);

    for (auto* current = *reinterpret_cast<Callback**>(base + 0x28);
         current != end;
         ++current)
    {
        if (*current != nullptr)
        {
            (*current)();
        }
    }

    return result;
}