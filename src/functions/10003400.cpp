#include <cstddef>
#include <cstdint>
#include <cmath>

extern std::int32_t DAT_1003c248;
extern std::uint32_t DAT_1003bc7c;
extern std::uint32_t DAT_1003bbb4;
extern std::int32_t* _DAT_00b74494;

extern float _DAT_10024fc8;
extern float _DAT_10024fd0;
extern float _DAT_10024fd8;
extern float _DAT_10024fe0;
extern float _DAT_10024fe8;

extern "C" float __stdcall FUN_1001b5a0();
extern "C" std::int32_t __stdcall FUN_10009360();

struct FUN_10003400_this {
    void __thiscall FUN_10003400(float* param_1, char param_2);
};

void FUN_10003400_this::FUN_10003400(float* param_1, char param_2)
{
    void* this_ = static_cast<void*>(this);
    struct ObjectLayout
    {
        std::uint8_t padding_00[0x04];
        float position[3];
        std::uint8_t padding_10[0x04];
        std::uint32_t related_object_14;
        std::uint8_t padding_18[0x0A];
        std::int16_t effect_index_22;
        std::uint8_t padding_24[0x570];
        std::int32_t object_state_594;
    };

    struct RelatedObject
    {
        std::uint8_t padding_00[0x30];
        float position[3];
    };

    struct EffectRecord
    {
        std::uint8_t padding_00[0x5C];
        float effect_data[2];
    };

    struct ContextRoot
    {
        std::uint8_t padding_00[0x48];
        std::uint32_t entry_table_48;
    };

    auto* self = static_cast<ObjectLayout*>(this_);

    const std::int16_t effect_index = self->effect_index_22;

    const auto effect_entry_address =
        static_cast<std::uintptr_t>(
            static_cast<std::intptr_t>(0x00A9B0C8u) +
            static_cast<std::int32_t>(effect_index) * 4);

    const auto effect_record_address =
        *reinterpret_cast<const std::uint32_t*>(effect_entry_address);

    const auto* effect_record =
        reinterpret_cast<const EffectRecord*>(
            static_cast<std::uintptr_t>(effect_record_address));

    float local_38 = effect_record->effect_data[0];
    const float fVar1 = effect_record->effect_data[1];

    if (param_2 == '\0')
    {
        local_38 = -local_38;
    }

    float* position;

    if (self->related_object_14 == 0)
    {
        position = self->position;
    }
    else
    {
        position =
            reinterpret_cast<RelatedObject*>(
                static_cast<std::uintptr_t>(self->related_object_14))
                ->position;
    }

    float local_14 = position[0];
    float local_10 = position[1];
    const float fVar2 = param_1[5];
    float local_c = position[2];
    const float fVar3 = param_1[4];

    long double fVar12 =
        static_cast<long double>(fVar2) * static_cast<long double>(fVar2) +
        static_cast<long double>(fVar3) * static_cast<long double>(fVar3);

    if (fVar12 != 0.0L)
    {
        fVar12 = static_cast<long double>(FUN_1001b5a0());
        fVar12 = static_cast<long double>(1) / fVar12;
    }

    const float fVar4 = param_1[0];
    const float fVar5 = param_1[1];

    long double fVar13 =
        static_cast<long double>(fVar5) * static_cast<long double>(fVar5) +
        static_cast<long double>(fVar4) * static_cast<long double>(fVar4);

    if (fVar13 != 0.0L)
    {
        fVar13 = static_cast<long double>(FUN_1001b5a0());
        fVar13 = static_cast<long double>(1) / fVar13;
    }

    const std::int32_t flag_index = DAT_1003c248;
    const long double fVar14 = static_cast<long double>(local_38);

    long double fVar15 =
        static_cast<long double>(
            static_cast<float>(std::fabs(fVar14))) *
        static_cast<long double>(_DAT_10024fd8);

    if (self->object_state_594 == 9 || effect_index == 0x1D7)
    {
        fVar15 = static_cast<long double>(_DAT_10024fe8);
    }

    const long double fVar16 = fVar15 + fVar15;

    const long double fVar17 =
        static_cast<long double>(_DAT_10024fe0) +
        fVar16 +
        static_cast<long double>(fVar1);

    const long double fVar18 =
        static_cast<long double>(
            static_cast<float>(fVar12 * static_cast<long double>(fVar2)));

    local_c = local_c + _DAT_10024fd0;

    fVar12 =
        static_cast<long double>(
            static_cast<float>(static_cast<long double>(fVar3) * fVar12));

    local_14 =
        static_cast<float>(
            static_cast<long double>(local_14) +
            static_cast<long double>(
                static_cast<float>(
                    static_cast<long double>(fVar4) * fVar13)) *
                fVar14 +
            fVar12 * fVar17);

    local_10 =
        static_cast<float>(
            static_cast<long double>(
                static_cast<float>(
                    fVar18 * fVar17 +
                    static_cast<long double>(local_10))) +
            static_cast<long double>(
                static_cast<float>(
                    fVar13 * static_cast<long double>(fVar5))) *
                fVar14);

    const std::int32_t context_address = FUN_10009360();
    std::uint32_t color = DAT_1003bc7c;

    const std::int32_t object_slot =
        (static_cast<std::int32_t>(
             reinterpret_cast<std::uintptr_t>(this_)) -
         *_DAT_00b74494) /
        0xA18;

    const auto* context =
        reinterpret_cast<const ContextRoot*>(
            static_cast<std::uintptr_t>(context_address));

    const auto context_entry_address =
        static_cast<std::uintptr_t>(
            static_cast<std::intptr_t>(
                static_cast<std::uintptr_t>(context->entry_table_48)) +
            object_slot * 4);

    const auto context_entry =
        *reinterpret_cast<const std::uint32_t*>(
            context_entry_address);

    const auto flag_address =
        reinterpret_cast<const std::uint8_t*>(
            static_cast<std::intptr_t>(
                static_cast<std::uintptr_t>(context_entry)) +
            0x1C +
            flag_index);

    if (*flag_address == 0)
    {
        color = DAT_1003bbb4;
    }

    using AllocateFunction = void* (__cdecl*)(std::int32_t, std::int32_t);

    using SubmitFunction = void (__cdecl*)(
        std::int32_t,
        std::uint32_t,
        float*,
        float,
        float,
        float,
        float,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        float,
        std::uint32_t,
        float,
        std::uint32_t,
        bool);

    void* allocated =
        reinterpret_cast<AllocateFunction>(0x0056E0D0u)(-1, 0);

    reinterpret_cast<SubmitFunction>(0x00707390u)(
        2,
        color,
        &local_14,
        static_cast<float>(fVar12 * fVar16),
        static_cast<float>(fVar18 * fVar16),
        static_cast<float>(fVar18 * fVar15),
        static_cast<float>(-(fVar12 * fVar15)),
        0xFF,
        0x3C,
        0x3C,
        0x3C,
        _DAT_10024fc8,
        0,
        1.0f,
        0,
        this_ == allocated);
}