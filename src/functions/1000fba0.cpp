#include <cstdint>

extern std::uint32_t DAT_1003c3d8;

using Callback = void (__cdecl *)(std::uint32_t);
using ReturnCallback = std::uint32_t (__cdecl *)();

std::uint32_t __stdcall FUN_1000fba0(std::uint32_t param_1)
{
    const std::uint32_t iVar2 = DAT_1003c3d8;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(DAT_1003c3d8) + 0x1c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(DAT_1003c3d8) + 0x18);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        const Callback callback = reinterpret_cast<Callback>(*puVar3);
        if (callback != nullptr)
        {
            callback(param_1);
        }
    }

    std::uint32_t local_8;
    const ReturnCallback returnCallback =
        *reinterpret_cast<ReturnCallback*>(
            static_cast<std::uintptr_t>(iVar2) + 0x14);

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
         puVar3 += 1)
    {
        const Callback callback = reinterpret_cast<Callback>(*puVar3);
        if (callback != nullptr)
        {
            callback(param_1);
        }
    }

    return local_8;
}