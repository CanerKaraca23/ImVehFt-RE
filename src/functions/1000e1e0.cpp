#include <cstdint>

using Callback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();

extern std::uint32_t DAT_1003c3a8;

std::uint32_t __stdcall FUN_1000e1e0()
{
    const std::uint32_t state = DAT_1003c3a8;

    std::uint32_t* end = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(state) + 0x1cU);

    for (std::uint32_t* current = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(state) + 0x18U);
         current != end;
         current += 1)
    {
        if (*current != 0U)
        {
            reinterpret_cast<Callback>(*current)();
        }
    }

    std::uint32_t result;

    const ReturnCallback callback = *reinterpret_cast<ReturnCallback*>(
        static_cast<std::uintptr_t>(state) + 0x04U);

    if (callback == nullptr)
    {
        result = 0U;
    }
    else
    {
        result = callback();
    }

    end = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(state) + 0x2cU);

    for (std::uint32_t* current = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(state) + 0x28U);
         current != end;
         current += 1)
    {
        if (*current != 0U)
        {
            reinterpret_cast<Callback>(*current)();
        }
    }

    return result;
}