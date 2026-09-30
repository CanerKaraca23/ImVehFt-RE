#include <bit>
#include <cstdint>
#include "gta_sa_address_access.hpp"

extern std::uint32_t DAT_1003bc1c;
extern std::uint32_t DAT_1003c1f8;

extern double _DAT_10024f00;
extern double _DAT_10024f08;
extern float _DAT_10024f10;
extern float _DAT_10024f14;
extern float _DAT_10024f28;
extern double _DAT_10024f18;
extern double _DAT_10024f20;
extern double _DAT_10024f30;
extern float _DAT_10024ef8;
extern double _DAT_10024ef0;
extern std::uint32_t _DAT_10024eec;
extern std::uint32_t _DAT_10024ee8;
extern double _DAT_10024ee0;
extern float _DAT_10024ed8;
extern double _DAT_10024ed0;
extern std::uint32_t _DAT_10024ec8;
extern double _DAT_10024ec0;

extern "C" std::uint64_t __fastcall FUN_1001ba40(
    std::uint32_t,
    int);

extern "C" long double __stdcall FUN_10008d20();

extern "C" void __fastcall FUN_100073f0(
    void*,
    std::uint32_t,
    void*,
    float,
    float,
    float,
    std::uint32_t,
    std::uint32_t);

using Callback6fc580 = void(__cdecl*)(
    int, int,
    std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, void*,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t);

