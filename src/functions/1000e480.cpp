#include <cstdint>

extern std::uintptr_t DAT_1003c3ac;

using VoidCallback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();

std::uint32_t __stdcall FUN_1000e480()
{
    const std::uintptr_t state = DAT_1003c3ac;

    std::uint32_t* puVar1 =
        *reinterpret_cast<std::uint32_t**>(state + 0x1C);

    for (std::uint32_t* puVar3 =
             *reinterpret_cast<std::uint32_t**>(state + 0x18);
         puVar3 != puVar1;
         ++puVar3)
    {
        if (*puVar3 != 0U)
        {
            const VoidCallback callback =
                reinterpret_cast<VoidCallback>(
                    static_cast<std::uintptr_t>(*puVar3));
            callback();
        }
    }

    std::uint32_t local_8;
    const std::uint32_t callbackAddress =
        *reinterpret_cast<std::uint32_t*>(state + 0x0C);

    if (callbackAddress == 0U)
    {
        local_8 = 0U;
    }
    else
    {
        const ReturnCallback callback =
            reinterpret_cast<ReturnCallback>(
                static_cast<std::uintptr_t>(callbackAddress));
        local_8 = callback();
    }

    puVar1 = *reinterpret_cast<std::uint32_t**>(state + 0x2C);

    for (std::uint32_t* puVar3 =
             *reinterpret_cast<std::uint32_t**>(state + 0x28);
         puVar3 != puVar1;
         ++puVar3)
    {
        if (*puVar3 != 0U)
        {
            const VoidCallback callback =
                reinterpret_cast<VoidCallback>(
                    static_cast<std::uintptr_t>(*puVar3));
            callback();
        }
    }

    return local_8;
}