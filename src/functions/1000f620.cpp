#include <cstdint>

extern std::uint32_t DAT_1003c3d0;

using Callback = void(__cdecl*)(std::uint32_t);
using ReturnCallback = std::uint32_t(__cdecl*)();

std::uint32_t __stdcall FUN_1000f620(std::uint32_t param_1)
{
    const std::uint32_t iVar2 = DAT_1003c3d0;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x1c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x18);
         puVar3 != puVar1;
         ++puVar3)
    {
        if (*puVar3 != 0)
        {
            reinterpret_cast<Callback>(*puVar3)(param_1);
        }
    }

    std::uint32_t local_8;

    auto returnCallback = *reinterpret_cast<ReturnCallback*>(
        static_cast<std::uintptr_t>(iVar2) + 0x10);

    if (returnCallback == nullptr)
    {
        local_8 = 0;
    }
    else
    {
        local_8 = returnCallback();
    }

    puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x2c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x28);
         puVar3 != puVar1;
         ++puVar3)
    {
        if (*puVar3 != 0)
        {
            reinterpret_cast<Callback>(*puVar3)(param_1);
        }
    }

    return local_8;
}