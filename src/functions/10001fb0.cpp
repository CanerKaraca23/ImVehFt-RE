#include <cstdint>
#include <windows.h>

using undefined1 = std::uint8_t;
using undefined4 = std::uint32_t;
using Address = std::uintptr_t;

struct NestedObject
{
    std::uint8_t padding_00[0x0c];
    std::int32_t member_0c;
    std::uint8_t padding_10[0x04];
    std::int32_t member_10;
};

struct EaxObject
{
    std::uint8_t padding_00[0x0c];
    NestedObject* member_0c;
};

struct InputObject
{
    std::uint8_t padding_00[0x50];
    undefined4 member_50;
};

struct ContextObject
{
    std::uint8_t padding_00[0x60];
    NestedObject* member_60;
    undefined4 member_64;
};

using StateFunction = void(__cdecl*)(int, int);

struct StateInterface
{
    std::uint8_t padding_00[0x20];
    StateFunction member_20;
};

using ContextFunction = void(__thiscall*)(void*, int, void*, int);

struct ContextVTable
{
    std::uint8_t padding_00[0x1b4];
    ContextFunction member_1b4;
};

struct ContextInterface
{
    ContextVTable* vtable;
};

struct PatchSite
{
    std::uint32_t instruction;
    std::uint8_t trailing_byte;
};

extern "C" Address DAT_1003aacc;
extern "C" ContextObject* DAT_1003bd98;
extern "C" Address DAT_1003bbb0;
extern "C" StateInterface* _DAT_00c97b24;
extern "C" ContextInterface* _DAT_00c97c28;
extern "C" Address _DAT_00c1703c;


extern "C" void(__cdecl* FUN_7ee180)(Address);
extern "C" void(__cdecl* FUN_7ee190)(Address);
extern "C" void(__cdecl* FUN_7fdcd0)(undefined4, int);
extern "C" void(__cdecl* FUN_7f9fb0)(int);
extern "C" void(__cdecl* FUN_7f9ff0)(Address);
extern "C" void(__cdecl* FUN_7170c0)(int, int, int, int);
extern "C" void(__cdecl* FUN_4041c0)(int, int, float, float);
extern "C" void(__cdecl* FUN_727be0)(void*, DWORD*);

extern "C" undefined4* __cdecl FUN_10001fb0(undefined4* param_1)
{
    undefined4* in_EAX;
    __asm mov in_EAX, eax
    undefined4* puVar2;
    undefined1 local_1c[16];
    DWORD local_c;
    DWORD local_8;

    if (in_EAX == nullptr)
    {
        puVar2 = nullptr;
    }
    else
    {
        puVar2 = reinterpret_cast<undefined4*>(
            reinterpret_cast<EaxObject*>(
                DAT_1003aacc +
                reinterpret_cast<Address>(in_EAX))->member_0c);
    }

    _DAT_00c97b24->member_20(6, 0);
    _DAT_00c97b24->member_20(8, 0);

    DAT_1003bd98->member_60 =
        reinterpret_cast<NestedObject*>(*puVar2);
    DAT_1003bd98->member_64 = 0;

    FUN_7ee180(_DAT_00c1703c);
    FUN_7ee190(reinterpret_cast<Address>(DAT_1003bd98));

    FUN_7fdcd0(*param_1, 0);
    FUN_7fdcd0(*in_EAX, 1);

    _DAT_00c97c28->vtable->member_1b4(
        _DAT_00c97c28, 0, &local_8, 1);

    auto* patch_81d =
        reinterpret_cast<PatchSite*>(0x007fb81d);
    auto* patch_824 =
        reinterpret_cast<PatchSite*>(0x007fb824);

    VirtualProtect(patch_81d, 5, PAGE_EXECUTE_READWRITE, &local_c);
    patch_81d->instruction = 0x90909090;
    patch_81d->trailing_byte = 0x90;
    VirtualProtect(patch_81d, 5, local_c, &local_8);

    VirtualProtect(patch_824, 5, PAGE_EXECUTE_READWRITE, &local_c);
    patch_824->instruction = 0x90909090;
    patch_824->trailing_byte = 0x90;
    VirtualProtect(patch_824, 5, local_c, &local_8);

    FUN_7f9fb0(0);
    FUN_7f9ff0(DAT_1003bbb0);
    FUN_7170c0(0xff, 0xff, 0xff, 0xff);

    FUN_4041c0(
        0,
        0,
        static_cast<float>(DAT_1003bd98->member_60->member_0c),
        static_cast<float>(DAT_1003bd98->member_60->member_10));

    FUN_727be0(local_1c, &local_8);

    VirtualProtect(patch_81d, 1, PAGE_EXECUTE_READWRITE, &local_c);
    patch_81d->instruction = 0x909090e8;
    VirtualProtect(patch_81d, 1, local_c, &local_8);

    VirtualProtect(
        reinterpret_cast<std::uint8_t*>(patch_81d) + 1,
        4,
        PAGE_EXECUTE_READWRITE,
        &local_c);

    patch_81d->instruction = 0xffe78ee8;
    patch_81d->trailing_byte = 0xff;

    VirtualProtect(
        reinterpret_cast<std::uint8_t*>(patch_81d) + 1,
        4,
        local_c,
        &local_8);

    VirtualProtect(patch_824, 1, PAGE_EXECUTE_READWRITE, &local_c);
    patch_824->instruction = 0x909090e8;
    VirtualProtect(patch_824, 1, local_c, &local_8);

    VirtualProtect(
        reinterpret_cast<std::uint8_t*>(patch_824) + 1,
        4,
        PAGE_EXECUTE_READWRITE,
        &local_c);

    patch_824->instruction = 0xffe7c7e8;
    patch_824->trailing_byte = 0xff;

    VirtualProtect(
        reinterpret_cast<std::uint8_t*>(patch_824) + 1,
        4,
        local_c,
        &local_8);

    FUN_7f9ff0(0);
    FUN_7ee180(reinterpret_cast<Address>(DAT_1003bd98));
    FUN_7ee190(_DAT_00c1703c);

    reinterpret_cast<InputObject*>(puVar2)->member_50 =
        reinterpret_cast<InputObject*>(param_1)->member_50;

    _DAT_00c97b24->member_20(6, 1);
    _DAT_00c97b24->member_20(8, 1);

    return puVar2;
}