#include <cstdint>
#include <cmath>



extern std::uintptr_t DAT_1003759c;
extern float _DAT_10024f58;
extern float _DAT_10024f40;
extern float _DAT_10024f28;
extern float _DAT_10024f48;
extern float _DAT_10024f60;
extern float _DAT_10024f68;
extern float _DAT_10024ee0;
extern float _DAT_10024ed8;
extern float _DAT_00c812a8;
extern std::uint32_t _DAT_10024ec8;
extern std::uint32_t DAT_1003bc1c;

extern void __cdecl FUN_0054eef0(
    float*,
    int,
    std::uint32_t,
    float*);

extern void __cdecl FUN_007000e0(
    int,
    float,
    float,
    float,
    float,
    float,
    float,
    float,
    float,
    int,
    int,
    int,
    int,
    int);

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
    std::uintptr_t in_EAX;
    __asm mov in_EAX, eax
    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    float local_10;
    float local_c;
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

    local_20 = 0.0f;
    local_1c = *reinterpret_cast<const float*>(iVar1 + 0x10);
    local_18 = *reinterpret_cast<const float*>(iVar1 + 0x14);

    FUN_0054eef0(&local_20, 1, uVar5, &local_20);

    local_14 = 0.0f;
    local_10 =
        *reinterpret_cast<const float*>(iVar1 + 0x10) - _DAT_10024f58;
    local_c = *reinterpret_cast<const float*>(iVar1 + 0x14);

    FUN_0054eef0(&local_14, 1, uVar5, &local_14);

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
        _DAT_10024f40,
        _DAT_10024f28,
        0,
        0,
        1,
        1,
        0);

    local_20 = 0.0f;
    local_1c =
        *reinterpret_cast<const float*>(iVar1 + 0x10) - _DAT_10024f48;
    local_18 = *reinterpret_cast<const float*>(iVar1 + 0x14);

    FUN_0054eef0(&local_20, 1, uVar5, &local_20);

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

    float fVar2 = _DAT_00c812a8;
    if (_DAT_00c812a8 < _DAT_10024ee0)
    {
        fVar2 = _DAT_10024ed8;
    }

    local_8 = static_cast<int>(
        std::round(
            static_cast<float>(
                static_cast<int>(
                    static_cast<std::uint8_t>(param_1 >> 24))) *
            fVar2));

    const std::uint8_t uVar3 =
        static_cast<std::uint8_t>(local_8);

    const std::uint32_t uVar6 = DAT_1003bc1c;
    const float fVar4 =
        static_cast<float>(FUN_10008d20());

    FUN_100073f0(
        nullptr,
        static_cast<std::uint32_t>(uVar3),
        &local_20,
        *reinterpret_cast<const float*>(iVar1 + 0x0c) +
            *reinterpret_cast<const float*>(iVar1 + 0x0c) +
            _DAT_10024f60,
        _DAT_10024f68,
        fVar4,
        _DAT_10024ec8,
        uVar6);
}