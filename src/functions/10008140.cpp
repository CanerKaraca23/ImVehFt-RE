#include <cstdint>

extern "C" {
    extern std::int32_t DAT_1003c1f4;
    extern char DAT_1003a6c8[0x200];
    extern char DAT_1003a8c8[];
    extern char DAT_1003bc80[];
    extern std::int32_t DAT_1003aac8;
    extern std::uint32_t DAT_1003c208[0x10];
    extern std::uint32_t DAT_1003bbb4;
    extern std::uint32_t DAT_1003bc7c;
    extern std::uint32_t DAT_1003bc1c;
    extern std::uint32_t DAT_1003bc08;
    extern std::uint16_t DAT_1003bd8c;
    extern std::uint32_t DAT_1003c1f8;

    extern const std::uint32_t s_tyrewall_dirt_1_100249a8[4];

    int strcpy_s(char* destination, std::uint32_t destination_size,
                  const char* source);
    int strcat_s(char* destination, std::uint32_t destination_size,
                  const char* source);
    int _sprintf(char* buffer, const char* format, ...);

    extern "C" void __cdecl FUN_100014c0(const char* message);
    std::uint32_t __cdecl FUN_10001b90(const char* pattern, void* callback);
    void __stdcall FUN_10001350(void);

    void __cdecl FUN_0x5d5bc0(void);

    std::uint32_t __cdecl FUN_0x7cf9b0(
        const char* path,
        const char* log_format,
        const char* texture_name,
        std::int32_t texture_count);

    void __cdecl FUN_0x8042c0(
        std::uint32_t texture,
        std::int32_t parameter,
        std::uint32_t* value_1,
        std::uint32_t* value_2,
        std::uint32_t* value_3,
        std::uint32_t* value_4);

    std::uint32_t __cdecl FUN_0x7fb230(
        std::uint32_t value_1,
        std::uint32_t value_2,
        std::uint32_t value_3,
        std::uint32_t value_4);

    void __cdecl FUN_0x804290(
        std::uint32_t destination,
        std::uint32_t source);

    void __cdecl FUN_0x802740(std::uint32_t texture);

    std::uint32_t __cdecl FUN_0x7f37c0(std::uint32_t value);

    extern void* FUN_10003810;
    extern void* FUN_10001040;
}

