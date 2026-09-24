#include <cstddef>
#include <cstdint>

struct RwTexture;

extern std::int32_t DAT_1003c248;
extern std::int32_t DAT_1003c1fc;
extern float _DAT_1003c1ec;
extern std::int32_t DAT_1003aef4;
extern std::uintptr_t DAT_1003759c;
extern std::uintptr_t DAT_1003aacc;
extern std::int32_t _DAT_10024f08;
extern std::int32_t DAT_1003bd9c;
extern std::int32_t DAT_10024a14;
extern std::int32_t DAT_10024f90;
extern std::int32_t _DAT_10024f90;
extern std::int32_t _DAT_10024f94;
extern float _DAT_10024e90;
extern std::int32_t DAT_1003c250;
extern std::int32_t DAT_1003c254;
extern std::int32_t _DAT_1003bc00;

extern std::int32_t* _DAT_00b74494;
extern std::int32_t* _DAT_00c8800c;

extern std::int32_t DAT_1003bc78;
extern char DAT_1003aef0;
extern char DAT_1003aeec;
extern char DAT_1003aef1;
extern std::uint8_t DAT_1003aedc[0x12];
extern std::uint32_t DAT_100374c0[0x12];

extern std::int32_t* DAT_10037594;
extern std::int32_t* _DAT_1003c1a8;
extern std::int32_t* _DAT_1003bbc0;
extern std::int32_t* _DAT_1003bc30;
extern std::int32_t* _DAT_1003c208;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" std::int32_t __stdcall FUN_10008e00();
extern "C" std::uint32_t* __cdecl FUN_10001fb0(std::uint32_t*);
extern "C" int __cdecl strncmp(const char*, const char*, std::size_t);

using TextureCallback = void(__cdecl*)(int*, std::int32_t);
using TextureLookup = std::int32_t(__cdecl*)(std::int32_t, const char*);
using PaletteLookup = std::uint8_t*(__cdecl*)(std::int32_t);

