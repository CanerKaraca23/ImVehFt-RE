#include <cstdint>

struct localeinfo_struct;

using LocaleUpdateCtor = void(__thiscall*)(
    void* self,
    localeinfo_struct* locale);

extern "C" int __cdecl x_ismbbtype_l(
    localeinfo_struct* param_1,
    std::uint32_t param_2,
    int param_3,
    int param_4)
{
    std::uint8_t update[0x10];
    std::uint32_t uVar1;
    int iVar2;

    // Ghidra 0x1001aa5d: ECX=update, pushed param_1, CALL 0x10010b1a.
    reinterpret_cast<LocaleUpdateCtor>(0x10010b1a)(update, param_1);

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