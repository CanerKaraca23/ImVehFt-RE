#include <cstdint>

extern std::uintptr_t DAT_1003759c;
extern float DAT_10024f58;
extern float DAT_10024f48;
extern float DAT_10024f50;
extern float DAT_10024f28;
extern float DAT_10024ee0;
extern float DAT_10024ed8;
extern float DAT_10024eb0;
extern float DAT_00c812a8;
extern float DAT_10024f3c;
extern float DAT_10024f40;
extern std::uint32_t DAT_10024ec8;
extern std::uint32_t DAT_1003bc1c;

extern "C" void __cdecl FUN_0054eef0(
    float*, int, std::uint32_t, float*);

extern "C" void __cdecl FUN_007000e0(
    int, float, float, float, float, float, float,
    float, float, int, int, int, int, int);

extern "C" long double __stdcall FUN_10008d20();

extern "C" void __fastcall FUN_100073f0(
    void*, std::uint32_t, void*, float, float, float,
    std::uint32_t, std::uint32_t);

extern "C" int __cdecl ROUND(float);

extern "C" void __cdecl FUN_10005ef0(std::uint32_t param_1)
{
    std::uintptr_t in_EAX;
    __asm { mov in_EAX, eax }

    const std::uint32_t uVar6 =
        *reinterpret_cast<const std::uint32_t*>(in_EAX + 0x14);

    const std::int32_t iVar1 =
        *reinterpret_cast<const std::int32_t*>(
            *reinterpret_cast<const std::int32_t*>(
                DAT_1003759c +
                static_cast<std::int32_t>(
                    *reinterpret_cast<const std::int16_t*>(in_EAX + 0x22)) * 4) +
            0x5c);

    float* pfVar4 = reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x0c);

    float local_20 = -*pfVar4;
    float local_1c = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x10);
    float local_18 = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x14);

    FUN_0054eef0(&local_20, 1, uVar6, pfVar4);

    float local_14 = -*pfVar4;
    float local_10 = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x10) - DAT_10024f58;
    float local_c = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x14);

    FUN_0054eef0(&local_14, 1, uVar6, &local_14);

    local_14 = local_14 - local_20;
    local_10 = local_10 - local_1c;
    local_c = local_c - local_18;

    FUN_007000e0(
        1,
        local_20,
        local_1c,
        local_18,
        local_14,
        local_10,
        local_c,
        DAT_10024f50,
        DAT_10024f28,
        0,
        0,
        0,
        0,
        0);

    local_20 = -*pfVar4;
    local_1c = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x10) - DAT_10024f48;
    local_18 = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x14);

    FUN_0054eef0(&local_20, 1, uVar6, &local_20);

    std::uintptr_t extraout_ECX;
    __asm { mov extraout_ECX, ecx }

    if (static_cast<std::uint8_t>(param_1) == 0x01)
    {
        param_1 = (param_1 & 0x00ffffffu) | (0x32u << 24);
    }
    else if (static_cast<std::uint8_t>(param_1) == 0x02)
    {
        param_1 = (param_1 & 0x00ffffffu) | (0x14u << 24);
    }
    else if (static_cast<std::uint8_t>(param_1) == 0x03)
    {
        param_1 = (param_1 & 0x00ffffffu) | (0x46u << 24);
    }

    float fVar2 = DAT_00c812a8;
    if (DAT_00c812a8 < DAT_10024ee0)
    {
        fVar2 = DAT_10024ed8;
    }

    const std::int32_t local_8 = ROUND(
        static_cast<float>(
            static_cast<std::int32_t>(
                static_cast<std::uint8_t>(param_1 >> 24))) *
            fVar2 *
            DAT_10024eb0);

    const std::uint8_t uVar3 =
        static_cast<std::uint8_t>(local_8);

    FUN_100073f0(
        reinterpret_cast<void*>(extraout_ECX & 0xffffff00u),
        static_cast<std::uint32_t>(
            (reinterpret_cast<std::uintptr_t>(&local_20) & 0xffffff00u) |
            uVar3),
        &local_20,
        DAT_10024f3c,
        DAT_10024f40,
        static_cast<float>(FUN_10008d20()),
        DAT_10024ec8,
        DAT_1003bc1c);
}