extern "C" int* __cdecl FUN_100076d0(int* param_1, int* param_2)
{
    char local_34[32];
    std::int32_t local_14;
    float local_10;
    std::int32_t local_c = 0;
    std::int32_t local_8;

    std::uint32_t* puVar1;
    int* piVar2;
    int* piVar3;
    int* piVar4;
    float* pfVar5;
    float* pfVar6;
    std::uint8_t bVar7;
    char cVar8;
    float fVar9;
    std::int32_t iVar10;
    std::uint32_t uVar11;
    std::int32_t iVar12;
    std::uint32_t* puVar13;
    char* pcVar14;
    std::uint32_t uVar15;
    std::int32_t iVar16;
    std::int32_t iVar18;
    std::uint8_t* puVar17;
    std::uint8_t* pbVar19;
    bool bVar20;

    const auto texture_callback =
        reinterpret_cast<TextureCallback>(0x74dbc0);
    const auto texture_lookup =
        reinterpret_cast<TextureLookup>(0x7f39f0);
    const auto palette_lookup =
        reinterpret_cast<PaletteLookup>(0x447090);

#define WRITE_SLOT(address)                                                   \
    do                                                                        \
    {                                                                         \
        *reinterpret_cast<void**>(*param_2) = (address);                      \
        *reinterpret_cast<std::uint32_t*>(*param_2 + 4) =                    \
            *reinterpret_cast<std::uint32_t*>(address);                      \
        *param_2 = *param_2 + 8;                                               \
    } while (false)

    iVar16 = DAT_1003c248;
    iVar12 = DAT_1003c1fc;

    if (DAT_1003c1fc != 0)
    {
        iVar10 = FUN_10009360();
        local_c =
            *reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(iVar10) + 0x48) +
                ((iVar12 - *_DAT_00b74494) / 0xa18) * 4) +
            iVar16;
    }

    local_14 = *param_1;
    puVar1 = reinterpret_cast<std::uint32_t*>(param_1 + 1);
    uVar11 = param_1[1] & 0xffffff;
    iVar12 = 0;

    local_8 =
        *reinterpret_cast<std::int32_t*>(
            *_DAT_00c8800c +
            *reinterpret_cast<std::int16_t*>(
                *reinterpret_cast<std::int32_t*>(
                    DAT_1003759c + DAT_1003aef4 * 4) + 10) *
            0xc);

    if (local_14 != 0)
    {
        iVar12 =
            *reinterpret_cast<std::int32_t*>(
                DAT_1003aacc + 8 + local_14);
    }

    if (*reinterpret_cast<RwTexture**>(
            static_cast<std::uintptr_t>(0x00b4e47c)) != nullptr &&
        local_14 != 0 &&
        *reinterpret_cast<char*>(
            static_cast<std::uintptr_t>(local_14) + 0x10) == '#')
    {
        WRITE_SLOT(param_1);

        if (iVar12 == 0)
        {
            *param_1 = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(
                    *reinterpret_cast<RwTexture**>(
                        static_cast<std::uintptr_t>(0x00b4e47c))));
        }
        else
        {
            puVar13 = FUN_10001fb0(reinterpret_cast<std::uint32_t*>(
                *reinterpret_cast<RwTexture**>(
                    static_cast<std::uintptr_t>(0x00b4e47c))));
            *param_1 = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(puVar13));
        }

        WRITE_SLOT(puVar1);
        *puVar1 = *puVar1 | 0xffffff;
        return param_1;
    }

    _DAT_1003bc00 = 0;

    if (local_14 != 0)
    {
        if (iVar12 == 0)
        {
            pbVar19 = reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(local_14) + 0x10);
            pcVar14 = const_cast<char*>("vehiclegrunge256");

            do
            {
                bVar7 = *pbVar19;
                bVar20 = bVar7 < static_cast<std::uint8_t>(*pcVar14);

                if (bVar7 != static_cast<std::uint8_t>(*pcVar14))
                {
                    iVar12 =
                        (1 - static_cast<std::uint32_t>(bVar20)) -
                        static_cast<std::uint32_t>(bVar20 != 0);
                    goto CHECK_GRUNGE_256;
                }

                if (bVar7 == 0)
                    break;

                bVar7 = pbVar19[1];
                bVar20 = bVar7 <
                    static_cast<std::uint8_t>(pcVar14[1]);

                if (bVar7 != static_cast<std::uint8_t>(pcVar14[1]))
                {
                    iVar12 =
                        (1 - static_cast<std::uint32_t>(bVar20)) -
                        static_cast<std::uint32_t>(bVar20 != 0);
                    goto CHECK_GRUNGE_256;
                }

                pbVar19 += 2;
                pcVar14 += 2;
            }
            while (bVar7 != 0);

            iVar12 = 0;

        CHECK_GRUNGE_256:
            if (iVar12 == 0)
            {
                texture_callback(
                    param_1,
                    _DAT_1003c1a8[DAT_1003bc78]);
            }

            pbVar19 = reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(*param_1) + 0x10);
            pcVar14 = const_cast<char*>("vehiclegrunge512");

            do
            {
                bVar7 = *pbVar19;
                bVar20 = bVar7 < static_cast<std::uint8_t>(*pcVar14);

                if (bVar7 != static_cast<std::uint8_t>(*pcVar14))
                {
                    iVar12 =
                        (1 - static_cast<std::uint32_t>(bVar20)) -
                        static_cast<std::uint32_t>(bVar20 != 0);
                    goto CHECK_GRUNGE_512;
                }

                if (bVar7 == 0)
                    break;

                bVar7 = pbVar19[1];
                bVar20 = bVar7 <
                    static_cast<std::uint8_t>(pcVar14[1]);

                if (bVar7 != static_cast<std::uint8_t>(pcVar14[1]))
                {
                    iVar12 =
                        (1 - static_cast<std::uint32_t>(bVar20)) -
                        static_cast<std::uint32_t>(bVar20 != 0);
                    goto CHECK_GRUNGE_512;
                }

                pbVar19 += 2;
                pcVar14 += 2;
            }
            while (bVar7 != 0);

            iVar12 = 0;

        CHECK_GRUNGE_512:
            if (iVar12 == 0)
            {
                texture_callback(
                    param_1,
                    _DAT_1003bbc0[DAT_1003bc78]);
            }
            else
            {
                pcVar14 = const_cast<char*>("vehiclegrunge_iv");
                pbVar19 = reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(*param_1) + 0x10);

                do
                {
                    bVar7 = *pbVar19;
                    bVar20 =
                        bVar7 < static_cast<std::uint8_t>(*pcVar14);

                    if (bVar7 != static_cast<std::uint8_t>(*pcVar14))
                    {
                        iVar12 =
                            (1 - static_cast<std::uint32_t>(bVar20)) -
                            static_cast<std::uint32_t>(bVar20 != 0);
                        goto CHECK_GRUNGE_IV;
                    }

                    if (bVar7 == 0)
                        break;

                    bVar7 = pbVar19[1];
                    bVar20 =
                        bVar7 < static_cast<std::uint8_t>(pcVar14[1]);

                    if (bVar7 != static_cast<std::uint8_t>(pcVar14[1]))
                    {
                        iVar12 =
                            (1 - static_cast<std::uint32_t>(bVar20)) -
                            static_cast<std::uint32_t>(bVar20 != 0);
                        goto CHECK_GRUNGE_IV;
                    }

                    pbVar19 += 2;
                    pcVar14 += 2;
                }
                while (bVar7 != 0);

                iVar12 = 0;

            CHECK_GRUNGE_IV:
                if (iVar12 == 0)
                {
                    texture_callback(
                        param_1,
                        _DAT_1003bc30[DAT_1003bc78]);
                }
                else
                {
                    pcVar14 = const_cast<char*>("tyrewall_dirt_1");
                    pbVar19 = reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(*param_1) + 0x10);

                    do
                    {
                        bVar7 = *pbVar19;
                        bVar20 =
                            bVar7 < static_cast<std::uint8_t>(*pcVar14);

                        if (bVar7 != static_cast<std::uint8_t>(*pcVar14))
                        {
                            iVar12 =
                                (1 - static_cast<std::uint32_t>(bVar20)) -
                                static_cast<std::uint32_t>(bVar20 != 0);
                            goto CHECK_TYREWALL;
                        }

                        if (bVar7 == 0)
                            break;

                        bVar7 = pbVar19[1];
                        bVar20 =
                            bVar7 < static_cast<std::uint8_t>(pcVar14[1]);

                        if (bVar7 != static_cast<std::uint8_t>(pcVar14[1]))
                        {
                            iVar12 =
                                (1 - static_cast<std::uint32_t>(bVar20)) -
                                static_cast<std::uint32_t>(bVar20 != 0);
                            goto CHECK_TYREWALL;
                        }

                        pbVar19 += 2;
                        pcVar14 += 2;
                    }
                    while (bVar7 != 0);

                    iVar12 = 0;

                CHECK_TYREWALL:
                    if (iVar12 == 0)
                    {
                        texture_callback(
                            param_1,
                            _DAT_1003c208[DAT_1003bc78]);
                    }
                    else if (DAT_1003aef1 == '\0' &&
                             DAT_1003c1fc != 0 &&
                             *reinterpret_cast<char*>(
                                 static_cast<std::uintptr_t>(local_c) +
                                 0x20) != '\0')
                    {
                        iVar12 = strncmp(
                            reinterpret_cast<const char*>(
                                static_cast<std::uintptr_t>(*param_1) +
                                0x10),
                            "plateback1",
                            10);

                        if (iVar12 == 0)
                        {
                            WRITE_SLOT(param_1);
                            *param_1 = DAT_1003bd9c;

                            piVar2 = param_1 + 3;
                            WRITE_SLOT(piVar2);
                            *piVar2 = _DAT_10024f94;
                        }
                        else
                        {
                            iVar12 = strncmp(
                                reinterpret_cast<const char*>(
                                    static_cast<std::uintptr_t>(*param_1) +
                                    0x10),
                                "plateback2",
                                10);

                            if (iVar12 != 0)
                            {
                                iVar12 = strncmp(
                                    reinterpret_cast<const char*>(
                                        static_cast<std::uintptr_t>(
                                            *param_1) + 0x10),
                                    "plateback3",
                                    10);
                            }

                            if (iVar12 == 0)
                            {
                                WRITE_SLOT(param_1);
                                *param_1 = DAT_1003bd9c;

                                piVar2 = param_1 + 3;
                                WRITE_SLOT(piVar2);
                                *piVar2 = _DAT_10024f94;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            local_10 =
                _DAT_1003c1ec /
                static_cast<float>(_DAT_10024f08);

            WRITE_SLOT(param_1);

            puVar13 = FUN_10001fb0(
                reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(*param_1)));

            *param_1 = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(puVar13));
        }
    }

    if (local_8 == 0 ||
        texture_lookup(local_8, "vehiclelights") == 0)
    {
        iVar12 = static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(
            *reinterpret_cast<RwTexture**>(
                static_cast<std::uintptr_t>(0x00b4e68c))));
    }

    if (local_14 == iVar12 ||
        local_14 == static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(
            *reinterpret_cast<RwTexture**>(
                static_cast<std::uintptr_t>(0x00b4e68c)))))
    {
        iVar12 = 0;

        do
        {
            iVar16 = iVar12;

            if (uVar11 == DAT_100374c0[iVar12])
                break;

            iVar12 = iVar12 + 1;
            iVar16 = -1;
        }
        while (iVar12 < 0x12);

        puVar1 = reinterpret_cast<std::uint32_t*>(param_1 + 1);
        WRITE_SLOT(puVar1);
        *puVar1 = *puVar1 | 0xffffff;

        iVar12 = DAT_1003c1fc;

        if (iVar16 != -1)
        {
            if (DAT_1003aedc[iVar16] == '\0')
                return param_1;

            if (DAT_1003aedc[iVar16] != '\x02')
            {
                WRITE_SLOT(param_1);

                piVar2 = param_1 + 3;
                WRITE_SLOT(piVar2);
                WRITE_SLOT(param_1 + 5);
                WRITE_SLOT(param_1 + 4);

                if (local_8 == 0 ||
                    texture_lookup(
                        local_8,
                        "vehiclelights_on") == 0)
                {
                    iVar12 = static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(
                        *reinterpret_cast<RwTexture**>(
                            static_cast<std::uintptr_t>(0x00b4e690))));
                }

                *param_1 = iVar12;
                *piVar2 = _DAT_10024f94;
                param_1[4] = 0;
                param_1[5] = 0;
                return param_1;
            }

            if (local_8 == 0)
                return param_1;

            iVar12 =
                texture_lookup(local_8, "vehiclelights_dam");

            if (iVar12 != 0)
            {
                WRITE_SLOT(param_1);
                *param_1 = iVar12;
            }

            return param_1;
        }

        local_14 = DAT_1003c248;
        iVar18 = FUN_10009360();
        iVar10 = DAT_1003c248;
        iVar16 = DAT_1003c1fc;

        if (*reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(
                    *reinterpret_cast<std::int32_t*>(
                        *reinterpret_cast<std::int32_t*>(
                            static_cast<std::uintptr_t>(iVar18) + 0x48) +
                        ((iVar12 - *_DAT_00b74494) / 0xa18) * 4) +
                    0x28 + local_14) +
                0x350) == 0)
        {
            return param_1;
        }

        local_c = 0;
        uVar15 = 0xff;

        while (uVar11 != uVar15)
        {
            uVar15 = uVar15 - 1;
            local_c = local_c + 1;

            if (static_cast<std::int32_t>(uVar15) < 0xf0)
                return param_1;
        }

        iVar12 = FUN_10009360();

        iVar12 =
            *reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(iVar12) + 0x48) +
                ((iVar16 - *_DAT_00b74494) / 0xa18) * 4) +
            0x28 + iVar10;

        piVar2 = param_1 + 1;
        WRITE_SLOT(piVar2);

        iVar16 =
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(iVar12) + 0xc);

        *reinterpret_cast<std::uint16_t*>(piVar2) =
            *reinterpret_cast<std::uint16_t*>(
                static_cast<std::uintptr_t>(iVar16) + 8);

        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uint8_t*>(param_1) + 6) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(iVar16) + 10);

        if (*reinterpret_cast<char*>(
                static_cast<std::uintptr_t>(iVar12) + 9) == '\0')
        {
            return param_1;
        }

        piVar2 = param_1 + 3;
        WRITE_SLOT(piVar2);

        pfVar5 = reinterpret_cast<float*>(param_1 + 5);
        WRITE_SLOT(pfVar5);

        pfVar6 = reinterpret_cast<float*>(param_1 + 4);
        WRITE_SLOT(pfVar6);

        *piVar2 = _DAT_10024f90;

        fVar9 = static_cast<float>(DAT_1003c250);
        if (DAT_1003c250 < 0)
            fVar9 = fVar9 + _DAT_10024e90;
        *pfVar6 = fVar9;

        fVar9 = static_cast<float>(DAT_1003c254);
        if (DAT_1003c254 < 0)
            fVar9 = fVar9 + _DAT_10024e90;
        *pfVar5 = fVar9;

        pcVar14 = reinterpret_cast<char*>(
            static_cast<std::uintptr_t>(*param_1) + 0x10);

        iVar12 = -static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(pcVar14));

        do
        {
            cVar8 = *pcVar14;
            pcVar14[
                reinterpret_cast<std::uintptr_t>(local_34) + iVar12] =
                cVar8;
            pcVar14 = pcVar14 + 1;
        }
        while (cVar8 != '\0');

        puVar13 = reinterpret_cast<std::uint32_t*>(local_34 - 1);

        do
        {
            pcVar14 = reinterpret_cast<char*>(
                reinterpret_cast<std::uintptr_t>(puVar13) + 1);
            puVar13 = reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(puVar13) + 1);
        }
        while (*pcVar14 != '\0');

        *puVar13 = DAT_10024a14;
        iVar12 = texture_lookup(local_8, local_34);

        if (iVar12 != 0)
        {
            WRITE_SLOT(param_1);
            *param_1 = iVar12;
        }

        return param_1;
    }

    if (uVar11 == 0xff3c)
    {
        iVar12 = DAT_10037594[0];
        goto WRITE_PALETTE;
    }

    if (uVar11 == 0xaf00ff)
    {
        iVar12 = DAT_10037594[1];
        goto WRITE_PALETTE;
    }

    if (uVar11 == 0xffff00)
    {
        iVar12 = DAT_10037594[2];
        goto WRITE_PALETTE;
    }

    if (uVar11 == 0xff00ff)
    {
        iVar12 = DAT_10037594[3];
        goto WRITE_PALETTE;
    }

    if (uVar11 == 0xff1200)
    {
        puVar1 = reinterpret_cast<std::uint32_t*>(param_1 + 1);
        WRITE_SLOT(puVar1);

        if (DAT_1003aef0 == '\0')
        {
            *reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uint8_t*>(param_1) + 7) = 0;
            return param_1;
        }

        *puVar1 = *puVar1 | 0xffffff;
        return param_1;
    }

    if (uVar11 == 0xff1000)
    {
        puVar1 = reinterpret_cast<std::uint32_t*>(param_1 + 1);
        WRITE_SLOT(puVar1);
        *puVar1 = *puVar1 | 0xffffff;

        if (DAT_1003aeec == '\0')
            return param_1;

        piVar2 = param_1 + 3;
        WRITE_SLOT(piVar2);

        piVar3 = param_1 + 5;
        WRITE_SLOT(piVar3);

        *piVar2 = _DAT_10024f94;
        *piVar3 = 0;

        pcVar14 = reinterpret_cast<char*>(
            static_cast<std::uintptr_t>(*param_1) + 0x10);

        iVar12 = -static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(pcVar14));

        do
        {
            cVar8 = *pcVar14;
            pcVar14[
                reinterpret_cast<std::uintptr_t>(local_34) + iVar12] =
                cVar8;
            pcVar14 = pcVar14 + 1;
        }
        while (cVar8 != '\0');

        puVar13 = reinterpret_cast<std::uint32_t*>(local_34 - 1);

        do
        {
            pcVar14 = reinterpret_cast<char*>(
                reinterpret_cast<std::uintptr_t>(puVar13) + 1);
            puVar13 = reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(puVar13) + 1);
        }
        while (*pcVar14 != '\0');

        *puVar13 = DAT_10024a14;
        goto LOOKUP_TEXTURE;
    }

    iVar12 = FUN_10008e00();

    if (*reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(iVar12) + 0x28) +
            0x350) == 0)
    {
        return param_1;
    }

    uVar15 = 0xff;
    iVar12 = 0;

    while (uVar11 != uVar15)
    {
        uVar15 = uVar15 - 1;
        iVar12 = iVar12 + 1;

        if (static_cast<std::int32_t>(uVar15) < 0xf0)
            return param_1;
    }

    iVar16 = FUN_10008e00();

    iVar12 =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(iVar16) + 0x28) +
        0x354 + iVar12 * 0x14;

    piVar2 = param_1 + 1;
    WRITE_SLOT(piVar2);

    iVar16 =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(iVar12) + 0xc);

    *reinterpret_cast<std::uint16_t*>(piVar2) =
        *reinterpret_cast<std::uint16_t*>(
            static_cast<std::uintptr_t>(iVar16) + 8);

    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(param_1) + 6) =
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(iVar16) + 10);

    if (*reinterpret_cast<char*>(
            static_cast<std::uintptr_t>(iVar12) + 9) == '\0')
    {
        return param_1;
    }

    piVar2 = param_1 + 3;
    WRITE_SLOT(piVar2);

    piVar3 = param_1 + 5;
    WRITE_SLOT(piVar3);

    piVar4 = param_1 + 4;
    WRITE_SLOT(piVar4);

    *piVar2 = _DAT_10024f94;
    *piVar4 = 0;
    *piVar3 = 0;

    pcVar14 = reinterpret_cast<char*>(
        static_cast<std::uintptr_t>(*param_1) + 0x10);

    iVar12 = -static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(pcVar14));

    do
    {
        cVar8 = *pcVar14;
        pcVar14[
            reinterpret_cast<std::uintptr_t>(local_34) + iVar12] =
            cVar8;
        pcVar14 = pcVar14 + 1;
    }
    while (cVar8 != '\0');

    puVar13 = reinterpret_cast<std::uint32_t*>(local_34 - 1);

    do
    {
        pcVar14 = reinterpret_cast<char*>(
            reinterpret_cast<std::uintptr_t>(puVar13) + 1);
        puVar13 = reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uintptr_t>(puVar13) + 1);
    }
    while (*pcVar14 != '\0');

    *puVar13 = DAT_10024a14;

