#include <cstdint>


extern std::uint32_t DAT_00b7cb84;
extern float DAT_10024e80;
extern float DAT_10024e90;
extern float DAT_10024e98;
extern float DAT_10024ea0;

extern "C" void __stdcall FUN_10003f80();

extern "C" void __fastcall FUN_10006790(std::uint32_t param_1)
{
    std::uint32_t* unaff_EBX;
    __asm mov unaff_EBX, ebx
    std::uint32_t uVar1;
    std::uint32_t uVar2;
    float fVar3;
    char cVar4;
    long double fVar5;

    auto* bytes = reinterpret_cast<std::uint8_t*>(unaff_EBX);

    if (bytes[4] == 0)
    {
        cVar4 = reinterpret_cast<char(__cdecl*)(std::uint8_t)>(0x6c2180)(
            bytes[5]);

        if (cVar4 == 0)
        {
            if (bytes[0x15] == 2)
            {
                uVar1 = *unaff_EBX;

                reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                    0x7f1200)(uVar1, reinterpret_cast<void*>(0x10003fe0), 1);

                reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                    0x7f0dc0)(uVar1, reinterpret_cast<void*>(0x10003fb0), 1);

                bytes[0x14] = 0;
            }
        }
        else if (bytes[0x15] == 0)
        {
            uVar1 = *unaff_EBX;

            reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                0x7f1200)(uVar1, reinterpret_cast<void*>(0x10003fe0), 0);

            reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                0x7f0dc0)(uVar1, reinterpret_cast<void*>(0x10003fb0), 0);

        LAB_10006881:
            bytes[0x14] = 2;
        }
    }
    else if (static_cast<std::uint8_t>(bytes[4] - 2u) < 3u)
    {
        cVar4 = reinterpret_cast<char(__cdecl*)(std::uint8_t)>(0x6c2230)(
            bytes[0x14]);

        if ((cVar4 == 0) ||
            (cVar4 = reinterpret_cast<char(__cdecl*)(std::uint8_t)>(
                 0x6c2230)(bytes[0x14]),
             cVar4 == 1))
        {
            if (bytes[0x15] == 2)
            {
                FUN_10003f80();
                bytes[0x14] = 0;
            }
        }
        else if (bytes[0x15] == 0)
        {
            FUN_10003f80();
            goto LAB_10006881;
        }
    }

    if (bytes[0x15] != 0)
    {
        return;
    }

    switch (bytes[0x14])
    {
    case 0:
        fVar5 = static_cast<long double>(
            reinterpret_cast<float(__cdecl*)()>(0x4082c0)());

        if (static_cast<long double>(DAT_10024e98) <=
            fVar5 * static_cast<long double>(DAT_10024ea0))
        {
            bytes[0x14] = 3;
            unaff_EBX[4] = DAT_00b7cb84;
            return;
        }
        break;

    case 1:
        fVar5 = static_cast<long double>(
            reinterpret_cast<float(__cdecl*)(std::uint32_t)>(0x4082c0)(
                param_1));

        if (fVar5 * static_cast<long double>(DAT_10024ea0) <
            static_cast<long double>(DAT_10024e98))
        {
            bytes[0x14] = 2;
            unaff_EBX[4] = DAT_00b7cb84;
            return;
        }
        break;

    case 2:
        uVar2 = unaff_EBX[3];

        if (uVar2 < static_cast<std::uint32_t>(
                       DAT_00b7cb84 - unaff_EBX[4]))
        {
            fVar3 = 0.0f;
            bytes[0x14] = 0;
        }
        else
        {
            fVar3 = static_cast<float>(static_cast<std::int32_t>(uVar2));

            if (static_cast<std::int32_t>(uVar2) < 0)
            {
                fVar3 = fVar3 + DAT_10024e90;
            }

            fVar3 =
                (1.0f -
                 static_cast<float>(DAT_00b7cb84 - unaff_EBX[4]) / fVar3) *
                static_cast<float>(unaff_EBX[2]) *
                static_cast<float>(DAT_10024e80);
        }

        reinterpret_cast<void(__cdecl*)(float)>(0x59afa0)(fVar3);
        break;

    case 3:
        uVar2 = unaff_EBX[3];

        if (uVar2 < static_cast<std::uint32_t>(
                       DAT_00b7cb84 - unaff_EBX[4]))
        {
            bytes[0x14] = 1;
            fVar3 = static_cast<float>(unaff_EBX[2]) *
                    static_cast<float>(DAT_10024e80);
        }
        else
        {
            fVar3 = static_cast<float>(static_cast<std::int32_t>(uVar2));

            if (static_cast<std::int32_t>(uVar2) < 0)
            {
                fVar3 = fVar3 + DAT_10024e90;
            }

            fVar3 =
                static_cast<float>(DAT_00b7cb84 - unaff_EBX[4]) / fVar3 *
                static_cast<float>(unaff_EBX[2]) *
                static_cast<float>(DAT_10024e80);
        }

        reinterpret_cast<void(__cdecl*)(float)>(0x59afa0)(fVar3);
        break;
    }
}