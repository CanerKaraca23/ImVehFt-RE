#include <cstdint>
#include "gta_sa_address_access.hpp"


extern std::uint32_t DAT_1003759c;

extern double _DAT_10024f58;
extern float _DAT_10024f50;
extern float _DAT_10024f28;
extern double _DAT_10024f48;
extern float _DAT_10024f3c;
extern float _DAT_10024f40;
extern double _DAT_10024ee0;
extern float _DAT_10024ed8;
extern double _DAT_10024eb0;

extern std::uint32_t _DAT_10024ec8;
extern std::uint32_t DAT_1003bc1c;

using FUN_0054eef0_t = void(__cdecl*)(
    float*, int, std::uint32_t, const float*);
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

extern "C" void __cdecl FUN_10005d30(std::uint32_t param_1)
{
    const auto FUN_0054eef0 = reinterpret_cast<FUN_0054eef0_t>(
        static_cast<std::uintptr_t>(0x0054eef0));
    const auto FUN_007000e0 = reinterpret_cast<FUN_007000e0_t>(
        static_cast<std::uintptr_t>(0x007000e0));

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

    float local_a[3];
    float local_b[3];

    FUN_0054eef0(local_a, 1, value, position);

    local_b[0] = *position;
    local_b[1] = static_cast<float>(
        static_cast<double>(*reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x10u)) -
        _DAT_10024f58);
    local_b[2] =
        *reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x14u);

    FUN_0054eef0(local_b, 1, value, local_b);

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
        _DAT_10024f50,
        _DAT_10024f28,
        0,
        0,
        0,
        0,
        0);

    local_a[0] = *position;
    local_a[1] = static_cast<float>(
        static_cast<double>(*reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x10u)) -
        _DAT_10024f48);
    local_a[2] =
        *reinterpret_cast<const float*>(
            static_cast<std::uintptr_t>(target) + 0x14u);

    FUN_0054eef0(local_a, 1, value, local_a);

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

    float scale = IMVEHFT_GLOBAL_AT(float, 0x00c812a8);

    if (IMVEHFT_GLOBAL_AT(float, 0x00c812a8) < _DAT_10024ee0)
    {
        scale = _DAT_10024ed8;
    }

    const int signed_color = static_cast<std::int8_t>(param_1 >> 24);
    int local_8;
    std::uint16_t saved_fpu_control_word;
    std::uint16_t truncating_fpu_control_word;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm
    {
        fld scale
        fild signed_color
        fnstcw saved_fpu_control_word
        mov ax, saved_fpu_control_word
        or ax, 0c00h
        mov truncating_fpu_control_word, ax
        fmulp st(1), st(0)
        fmul qword ptr _DAT_10024eb0
        fldcw truncating_fpu_control_word
        fistp local_8
        fldcw saved_fpu_control_word
    }
#else
#error "Ghidra-observed x87 truncation requires MSVC x86"
#endif

    const std::uintptr_t aligned_local_20 =
        reinterpret_cast<std::uintptr_t>(local_a) &
        ~static_cast<std::uintptr_t>(0xFFu);

    const std::uint32_t packed_pointer =
        static_cast<std::uint32_t>(aligned_local_20) |
        static_cast<std::uint8_t>(local_8);

    float angle;
    std::uintptr_t ecx_after_angle;
    __asm
    {
        mov eax, in_EAX_10005d30
        call FUN_10008d20
        mov ecx_after_angle, ecx
        fstp angle
    }

    FUN_100073f0(
        reinterpret_cast<void*>(aligned_local_20),
        packed_pointer,
        local_a,
        _DAT_10024f3c,
        _DAT_10024f40,
        angle,
        _DAT_10024ec8,
        DAT_1003bc1c);
}
