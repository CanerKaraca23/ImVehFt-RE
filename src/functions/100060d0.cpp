#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" void __cdecl FUN_10005b60(std::uint32_t);
extern "C" void __cdecl FUN_10005ef0(std::uint32_t);
extern "C" void __cdecl FUN_10005d30(std::uint32_t);
extern "C" char (__cdecl* FUN_006c2130)(...);

void __stdcall FUN_100060d0()
{
    std::int32_t iVar4Resolved;
    std::int32_t unaff_ESI;
    __asm mov unaff_ESI, esi
    const std::int32_t iVar4 = DAT_1003c248;
    const std::int32_t iVar7 = FUN_10009360();
    const auto self = static_cast<std::uintptr_t>(unaff_ESI);
    const std::int32_t iVar2 =
        *reinterpret_cast<std::int32_t*>(self + 0x594);

    if (iVar2 == 5)
        return;
    if (iVar2 == 4)
        return;
    if (iVar2 == 3)
        return;
    if (iVar2 == 10)
        return;

    const bool bVar5 =
        0.0f < *reinterpret_cast<float*>(self + 0x4A0);

    std::uint32_t uVar8;

    if ((*reinterpret_cast<std::uint8_t*>(self + 0x428) & 0x10) == 0)
    {
        if ((!bVar5 ||
             *reinterpret_cast<std::int32_t*>(self + 0x460) == 0) ||
            iVar2 == 0xB)
        {
            if (iVar2 != 0xB)
                return;

            const std::int32_t iVar3 =
                *reinterpret_cast<std::int32_t*>(self + 0x4C8);

            if (iVar3 == 0)
                return;
            if (*reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(iVar3) + 0x460) == 0)
                return;
            if (*reinterpret_cast<float*>(
                    static_cast<std::uintptr_t>(iVar3) + 0x4A0) <= 0.0f)
                return;
        }

        uVar8 = 2;
    }
    else
    {
        bool active = false;

        if (bVar5)
        {
            if (*reinterpret_cast<std::int32_t*>(self + 0x460) != 0)
            {
                if (iVar2 != 0xB)
                    active = true;
            }
        }

        if (!active)
        {
            if (iVar2 == 0xB)
            {
                const std::int32_t iVar3 =
                    *reinterpret_cast<std::int32_t*>(self + 0x4C8);

                if (iVar3 != 0)
                {
                    if (*reinterpret_cast<std::int32_t*>(
                            static_cast<std::uintptr_t>(iVar3) + 0x460) != 0)
                    {
                        if (0.0f < *reinterpret_cast<float*>(
                                static_cast<std::uintptr_t>(iVar3) + 0x4A0))
                            active = true;
                    }
                }
            }
        }

        if (active)
            uVar8 = 3;
        else
            uVar8 = 1;
    }

    const std::uint8_t bVar1 =
        *reinterpret_cast<std::uint8_t*>(self + 0x584);

    if ((bVar1 & 4) != 0)
    {
        if ((bVar1 & 8) != 0)
        {
            FUN_10005b60(uVar8);
            return;
        }

        goto LAB_100062FD;
    }

    if ((bVar1 & 8) != 0)
    {
        FUN_10005ef0(uVar8);
        return;
    }

    if ((*reinterpret_cast<float*>(self + 0x4A0) <= 0.0f) ||
        (*reinterpret_cast<std::int32_t*>(self + 0x460) == 0) ||
        iVar2 == 0xB)
    {
        if (iVar2 != 0xB)
            return;

        const std::int32_t iVar3 =
            *reinterpret_cast<std::int32_t*>(self + 0x4C8);

        if (iVar3 == 0)
            return;
        if (*reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(iVar3) + 0x460) == 0)
            return;
        if (*reinterpret_cast<float*>(
                static_cast<std::uintptr_t>(iVar3) + 0x4A0) <= 0.0f)
            return;
    }

    iVar4Resolved =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(
                        *reinterpret_cast<std::int32_t*>(
                            static_cast<std::uintptr_t>(iVar7) + 0x48) +
                        ((unaff_ESI - *_DAT_00b74494) / 0xA18) * 4)) +
                    0x28) +
                iVar4);

    if (*reinterpret_cast<char*>(
            static_cast<std::uintptr_t>(iVar4Resolved) + 0x325) == '\0')
        return;

    if (*reinterpret_cast<char*>(
            static_cast<std::uintptr_t>(iVar4Resolved) + 0x324) == '\0')
    {
        switch (iVar2)
        {
        case 0:
        case 1:
        case 2:
        case 0xB:
            break;

        case 6:
        case 9:
            goto switchD_1000628b_caseD_9;

        default:
            return;
        }
    }
    else
    {
        switch (iVar2)
        {
        case 0:
        case 1:
        case 0xB:
            if (FUN_006c2130(3) == '\0')
            {
                if (FUN_006c2130() != '\0')
                {
                    FUN_10005ef0(2);
                    return;
                }

                FUN_10005b60(2);
                return;
            }
            break;

        case 6:
            FUN_10005b60(2);
            [[fallthrough]];

        case 2:
            break;

        case 9:
            goto switchD_1000628b_caseD_9;

        default:
            return;
        }
    }

    if (FUN_006c2130(2) != '\0')
        return;

switchD_1000628b_caseD_9:
    uVar8 = 2;

LAB_100062FD:
    FUN_10005d30(uVar8);
}