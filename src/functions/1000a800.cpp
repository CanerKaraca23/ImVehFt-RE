#include <cstdint>

extern std::uint8_t* DAT_1003c394;
extern std::uint8_t DAT_1003aef3;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" void __fastcall FUN_1000a560(std::int32_t param_1);
extern "C" std::int32_t* __stdcall FUN_1000cf80();

extern "C" std::uint32_t __stdcall FUN_1000a800(
    std::uint32_t param_1,
    std::uint32_t param_2)
{
    const std::int32_t iVar4 = FUN_10009360();

    if (DAT_1003c394 == nullptr)
    {
        DAT_1003c394 = &DAT_1003aef3;

        FUN_1000a560(0x14);
        FUN_1000a560(0x15);
        FUN_1000a560(0x19);
        FUN_1000a560(7);
    }

    auto* piVar1 = reinterpret_cast<std::int32_t*>(
        static_cast<std::uintptr_t>(iVar4) + 0x50);

    if (*reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(iVar4) + 0x54) == 0)
    {
        *reinterpret_cast<std::int32_t**>(
            static_cast<std::uintptr_t>(iVar4) + 0x54) = piVar1;

        *piVar1 = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(piVar1));
    }

    std::int32_t* piVar5 = FUN_1000cf80();

    if (piVar5 == nullptr)
    {
        piVar5 = nullptr;
    }
    else if (piVar5[1] == 0)
    {
        piVar5[1] = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(piVar5));
        *piVar5 = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(piVar5));
    }

    const std::int32_t iVar2 = *piVar1;

    auto* puVar3 = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 4);

    *puVar3 = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(piVar5));

    *piVar5 = iVar2;

    piVar5[1] = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(puVar3));

    *reinterpret_cast<std::int32_t**>(
        static_cast<std::uintptr_t>(iVar2) + 4) = piVar5;

    const std::int32_t iVar2AfterLink = *piVar1;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar2AfterLink) + 8) =
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(iVar4) + 0x44);

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar2AfterLink) + 0x0c) = 0x34;

    *reinterpret_cast<std::int32_t*>(
        static_cast<std::uintptr_t>(iVar4) + 0x44) += 0x34;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar2AfterLink) + 0x10) =
        0x32465649;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar2AfterLink) + 0x14) = param_1;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar2AfterLink) + 0x18) = param_2;

    return *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar2AfterLink) + 8);
}