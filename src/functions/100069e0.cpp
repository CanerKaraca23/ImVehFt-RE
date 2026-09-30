#include <cstdint>
#include "gta_sa_address_access.hpp"

extern std::int32_t DAT_1003c248;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" void __cdecl FUN_10006790(std::int32_t param_1);

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
        iVar3 + ((param_1 - IMVEHFT_VEHICLE_OBJECTS_BASE_B74494) / 0xA18) * 4);

    iVar4 = 0;
    do
    {
        auto* const callback_record = reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar1 + iVar2 + 0x28) +
            0x4A0 + iVar4);
        if (*callback_record != 0)
        {
            __asm {
                push ebx
                mov ebx, callback_record
                mov eax, param_1
                push eax
                call FUN_10006790
                add esp, 4
                pop ebx
            }
        }

        iVar4 = iVar4 + 0x18;
    } while (iVar4 < 0x48);
}
