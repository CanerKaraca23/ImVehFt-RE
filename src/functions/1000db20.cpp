#include <cstdint>

extern "C" std::uint32_t DAT_1003c398;

using Callback = std::uint32_t (*)();

std::uint32_t __stdcall FUN_1000db20()
{
    const std::uintptr_t base =
        static_cast<std::uintptr_t>(DAT_1003c398);

    auto* puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(
            *reinterpret_cast<std::uint32_t*>(base + 0x1C)));

    for (auto* puVar3 = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(
                 *reinterpret_cast<std::uint32_t*>(base + 0x18)));
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            Callback callback = reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*puVar3));
            callback();
        }
    }

    std::uint32_t local_8;
    const std::uint32_t callbackAddress =
        *reinterpret_cast<std::uint32_t*>(base + 0x0C);

    if (callbackAddress == 0U)
    {
        local_8 = 0U;
    }
    else
    {
        Callback callback = reinterpret_cast<Callback>(
            static_cast<std::uintptr_t>(callbackAddress));
        local_8 = callback();
    }

    puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(
            *reinterpret_cast<std::uint32_t*>(base + 0x2C)));

    for (auto* puVar3 = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(
                 *reinterpret_cast<std::uint32_t*>(base + 0x28)));
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            Callback callback = reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*puVar3));
            callback();
        }
    }

    return local_8;
}