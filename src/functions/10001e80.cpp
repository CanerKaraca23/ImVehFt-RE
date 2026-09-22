#include <cstddef>
#include <cstdint>

extern std::uint32_t DAT_1003bd98;
extern char DAT_1003a6c8[0x200];
extern char DAT_1003a8c8[];
extern char DAT_10024424[];
extern std::uint32_t DAT_1003bbb0;
extern int** _DAT_00c97c28;

extern "C" std::uint32_t __cdecl FUN_007ee4f0();
extern "C" std::uint32_t __cdecl FUN_007f0410();
extern "C" void __cdecl FUN_00804ef0(std::uint32_t, std::uint32_t);
extern "C" void __cdecl FUN_007ee3a0(std::uint32_t, int);

extern "C" int __cdecl strcpy_s(char*, std::size_t, const char*);
extern "C" int __cdecl strcat_s(char*, std::size_t, const char*);

extern "C" int __stdcall D3DXCompileShaderFromFileA(
    const char*,
    const void*,
    const void*,
    const char*,
    const char*,
    std::uint32_t,
    int**,
    int**,
    void*);

extern "C" int __stdcall MessageBoxA(
    void*,
    const char*,
    const char*,
    std::uint32_t);

extern "C" void __stdcall FUN_10001e80()
{
    std::uint32_t uVar1;
    int iVar2;
    const char* lpText;
    int* piVar3;
    std::uint32_t uType;
    std::uint8_t local_10[4];
    int* local_c;
    int* local_8;

    DAT_1003bd98 = FUN_007ee4f0();

    uVar1 = FUN_007f0410();
    FUN_00804ef0(DAT_1003bd98, uVar1);
    FUN_007ee3a0(DAT_1003bd98, 2);

    local_8 = nullptr;

    strcpy_s(DAT_1003a6c8, 0x200, DAT_1003a8c8);
    strcat_s(
        DAT_1003a6c8,
        0x200,
        "ImVehFt\\effect\\dirt_layer.fx");

    iVar2 = D3DXCompileShaderFromFileA(
        DAT_1003a6c8,
        nullptr,
        nullptr,
        DAT_10024424,
        "ps_2_0",
        1,
        &local_c,
        &local_8,
        local_10);

    if (local_8 != nullptr)
    {
        uType = 0;
        piVar3 = local_8;

        lpText =
            reinterpret_cast<const char* (__thiscall*)(int*, int, int)>(
                (*reinterpret_cast<std::uintptr_t**>(local_8))[3])(
                    local_8,
                    0,
                    0);

        MessageBoxA(
            nullptr,
            lpText,
            reinterpret_cast<const char*>(piVar3),
            uType);

        reinterpret_cast<void (__thiscall*)(int*)>(
            (*reinterpret_cast<std::uintptr_t**>(local_8))[2])(
                local_8);
    }

    piVar3 = *_DAT_00c97c28;

    if (iVar2 < 0)
    {
        MessageBoxA(
            nullptr,
            "ImVehFtDecals::Initialise: D3DXCreateEffectFromFile() - FAILED",
            nullptr,
            0);
        return;
    }

    iVar2 = reinterpret_cast<int>(*_DAT_00c97c28);

    uVar1 =
        reinterpret_cast<std::uint32_t (__thiscall*)(int*, std::uint32_t*)>(
            (*reinterpret_cast<std::uintptr_t**>(local_c))[3])(
                local_c,
                &DAT_1003bbb0);

    iVar2 =
        reinterpret_cast<int (__thiscall*)(int*, std::uint32_t)>(
            (*reinterpret_cast<std::uintptr_t**>(piVar3))[106])(
                piVar3,
                uVar1);

    if (iVar2 < 0)
    {
        MessageBoxA(
            nullptr,
            "ImVehFtDecals::Initialise: Failed to create pixel shader",
            nullptr,
            0);
        return;
    }

    reinterpret_cast<void (__thiscall*)(int*)>(
        (*reinterpret_cast<std::uintptr_t**>(local_c))[2])(
            local_c);
}