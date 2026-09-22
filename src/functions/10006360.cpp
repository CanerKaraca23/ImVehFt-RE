#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;
extern float _DAT_10024fa0;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" long double __cdecl FUN_10010120(std::uint32_t, std::uint32_t);
extern long double __cdecl FUN_0053cc70(std::uint32_t, std::uint32_t);
extern void __cdecl FUN_0059b020(float);
extern void __cdecl FUN_007f18b0(std::int32_t, std::int32_t, std::int32_t);

extern "C" void __cdecl FUN_10006360(std::int32_t param_1)
{
    std::int32_t iVar1;
    std::int32_t iVar2;
    std::int32_t iVar3;
    long double fVar4;

    iVar2 = DAT_1003c248;
    iVar1 = FUN_10009360();
    iVar3 = *reinterpret_cast<std::int32_t*>(param_1 + 0x594);

    iVar2 =
        *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar1 + 0x48) +
            ((param_1 - *_DAT_00b74494) / 0xa18) * 4) +
        iVar2;

    if ((iVar3 == 0) || (iVar3 == 2) || (iVar3 == 0xb) || (iVar3 == 1))
    {
        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x4e8);

        if ((iVar3 != 0) &&
            ((iVar1 = *reinterpret_cast<std::int32_t*>(param_1 + 0x650)) != 0))
        {
            fVar4 = FUN_0053cc70(
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x10),
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x14));
            FUN_0059b020(static_cast<float>(fVar4));

            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x40);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x44);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x48);

            FUN_007f18b0(
                iVar3 + 0x50,
                iVar3 + 0x10,
                *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
        }

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x4f0);

        if ((iVar3 != 0) &&
            ((iVar1 = *reinterpret_cast<std::int32_t*>(param_1 + 0x65c)) != 0))
        {
            fVar4 = FUN_0053cc70(
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x10),
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x14));
            FUN_0059b020(static_cast<float>(
                fVar4 - static_cast<long double>(_DAT_10024fa0)));

            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x40);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x44);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x48);

            FUN_007f18b0(
                iVar3 + 0x50,
                iVar3 + 0x10,
                *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
        }

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x4f8);

        if ((iVar3 != 0) &&
            ((iVar1 = *reinterpret_cast<std::int32_t*>(param_1 + 0x654)) != 0))
        {
            fVar4 = FUN_0053cc70(
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x10),
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x14));
            FUN_0059b020(static_cast<float>(fVar4));

            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x40);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x44);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x48);

            FUN_007f18b0(
                iVar3 + 0x50,
                iVar3 + 0x10,
                *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
        }

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x500);

        if ((iVar3 != 0) &&
            ((iVar1 = *reinterpret_cast<std::int32_t*>(param_1 + 0x660)) != 0))
        {
            fVar4 = FUN_0053cc70(
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x10),
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x14));
            FUN_0059b020(static_cast<float>(
                fVar4 - static_cast<long double>(_DAT_10024fa0)));

            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x40);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x44);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x48);

            FUN_007f18b0(
                iVar3 + 0x50,
                iVar3 + 0x10,
                *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
        }

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x508);

        if ((iVar3 != 0) &&
            ((iVar1 = *reinterpret_cast<std::int32_t*>(param_1 + 0x658)) != 0))
        {
            fVar4 = FUN_0053cc70(
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x10),
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x14));
            FUN_0059b020(static_cast<float>(fVar4));

            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x40);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x44);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x48);

            FUN_007f18b0(
                iVar3 + 0x50,
                iVar3 + 0x10,
                *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
        }

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x510);

        if (iVar3 == 0)
            return;

        iVar2 = *reinterpret_cast<std::int32_t*>(param_1 + 0x664);

        if (iVar2 == 0)
            return;

        fVar4 = FUN_0053cc70(
            *reinterpret_cast<std::uint32_t*>(iVar2 + 0x10),
            *reinterpret_cast<std::uint32_t*>(iVar2 + 0x14));

        fVar4 = static_cast<float>(
            fVar4 - static_cast<long double>(_DAT_10024fa0));
    }
    else
    {
        if ((iVar3 != 9) && (iVar3 != 10))
            return;

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x4e8);

        if ((iVar3 != 0) &&
            ((iVar1 = *reinterpret_cast<std::int32_t*>(param_1 + 0x5b0)) != 0))
        {
            fVar4 = FUN_10010120(
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x10),
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x14));
            FUN_0059b020(static_cast<float>(fVar4));

            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x40);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x44);
            *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
                *reinterpret_cast<std::uint32_t*>(iVar1 + 0x48);

            FUN_007f18b0(
                iVar3 + 0x50,
                iVar3 + 0x10,
                *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
        }

        iVar3 = *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x28) + 0x508);

        if (iVar3 == 0)
            return;

        iVar2 = *reinterpret_cast<std::int32_t*>(param_1 + 0x5b4);

        if (iVar2 == 0)
            return;

        fVar4 = FUN_10010120(
            *reinterpret_cast<std::uint32_t*>(iVar2 + 0x10),
            *reinterpret_cast<std::uint32_t*>(iVar2 + 0x14));
    }

    FUN_0059b020(static_cast<float>(fVar4));

    *reinterpret_cast<std::uint32_t*>(iVar3 + 0x40) =
        *reinterpret_cast<std::uint32_t*>(iVar2 + 0x40);
    *reinterpret_cast<std::uint32_t*>(iVar3 + 0x44) =
        *reinterpret_cast<std::uint32_t*>(iVar2 + 0x44);
    *reinterpret_cast<std::uint32_t*>(iVar3 + 0x48) =
        *reinterpret_cast<std::uint32_t*>(iVar2 + 0x48);

    FUN_007f18b0(
        iVar3 + 0x50,
        iVar3 + 0x10,
        *reinterpret_cast<std::int32_t*>(iVar3 + 4) + 0x10);
}