#include <cstdint>

extern std::int32_t DAT_1003c390;

extern std::uint32_t __stdcall FUN_100096e0(
    std::int32_t param_1,
    std::int32_t param_2
);

using Callback = void (__cdecl*)();

std::uint32_t __stdcall FUN_1000d9a0()
{
    const std::int32_t iVar2 = DAT_1003c390;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x48
    );

    for (auto* puVar4 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x44);
         puVar4 != puVar1;
         puVar4 += 1)
    {
        if (*puVar4 != 0U)
        {
            reinterpret_cast<Callback>(*puVar4)();
        }
    }

    const std::uint32_t uVar3 = FUN_100096e0(iVar2 + 4, 0x0E);

    puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x58
    );

    for (auto* puVar4 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x54);
         puVar4 != puVar1;
         puVar4 += 1)
    {
        if (*puVar4 != 0U)
        {
            reinterpret_cast<Callback>(*puVar4)();
        }
    }

    return uVar3;
}