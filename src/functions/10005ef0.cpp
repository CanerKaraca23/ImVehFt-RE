#include <cstdint>
#include "gta_sa_address_access.hpp"

extern std::uintptr_t DAT_1003759c;
extern double DAT_10024f58;
extern double DAT_10024f48;
extern float DAT_10024f50;
extern float DAT_10024f28;
extern double DAT_10024ee0;
extern float DAT_10024ed8;
extern double DAT_10024eb0;
extern float DAT_10024f3c;
extern float DAT_10024f40;
extern std::uint32_t DAT_10024ec8;
extern std::uint32_t DAT_1003bc1c;

using FUN_0054eef0_t = void(__cdecl*)(float*, int, std::uint32_t, float*);
using FUN_007000e0_t = void(__cdecl*)(
    int, float, float, float, float, float, float, float, float,
    int, int, int, int, int);

extern "C" long double __stdcall FUN_10008d20();

extern "C" void __fastcall FUN_100073f0(
    void*, std::uint32_t, void*, float, float, float,
    std::uint32_t, std::uint32_t);

extern "C" void __cdecl FUN_10005ef0(std::uint32_t param_1)
{
    const auto FUN_0054eef0 = reinterpret_cast<FUN_0054eef0_t>(
        static_cast<std::uintptr_t>(0x0054eef0));
    const auto FUN_007000e0 = reinterpret_cast<FUN_007000e0_t>(
        static_cast<std::uintptr_t>(0x007000e0));

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

    float local_a[3];
    float local_b[3];
    local_a[0] = -*pfVar4;
    local_a[1] = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x10);
    local_a[2] = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x14);

    FUN_0054eef0(local_a, 1, uVar6, pfVar4);

    local_b[0] = -*pfVar4;
    local_b[1] = static_cast<float>(static_cast<double>(*reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x10)) - DAT_10024f58);
    local_b[2] = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x14);

    FUN_0054eef0(local_b, 1, uVar6, local_b);

    local_b[0] = local_b[0] - local_a[0];
    local_b[1] = local_b[1] - local_a[1];
    local_b[2] = local_b[2] - local_a[2];

    FUN_007000e0(
        1,
        local_a[0],
        local_a[1],
        local_a[2],
        local_b[0],
        local_b[1],
        local_b[2],
        DAT_10024f50,
        DAT_10024f28,
        0,
        0,
        0,
        0,
        0);

    local_a[0] = -*pfVar4;
    local_a[1] = static_cast<float>(static_cast<double>(*reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x10)) - DAT_10024f48);
    local_a[2] = *reinterpret_cast<float*>(
        static_cast<std::uintptr_t>(iVar1) + 0x14);

    FUN_0054eef0(local_a, 1, uVar6, local_a);

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

    float fVar2 = IMVEHFT_GLOBAL_AT(float, 0x00c812a8);
    if (IMVEHFT_GLOBAL_AT(float, 0x00c812a8) < DAT_10024ee0)
    {
        fVar2 = DAT_10024ed8;
    }

    const std::int32_t signed_color =
        static_cast<std::int8_t>(param_1 >> 24);
    std::int32_t local_8;
    std::uint16_t saved_fpu_control_word;
    std::uint16_t truncating_fpu_control_word;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm
    {
        fld fVar2
        fild signed_color
        fnstcw saved_fpu_control_word
        mov ax, saved_fpu_control_word
        or ax, 0c00h
        mov truncating_fpu_control_word, ax
        fmulp st(1), st(0)
        fmul qword ptr DAT_10024eb0
        fldcw truncating_fpu_control_word
        fistp local_8
        fldcw saved_fpu_control_word
    }
#else
#error "Ghidra-observed x87 truncation requires MSVC x86"
#endif

    const std::uint8_t uVar3 =
        static_cast<std::uint8_t>(local_8);

    float angle;
    std::uintptr_t extraout_ECX;
    __asm
    {
        mov eax, in_EAX
        call FUN_10008d20
        mov extraout_ECX, ecx
        fstp angle
    }

    FUN_100073f0(
        reinterpret_cast<void*>(extraout_ECX & 0xffffff00u),
        static_cast<std::uint32_t>(
            (reinterpret_cast<std::uintptr_t>(local_a) & 0xffffff00u) |
            uVar3),
        local_a,
        DAT_10024f3c,
        DAT_10024f40,
        angle,
        DAT_10024ec8,
        DAT_1003bc1c);
}
