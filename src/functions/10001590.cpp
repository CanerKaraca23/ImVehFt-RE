#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_100014c0(char*);
extern "C" int __cdecl FUN_10001590(unsigned int param_1)
{
    char* unaff_EBX;
    __asm mov unaff_EBX, ebx
    struct TextureRecord
    {
        unsigned char reserved_00[0x10];
        char texture_name[0x20];
    };

    extern unsigned int DAT_1003aac8;


    extern int __cdecl strcpy_s(char*, unsigned int, const char*);

    unsigned int uVar1;
    unsigned int uVar2;
    int iVar3;
    unsigned int local_14;
    unsigned int local_10;
    unsigned int local_c;
    unsigned int local_8;

    DAT_1003aac8 = DAT_1003aac8 + 1;
    FUN_100014c0(const_cast<char*>(
        "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d"));

    uVar1 = reinterpret_cast<unsigned int (*)(unsigned int)>(
        0x7cf9b0)(param_1);

    reinterpret_cast<void (*)(unsigned int, unsigned int,
                              unsigned int*, unsigned int*,
                              unsigned int*, unsigned int*)>(
        0x8042c0)(
        uVar1,
        4,
        &local_14,
        &local_10,
        &local_c,
        &local_8);

    uVar2 = reinterpret_cast<unsigned int (*)(
        unsigned int,
        unsigned int,
        unsigned int,
        unsigned int)>(
        0x7fb230)(
        local_14,
        local_10,
        local_c,
        local_8);

    reinterpret_cast<void (*)(unsigned int, unsigned int)>(
        0x804290)(uVar2, uVar1);

    reinterpret_cast<void (*)(unsigned int)>(
        0x802740)(uVar1);

    iVar3 = reinterpret_cast<int (*)(unsigned int)>(
        0x7f37c0)(uVar2);

    strcpy_s(
        reinterpret_cast<TextureRecord*>(
            static_cast<unsigned int>(iVar3))->texture_name,
        0x20,
        unaff_EBX);

    return iVar3;
}