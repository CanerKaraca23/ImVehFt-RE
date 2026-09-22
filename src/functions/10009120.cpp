#include <cstdint>

using HMODULE = void*;
using BOOL = std::int32_t;
using DWORD = std::uint32_t;

extern "C" HMODULE __stdcall GetModuleHandleA(const char*);
extern "C" BOOL __stdcall VirtualProtect(void*, DWORD, DWORD, DWORD*);

extern "C" std::uint32_t __stdcall FUN_10009120()
{
    volatile auto& DAT_1003c3f4 =
        *reinterpret_cast<volatile std::uint16_t*>(0x1003c3f4u);
    volatile auto& DAT_1003c3f6 =
        *reinterpret_cast<volatile std::uint16_t*>(0x1003c3f6u);
    volatile auto& DAT_1003c3f8 =
        *reinterpret_cast<volatile std::uint8_t*>(0x1003c3f8u);
    volatile auto& DAT_1003c3f9 =
        *reinterpret_cast<volatile std::uint8_t*>(0x1003c3f9u);

    DAT_1003c3f6 = 0;
    DAT_1003c3f8 = 0;
    DAT_1003c3f9 = 0;
    DAT_1003c3f4 = 0;

    DWORD local_14;
    std::uint8_t local_10;
    DWORD local_c;
    std::int8_t local_5;

    HMODULE pHVar1 = GetModuleHandleA(nullptr);

    const std::uint32_t moduleBase =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(pHVar1));

    const std::uint32_t uVar3 =
        (moduleBase >> 8u) & 0x00ffffffu;

    const std::int32_t imageOffset =
        *reinterpret_cast<const volatile std::int32_t*>(
            static_cast<std::uintptr_t>(moduleBase + 0x3cu));

    const std::uint32_t imageAddress =
        moduleBase + 0x28u +
        static_cast<std::uint32_t>(imageOffset);

    const std::int32_t imageValue =
        *reinterpret_cast<const volatile std::int32_t*>(
            static_cast<std::uintptr_t>(imageAddress));

    const std::uint32_t uVar5 =
        moduleBase + static_cast<std::uint32_t>(imageValue);

    if (uVar5 < 0x82457du) {
        if (uVar5 == 0x82457cu)
            goto LAB_100091ed;

        if (uVar5 < 0x666ba1u) {
            if (uVar5 == 0x666ba0u)
                goto LAB_1000933d;

            if (uVar5 == 0x5c1e70u) {
                DAT_1003c3f4 = 0x33;
                DAT_1003c3f6 = 1;
                DAT_1003c3f9 = 0;
                return (uVar3 << 8u) | 1u;
            }

            if (uVar5 == 0x5c2130u) {
                DAT_1003c3f9 = 0;
                DAT_1003c3f4 = 0x33;
                DAT_1003c3f6 = 0x101;
                return (uVar3 << 8u) | 1u;
            }

            if (uVar5 == 0x5c6fd0u)
                goto LAB_10009184;
        } else {
            if (uVar5 == 0x667bf0u) {
                DAT_1003c3f4 = 0x56;
                DAT_1003c3f6 = 1;
                DAT_1003c3f9 = 0;
                return (uVar3 << 8u) | 1u;
            }

            if (uVar5 == 0x667c40u) {
                DAT_1003c3f4 = 0x56;
                DAT_1003c3f6 = 0x101;
                DAT_1003c3f9 = 0;
                return (uVar3 << 8u) | 1u;
            }

            if (uVar5 == 0x824570u)
                goto LAB_100091ed;
        }
    } else if (uVar5 < 0x85ec4bu) {
        if (uVar5 == 0x85ec4au)
            goto LAB_10009323;

        if (uVar5 == 0x8245bcu) {
            DAT_1003c3f4 = 0x4553;
            DAT_1003c3f6 = 1;
            DAT_1003c3f9 = 0;
            return (uVar3 << 8u) | 1u;
        }

        if (uVar5 == 0x8252fcu) {
            DAT_1003c3f4 = 0x5553;
            DAT_1003c3f6 = 0x101;
            DAT_1003c3f9 = 0;
            return (uVar3 << 8u) | 1u;
        }

        if (uVar5 == 0x82533cu) {
            DAT_1003c3f4 = 0x4553;
            DAT_1003c3f6 = 0x101;
            DAT_1003c3f9 = 0;
            return (uVar3 << 8u) | 1u;
        }
    } else {
        if (uVar5 == 0x9912edu)
            goto LAB_10009184;

        if (uVar5 == 0xa402edu)
            goto LAB_1000933d;

        if (uVar5 == 0xd3c3dbu)
            goto LAB_10009323;
    }

    return uVar3 << 8u;

LAB_10009184:
    DAT_1003c3f9 = 1;
    DAT_1003c3f4 = 0x33;
    DAT_1003c3f6 = 0x101;
    return (uVar3 << 8u) | 1u;

LAB_1000933d:
    DAT_1003c3f4 = 0x56;
    DAT_1003c3f6 = 0x101;
    DAT_1003c3f9 = 1;
    return (uVar3 << 8u) | 1u;

LAB_10009323:
    DAT_1003c3f4 = 0x53;
    DAT_1003c3f6 = 3;
    DAT_1003c3f9 = 1;
    return (uVar3 << 8u) | 1u;

LAB_100091ed:
    DAT_1003c3f4 = 0x5553;
    DAT_1003c3f6 = 1;
    DAT_1003c3f9 = 0;

    BOOL BVar2 = VirtualProtect(
        reinterpret_cast<void*>(0x00406a20u),
        1,
        0x40,
        &local_14);

    local_10 = static_cast<std::uint8_t>(BVar2 != 0);
    local_5 = *reinterpret_cast<volatile std::int8_t*>(0x00406a20u);

    if (local_10 != 0) {
        local_c = local_14;
        BVar2 = VirtualProtect(
            reinterpret_cast<void*>(0x00406a20u),
            1,
            local_14,
            &local_c);
    }

    DAT_1003c3f8 = static_cast<std::uint8_t>(
        (local_5 != static_cast<std::int8_t>(-0x17)) - 1u & 0x48u);

    return (((static_cast<std::uint32_t>(BVar2) >> 8u) << 8u) | 1u);
}