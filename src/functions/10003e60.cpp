#include <cstdint>

using Address32 = std::uint32_t;

extern std::uint32_t DAT_007fb2d0(std::int32_t, std::int32_t, std::int32_t);
extern void __cdecl FUN_006fd7c0(std::int32_t*, std::int32_t*);
extern std::uint32_t DAT_007faec0(std::int32_t);

extern std::uint32_t DAT_00c3ef78;

std::uint32_t __cdecl FUN_10003e60(
    std::uint32_t,
    std::int32_t param_2,
    std::uint32_t,
    std::int32_t param_4)
{
    std::uint32_t uVar1;
    std::uint32_t uVar3;
    std::int32_t iVar2;
    std::int32_t iVar4;
    std::int32_t iVar5;
    std::uint32_t uVar6;
    std::int32_t iVar7;
    std::int32_t iStack_10;
    std::int32_t iStack_c;
    std::int32_t iStack_8;
    std::int32_t iStack_4;

    uVar1 = DAT_007fb2d0(param_4, 0, 5);

    if ((uVar1 != 0) &&
        (DAT_00c3ef78 != 0) &&
        ((iStack_8 =
              *reinterpret_cast<std::int32_t*>(
                  static_cast<std::uintptr_t>(
                      static_cast<std::uint32_t>(param_2) + 0x18)),
          iStack_8 != 0)) &&
        ((iStack_4 =
              *reinterpret_cast<std::int32_t*>(
                  static_cast<std::uintptr_t>(
                      static_cast<std::uint32_t>(param_4) + 0x18)),
          iStack_4 != 0)))
    {
        iVar5 = 0;

        do
        {
            iStack_c = 1;
            iStack_10 = 1;

            FUN_006fd7c0(&iStack_c, &iStack_10);

            iVar2 =
                (iStack_10 * 0x100 + iStack_c) * 0x80 +
                static_cast<std::int32_t>(DAT_00c3ef78);

            iVar7 = 0x40;
            uVar6 = uVar1;

            do
            {
                iVar4 = 0;

                do
                {
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(
                            uVar6 + static_cast<std::uint32_t>(iVar4))) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(
                                static_cast<std::uint32_t>(iVar2) +
                                static_cast<std::uint32_t>(iVar4)));

                    iVar4 = iVar4 + 1;
                }
                while (iVar4 < 0x80);

                iVar2 = iVar2 + iStack_8;
                uVar6 = uVar6 + static_cast<std::uint32_t>(iStack_4);
                iVar7 = iVar7 + -1;
            }
            while (iVar7 != 0);

            iVar5 = iVar5 + 1;
            uVar1 = uVar1 + 0x80;
        }
        while (iVar5 < 8);

        uVar3 = DAT_007faec0(param_4);
        return (uVar3 & 0xffffff00u) | 1u;
    }

    return uVar1 & 0xffffff00u;
}