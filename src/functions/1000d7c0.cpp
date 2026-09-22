#include <cstdint>

extern std::uint32_t DAT_1003c390;

extern std::uint32_t __stdcall FUN_100096e0(
    std::int32_t param_1,
    std::int32_t param_2
);

// Indirect callback calling convention is unresolved by the supplied evidence.
using Callback = void (*)();

std::uint32_t __stdcall FUN_1000d7c0()
{
    const std::int32_t iVar2 =
        static_cast<std::int32_t>(DAT_1003c390);

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x48u);

    for (auto* puVar4 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x44u);
         puVar4 != puVar1;
         puVar4 += 1)
    {
        if (*puVar4 != 0u)
        {
            reinterpret_cast<Callback>(*puVar4)();
        }
    }

    const std::uint32_t uVar3 = FUN_100096e0(iVar2 + 4, 9);

    puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x58u);

    for (auto* puVar4 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x54u);
         puVar4 != puVar1;
         puVar4 += 1)
    {
        if (*puVar4 != 0u)
        {
            reinterpret_cast<Callback>(*puVar4)();
        }
    }

    return uVar3;
}