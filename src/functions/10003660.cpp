#include <cstdint>

using Float10 = long double;

extern float _DAT_10024fd8;
extern float _DAT_10024e88;
extern float _DAT_10024fd0;
extern float _DAT_10024fc8;

extern std::int32_t DAT_1003c248;
extern std::uint32_t DAT_1003bc7c;
extern std::uint32_t DAT_1003bbb4;
extern std::int32_t* _DAT_00b74494;

extern "C" Float10 __stdcall FUN_1001b5a0();
extern "C" std::int32_t __stdcall FUN_10009360();

struct FUN_10003660_this {
    void __thiscall FUN_10003660(std::int32_t param_1);
};

void FUN_10003660_this::FUN_10003660(std::int32_t param_1)
{
    void* this_ = static_cast<void*>(this);
    float* effectValues =
        *reinterpret_cast<float**>(
            *reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int16_t*>(
                    reinterpret_cast<std::uint8_t*>(this_) + 0x22) *
                4 +
                0xA9B0C8) +
            0x5C);

    const float fVar1 = effectValues[0];
    const float fVar2 = effectValues[1];

    float* position;
    if (*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(this_) + 0x14) == 0)
    {
        position = reinterpret_cast<float*>(
            reinterpret_cast<std::uint8_t*>(this_) + 4);
    }
    else
    {
        position = reinterpret_cast<float*>(
            *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(this_) + 0x14) +
            0x30);
    }

    float local_14 = position[0];
    float local_10 = position[1];
    float local_c = position[2];

    const float fVar3 =
        *reinterpret_cast<float*>(
            reinterpret_cast<std::uint8_t*>(param_1) + 0x14);

    Float10 fVar10 = static_cast<Float10>(fVar3);

    const float fVar4 =
        *reinterpret_cast<float*>(
            reinterpret_cast<std::uint8_t*>(param_1) + 0x10);

    Float10 fVar11 = static_cast<Float10>(fVar4);

    fVar10 = fVar10 * fVar10 + fVar11 * fVar11;

    if (fVar10 != static_cast<Float10>(0.0))
    {
        fVar10 = static_cast<Float10>(FUN_1001b5a0());
        fVar10 = static_cast<Float10>(1.0) / fVar10;
    }

    const std::int32_t iVar5 = DAT_1003c248;

    const Float10 fVar13 =
        fVar10 * static_cast<Float10>(fVar3);

    fVar11 =
        static_cast<Float10>(fVar1) *
        static_cast<Float10>(_DAT_10024fd8);

    const Float10 fVar12 =
        static_cast<Float10>(_DAT_10024e88) +
        fVar11 +
        static_cast<Float10>(fVar2);

    fVar10 = static_cast<Float10>(
        static_cast<float>(
            static_cast<Float10>(fVar4) * fVar10));

    local_14 = static_cast<float>(
        fVar10 * fVar12 +
        static_cast<Float10>(local_14));

    local_10 = static_cast<float>(
        fVar12 * fVar13 +
        static_cast<Float10>(local_10));

    local_c =
        local_c +
        static_cast<float>(_DAT_10024fd0);

    const std::int32_t iVar7 = FUN_10009360();

    std::uint32_t uVar9 = DAT_1003bc7c;

    const std::int32_t thisAddress =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(this_));

    const std::int32_t objectIndex =
        (thisAddress - *_DAT_00b74494) / 0xA18;

    if (*reinterpret_cast<std::uint8_t*>(
            *reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(
                    iVar7 + 0x48) +
                objectIndex * 4) +
            0x1C +
            iVar5) == 0)
    {
        uVar9 = DAT_1003bbb4;
    }

    using AllocateFunction = void* (__cdecl*)(std::int32_t, std::int32_t);
    using DispatchFunction = void (__cdecl*)(
        std::int32_t,
        std::uint32_t,
        const float*,
        float,
        float,
        float,
        float,
        std::uint8_t,
        std::uint8_t,
        std::uint8_t,
        std::uint8_t,
        float,
        std::int32_t,
        std::uint32_t,
        std::int32_t,
        bool);

    const auto allocate =
        reinterpret_cast<AllocateFunction>(
            static_cast<std::uintptr_t>(0x0056E0D0));

    const auto dispatch =
        reinterpret_cast<DispatchFunction>(
            static_cast<std::uintptr_t>(0x00707390));

    void* pvVar8 = allocate(-1, 0);

    dispatch(
        2,
        uVar9,
        &local_14,
        static_cast<float>(
            fVar10 *
            static_cast<Float10>(
                static_cast<float>(fVar11))),
        static_cast<float>(
            static_cast<Float10>(
                static_cast<float>(fVar11)) *
            fVar13),
        static_cast<float>(
            fVar11 *
            fVar13),
        static_cast<float>(
            -(fVar10 * fVar11)),
        0xFF,
        0x3C,
        0x3C,
        0x3C,
        _DAT_10024fc8,
        0,
        0x3F800000,
        0,
        this_ == pvVar8);
}