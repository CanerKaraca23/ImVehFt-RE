#include <cstdint>

extern volatile std::uintptr_t DAT_1003c3d0;

using Callback = void (__cdecl*)(std::uint32_t);
using ReturnCallback = std::uint32_t (__cdecl*)();

std::uint32_t __stdcall FUN_1000f4a0(std::uint32_t param_1)
{
    const std::uintptr_t iVar2 = DAT_1003c3d0;
    auto* puVar1 =
        *reinterpret_cast<std::uint32_t**>(iVar2 + 0x1c);

    for (auto* puVar3 =
             *reinterpret_cast<std::uint32_t**>(iVar2 + 0x18);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        Callback callback =
            reinterpret_cast<Callback>(*puVar3);

        if (callback != nullptr)
        {
            callback(param_1);
        }
    }

    std::uint32_t local_8;
    ReturnCallback returnCallback =
        *reinterpret_cast<ReturnCallback*>(iVar2 + 0x04);

    if (returnCallback == nullptr)
    {
        local_8 = 0U;
    }
    else
    {
        local_8 = returnCallback();
    }

    puVar1 =
        *reinterpret_cast<std::uint32_t**>(iVar2 + 0x2c);

    for (auto* puVar3 =
             *reinterpret_cast<std::uint32_t**>(iVar2 + 0x28);
         puVar3 != puVar1;
         puVar3 += 1)
    {
        Callback callback =
            reinterpret_cast<Callback>(*puVar3);

        if (callback != nullptr)
        {
            callback(param_1);
        }
    }

    return local_8;
}