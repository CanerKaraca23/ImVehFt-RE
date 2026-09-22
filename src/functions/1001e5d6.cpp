#include <cstdint>
using INTRNCVT_STATUS = int;
enum : int { INTRNCVT_OK = 0, INTRNCVT_OVERFLOW = 1, INTRNCVT_UNDERFLOW = 2 };
struct _LDBL12 { std::uint8_t ld12[12]; };
struct _CRT_DOUBLE { double x; };
extern std::uint32_t DAT_10029490;
extern std::uint32_t DAT_100395d8;
extern std::uint32_t DAT_100395dc;
extern std::uint32_t DAT_100395e0;
extern std::uint32_t DAT_100395e4;
extern std::uint32_t DAT_100395e8;
extern std::uint32_t DAT_100395ec;

extern "C" INTRNCVT_STATUS __cdecl FUN_1001e5d6(
    _LDBL12* _Ifp,
    _CRT_DOUBLE* _D)
{
    std::uint16_t uVar1;
    std::uint32_t uVar2;
    std::uint32_t uVar3;
    std::uint8_t bVar4;
    bool bVar5;
    int iVar6;
    INTRNCVT_STATUS IVar7;
    int iVar8;
    std::uint8_t bVar9;
    std::uint32_t* puVar10;
    std::uint32_t* puVar11;
    std::uint32_t uVar12;
    std::uint32_t uVar13;
    int iVar14;
    int iVar15;
    int iVar16;
    bool bVar17;
    std::uint32_t local_2c;
    std::uint32_t local_24;
    std::uint32_t local_14[4];

    local_14[3] =
        DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_14[3]));

    uVar1 = *reinterpret_cast<std::uint16_t*>(_Ifp->ld12 + 10);
    uVar2 = *reinterpret_cast<std::uint32_t*>(_Ifp->ld12 + 6);
    local_14[0] = uVar2;
    uVar3 = *reinterpret_cast<std::uint32_t*>(_Ifp->ld12 + 2);
    uVar13 = uVar1 & 0x7fffU;
    iVar14 = uVar13 - 0x3fffU;
    iVar6 =
        static_cast<int>(
            static_cast<std::uint32_t>(
                *reinterpret_cast<std::uint16_t*>(_Ifp->ld12)) << 0x10);
    local_14[1] = uVar3;
    local_14[2] = static_cast<std::uint32_t>(iVar6);

    bVar4 = static_cast<std::uint8_t>(DAT_100395e4);

    if (iVar14 == -0x3fff)
    {
        iVar15 = 0;
        iVar6 = 0;

        do
        {
            if (local_14[iVar6] != 0)
            {
                local_14[0] = 0;
                local_14[1] = 0;
                IVar7 = INTRNCVT_UNDERFLOW;
                goto LAB_1001eada;
            }

            iVar6 = iVar6 + 1;
        }
        while (iVar6 < 3);

        IVar7 = INTRNCVT_OK;
    }
    else
    {
        bVar5 = false;
        iVar16 = DAT_100395e0 - 1;
        iVar15 =
            static_cast<int>(
                DAT_100395e0 +
                ((DAT_100395e0 >> 0x1f) & 0x1fU)) >>
            5;

        puVar11 = local_14 + iVar15;
        bVar9 = static_cast<std::uint8_t>(
            0x1fU - (static_cast<std::uint8_t>(DAT_100395e0) & 0x1fU));

        if ((*puVar11 & (1U << (bVar9 & 0x1fU))) != 0)
        {
            uVar12 =
                local_14[iVar15] &
                ~(~std::uint32_t{0} << (bVar9 & 0x1fU));

            iVar8 = iVar15;

            while (true)
            {
                if (uVar12 != 0)
                {
                    iVar8 =
                        static_cast<int>(
                            iVar16 +
                            ((iVar16 >> 0x1f) & 0x1fU)) >>
                        5;

                    uVar12 =
                        1U << (0x1fU -
                               (static_cast<std::uint8_t>(iVar16) & 0x1fU));

                    puVar10 = local_14 + iVar8;
                    local_24 = *puVar10 + uVar12;

                    if (local_24 < *puVar10)
                        goto LAB_1001e71a;

                    bVar17 = local_24 < uVar12;

                    do
                    {
                        bVar5 = false;

                        if (!bVar17)
                            goto LAB_1001e721;

LAB_1001e71a:
                        do
                        {
                            bVar5 = true;

LAB_1001e721:
                            iVar8 = iVar8 - 1;
                            *puVar10 = local_24;

                            if ((iVar8 < 0) || (!bVar5))
                                goto LAB_1001e72f;

                            puVar10 = local_14 + iVar8;
                            local_24 = *puVar10 + 1;
                        }
                        while (local_24 < *puVar10);

                        bVar17 = local_24 == 0;
                    }
                    while (true);
                }

                iVar8 = iVar8 + 1;

                if (2 < iVar8)
                    break;

                uVar12 = local_14[iVar8];
            }
        }

LAB_1001e72f:
        *puVar11 &= ~std::uint32_t{0} << (bVar9 & 0x1fU);
        iVar15 = iVar15 + 1;

        if (iVar15 < 3)
        {
            puVar11 = local_14 + iVar15;

            for (iVar16 = 3 - iVar15;
                 iVar16 != 0;
                 iVar16 = iVar16 - 1)
            {
                *puVar11 = 0;
                puVar11 = puVar11 + 1;
            }
        }

        iVar15 = iVar14;

        if (bVar5)
            iVar15 = uVar13 - 0x3ffeU;

        if (static_cast<std::uint32_t>(iVar15) <
            DAT_100395dc - DAT_100395e0)
        {
            local_14[0] = 0;
            local_14[1] = 0;
        }
        else
        {
            if (DAT_100395dc < static_cast<std::uint32_t>(iVar15))
            {
                if (static_cast<std::uint32_t>(iVar15) < DAT_100395d8)
                {
                    iVar15 = iVar15 + DAT_100395ec;
                    local_14[0] = local_14[0] & 0x7fffffffU;

                    iVar6 =
                        static_cast<int>(
                            DAT_100395e4 +
                            ((DAT_100395e4 >> 0x1f) & 0x1fU)) >>
                        5;

                    bVar9 = bVar4 & 0x1fU;
                    local_2c = 0;
                    local_24 = 0;

                    do
                    {
                        uVar2 = local_14[local_24];
                        local_14[local_24] = uVar2 >> bVar9 | local_2c;
                        local_2c =
                            (uVar2 & ~(~std::uint32_t{0} << bVar9)) <<
                            ((0x20U - bVar9) & 0x1fU);
                        local_24 = local_24 + 1;
                    }
                    while (static_cast<int>(local_24) < 3);

                    iVar14 = 2;
                    puVar11 = local_14 + (2 - iVar6);

                    do
                    {
                        if (iVar14 < iVar6)
                            local_14[iVar14] = 0;
                        else
                            local_14[iVar14] = *puVar11;

                        puVar11 = puVar11 - 1;
                        iVar14 = iVar14 - 1;
                    }
                    while (-1 < iVar14);

                    IVar7 = INTRNCVT_OK;
                }
                else
                {
                    local_14[1] = 0;
                    local_14[2] = 0;
                    local_14[0] = 0x80000000U;

                    iVar6 =
                        static_cast<int>(
                            DAT_100395e4 +
                            ((DAT_100395e4 >> 0x1f) & 0x1fU)) >>
                        5;

                    bVar9 = bVar4 & 0x1fU;
                    local_2c = 0;
                    local_24 = 0;

                    do
                    {
                        uVar2 = local_14[local_24];
                        local_14[local_24] = uVar2 >> bVar9 | local_2c;
                        local_2c =
                            (uVar2 & ~(~std::uint32_t{0} << bVar9)) <<
                            ((0x20U - bVar9) & 0x1fU);
                        local_24 = local_24 + 1;
                    }
                    while (static_cast<int>(local_24) < 3);

                    iVar14 = 2;
                    puVar11 = local_14 + (2 - iVar6);

                    do
                    {
                        if (iVar14 < iVar6)
                            local_14[iVar14] = 0;
                        else
                            local_14[iVar14] = *puVar11;

                        puVar11 = puVar11 - 1;
                        iVar14 = iVar14 - 1;
                    }
                    while (-1 < iVar14);

                    iVar15 = DAT_100395ec + DAT_100395d8;
                    IVar7 = INTRNCVT_OVERFLOW;
                }

                goto LAB_1001eada;
            }

            iVar14 = DAT_100395dc - iVar14;
            local_14[0] = uVar2;
            local_14[1] = uVar3;

            iVar15 =
                static_cast<int>(
                    iVar14 +
                    ((iVar14 >> 0x1f) & 0x1fU)) >>
                5;

            bVar9 = static_cast<std::uint8_t>(iVar14) & 0x1fU;
            local_2c = 0;
            local_24 = 0;

            do
            {
                uVar2 = local_14[local_24];
                local_14[local_24] = uVar2 >> bVar9 | local_2c;
                local_2c =
                    (uVar2 & ~(~std::uint32_t{0} << bVar9)) <<
                    ((0x20U - bVar9) & 0x1fU);
                local_24 = local_24 + 1;
            }
            while (static_cast<int>(local_24) < 3);

            iVar6 = 2;
            puVar11 = local_14 + (2 - iVar15);

            do
            {
                if (iVar6 < iVar15)
                    local_14[iVar6] = 0;
                else
                    local_14[iVar6] = *puVar11;

                puVar11 = puVar11 - 1;
                iVar6 = iVar6 - 1;
            }
            while (-1 < iVar6);

            iVar14 = DAT_100395e0 - 1;
            iVar6 =
                static_cast<int>(
                    DAT_100395e0 +
                    ((DAT_100395e0 >> 0x1f) & 0x1fU)) >>
                5;

            bVar9 = static_cast<std::uint8_t>(
                0x1fU - (static_cast<std::uint8_t>(DAT_100395e0) & 0x1fU));

            puVar11 = local_14 + iVar6;

            if ((*puVar11 & (1U << (bVar9 & 0x1fU))) != 0)
            {
                uVar2 =
                    local_14[iVar6] &
                    ~(~std::uint32_t{0} << (bVar9 & 0x1fU));

                iVar15 = iVar6;

                while (uVar2 == 0)
                {
                    iVar15 = iVar15 + 1;

                    if (2 < iVar15)
                        goto LAB_1001e8ce;

                    uVar2 = local_14[iVar15];
                }

                iVar15 =
                    static_cast<int>(
                        iVar14 +
                        ((iVar14 >> 0x1f) & 0x1fU)) >>
                    5;

                bVar5 = false;
                uVar12 =
                    1U << (0x1fU -
                           (static_cast<std::uint8_t>(iVar14) & 0x1fU));

                uVar13 = local_14[iVar15];
                uVar2 = uVar13 + uVar12;

                if ((uVar2 < uVar13) || (uVar2 < uVar12))
                    bVar5 = true;

                local_14[iVar15] = uVar2;

                while ((iVar15 = iVar15 - 1, -1 < iVar15 && bVar5))
                {
                    uVar13 = local_14[iVar15];
                    uVar2 = uVar13 + 1;
                    bVar5 = false;

                    if ((uVar2 < uVar13) || (uVar2 == 0))
                        bVar5 = true;

                    local_14[iVar15] = uVar2;
                }
            }

LAB_1001e8ce:
            *puVar11 &= ~std::uint32_t{0} << (bVar9 & 0x1fU);
            iVar6 = iVar6 + 1;

            if (iVar6 < 3)
            {
                puVar11 = local_14 + iVar6;

                for (iVar14 = 3 - iVar6;
                     iVar14 != 0;
                     iVar14 = iVar14 - 1)
                {
                    *puVar11 = 0;
                    puVar11 = puVar11 + 1;
                }
            }

            iVar6 =
                static_cast<int>(
                    DAT_100395e4 + 1 +
                    (((DAT_100395e4 + 1) >> 0x1f) & 0x1fU)) >>
                5;

            bVar9 = static_cast<std::uint8_t>(bVar4 + 1) & 0x1fU;
            local_2c = 0;
            local_24 = 0;

            do
            {
                uVar2 = local_14[local_24];
                local_14[local_24] = uVar2 >> bVar9 | local_2c;
                local_2c =
                    (uVar2 & ~(~std::uint32_t{0} << bVar9)) <<
                    ((0x20U - bVar9) & 0x1fU);
                local_24 = local_24 + 1;
            }
            while (static_cast<int>(local_24) < 3);

            iVar14 = 2;
            puVar11 = local_14 + (2 - iVar6);

            do
            {
                if (iVar14 < iVar6)
                    local_14[iVar14] = 0;
                else
                    local_14[iVar14] = *puVar11;

                puVar11 = puVar11 - 1;
                iVar14 = iVar14 - 1;
            }
            while (-1 < iVar14);
        }

        iVar15 = 0;
        IVar7 = INTRNCVT_UNDERFLOW;
    }

LAB_1001eada:
    local_14[0] =
        (iVar15 << (0x1f - bVar4 & 0x1f)) |
        ((0U - static_cast<std::uint32_t>((uVar1 & 0x8000U) != 0)) &
         0x80000000U) |
        local_14[0];

    if (DAT_100395e8 == 0x40)
    {
        *reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(&_D->x) + 4) = local_14[0];
        *reinterpret_cast<std::uint32_t*>(&_D->x) = local_14[1];
    }
    else if (DAT_100395e8 == 0x20)
    {
        *reinterpret_cast<std::uint32_t*>(&_D->x) = local_14[0];
    }

    __security_check_cookie(local_14[3]);
    return IVar7;
}