#include <cstdint>

using Callback = void(__cdecl*)();
using ReturnCallback = std::uint32_t(__cdecl*)();

extern std::int32_t DAT_1003c3b4;

std::uint32_t __stdcall FUN_1000e900()
{
    const std::int32_t iVar2 = DAT_1003c3b4;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x1c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x18);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            const Callback callback =
                reinterpret_cast<Callback>(*puVar3);
            callback();
        }
    }

    std::uint32_t local_8;

    if (*reinterpret_cast<ReturnCallback*>(
            static_cast<std::uintptr_t>(iVar2) + 0x14) == nullptr)
    {
        local_8 = 0U;
    }
    else
    {
        const ReturnCallback callback =
            *reinterpret_cast<ReturnCallback*>(
                static_cast<std::uintptr_t>(iVar2) + 0x14);
        local_8 = callback();
    }

    puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x2c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x28);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            const Callback callback =
                reinterpret_cast<Callback>(*puVar3);
            callback();
        }
    }

    return local_8;
}