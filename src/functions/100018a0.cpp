#include <cstdint>

extern int __cdecl FUN_007ed2d0(
    std::uint32_t param_1,
    std::int32_t param_2,
    std::int32_t* param_3,
    std::uint8_t* param_4);

extern int __cdecl FUN_007ec9d0(
    std::uint32_t param_1,
    std::int16_t* param_2,
    std::int32_t param_3);

extern int __cdecl FUN_007f3600();
extern int __cdecl FUN_00730e60(std::uint32_t param_1);
extern void __cdecl FUN_007f3980(
    std::int32_t param_1,
    std::int32_t param_2);

extern void __cdecl FUN_007f3730(
    std::int32_t param_1,
    std::uintptr_t param_2,
    std::int32_t param_3);

extern void __cdecl FUN_007f36a0(std::int32_t param_1);

extern "C" int* __cdecl FUN_10001980(int*, unsigned int);

int __cdecl FUN_100018a0(std::uint32_t param_1)
{
    int iVar1;
    int iVar2;
    std::uint8_t local_10[4];
    int local_c;
    std::int16_t local_8[2];

    iVar1 = FUN_007ed2d0(param_1, 1, &local_c, local_10);

    if ((iVar1 != 0) &&
        ((iVar1 = FUN_007ec9d0(param_1, local_8, local_c)),
         (iVar1 == local_c)))
    {
        iVar1 = FUN_007f3600();

        if (iVar1 != 0)
        {
            if (local_8[0] == 0)
            {
                return iVar1;
            }

            local_8[0] = local_8[0] + -1;
            iVar2 = FUN_00730e60(param_1);

            while (iVar2 != 0)
            {
                FUN_007f3980(iVar1, iVar2);

                if (local_8[0] == 0)
                {
                    FUN_007f3730(
                        iVar1,
                        reinterpret_cast<std::uintptr_t>(&FUN_10001980),
                        iVar1);
                    return iVar1;
                }

                local_8[0] = local_8[0] + -1;
                iVar2 = FUN_00730e60(param_1);
            }

            FUN_007f3730(iVar1, static_cast<std::uintptr_t>(0x730e50), 0);
            FUN_007f36a0(iVar1);
        }

        return 0;
    }

    return 0;
}