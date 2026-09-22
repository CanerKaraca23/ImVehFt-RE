#include <cstdint>

extern "C" std::uint32_t DAT_1003c3b0;

using VoidCallback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();

std::uint32_t __stdcall FUN_1000e6c0()
{
    const std::uint32_t iVar2 = DAT_1003c3b0;

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x1c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x18);
         puVar3 != puVar1;
         ++puVar3)
    {
        const auto void_callback = reinterpret_cast<VoidCallback>(*puVar3);
        if (void_callback != nullptr)
            void_callback();
    }

    std::uint32_t local_8;

    const auto return_callback = *reinterpret_cast<ReturnCallback*>(
        static_cast<std::uintptr_t>(iVar2) + 0x10);

    if (return_callback == nullptr)
        local_8 = 0;
    else
        local_8 = return_callback();

    puVar1 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 0x2c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
             static_cast<std::uintptr_t>(iVar2) + 0x28);
         puVar3 != puVar1;
         ++puVar3)
    {
        const auto void_callback = reinterpret_cast<VoidCallback>(*puVar3);
        if (void_callback != nullptr)
            void_callback();
    }

    return local_8;
}