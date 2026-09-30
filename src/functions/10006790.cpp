#include <cstdint>
#include <cstring>
#include "gta_sa_address_access.hpp"


extern double DAT_10024e80;
extern float DAT_10024e90;
extern double DAT_10024e98;
extern double DAT_10024ea0;

extern "C" void __stdcall FUN_10003f80();
extern "C" std::uint32_t __cdecl FUN_10003fb0(
    std::uint32_t param_1,
    std::uint32_t param_2);
extern "C" void __cdecl FUN_10003fe0(int param_1, int param_2);

using ImVehFtCallback = void (__cdecl*)(int, int);
using ImVehFtCallbackReturningValue = std::uint32_t (__cdecl*)(
    std::uint32_t,
    std::uint32_t);
using CMatrixSetRotateXOnly = void (__thiscall*)(void*, float);

extern "C" void __cdecl FUN_10006790(std::uint32_t param_1)
{
    std::uint32_t* unaff_EBX;
    __asm mov unaff_EBX, ebx
    std::uint32_t uVar1;
    std::uint32_t uVar2;
    float fVar3;
    char cVar4;
    long double fVar5;

    auto* bytes = reinterpret_cast<std::uint8_t*>(unaff_EBX);
    float fVehicleValue;
    std::memcpy(&fVehicleValue, bytes + 8, sizeof(fVehicleValue));

    if (bytes[4] == 0)
    {
        cVar4 = reinterpret_cast<char(__thiscall*)(void*, std::uint8_t)>(
            0x6c2180)(reinterpret_cast<void*>(param_1 + 0x5A0), bytes[5]);

        if (cVar4 == 0)
        {
            if (bytes[0x15] == 2)
            {
                uVar1 = *unaff_EBX;

                reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                    0x7f1200)(
                    uVar1,
                    reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(
                        static_cast<ImVehFtCallback>(FUN_10003fe0))),
                    1);

                reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                    0x7f0dc0)(
                    uVar1,
                    reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(
                        static_cast<ImVehFtCallbackReturningValue>(FUN_10003fb0))),
                    1);

                bytes[0x14] = 0;
            }
        }
        else if (bytes[0x15] == 0)
        {
            uVar1 = *unaff_EBX;

            reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                0x7f1200)(
                uVar1,
                reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(
                    static_cast<ImVehFtCallback>(FUN_10003fe0))),
                0);

            reinterpret_cast<void(__cdecl*)(std::uint32_t, void*, int)>(
                0x7f0dc0)(
                uVar1,
                reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(
                    static_cast<ImVehFtCallbackReturningValue>(FUN_10003fb0))),
                0);

        LAB_10006881:
            bytes[0x14] = 2;
        }
    }
    else if (static_cast<std::uint8_t>(bytes[4] - 2u) < 3u)
    {
        cVar4 = reinterpret_cast<char(__thiscall*)(void*, std::uint8_t)>(
            0x6c2230)(reinterpret_cast<void*>(param_1 + 0x5A0), bytes[5]);

        if ((cVar4 == 0) ||
            (cVar4 = reinterpret_cast<char(__thiscall*)(void*, std::uint8_t)>(
                 0x6c2230)(reinterpret_cast<void*>(param_1 + 0x5A0),
                           bytes[5]),
             cVar4 == 1))
        {
            if (bytes[0x15] == 2)
            {
                uVar1 = *unaff_EBX;
                __asm {
                    mov esi, uVar1
                    mov edi, 1
                }
                FUN_10003f80();
                bytes[0x14] = 0;
            }
        }
        else if (bytes[0x15] == 0)
        {
            uVar1 = *unaff_EBX;
            __asm {
                mov esi, uVar1
                xor edi, edi
            }
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
            unaff_EBX[4] = IMVEHFT_GLOBAL_AT(std::uint32_t, 0x00b7cb84);
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
            unaff_EBX[4] = IMVEHFT_GLOBAL_AT(std::uint32_t, 0x00b7cb84);
            return;
        }
        break;

    case 2:
    {
        uVar2 = unaff_EBX[3];
        const std::uint32_t elapsed_delta =
            IMVEHFT_GLOBAL_AT(std::uint32_t, 0x00b7cb84) - unaff_EBX[4];

        if (uVar2 < elapsed_delta)
        {
            fVar3 = 0.0f;
            bytes[0x14] = 0;
        }
        else
        {
            const std::int32_t signed_elapsed =
                static_cast<std::int32_t>(uVar2);
            double elapsed_denominator =
                static_cast<double>(signed_elapsed);
            if (signed_elapsed < 0)
            {
                elapsed_denominator +=
                    static_cast<double>(DAT_10024e90);
            }

            volatile float intermediate_angle = static_cast<float>(
                (1.0 - static_cast<double>(
                    static_cast<std::int32_t>(elapsed_delta)) /
                           elapsed_denominator) *
                static_cast<double>(fVehicleValue));
            fVar3 = static_cast<float>(
                static_cast<double>(intermediate_angle) * DAT_10024e80);
        }

        reinterpret_cast<CMatrixSetRotateXOnly>(0x59afa0)(
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(
                unaff_EBX[0] + 0x10u)),
            fVar3);
        break;
    }

    case 3:
    {
        uVar2 = unaff_EBX[3];
        const std::uint32_t elapsed_delta =
            IMVEHFT_GLOBAL_AT(std::uint32_t, 0x00b7cb84) - unaff_EBX[4];

        if (uVar2 < elapsed_delta)
        {
            bytes[0x14] = 1;
            fVar3 = static_cast<float>(
                static_cast<double>(fVehicleValue) * DAT_10024e80);
        }
        else
        {
            const std::int32_t signed_elapsed =
                static_cast<std::int32_t>(uVar2);
            double elapsed_denominator =
                static_cast<double>(signed_elapsed);
            if (signed_elapsed < 0)
            {
                elapsed_denominator +=
                    static_cast<double>(DAT_10024e90);
            }

            volatile float intermediate_angle = static_cast<float>(
                static_cast<double>(
                    static_cast<std::int32_t>(elapsed_delta)) /
                elapsed_denominator *
                static_cast<double>(fVehicleValue));
            fVar3 = static_cast<float>(
                static_cast<double>(intermediate_angle) * DAT_10024e80);
        }

        reinterpret_cast<CMatrixSetRotateXOnly>(0x59afa0)(
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(
                unaff_EBX[0] + 0x10u)),
            fVar3);
        break;
    }
    }
}
