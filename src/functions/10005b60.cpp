#include <cstdint>
#include "gta_sa_address_access.hpp"



extern std::uintptr_t DAT_1003759c;
extern double _DAT_10024f58;
extern float _DAT_10024f40;
extern float _DAT_10024f28;
extern double _DAT_10024f48;
extern double _DAT_10024f60;
extern float _DAT_10024f68;
extern double _DAT_10024ee0;
extern float _DAT_10024ed8;
extern std::uint32_t _DAT_10024ec8;
extern std::uint32_t DAT_1003bc1c;

using FUN_0054eef0_t = void(__cdecl*)(float*, int, std::uint32_t, float*);
using FUN_007000e0_t = void(__cdecl*)(
    int, float, float, float, float, float, float, float, float,
    int, int, int, int, int);

extern "C" long double __stdcall FUN_10008d20();

extern "C" void __fastcall FUN_100073f0(
    void*,
    std::uint32_t,
    float*,
    float,
    float,
    float,
    std::uint32_t,
    std::uint32_t);

extern "C" void __cdecl FUN_10005b60(std::uint32_t param_1)
{
    const auto FUN_0054eef0 = reinterpret_cast<FUN_0054eef0_t>(
        static_cast<std::uintptr_t>(0x0054eef0));
    const auto FUN_007000e0 = reinterpret_cast<FUN_007000e0_t>(
        static_cast<std::uintptr_t>(0x007000e0));

    std::uintptr_t in_EAX;
    __asm mov in_EAX, eax
    float local_a[3];
    float local_b[3];
    int local_8;

    const std::uint32_t uVar5 =
        *reinterpret_cast<const std::uint32_t*>(in_EAX + 0x14);

    const int iVar1 =
        *reinterpret_cast<const int*>(
            *reinterpret_cast<const std::uintptr_t*>(
                DAT_1003759c +
                static_cast<std::uint32_t>(
                    *reinterpret_cast<const std::int16_t*>(in_EAX + 0x22)) *
                4) +
            0x5c);

    local_a[0] = 0.0f;
    local_a[1] = *reinterpret_cast<const float*>(iVar1 + 0x10);
    local_a[2] = *reinterpret_cast<const float*>(iVar1 + 0x14);

    FUN_0054eef0(local_a, 1, uVar5, local_a);

    local_b[0] = 0.0f;
    local_b[1] = static_cast<float>(
        static_cast<double>(*reinterpret_cast<const float*>(iVar1 + 0x10)) -
        _DAT_10024f58);
    local_b[2] = *reinterpret_cast<const float*>(iVar1 + 0x14);

    FUN_0054eef0(local_b, 1, uVar5, local_b);

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
        _DAT_10024f40,
        _DAT_10024f28,
        0,
        0,
        1,
        1,
        0);

    local_a[0] = 0.0f;
    local_a[1] = static_cast<float>(
        static_cast<double>(*reinterpret_cast<const float*>(iVar1 + 0x10)) -
        _DAT_10024f48);
    local_a[2] = *reinterpret_cast<const float*>(iVar1 + 0x14);

    FUN_0054eef0(local_a, 1, uVar5, local_a);

    const std::uint8_t selector =
        static_cast<std::uint8_t>(param_1);

    if (selector == 0x01)
    {
        param_1 = (param_1 & 0x00FFFFFFu) | (0x32u << 24);
    }
    else if (selector == 0x02)
    {
        param_1 = (param_1 & 0x00FFFFFFu) | (0x14u << 24);
    }
    else if (selector == 0x03)
    {
        param_1 = (param_1 & 0x00FFFFFFu) | (0x46u << 24);
    }

    float fVar2 = IMVEHFT_GLOBAL_AT(float, 0x00c812a8);
    if (IMVEHFT_GLOBAL_AT(float, 0x00c812a8) < _DAT_10024ee0)
    {
        fVar2 = _DAT_10024ed8;
    }

    const std::int32_t round_input = static_cast<std::int8_t>(param_1 >> 24);
    std::uint16_t original_control_word;
    std::uint16_t truncate_control_word;
    __asm {
        fld     dword ptr [fVar2]
        fild    dword ptr [round_input]
        fnstcw  word ptr [original_control_word]
        movzx   eax, word ptr [original_control_word]
        fmulp   st(1), st(0)
        or      eax, 0x0c00
        mov     word ptr [truncate_control_word], ax
        fldcw   word ptr [truncate_control_word]
        fistp   dword ptr [local_8]
        fldcw   word ptr [original_control_word]
    }

    const std::uint8_t uVar3 =
        static_cast<std::uint8_t>(local_8);

    const std::uint32_t uVar6 = DAT_1003bc1c;
    const float fVar4 =
        static_cast<float>(FUN_10008d20());

    FUN_100073f0(
        nullptr,
        static_cast<std::uint32_t>(uVar3),
        local_a,
        *reinterpret_cast<const float*>(iVar1 + 0x0c) +
            *reinterpret_cast<const float*>(iVar1 + 0x0c) +
            static_cast<float>(_DAT_10024f60),
        _DAT_10024f68,
        fVar4,
        _DAT_10024ec8,
        uVar6);
}
