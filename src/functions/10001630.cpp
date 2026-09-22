#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
#include <cstddef>
#include <cstdint>
#include <windows.h>
extern "C" void __cdecl FUN_100014c0(char*);
#include <cstddef>
#include <cstdint>
#include <windows.h>

struct PNG_Image;
extern PNG_Image PNG_10029f68;
extern "C" int __cdecl strcpy_s(char*, std::size_t, const char*);

extern "C" int __stdcall FUN_10001630(void)
{
    struct TextureRecord
    {
        std::uint8_t reserved_00[0x10];
        char texture_name[0x20];
    };

    using FUN_007cf9b0_t =
        std::uint32_t(__cdecl *)(PNG_Image**, char*, char*, int);
    using FUN_008042c0_t =
        void(__cdecl *)(std::uint32_t, std::uint32_t,
                        std::uint32_t*, std::uint32_t*,
                        std::uint32_t*, std::uint32_t*);
    using FUN_007fb230_t =
        std::uint32_t(__cdecl *)(std::uint32_t, std::uint32_t,
                                 std::uint32_t, std::uint32_t);
    using FUN_00804290_t =
        void(__cdecl *)(std::uint32_t, std::uint32_t);
    using FUN_00802740_t =
        void(__cdecl *)(std::uint32_t);
    using FUN_007f37c0_t =
        int(__cdecl *)(std::uint32_t);

    extern unsigned char DAT_007cf9ca;
    extern int DAT_1003aac8;


    const FUN_007cf9b0_t FUN_007cf9b0 =
        reinterpret_cast<FUN_007cf9b0_t>(0x007cf9b0);
    const FUN_008042c0_t FUN_008042c0 =
        reinterpret_cast<FUN_008042c0_t>(0x008042c0);
    const FUN_007fb230_t FUN_007fb230 =
        reinterpret_cast<FUN_007fb230_t>(0x007fb230);
    const FUN_00804290_t FUN_00804290 =
        reinterpret_cast<FUN_00804290_t>(0x00804290);
    const FUN_00802740_t FUN_00802740 =
        reinterpret_cast<FUN_00802740_t>(0x00802740);
    const FUN_007f37c0_t FUN_007f37c0 =
        reinterpret_cast<FUN_007f37c0_t>(0x007f37c0);

    std::uint32_t uVar1;
    std::uint32_t uVar2;
    int iVar3;
    char* pcVar4;
    char* pcVar5;
    PNG_Image* local_24;
    std::uint32_t local_20;
    DWORD local_1c;
    DWORD local_18;
    std::uint32_t local_14;
    std::uint32_t local_10;
    std::uint32_t local_c;
    std::uint32_t local_8;

    VirtualProtect(&DAT_007cf9ca, 1, 0x40, &local_1c);
    DAT_007cf9ca = 3;
    VirtualProtect(&DAT_007cf9ca, 1, local_1c, &local_18);

    DAT_1003aac8 = DAT_1003aac8 + 1;

    pcVar5 = const_cast<char*>("IVF_Logo");
    pcVar4 = const_cast<char*>(
        "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");
    iVar3 = DAT_1003aac8;

    FUN_100014c0(const_cast<char*>(
        "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d"));

    local_24 = &PNG_10029f68;
    local_20 = 0xd528;

    uVar1 = FUN_007cf9b0(&local_24, pcVar4, pcVar5, iVar3);

    FUN_008042c0(
        uVar1,
        4,
        &local_14,
        &local_10,
        &local_c,
        &local_8);

    uVar2 = FUN_007fb230(local_14, local_10, local_c, local_8);
    FUN_00804290(uVar2, uVar1);
    FUN_00802740(uVar1);

    VirtualProtect(&DAT_007cf9ca, 1, 0x40, &local_1c);
    DAT_007cf9ca = 2;
    VirtualProtect(&DAT_007cf9ca, 1, local_1c, &local_18);

    iVar3 = FUN_007f37c0(uVar2);

    strcpy_s(
        reinterpret_cast<TextureRecord*>(iVar3)->texture_name,
        0x20,
        "IVF_Logo");

    return iVar3;
}