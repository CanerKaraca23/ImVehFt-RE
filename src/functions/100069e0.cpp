#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" void __fastcall FUN_10006790(std::int32_t param_1);

extern "C" void __cdecl FUN_100069e0(std::int32_t param_1)
{
    std::int32_t iVar1;
    std::int32_t iVar2;
    std::int32_t iVar3;
    std::int32_t iVar4;

    iVar2 = DAT_1003c248;
    iVar3 = FUN_10009360();
    iVar3 = *reinterpret_cast<std::int32_t*>(iVar3 + 0x48);

    iVar1 = *reinterpret_cast<std::int32_t*>(
        iVar3 + ((param_1 - *_DAT_00b74494) / 0xA18) * 4);

    iVar4 = 0;
    do
    {
        if (*reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(iVar1 + iVar2 + 0x28) +
                0x4A0 + iVar4) != 0)
        {
            FUN_10006790(iVar3);
        }

        iVar4 = iVar4 + 0x18;
    } while (iVar4 < 0x48);
}