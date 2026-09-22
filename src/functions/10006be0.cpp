#include <cstdint>

extern std::uint32_t DAT_10024ec8;
extern float DAT_10024ec0;
extern float DAT_1003c1f8;
extern float DAT_1003bc1c;
extern float _DAT_00c812a8;
extern float _DAT_10024ed8;
extern std::uint32_t _DAT_10024e88;
extern float _DAT_10024ed0;
extern std::uint32_t _DAT_10024eec;
extern float _DAT_10024ee0;
extern float _DAT_10024ef8;
extern float _DAT_10024f28;
extern float _DAT_10024f30;
extern float _DAT_10024f38;

extern "C" long double __stdcall FUN_10008d20();

extern "C" void __cdecl FUN_10006be0(
    int param_1,
    std::uint32_t param_2,
    char param_3,
    std::uint8_t param_4,
    std::uint8_t param_5,
    std::uint32_t param_6,
    std::uint8_t param_7,
    float param_8,
    char param_9,
    float param_10,
    char param_11)
{
    (void)param_6;

    struct Object
    {
        std::uint32_t field_00;
        std::int32_t field_04;
        std::uint8_t field_08[8];
        std::uint32_t field_10[16];
        std::uint32_t field_50[16];
    };

    const auto* object = reinterpret_cast<const Object*>(
        static_cast<std::uintptr_t>(param_1));

    std::uint8_t frame[0xe8];

    auto* local_ec = frame + 0x00;
    auto* local_ac = frame + 0x40;
    auto* local_7c = frame + 0x70;
    auto* local_6c = frame + 0x80;
    auto* local_3c = frame + 0xb0;
    auto* local_28 = reinterpret_cast<std::uint32_t*>(frame + 0xc4);
    auto* local_24 = reinterpret_cast<std::uint32_t*>(frame + 0xc8);
    auto* local_20 = reinterpret_cast<std::uint32_t*>(frame + 0xcc);
    auto* local_1c = reinterpret_cast<float*>(frame + 0xd0);
    auto* local_18 = frame + 0xd4;
    auto* local_14 = reinterpret_cast<float*>(frame + 0xd8);
    auto* local_c = reinterpret_cast<float*>(frame + 0xe0);
    auto* local_8 = frame + 0xe4;
    auto* bStack_5 = frame + 0xe7;

    if ((param_8 <= 0.0f) && (param_10 <= 0.0f))
        return;

    if (param_9 == '\0')
    {
        auto* destination =
            reinterpret_cast<std::uint32_t*>(local_6c);

        for (int iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
        {
            *destination = object->field_10[0x10 - iVar3];
            destination = destination + 1;
        }
    }
    else
    {
        reinterpret_cast<void(__cdecl*)(void*, const void*, std::uint32_t)>(
            0x007f18b0)(
            local_6c,
            object->field_10,
            static_cast<std::uint32_t>(object->field_04 + 0x10));
    }

    {
        auto* destination =
            reinterpret_cast<std::uint32_t*>(local_ac);

        for (int iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
        {
            *destination = object->field_50[0x10 - iVar3];
            destination = destination + 1;
        }
    }

    reinterpret_cast<void(__cdecl*)(void*, std::uint32_t, void*)>(
        0x0040fe60)(local_18, param_2, local_7c);

    reinterpret_cast<void(__cdecl*)()>(0x0059c910)();

    reinterpret_cast<void(__cdecl*)(void*, const void*)>(
        0x007f2070)(local_ec, local_ac);

    int in_EAX;
    std::uint32_t extraout_EDX;

    __asm
    {
        push local_18
        push local_ec
        push local_18
        mov eax, 0x0059c790
        call eax
        add esp, 12
        mov in_EAX, eax
        mov extraout_EDX, edx
    }

    std::uint32_t uVar4;

    if (param_8 > 0.0f)
    {
        if ((param_11 == '\x03') || (param_11 == '\x04'))
        {
            if ((_DAT_10024f28 <= *local_14) ||
                (*local_14 <= _DAT_10024f38))
            {
                param_8 = static_cast<float>(param_7);
                uVar4 = extraout_EDX;
            }
            else
            {
                if (*local_14 < 0.0f)
                    *local_14 = *local_14 * _DAT_10024f30;

                uVar4 = static_cast<std::uint32_t>(param_7);
                param_8 =
                    (static_cast<float>(uVar4) +
                     static_cast<float>(uVar4)) *
                    *local_14;
            }

            reinterpret_cast<std::uint64_t(__fastcall*)(
                void*, std::uint32_t)>(
                0x1001ba40)(local_3c, uVar4);
        }
        else
        {
            if (param_11 == '\x02')
            {
                reinterpret_cast<void(__cdecl*)(int)>(
                    0x006fc580)(param_3 + 0xff00 + in_EAX);
                goto LAB_10006e94;
            }

            if (param_11 != '\0')
                *local_14 = *local_14 * _DAT_10024f30;

            if (*local_14 <= 0.0f)
                goto LAB_10006e94;

            uVar4 = extraout_EDX;

            if (*local_14 < _DAT_10024f28)
                uVar4 = static_cast<std::uint32_t>(param_7);

            param_8 =
                static_cast<float>(static_cast<std::uint32_t>(param_7));

            reinterpret_cast<std::uint64_t(__fastcall*)(
                void*, std::uint32_t)>(
                0x1001ba40)(local_3c, uVar4);
        }

        reinterpret_cast<void(__cdecl*)(int)>(
            0x006fc580)(param_3 + 0xff00 + in_EAX);
    }

LAB_10006e94:
    if (param_10 <= 0.0f)
        return;

    if (param_11 != '\x03')
    {
        if ((param_11 == '\x02') || (param_11 == '\x04'))
        {
            *local_1c = 1.0f;
            param_8 = DAT_1003c1f8;
        }
        else
        {
            *local_1c = _DAT_10024ef8;
            param_8 = DAT_1003bc1c;
        }
    }

    const float fVar1 = static_cast<float>(_DAT_10024e88);

    *local_28 = 0;
    *local_24 = _DAT_10024eec;
    *local_20 = 0;

    reinterpret_cast<void(__cdecl*)(void*, int, void*, void*)>(
        0x0054eef0)(local_18, 1, local_ac, local_28);

    float fVar2 = _DAT_00c812a8;

    if (_DAT_00c812a8 < static_cast<float>(_DAT_10024ee0))
        fVar2 = _DAT_10024ed8;

    int rounded_value;

    const float first_round =
        static_cast<float>(param_5) *
        fVar2 *
        static_cast<float>(_DAT_10024ed0);

    __asm
    {
        fld first_round
        fistp rounded_value
    }

    uVar4 = static_cast<std::uint32_t>(rounded_value);

    local_8[0] = static_cast<std::uint8_t>(uVar4);
    local_8[1] = static_cast<std::uint8_t>(uVar4 >> 8);

    std::uint16_t in_FPUControlWord;

    __asm
    {
        fnstcw in_FPUControlWord
    }

    local_8[2] =
        static_cast<std::uint8_t>(in_FPUControlWord);

    const float second_round =
        static_cast<float>(_DAT_10024ed0) *
        static_cast<float>(param_4) *
        fVar2;

    __asm
    {
        fld second_round
        fistp rounded_value
    }

    *local_c = static_cast<float>(rounded_value);
    *bStack_5 = *reinterpret_cast<const std::uint8_t*>(local_c);

    const std::uint32_t uVar8 = DAT_10024ec8;
    const long double fVar7 = FUN_10008d20();

    *local_c = (param_10 - fVar1) * *local_1c;

    reinterpret_cast<void(__fastcall*)(
        void*,
        std::uint32_t,
        void*,
        float,
        float,
        float,
        std::uint32_t,
        float)>(
        0x100073f0)(
        reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(uVar4 & 0xffu)),
        static_cast<std::uint32_t>(*bStack_5),
        local_18,
        *local_c,
        param_10 - fVar1,
        static_cast<float>(
            fVar7 + static_cast<long double>(DAT_10024ec0)),
        uVar8,
        param_8);
}