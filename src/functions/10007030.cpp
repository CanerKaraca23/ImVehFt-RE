#include <bit>
#include <cstdint>

extern volatile std::uint8_t unresolved_in_AL;
extern volatile std::uint32_t unresolved_extraout_ECX;
extern volatile std::uint16_t unresolved_in_FPUControlWord;

extern std::uint32_t DAT_1003bc1c;
extern std::uint32_t DAT_1003c1f8;

extern float _DAT_10024f00;
extern float _DAT_10024f08;
extern float _DAT_10024f10;
extern float _DAT_10024f14;
extern float _DAT_10024f28;
extern float _DAT_10024f30;
extern float _DAT_10024ef8;
extern float _DAT_10024ef0;
extern std::uint32_t _DAT_10024eec;
extern std::uint32_t _DAT_10024ee8;
extern float _DAT_10024ee0;
extern float _DAT_10024ed8;
extern float _DAT_10024ed0;
extern std::uint32_t _DAT_10024ec8;
extern float _DAT_10024ec0;
extern float _DAT_00c812a8;

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

extern "C" void __cdecl FUN_10007030(
    int param_1,
    int param_2,
    std::uint32_t param_3,
    char param_4,
    std::uint32_t param_5,
    std::uint32_t param_6,
    std::uint32_t param_7,
    char param_8,
    char param_9,
    std::uint8_t param_10)
{
    const char in_AL = static_cast<char>(unresolved_in_AL);
    const std::uint32_t extraout_ECX = unresolved_extraout_ECX;
    const std::uint16_t in_FPUControlWord =
        unresolved_in_FPUControlWord;

    std::uint8_t local_f4[64];
    std::uint32_t local_b4[12];
    std::uint8_t local_84[16];
    std::uint32_t local_74[12];
    std::uint8_t local_44[20];
    std::uint8_t local_1c[4];

    std::uint32_t local_30;
    std::uint32_t local_2c;
    std::uint32_t local_28;
    float local_24;
    float local_20;
    float local_18;
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
        void(__cdecl*)(void*, std::uint32_t, void*);
    using Callback59c910 = void(__fastcall*)(void*, std::uint32_t);
    using Callback7f2070 = void(__cdecl*)(void*, void*);
    using Callback59c790 =
        void(__cdecl*)(void*, void*, void*);

    reinterpret_cast<Callback40fe60>(0x40fe60)(
        local_1c,
        param_3,
        local_44);

    reinterpret_cast<Callback59c910>(0x59c910)(&local_18, 0);

    reinterpret_cast<Callback7f2070>(0x7f2070)(
        local_f4,
        local_74);

    reinterpret_cast<Callback59c790>(0x59c790)(
        local_1c,
        local_f4,
        local_1c);

    std::uint32_t uVar5 = 0;
    std::uint32_t uVar3 =
        (extraout_ECX & 0xffffff00u) |
        static_cast<std::uint32_t>(param_10);

    if (in_AL != '\0')
    {
        if (param_10 == 2)
        {
            const float local_8_value =
                static_cast<float>(static_cast<int>(in_AL)) /
                    _DAT_10024f08 -
                _DAT_10024f00;

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
                local_18 *= _DAT_10024f30;

            if (0.0f < local_18)
            {
                const float fVar10 =
                    static_cast<float>(static_cast<int>(in_AL)) /
                        _DAT_10024f08 -
                    _DAT_10024f00;

                const std::uint64_t uVar8 =
                    FUN_1001ba40(
                        uVar3,
                        static_cast<int>(in_AL));

                reinterpret_cast<Callback6fc580>(0x6fc580)(
                    param_4 + 0xff00 + param_2,
                    param_2,
                    param_5,
                    param_6,
                    param_7,
                    static_cast<std::uint32_t>(uVar8) & 0xffu,
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

        local_24 =
            _DAT_10024ef0 +
            static_cast<float>(static_cast<int>(local_c)) *
                _DAT_10024ef0;

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

        float fVar10 = _DAT_00c812a8;

        if (_DAT_00c812a8 < _DAT_10024ee0)
            fVar10 = _DAT_10024ed8;

        const float width_operand =
            static_cast<float>(param_6 & 0xffu);

        int rounded_width;

#if defined(_MSC_VER) && defined(_M_IX86)
        __asm
        {
            fld width_operand
            fmul fVar10
            fmul _DAT_10024ed0
            fistp rounded_width
        }
#elif defined(__GNUC__) && defined(__i386__)
        __asm__ __volatile__(
            "flds %1\n\t"
            "fmuls %2\n\t"
            "fmuls %3\n\t"
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
            fistp rounded_height
        }
#elif defined(__GNUC__) && defined(__i386__)
        __asm__ __volatile__(
            "flds %1\n\t"
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