std::uint32_t __stdcall FUN_10008140()
{
    struct TextureObject
    {
        std::uint8_t field_00[0x10];

        union
        {
            char name[0x20];

            struct
            {
                std::uint32_t field_10;
                std::uint32_t field_14;
                std::uint32_t field_18;
                std::uint32_t field_1c;
            } metadata;
        };

        std::uint8_t field_30[0x20];
        std::uint32_t field_50;
    };

    std::int32_t iVar1;
    std::int32_t iVar2;
    std::uint32_t uVar3;
    std::int32_t iVar4;
    std::uint32_t uVar5;
    const char* pcVar6;
    const char* pcVar7;
    char local_7c[100];
    std::uint32_t local_18;
    std::uint32_t local_14;
    std::uint32_t local_10;
    std::uint32_t local_c;
    std::uint32_t local_8;

    DAT_1003c1f4 = 1;
    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\grunge\\vehiclegrunge256.png");

    iVar2 = 0;
    do
    {
        pcVar6 = DAT_1003a6c8 + iVar2;
        DAT_1003bc80[iVar2] = *pcVar6;
        iVar2 = iVar2 + 1;
    } while (*pcVar6 != '\0');

    reinterpret_cast<void (__cdecl*)()>(0x5d5bc0)();

    DAT_1003c1f4 = 2;
    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\grunge\\vehiclegrunge512.png");

    iVar2 = 0;
    do
    {
        pcVar6 = DAT_1003a6c8 + iVar2;
        DAT_1003bc80[iVar2] = *pcVar6;
        iVar2 = iVar2 + 1;
    } while (*pcVar6 != '\0');

    reinterpret_cast<void (__cdecl*)()>(0x5d5bc0)();

    DAT_1003c1f4 = 3;
    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\grunge\\vehiclegrunge_iv.png");

    iVar2 = 0;
    do
    {
        pcVar6 = DAT_1003a6c8 + iVar2;
        DAT_1003bc80[iVar2] = *pcVar6;
        iVar2 = iVar2 + 1;
    } while (*pcVar6 != '\0');

    reinterpret_cast<void (__cdecl*)()>(0x5d5bc0)();

    iVar2 = 0;
    do
    {
        strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
        strcat_s(DAT_1003a6c8, 0x200,
                  "ImVehFt\\tyres\\tyrewall_dirt_%d.png");

        iVar1 = iVar2 + 1;
        _sprintf(local_7c, DAT_1003a6c8, iVar1);

        DAT_1003aac8 = DAT_1003aac8 + 1;
        pcVar7 = "_tyre";
        pcVar6 = "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d";
        iVar4 = DAT_1003aac8;

        FUN_100014c0("____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");

        uVar3 = reinterpret_cast<std::uint32_t (__cdecl*)(
            char*, const char*, const char*, std::int32_t)>(0x7cf9b0)(
                local_7c, pcVar6, pcVar7, iVar4);

        reinterpret_cast<void (__cdecl*)(
            std::uint32_t, std::int32_t,
            std::uint32_t*, std::uint32_t*,
            std::uint32_t*, std::uint32_t*)>(0x8042c0)(
                uVar3, 4, &local_14, &local_10, &local_c, &local_8);

        local_18 = reinterpret_cast<std::uint32_t (__cdecl*)(
            std::uint32_t, std::uint32_t,
            std::uint32_t, std::uint32_t)>(0x7fb230)(
                local_14, local_10, local_c, local_8);

        reinterpret_cast<void (__cdecl*)(
            std::uint32_t, std::uint32_t)>(0x804290)(local_18, uVar3);
        reinterpret_cast<void (__cdecl*)(
            std::uint32_t)>(0x802740)(uVar3);

        iVar4 = reinterpret_cast<std::int32_t (__cdecl*)(
            std::uint32_t)>(0x7f37c0)(local_18);

        auto* texture = reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar4));

        strcpy_s(texture->name, 0x20, "_tyre");

        DAT_1003c208[iVar2] = iVar4;
        texture->field_50 = 2;

        iVar2 = DAT_1003c208[iVar2];

        texture = reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar2));

        texture->metadata.field_10 =
            s_tyrewall_dirt_1_100249a8[0];
        texture->metadata.field_14 =
            s_tyrewall_dirt_1_100249a8[1];
        texture->metadata.field_18 =
            s_tyrewall_dirt_1_100249a8[2];
        texture->metadata.field_1c =
            s_tyrewall_dirt_1_100249a8[3];

        iVar2 = iVar1;
    } while (iVar1 < 0x10);

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\shadows\\headlight_s.png");

    DAT_1003aac8 = DAT_1003aac8 + 1;
    pcVar7 = "IVF_texHeadlightS";
    pcVar6 = "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d";
    iVar2 = DAT_1003aac8;

    FUN_100014c0("____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");

    uVar3 = reinterpret_cast<std::uint32_t (__cdecl*)(
        char*, const char*, const char*, std::int32_t)>(0x7cf9b0)(
            DAT_1003a6c8, pcVar6, pcVar7, iVar2);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::int32_t,
        std::uint32_t*, std::uint32_t*,
        std::uint32_t*, std::uint32_t*)>(0x8042c0)(
            uVar3, 4, &local_c, &local_10, &local_14, &local_18);

    uVar5 = reinterpret_cast<std::uint32_t (__cdecl*)(
        std::uint32_t, std::uint32_t,
        std::uint32_t, std::uint32_t)>(0x7fb230)(
            local_c, local_10, local_14, local_18);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::uint32_t)>(0x804290)(uVar5, uVar3);
    reinterpret_cast<void (__cdecl*)(
        std::uint32_t)>(0x802740)(uVar3);

    iVar2 = reinterpret_cast<std::int32_t (__cdecl*)(
        std::uint32_t)>(0x7f37c0)(uVar5);

    strcpy_s(
        reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar2))->name,
        0x20,
        "IVF_texHeadlightS");

    DAT_1003bbb4 = iVar2;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\shadows\\headlight_l.png");

    DAT_1003aac8 = DAT_1003aac8 + 1;
    pcVar7 = "IVF_texHeadlightL";
    pcVar6 = "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d";
    iVar2 = DAT_1003aac8;

    FUN_100014c0("____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");

    uVar3 = reinterpret_cast<std::uint32_t (__cdecl*)(
        char*, const char*, const char*, std::int32_t)>(0x7cf9b0)(
            DAT_1003a6c8, pcVar6, pcVar7, iVar2);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::int32_t,
        std::uint32_t*, std::uint32_t*,
        std::uint32_t*, std::uint32_t*)>(0x8042c0)(
            uVar3, 4, &local_c, &local_10, &local_14, &local_18);

    uVar5 = reinterpret_cast<std::uint32_t (__cdecl*)(
        std::uint32_t, std::uint32_t,
        std::uint32_t, std::uint32_t)>(0x7fb230)(
            local_c, local_10, local_14, local_18);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::uint32_t)>(0x804290)(uVar5, uVar3);
    reinterpret_cast<void (__cdecl*)(
        std::uint32_t)>(0x802740)(uVar3);

    iVar2 = reinterpret_cast<std::int32_t (__cdecl*)(
        std::uint32_t)>(0x7f37c0)(uVar5);

    strcpy_s(
        reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar2))->name,
        0x20,
        "IVF_texHeadlightL");

    DAT_1003bc7c = iVar2;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\shadows\\taillight.png");

    DAT_1003aac8 = DAT_1003aac8 + 1;
    pcVar7 = "IVF_texTaillight";
    pcVar6 = "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d";
    iVar2 = DAT_1003aac8;

    FUN_100014c0("____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");

    uVar3 = reinterpret_cast<std::uint32_t (__cdecl*)(
        char*, const char*, const char*, std::int32_t)>(0x7cf9b0)(
            DAT_1003a6c8, pcVar6, pcVar7, iVar2);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::int32_t,
        std::uint32_t*, std::uint32_t*,
        std::uint32_t*, std::uint32_t*)>(0x8042c0)(
            uVar3, 4, &local_c, &local_10, &local_14, &local_18);

    uVar5 = reinterpret_cast<std::uint32_t (__cdecl*)(
        std::uint32_t, std::uint32_t,
        std::uint32_t, std::uint32_t)>(0x7fb230)(
            local_c, local_10, local_14, local_18);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::uint32_t)>(0x804290)(uVar5, uVar3);
    reinterpret_cast<void (__cdecl*)(
        std::uint32_t)>(0x802740)(uVar3);

    iVar2 = reinterpret_cast<std::int32_t (__cdecl*)(
        std::uint32_t)>(0x7f37c0)(uVar5);

    strcpy_s(
        reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar2))->name,
        0x20,
        "IVF_texTaillight");

    DAT_1003bc1c = iVar2;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\shadows\\backfire.png");

    DAT_1003aac8 = DAT_1003aac8 + 1;
    pcVar7 = "IVF_texBackfire";
    pcVar6 = "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d";
    iVar2 = DAT_1003aac8;

    FUN_100014c0("____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");

    uVar3 = reinterpret_cast<std::uint32_t (__cdecl*)(
        char*, const char*, const char*, std::int32_t)>(0x7cf9b0)(
            DAT_1003a6c8, pcVar6, pcVar7, iVar2);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::int32_t,
        std::uint32_t*, std::uint32_t*,
        std::uint32_t*, std::uint32_t*)>(0x8042c0)(
            uVar3, 4, &local_c, &local_10, &local_14, &local_18);

    uVar5 = reinterpret_cast<std::uint32_t (__cdecl*)(
        std::uint32_t, std::uint32_t,
        std::uint32_t, std::uint32_t)>(0x7fb230)(
            local_c, local_10, local_14, local_18);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::uint32_t)>(0x804290)(uVar5, uVar3);
    reinterpret_cast<void (__cdecl*)(
        std::uint32_t)>(0x802740)(uVar3);

    iVar2 = reinterpret_cast<std::int32_t (__cdecl*)(
        std::uint32_t)>(0x7f37c0)(uVar5);

    strcpy_s(
        reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar2))->name,
        0x20,
        "IVF_texBackfire");

    DAT_1003bc08 = iVar2;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\shadows\\pointlight.png");

    DAT_1003aac8 = DAT_1003aac8 + 1;
    pcVar7 = "IVF_texPointlight";
    pcVar6 = "____LOADED_TEXTURE %s, TEXTURES_LOADED: %d";
    iVar2 = DAT_1003aac8;

    FUN_100014c0("____LOADED_TEXTURE %s, TEXTURES_LOADED: %d");

    uVar3 = reinterpret_cast<std::uint32_t (__cdecl*)(
        char*, const char*, const char*, std::int32_t)>(0x7cf9b0)(
            DAT_1003a6c8, pcVar6, pcVar7, iVar2);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::int32_t,
        std::uint32_t*, std::uint32_t*,
        std::uint32_t*, std::uint32_t*)>(0x8042c0)(
            uVar3, 4, &local_c, &local_10, &local_14, &local_18);

    uVar5 = reinterpret_cast<std::uint32_t (__cdecl*)(
        std::uint32_t, std::uint32_t,
        std::uint32_t, std::uint32_t)>(0x7fb230)(
            local_c, local_10, local_14, local_18);

    reinterpret_cast<void (__cdecl*)(
        std::uint32_t, std::uint32_t)>(0x804290)(uVar5, uVar3);
    reinterpret_cast<void (__cdecl*)(
        std::uint32_t)>(0x802740)(uVar3);

    iVar2 = reinterpret_cast<std::int32_t (__cdecl*)(
        std::uint32_t)>(0x7f37c0)(uVar5);

    strcpy_s(
        reinterpret_cast<TextureObject*>(
            static_cast<std::uintptr_t>(iVar2))->name,
        0x20,
        "IVF_texPointlight");

    DAT_1003bd8c = 0;
    DAT_1003c1f8 = iVar2;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\eml\\*.eml");
    FUN_10001b90(DAT_1003a6c8, FUN_10003810);

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(DAT_1003a6c8, 0x200,
              "ImVehFt\\colors\\*.ivfc");
    FUN_10001b90(DAT_1003a6c8, FUN_10001040);

    FUN_10001350();
    return 1;
}