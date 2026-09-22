#include <cstdint>

extern std::uint32_t DAT_1003c3c4;

// Indirect callback calling conventions are not established by the available evidence.
using VoidCallback = void (*)();
using ReturnCallback = std::uint32_t (*)();

std::uint32_t __stdcall FUN_1000f020()
{
    const std::uint32_t iVar2 = DAT_1003c3c4;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x1c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x18);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<VoidCallback>(*puVar3)();
        }
    }

    std::uint32_t local_8;

    const auto callback = *reinterpret_cast<ReturnCallback*>(
        static_cast<std::uintptr_t>(iVar2) + 0x10);

    if (callback == nullptr)
    {
        local_8 = 0U;
    }
    else
    {
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
            reinterpret_cast<VoidCallback>(*puVar3)();
        }
    }

    return local_8;
}