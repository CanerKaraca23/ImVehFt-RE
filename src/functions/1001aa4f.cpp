#include <cstdint>
#include "locale_update_ctor_bridge.hpp"

struct localeinfo_struct;

extern "C" int __cdecl x_ismbbtype_l(
    localeinfo_struct* param_1,
    std::uint32_t param_2,
    int param_3,
    int param_4)
{
    std::uint8_t update[0x10];
    std::uint32_t uVar1;
    int iVar2;

    // Preserve Ghidra's ECX=this / one-stack-argument __thiscall setup.
    __asm {
        lea ecx, update
        push param_1
        call IVF_LocaleUpdate_ctor_relocatable
    }

    if ((*reinterpret_cast<const std::uint8_t*>(
             static_cast<std::uintptr_t>(
                 *reinterpret_cast<const std::uint32_t*>(update + 4)) +
             0x1dU + (param_2 & 0xffU)) &
         static_cast<std::uint8_t>(param_4)) == 0)
    {
        if (param_3 == 0)
        {
            uVar1 = 0;
        }
        else
        {
            uVar1 =
                static_cast<std::uint32_t>(
                    *reinterpret_cast<const std::uint16_t*>(
                        static_cast<std::uintptr_t>(
                            *reinterpret_cast<const std::uint32_t*>(
                                static_cast<std::uintptr_t>(
                                    *reinterpret_cast<const std::uint32_t*>(
                                        update) + 200U))) +
                        (param_2 & 0xffU) * 2U)) &
                static_cast<std::uint32_t>(param_3);
        }

        iVar2 = 0;

        if (uVar1 == 0)
        {
            goto LAB_1001aa93;
        }
    }

    iVar2 = 1;

LAB_1001aa93:
    if (update[12] != '\0')
    {
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(
                *reinterpret_cast<const std::uint32_t*>(update + 8)) +
            0x70U) &= 0xfffffffdU;
    }

    return iVar2;
}
