#include <cstddef>
#include <cstdint>

struct TextureBytes
{
    std::uint8_t field_50_byte;
    std::uint8_t field_51;
    std::uint8_t reserved_52[2];
};

struct Texture
{
    std::uint32_t field_00;
    std::uint8_t reserved_04[0x4c];

    union
    {
        std::uint32_t field_50;
        TextureBytes bytes;
    };
};

static_assert(offsetof(Texture, field_00) == 0x00);
static_assert(offsetof(Texture, field_50) == 0x50);
static_assert(sizeof(TextureBytes) == 4);
static_assert(offsetof(Texture, bytes) + offsetof(TextureBytes, field_51) == 0x51);

extern "C" void __cdecl FUN_100014c0(char*);
extern "C" int __cdecl FUN_10001590(std::uint32_t);
extern "C" int __cdecl strcpy_s(char*, std::size_t, char*);
extern "C" int __cdecl strcat_s(char*, std::size_t, char*);

extern char DAT_1003a6c8[0x200];
extern char DAT_1003a8c8[];

extern Texture* _DAT_00c3ef5c;
extern Texture* _DAT_00c3ef60;
extern Texture* _DAT_00c3ef64;
extern Texture* _DAT_00c3ef68;
extern Texture* _DAT_00c3ef78;

extern Texture* DAT_1003bd9c;
extern Texture* DAT_1003bda0;
extern Texture* DAT_1003bda4;

void __stdcall FUN_10003ba0()
{
    FUN_100014c0(const_cast<char*>("Loading HD plates textures..."));

    reinterpret_cast<void(__cdecl*)(Texture*)>(
        static_cast<std::uintptr_t>(0x7f3820))(_DAT_00c3ef5c);
    reinterpret_cast<void(__cdecl*)(Texture*)>(
        static_cast<std::uintptr_t>(0x7f3820))(_DAT_00c3ef60);
    reinterpret_cast<void(__cdecl*)(Texture*)>(
        static_cast<std::uintptr_t>(0x7f3820))(_DAT_00c3ef64);
    reinterpret_cast<void(__cdecl*)(Texture*)>(
        static_cast<std::uintptr_t>(0x7f3820))(_DAT_00c3ef68);

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\platecharset.png"));

    _DAT_00c3ef5c = reinterpret_cast<Texture*>(
        FUN_10001590(reinterpret_cast<std::uint32_t>(DAT_1003a6c8)));

    _DAT_00c3ef5c->field_50 = 3;
    _DAT_00c3ef5c->bytes.field_51 = 0x33;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\plateback1"));

    int iVar1 = reinterpret_cast<int(__cdecl*)(char*)>(
        static_cast<std::uintptr_t>(0x820a10))(DAT_1003a6c8);

    FUN_100014c0(const_cast<char*>("Loaded plateback1.dds..."));
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x50) = 4;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x51) = 0x33;
    _DAT_00c3ef60 = reinterpret_cast<Texture*>(
        static_cast<std::uintptr_t>(iVar1));

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\plateback2"));

    iVar1 = reinterpret_cast<int(__cdecl*)(char*)>(
        static_cast<std::uintptr_t>(0x820a10))(DAT_1003a6c8);

    FUN_100014c0(const_cast<char*>("Loaded plateback2.dds..."));
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x50) = 4;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x51) = 0x33;
    _DAT_00c3ef64 = reinterpret_cast<Texture*>(
        static_cast<std::uintptr_t>(iVar1));

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\plateback3"));

    iVar1 = reinterpret_cast<int(__cdecl*)(char*)>(
        static_cast<std::uintptr_t>(0x820a10))(DAT_1003a6c8);

    FUN_100014c0(const_cast<char*>("Loaded plateback3.dds..."));
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x50) = 4;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x51) = 0x33;
    _DAT_00c3ef68 = reinterpret_cast<Texture*>(
        static_cast<std::uintptr_t>(iVar1));

    _DAT_00c3ef78 = reinterpret_cast<Texture*>(
        reinterpret_cast<Texture*(__cdecl*)(std::uint32_t, int, int)>(
            static_cast<std::uintptr_t>(0x7fb2d0))(
            _DAT_00c3ef5c->field_00,
            0,
            2));

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\plateback1_l"));

    iVar1 = reinterpret_cast<int(__cdecl*)(char*)>(
        static_cast<std::uintptr_t>(0x820a10))(DAT_1003a6c8);

    FUN_100014c0(const_cast<char*>("Loaded plateback1_l.dds..."));
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x50) = 4;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x51) = 0x33;
    DAT_1003bd9c = reinterpret_cast<Texture*>(
        static_cast<std::uintptr_t>(iVar1));

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\plateback1_l"));

    iVar1 = reinterpret_cast<int(__cdecl*)(char*)>(
        static_cast<std::uintptr_t>(0x820a10))(DAT_1003a6c8);

    FUN_100014c0(const_cast<char*>("Loaded plateback2_l.dds..."));
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x50) = 4;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x51) = 0x33;
    DAT_1003bda0 = reinterpret_cast<Texture*>(
        static_cast<std::uintptr_t>(iVar1));

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        const_cast<char*>("ImVehFt\\plates\\plateback1_l"));

    iVar1 = reinterpret_cast<int(__cdecl*)(char*)>(
        static_cast<std::uintptr_t>(0x820a10))(DAT_1003a6c8);

    FUN_100014c0(const_cast<char*>("Loaded plateback3_l.dds..."));
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x50) = 4;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar1) + 0x51) = 0x33;
    DAT_1003bda4 = reinterpret_cast<Texture*>(
        static_cast<std::uintptr_t>(iVar1));
}