static void __cdecl FUN_10007030_impl(
    int param_1,
    int param_2,
    std::uint32_t param_3,
    char param_4,
    std::uint32_t param_5,
    std::uint32_t param_6,
    std::uint32_t param_7,
    char param_8,
    char param_9,
    std::uint8_t param_10,
    std::uint32_t captured_eax)
{
    const char in_AL = static_cast<char>(captured_eax);

    // Preserve the original function's overlapping EBP-relative scratch
    // regions. The two matrix copies are 16 dwords; their final elements
    // intentionally share storage with later corona/vector-input regions.
    // Modeling those lifetimes in one byte frame avoids both C++ array
    // overrun UB and compiler-dependent local-variable placement.
    alignas(std::uint32_t) std::uint8_t stack_overlay[0xf0];
    auto* local_f4 = stack_overlay + 0x04;
    auto* local_b4 = reinterpret_cast<std::uint32_t*>(stack_overlay + 0x44);
    auto* local_84 = stack_overlay + 0x74;
    auto* local_74 = reinterpret_cast<std::uint32_t*>(stack_overlay + 0x84);
    auto* local_44 = stack_overlay + 0xb4;
    auto* local_1c = stack_overlay + 0xd8;
    auto* local_18 = reinterpret_cast<float*>(stack_overlay + 0xdc);
    auto* local_14 = reinterpret_cast<float*>(stack_overlay + 0xe0);

    std::uint32_t local_30;
    std::uint32_t local_2c;
    std::uint32_t local_28;
    float local_24;
    float local_20;
    std::uint8_t local_d;
    float local_c;
    std::uint32_t local_8;

    if (in_AL == '\0' && param_9 == '\0')
        return;

    if (param_8 == '\0')
    {
        const auto* source =
            reinterpret_cast<const std::uint32_t*>(
                static_cast<std::uintptr_t>(param_1) + 0x10);

        for (int i = 0x10; i != 0; --i)
            local_b4[0x10 - i] = *source++;
    }
    else
    {
        using Callback =
            void(__cdecl*)(void*, const void*, int);

        reinterpret_cast<Callback>(0x7f18b0)(
            local_b4,
            reinterpret_cast<const void*>(
                static_cast<std::uintptr_t>(param_1) + 0x10),
            *reinterpret_cast<const int*>(
                static_cast<std::uintptr_t>(param_1) + 4) + 0x10);
    }

    {
        const auto* source =
            reinterpret_cast<const std::uint32_t*>(
                static_cast<std::uintptr_t>(param_1) + 0x50);

        for (int i = 0x10; i != 0; --i)
            local_74[0x10 - i] = *source++;
    }

    using Callback40fe60 =
        void(__cdecl*)(void*, const void*, const void*);
    using Callback59c910 = void(__fastcall*)(void*, std::uint32_t);
    using Callback7f2070 = void(__cdecl*)(void*, void*);
    using Callback59c790 =
        void(__cdecl*)(void*, void*, void*);

    reinterpret_cast<Callback40fe60>(0x40fe60)(
        local_18,
        reinterpret_cast<const void*>(
            static_cast<std::uintptr_t>(param_3)),
        local_44);

    reinterpret_cast<Callback59c910>(0x59c910)(local_18, 0);

    reinterpret_cast<Callback7f2070>(0x7f2070)(
        local_f4,
        local_74);

    std::uint32_t extraout_ECX;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm
    {
        mov eax, local_18
        push eax
        mov eax, local_f4
        push eax
        mov eax, local_18
        push eax
        mov ecx, 059c790h
        call ecx
        add esp, 0ch
        mov extraout_ECX, ecx
        fldz
    }
#else
    reinterpret_cast<Callback59c790>(0x59c790)(
        local_18,
        local_f4,
        local_18);
    #error "Capturing the post-call ECX value requires MSVC x86"
#endif

    std::uint32_t uVar5 = 0;
    std::uint32_t uVar3 =
        (extraout_ECX & 0xffffff00u) |
        static_cast<std::uint32_t>(param_10);

    if (in_AL != '\0')
    {
        if (param_10 == 2)
        {
            const float local_8_value = static_cast<float>(
                static_cast<double>(static_cast<float>(static_cast<int>(in_AL))) /
                    _DAT_10024f08 -
                _DAT_10024f00);

            reinterpret_cast<Callback6fc580>(0x6fc580)(
                param_4 + 0xff00 + param_2,
                param_2,
                param_5,
                param_6,
                param_7,
                0x50,
                local_84,
                std::bit_cast<std::uint32_t>(local_8_value),
                std::bit_cast<std::uint32_t>(_DAT_10024f10),
                1,
                0,
                1,
                0,
                0,
                0,
                0,
                std::bit_cast<std::uint32_t>(_DAT_10024f28),
                0,
                std::bit_cast<std::uint32_t>(_DAT_10024f14),
                0,
                0);

            uVar3 = 2;
        }
        else
        {
            if (param_10 != 0)
                *local_14 = static_cast<float>(
                    static_cast<double>(*local_14) * _DAT_10024f30);

            if (0.0f < *local_14)
            {
                const float alpha_local_14 = *local_14;
                const float fVar10 = static_cast<float>(
                    static_cast<double>(static_cast<float>(static_cast<int>(in_AL))) /
                        _DAT_10024f08 -
                    _DAT_10024f00);

                std::uint32_t alpha_result;
                __asm
                {
                    fld alpha_local_14
                    fld _DAT_10024f28
                    fcom st(1)
                    fnstsw ax
                    test ah, 41h
                    jnz use_fixed_alpha_scale
                    fxch st(1)
                    fmul qword ptr _DAT_10024f20
                    jmp invoke_alpha_helper
                use_fixed_alpha_scale:
                    fstp st(1)
                    fld qword ptr _DAT_10024f18
                invoke_alpha_helper:
                    mov ecx, uVar3
                    movsx edx, in_AL
                    call FUN_1001ba40
                    mov alpha_result, eax
                }

                reinterpret_cast<Callback6fc580>(0x6fc580)(
                    param_4 + 0xff00 + param_2,
                    param_2,
                    param_5,
                    param_6,
                    param_7,
                    alpha_result & 0xffu,
                    local_84,
                    std::bit_cast<std::uint32_t>(fVar10),
                    std::bit_cast<std::uint32_t>(_DAT_10024f10),
                    1,
                    0,
                    1,
                    0,
                    0,
                    uVar5,
                    0,
                    std::bit_cast<std::uint32_t>(_DAT_10024f28),
                    0,
                    std::bit_cast<std::uint32_t>(_DAT_10024f14),
                    0,
                    0);

                uVar3 = static_cast<std::uint32_t>(param_10);
            }
        }
    }

    if (param_9 != '\0')
    {
        const char cVar1 = static_cast<char>(uVar3);

        uVar5 = DAT_1003bc1c;
        local_8 = std::bit_cast<std::uint32_t>(_DAT_10024ef8);

        if (cVar1 == '\x02')
        {
            local_8 = std::bit_cast<std::uint32_t>(1.0f);
            uVar5 = DAT_1003c1f8;
        }

        local_c = static_cast<float>(
            static_cast<int>(
                static_cast<char>(param_9 - 1)));

        local_24 = static_cast<float>(
            _DAT_10024ef0 +
            static_cast<double>(static_cast<float>(static_cast<int>(local_c))) *
                _DAT_10024ef0);

        local_20 =
            std::bit_cast<float>(local_8) *
            local_24;

        local_30 = 0;

        if (cVar1 == '\0')
            local_2c = _DAT_10024eec;
        else if (cVar1 == '\x01')
            local_2c = _DAT_10024ee8;
        else
            local_2c = 0;

        local_28 = 0;

        using Callback54eef0 =
            void(__cdecl*)(void*, std::uint32_t, void*, void*);

        reinterpret_cast<Callback54eef0>(0x54eef0)(
            local_1c,
            1,
            local_74,
            &local_30);

        float fVar10 = IMVEHFT_GLOBAL_AT(float, 0x00c812a8);

        if (IMVEHFT_GLOBAL_AT(float, 0x00c812a8) < _DAT_10024ee0)
            fVar10 = _DAT_10024ed8;

        const float width_operand =
            static_cast<float>(param_6 & 0xffu);

        int rounded_width;
        std::uint16_t saved_fpu_control_word;
        std::uint16_t truncating_fpu_control_word;

#if defined(_MSC_VER) && defined(_M_IX86)
        __asm
        {
            fnstcw saved_fpu_control_word
            mov ax, saved_fpu_control_word
            or ax, 0c00h
            mov truncating_fpu_control_word, ax
            fld width_operand
            fmul fVar10
            fmul _DAT_10024ed0
            fldcw truncating_fpu_control_word
            fistp rounded_width
            fldcw saved_fpu_control_word
        }
#elif defined(__GNUC__) && defined(__i386__)
        __asm__ __volatile__(
            "flds %1\n\t"
            "fmuls %2\n\t"
            "fmull %3\n\t"
            "fistpl %0"
            : "=m"(rounded_width)
            : "m"(width_operand),
              "m"(fVar10),
              "m"(_DAT_10024ed0)
            : "st");
#else
#error "x87-compatible ROUND semantics are required"
#endif

        local_d = static_cast<std::uint8_t>(rounded_width);

        std::uint16_t in_FPUControlWord;
        __asm fnstcw in_FPUControlWord

        local_8 =
            (static_cast<std::uint32_t>(in_FPUControlWord) << 16) |
            (std::bit_cast<std::uint32_t>(fVar10) & 0xffffu);

        const float height_operand =
            static_cast<float>(param_5 & 0xffu);

        int rounded_height;

#if defined(_MSC_VER) && defined(_M_IX86)
        __asm
        {
            fld _DAT_10024ed0
            fmul height_operand
            fmul fVar10
            fldcw truncating_fpu_control_word
            fistp rounded_height
            fldcw saved_fpu_control_word
        }
#elif defined(__GNUC__) && defined(__i386__)
        __asm__ __volatile__(
            "fldl %1\n\t"
            "fmuls %2\n\t"
            "fmuls %3\n\t"
            "fistpl %0"
            : "=m"(rounded_height)
            : "m"(_DAT_10024ed0),
              "m"(height_operand),
              "m"(fVar10)
            : "st");
#else
#error "x87-compatible ROUND semantics are required"
#endif

        local_8 =
            (local_8 & 0x00ffffffu) |
            (static_cast<std::uint32_t>(
                static_cast<std::uint8_t>(rounded_height)) << 24);

        local_c = static_cast<float>(
            static_cast<long double>(FUN_10008d20()) +
            static_cast<long double>(_DAT_10024ec0));

        FUN_100073f0(
            reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(local_d)),
            (local_8 >> 24) & 0xffu,
            local_1c,
            local_20,
            local_24,
            local_c,
            _DAT_10024ec8,
            uVar5);
    }
}

#if defined(_MSC_VER) && defined(_M_IX86)
extern "C" __declspec(naked) void __cdecl FUN_10007030(
    int,
    int,
    std::uint32_t,
    char,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    char,
    char,
    std::uint8_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push eax
        push dword ptr [ebp + 2ch]
        push dword ptr [ebp + 28h]
        push dword ptr [ebp + 24h]
        push dword ptr [ebp + 20h]
        push dword ptr [ebp + 1ch]
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0ch]
        push dword ptr [ebp + 08h]
        call FUN_10007030_impl
        add esp, 2ch
        mov esp, ebp
        pop ebp
        ret
    }
}
#else
#error "FUN_10007030 requires an MSVC x86 entry shim to preserve incoming AL"
#endif
