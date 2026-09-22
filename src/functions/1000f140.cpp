#include <cstdint>

extern std::int32_t DAT_1003c3e4;

using Callback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();

std::uint32_t __stdcall FUN_1000f140()
{
    const std::int32_t iVar2 = DAT_1003c3e4;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(DAT_1003c3e4) + 0x1c
    );

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(DAT_1003c3e4) + 0x18);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<Callback>(*puVar3)();
        }
    }

    std::uint32_t local_8;

    const auto callback = *reinterpret_cast<ReturnCallback*>(
        static_cast<std::uintptr_t>(iVar2) + 0x08
    );

    if (callback == nullptr)
    {
        local_8 = 0U;
    }
    else
    {
        local_8 = callback();
    }

    puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x2c
    );

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x28);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<Callback>(*puVar3)();
        }
    }

    return local_8;
}