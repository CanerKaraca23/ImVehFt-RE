#include <cstdint>
#include <cmath>


extern std::uint32_t extraout_ECX_10005d30;

extern std::uint32_t DAT_1003759c;

extern float _DAT_10024f58;
extern float _DAT_10024f50;
extern float _DAT_10024f28;
extern float _DAT_10024f48;
extern float _DAT_10024f3c;
extern float _DAT_10024f40;
extern float _DAT_10024ee0;
extern float _DAT_10024ed8;
extern float _DAT_10024eb0;
extern float _DAT_00c812a8;

extern std::uint32_t _DAT_10024ec8;
extern std::uint32_t DAT_1003bc1c;

extern "C" void __cdecl FUN_0054eef0(
    float* destination,
    int count,
    std::uint32_t value,
    const float* source);

extern "C" void __cdecl FUN_007000e0(
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

extern "C" void __cdecl FUN_10005d30(std::uint32_t param_1)
{
    std::uint32_t in_EAX_10005d30;
    __asm mov in_EAX_10005d30, eax
    const std::uint32_t object = in_EAX_10005d30;

    const std::uint32_t value =
        *reinterpret_cast<const std::uint32_t*>(
            static_cast<std::uintptr_t>(object) + 0x14u);

    const std::int16_t index =
        *reinterpret_cast<const std::int16_t*>(
            static_cast<std::uintptr_t>(object) + 0x22u);

    const std::uint32_t table_entry =
        *reinterpret_cast<const std::uint32_t*>(
            static_cast<std::uintptr_t>(DAT_1003759c) +
            static_cast<std::int32_t>(index) * 4);

    const std::uint32_t target =
        *reinterpret_cast<const std::uint32_t*>(
            static_cast<std::uintptr_t>(table_entry) + 0x5Cu);

    float* position =
        reinterpret_cast<float*>(
            static_cast<std::uintptr_t>(target) + 0x0Cu);

    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    float local_10;
    float local_c;

    FUN_0054eef0(&local_20, 1, value, position);

    local_14 = *position;
    local_10 =
        *reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x10u) -
        _DAT_10024f58;
    local_c =
        *reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x14u);

    FUN_0054eef0(&local_14, 1, value, &local_14);

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
        _DAT_10024f50,
        _DAT_10024f28,
        0,
        0,
        0,
        0,
        0);

    local_20 = *position;
    local_1c =
        *reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x10u) -
        _DAT_10024f48;
    local_18 =
        *reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x14u);

    FUN_0054eef0(&local_20, 1, value, &local_20);

    if (static_cast<std::uint8_t>(param_1) == 0x01u)
    {
        param_1 =
            (param_1 & 0x00FFFFFFu) |
            (static_cast<std::uint32_t>(0x32u) << 24);
    }
    else if (static_cast<std::uint8_t>(param_1) == 0x02u)
    {
        param_1 =
            (param_1 & 0x00FFFFFFu) |
            (static_cast<std::uint32_t>(0x14u) << 24);
    }
    else if (static_cast<std::uint8_t>(param_1) == 0x03u)
    {
        param_1 =
            (param_1 & 0x00FFFFFFu) |
            (static_cast<std::uint32_t>(0x46u) << 24);
    }

    float scale = _DAT_00c812a8;

    if (_DAT_00c812a8 < _DAT_10024ee0)
    {
        scale = _DAT_10024ed8;
    }

    const int local_8 = static_cast<int>(std::nearbyint(
        static_cast<float>((param_1 >> 24) & 0xFFu) *
        scale *
        _DAT_10024eb0));

    const std::uint32_t packed_pointer =
        (static_cast<std::uint32_t>(
             reinterpret_cast<std::uintptr_t>(&local_20)) &
         0xFFFFFF00u) |
        static_cast<std::uint8_t>(local_8);

    FUN_100073f0(
        reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(extraout_ECX_10005d30) &
            0xFFFFFF00u),
        packed_pointer,
        &local_20,
        _DAT_10024f3c,
        _DAT_10024f40,
        static_cast<float>(FUN_10008d20()),
        _DAT_10024ec8,
        DAT_1003bc1c);
}