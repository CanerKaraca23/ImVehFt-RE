#include <cstdint>
using INTRNCVT_STATUS = int;
enum : int { INTRNCVT_OK = 0, INTRNCVT_OVERFLOW = 1, INTRNCVT_UNDERFLOW = 2 };
struct _LDBL12 { std::uint8_t ld12[12]; };
struct _CRT_DOUBLE { double x; };
extern std::uint32_t DAT_10029490;
extern std::uint32_t DAT_100395c0;
extern std::uint32_t DAT_100395c4;
extern std::uint32_t DAT_100395c8;
extern std::uint32_t DAT_100395cc;
extern std::uint32_t DAT_100395d0;
extern std::uint32_t DAT_100395d4;

extern "C" INTRNCVT_STATUS __cdecl FUN_1001e085(_LDBL12* _Ifp, _CRT_DOUBLE* _D)
{
    std::uint16_t uVar1;
    std::uint32_t uVar2, uVar3, uVar12, uVar13;
    std::uint8_t bVar4, bVar9;
    bool bVar5, bVar17;
    INTRNCVT_STATUS IVar7;
    std::int32_t iVar6, iVar8, iVar14, iVar15, iVar16;
    std::uint32_t* puVar10;
    std::uint32_t* puVar11;
    std::uint32_t local_2c, local_24, local_14[4];

    local_14[3] = DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_14[3]));

    uVar1 = *reinterpret_cast<const std::uint16_t*>(_Ifp->ld12 + 10);
    uVar2 = *reinterpret_cast<const std::uint32_t*>(_Ifp->ld12 + 6);
    local_14[0] = uVar2;
    uVar3 = *reinterpret_cast<const std::uint32_t*>(_Ifp->ld12 + 2);
    uVar13 = uVar1 & 0x7fffU;
    iVar14 = static_cast<std::int32_t>(uVar13 - 0x3fffU);
    iVar6 = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(
            *reinterpret_cast<const std::uint16_t*>(_Ifp->ld12)) << 0x10);
    local_14[1] = uVar3;
    local_14[2] = static_cast<std::uint32_t>(iVar6);
    bVar4 = static_cast<std::uint8_t>(DAT_100395cc);

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
                goto LAB_1001e589;
            }
            iVar6 = iVar6 + 1;
        }
        while (iVar6 < 3);
        IVar7 = INTRNCVT_OK;
    }
    else
    {
        bVar5 = false;
        iVar16 = static_cast<std::int32_t>(DAT_100395c8 - 1U);
        iVar15 = static_cast<std::int32_t>(
            (DAT_100395c8 +
             ((DAT_100395c8 >> 0x1f) & 0x1fU)) >> 5);
        puVar11 = local_14 + iVar15;
        bVar9 = static_cast<std::uint8_t>(
            0x1fU - (static_cast<std::uint8_t>(DAT_100395c8) & 0x1fU));

        if ((*puVar11 & (1U << (bVar9 & 0x1fU))) != 0)
        {
            uVar12 = local_14[iVar15] &
                ~(static_cast<std::uint32_t>(-1) << (bVar9 & 0x1fU));
            iVar8 = iVar15;

            while (true)
            {
                if (uVar12 != 0)
                {
                    iVar8 = static_cast<std::int32_t>(
                        (iVar16 +
                         ((iVar16 >> 0x1f) & 0x1fU)) >> 5);
                    uVar12 = 1U << (
                        (0x1fU -
                         (static_cast<std::uint8_t>(iVar16) & 0x1fU)) &
                        0x1fU);
                    puVar10 = local_14 + iVar8;
                    local_24 = *puVar10 + uVar12;

                    if (local_24 < *puVar10)
                        goto LAB_1001e1c9;

                    bVar17 = local_24 < uVar12;
                    do
                    {
                        bVar5 = false;
                        if (!bVar17)
                            goto LAB_1001e1d0;
                    LAB_1001e1c9:
                        do
                        {
                            bVar5 = true;
                        LAB_1001e1d0:
                            iVar8 = iVar8 - 1;
                            *puVar10 = local_24;
                            if ((iVar8 < 0) || (!bVar5))
                                goto LAB_1001e1de;
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

    LAB_1001e1de:
        *puVar11 = *puVar11 &
            (static_cast<std::uint32_t>(-1) << (bVar9 & 0x1fU));
        iVar15 = iVar15 + 1;

        if (iVar15 < 3)
        {
            puVar11 = local_14 + iVar15;
            for (iVar16 = 3 - iVar15; iVar16 != 0; iVar16 = iVar16 - 1)
            {
                *puVar11 = 0;
                puVar11 = puVar11 + 1;
            }
        }

        iVar15 = iVar14;
        if (bVar5)
            iVar15 = static_cast<std::int32_t>(uVar13 - 0x3ffeU);

        if (static_cast<std::uint32_t>(iVar15) <
            DAT_100395c4 - DAT_100395c8)
        {
            local_14[0] = 0;
            local_14[1] = 0;
        }
        else
        {
            if (DAT_100395c4 < static_cast<std::uint32_t>(iVar15))
            {
                if (static_cast<std::uint32_t>(iVar15) < DAT_100395c0)
                {
                    iVar15 = iVar15 +
                        static_cast<std::int32_t>(DAT_100395d4);
                    local_14[0] = local_14[0] & 0x7fffffffU;
                    iVar6 = static_cast<std::int32_t>(
                        (DAT_100395cc +
                         ((DAT_100395cc >> 0x1f) & 0x1fU)) >> 5);
                    bVar9 = bVar4 & 0x1fU;
                    local_2c = 0;
                    local_24 = 0;

                    do
                    {
                        uVar2 = local_14[local_24];
                        local_14[local_24] = uVar2 >> bVar9 | local_2c;
                        local_2c = (uVar2 &
                            ~(static_cast<std::uint32_t>(-1) << bVar9))
                            << ((0x20U - bVar9) & 0x1fU);
                        local_24 = local_24 + 1;
                    }
                    while (static_cast<std::int32_t>(local_24) < 3);

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
                    iVar6 = static_cast<std::int32_t>(
                        (DAT_100395cc +
                         ((DAT_100395cc >> 0x1f) & 0x1fU)) >> 5);
                    bVar9 = bVar4 & 0x1fU;
                    local_2c = 0;
                    local_24 = 0;

                    do
                    {
                        uVar2 = local_14[local_24];
                        local_14[local_24] = uVar2 >> bVar9 | local_2c;
                        local_2c = (uVar2 &
                            ~(static_cast<std::uint32_t>(-1) << bVar9))
                            << ((0x20U - bVar9) & 0x1fU);
                        local_24 = local_24 + 1;
                    }
                    while (static_cast<std::int32_t>(local_24) < 3);

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

                    iVar15 = static_cast<std::int32_t>(
                        DAT_100395d4 + DAT_100395c0);
                    IVar7 = INTRNCVT_OVERFLOW;
                }
                goto LAB_1001e589;
            }

            iVar14 = static_cast<std::int32_t>(
                DAT_100395c4 - static_cast<std::uint32_t>(iVar14));
            local_14[0] = uVar2;
            local_14[1] = uVar3;
            iVar15 = static_cast<std::int32_t>(
                (iVar14 +
                 ((iVar14 >> 0x1f) & 0x1fU)) >> 5);
            bVar9 = static_cast<std::uint8_t>(iVar14) & 0x1fU;
            local_2c = 0;
            local_24 = 0;

            do
            {
                uVar2 = local_14[local_24];
                local_14[local_24] = uVar2 >> bVar9 | local_2c;
                local_2c = (uVar2 &
                    ~(static_cast<std::uint32_t>(-1) << bVar9))
                    << ((0x20U - bVar9) & 0x1fU);
                local_24 = local_24 + 1;
            }
            while (static_cast<std::int32_t>(local_24) < 3);

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

            iVar14 = static_cast<std::int32_t>(DAT_100395c8 - 1U);
            iVar6 = static_cast<std::int32_t>(
                (DAT_100395c8 +
                 ((DAT_100395c8 >> 0x1f) & 0x1fU)) >> 5);
            bVar9 = static_cast<std::uint8_t>(
                0x1fU - (static_cast<std::uint8_t>(DAT_100395c8) & 0x1fU));
            puVar11 = local_14 + iVar6;

            if ((*puVar11 & (1U << (bVar9 & 0x1fU))) != 0)
            {
                uVar2 = local_14[iVar6] &
                    ~(static_cast<std::uint32_t>(-1) << (bVar9 & 0x1fU));
                iVar15 = iVar6;

                while (uVar2 == 0)
                {
                    iVar15 = iVar15 + 1;
                    if (2 < iVar15)
                        goto LAB_1001e37d;
                    uVar2 = local_14[iVar15];
                }

                iVar15 = static_cast<std::int32_t>(
                    (iVar14 +
                     ((iVar14 >> 0x1f) & 0x1fU)) >> 5);
                bVar5 = false;
                uVar12 = 1U << (
                    (0x1fU -
                     (static_cast<std::uint8_t>(iVar14) & 0x1fU)) & 0x1fU);
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

        LAB_1001e37d:
            *puVar11 = *puVar11 &
                (static_cast<std::uint32_t>(-1) << (bVar9 & 0x1fU));
            iVar6 = iVar6 + 1;

            if (iVar6 < 3)
            {
                puVar11 = local_14 + iVar6;
                for (iVar14 = 3 - iVar6; iVar14 != 0; iVar14 = iVar14 - 1)
                {
                    *puVar11 = 0;
                    puVar11 = puVar11 + 1;
                }
            }

            iVar6 = static_cast<std::int32_t>(
                (DAT_100395cc + 1U +
                 (((DAT_100395cc + 1U) >> 0x1f) & 0x1fU)) >> 5);
            bVar9 = static_cast<std::uint8_t>(bVar4 + 1U) & 0x1fU;
            local_2c = 0;
            local_24 = 0;

            do
            {
                uVar2 = local_14[local_24];
                local_14[local_24] = uVar2 >> bVar9 | local_2c;
                local_2c = (uVar2 &
                    ~(static_cast<std::uint32_t>(-1) << bVar9))
                    << ((0x20U - bVar9) & 0x1fU);
                local_24 = local_24 + 1;
            }
            while (static_cast<std::int32_t>(local_24) < 3);

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

LAB_1001e589:
    local_14[0] =
        (static_cast<std::uint32_t>(iVar15) <<
         ((0x1fU - bVar4) & 0x1fU)) |
        ((0U - static_cast<std::uint32_t>((uVar1 & 0x8000U) != 0)) &
         0x80000000U) |
        local_14[0];

    if (DAT_100395d0 == 0x40)
    {
        *reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(&_D->x) + 4) = local_14[0];
        *reinterpret_cast<std::uint32_t*>(&_D->x) = local_14[1];
    }
    else if (DAT_100395d0 == 0x20)
    {
        *reinterpret_cast<std::uint32_t*>(&_D->x) = local_14[0];
    }

    __security_check_cookie(local_14[3]);
    return IVar7;
}