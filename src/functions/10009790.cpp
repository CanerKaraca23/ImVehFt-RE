#include <cstdint>

extern std::uint8_t LAB_100098e0;
extern std::uint8_t LAB_100098f0;
extern std::uint8_t LAB_10009900;
extern std::uint8_t LAB_10009910;
extern std::uint8_t LAB_10009920;
extern std::uint8_t LAB_10009930;
extern std::uint8_t LAB_10009940;
extern std::uint8_t LAB_10009950;
extern std::uint8_t LAB_10009960;
extern std::uint8_t LAB_10009970;
extern std::uint8_t LAB_10009980;
extern std::uint8_t LAB_10009990;
extern std::uint8_t LAB_100099a0;
extern std::uint8_t LAB_100099b0;
extern std::uint8_t LAB_100099c0;
extern std::uint8_t LAB_100099d0;

using UpdateFn = void (__thiscall*)(void*, std::int32_t, std::int32_t);

void __fastcall FUN_10009790(std::int32_t param_1)
{
    const std::int32_t iVar1 = param_1 + 4;

    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_100098e0, iVar1, 0);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_100098f0, iVar1, 1);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009900, iVar1, 2);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009910, iVar1, 3);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009920, iVar1, 4);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009930, iVar1, 5);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009940, iVar1, 6);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009950, iVar1, 7);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009960, iVar1, 8);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009970, iVar1, 9);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009980, iVar1, 10);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_10009990, iVar1, 0xB);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_100099a0, iVar1, 0xC);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_100099b0, iVar1, 0xD);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_100099c0, iVar1, 0xE);
    reinterpret_cast<UpdateFn>(static_cast<std::uintptr_t>(0x10009610))(&LAB_100099d0, iVar1, 0xF);
}