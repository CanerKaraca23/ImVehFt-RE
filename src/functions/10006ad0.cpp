#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;

extern "C" std::int32_t __stdcall FUN_10009360();

extern char __cdecl FUN_006c2180(std::uint8_t value);
extern char __cdecl FUN_006c2230(std::uint8_t value);

extern void __cdecl FUN_007f1200(
    std::int32_t value,
    void (*callback)(std::int32_t, std::int32_t),
    std::int32_t enabled);

extern void __cdecl FUN_007f0dc0(
    std::int32_t value,
    void (*callback)(std::int32_t, std::int32_t),
    std::int32_t enabled);

extern "C" void __cdecl FUN_10003fe0(std::int32_t, std::int32_t);
extern "C" void __cdecl FUN_10003fb0(std::int32_t, std::int32_t);

extern "C" void __stdcall FUN_10006ad0()
{
    std::int32_t unaff_EDI;
    __asm mov unaff_EDI, edi
    std::int32_t iVar1 = DAT_1003c248;
    std::int32_t iVar3 = FUN_10009360();

    iVar3 = *reinterpret_cast<std::int32_t*>(
        *reinterpret_cast<std::int32_t*>(iVar3 + 0x48) +
        ((unaff_EDI - *_DAT_00b74494) / 0xa18) * 4);

    std::int32_t iVar5 =
        *reinterpret_cast<std::int32_t*>(unaff_EDI + 0x594);

    if (((iVar5 == 0) || (iVar5 == 1)) || (iVar5 == 0xb))
    {
        std::int32_t local_8 = 0x328;

        do
        {
            std::int32_t* piVar4 = reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(
                    iVar3 + iVar1 + 0x28) +
                local_8);

            if ((*piVar4 != 0) &&
                (static_cast<char>(piVar4[1]) != '\x06'))
            {
                char cVar2 = static_cast<char>(piVar4[1]);

                if (cVar2 == '\0')
                {
                    cVar2 = FUN_006c2180(
                        *reinterpret_cast<std::uint8_t*>(
                            reinterpret_cast<std::uintptr_t>(piVar4) + 5));

                    iVar5 = *piVar4;

                    if (cVar2 != '\0')
                        goto LAB_10006b60;

LAB_10006b9a:
                    FUN_007f1200(iVar5, FUN_10003fe0, 1);
                    FUN_007f0dc0(iVar5, FUN_10003fb0, 1);
                }
                else if (static_cast<std::uint8_t>(cVar2 - 2U) < 3U)
                {
                    cVar2 = FUN_006c2230(
                        *reinterpret_cast<std::uint8_t*>(
                            reinterpret_cast<std::uintptr_t>(piVar4) + 5));

                    iVar5 = *piVar4;

                    if (cVar2 < '\x02')
                        goto LAB_10006b9a;

LAB_10006b60:
                    FUN_007f1200(iVar5, FUN_10003fe0, 0);
                    FUN_007f0dc0(iVar5, FUN_10003fb0, 0);
                }
            }

            local_8 = local_8 + 8;
        }
        while (local_8 < 0x350);
    }
}