LOOKUP_TEXTURE:
    iVar12 = texture_lookup(local_8, local_34);

    if (iVar12 != 0)
    {
        WRITE_SLOT(param_1);
        *param_1 = iVar12;
    }

    return param_1;

WRITE_PALETTE:
    puVar1 = reinterpret_cast<std::uint32_t*>(param_1 + 1);
    WRITE_SLOT(puVar1);

    if (DAT_1003c1fc != 0 &&
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(local_c) + 0x30) != 0 &&
        iVar12 < static_cast<std::int32_t>(
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(local_c) + 0x2c)))
    {
        iVar16 =
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(local_c) + 0x30) +
            iVar12 * 4;

        *reinterpret_cast<std::uint8_t*>(puVar1) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(iVar16));

        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uint8_t*>(param_1) + 5) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(iVar16) + 1);

        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uint8_t*>(param_1) + 6) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(iVar16) + 2);

        return param_1;
    }

    puVar17 = palette_lookup(iVar12);
    *reinterpret_cast<std::uint8_t*>(param_1 + 1) = *puVar17;

    iVar16 = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(
            palette_lookup(iVar12)));

    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(param_1) + 5) =
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(iVar16) + 1);

    iVar12 = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(
            palette_lookup(iVar12)));

    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(param_1) + 6) =
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(iVar12) + 2);

    return param_1;

#undef WRITE_SLOT
}
