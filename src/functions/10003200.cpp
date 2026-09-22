#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;
extern std::uint32_t _DAT_10024ff0;
extern std::uint32_t _DAT_10024ff8;
extern float _DAT_00c81300;

extern "C" std::int32_t __stdcall FUN_10009360();

extern "C" void __cdecl FUN_10003200(
    std::uint32_t param_1,
    std::int32_t param_2,
    char param_3,
    std::uint32_t param_4,
    std::uint32_t param_5,
    std::uint32_t,
    std::uint32_t param_7,
    float param_8,
    std::uint32_t param_9,
    std::uint32_t param_10,
    std::uint32_t param_11,
    std::uint32_t param_12,
    std::uint32_t param_13,
    std::uint32_t param_14,
    std::uint32_t param_15,
    std::uint32_t param_16,
    std::uint32_t param_17,
    std::uint32_t param_18,
    std::uint32_t param_19,
    std::uint32_t param_20,
    std::uint32_t param_21)
{
    const std::int32_t base = DAT_1003c248;
    std::uint32_t local_8 = 200;

    if (param_2 != 0)
    {
        const std::int32_t context_1 = FUN_10009360();
        const std::int32_t base_1 = DAT_1003c248;

        if (*reinterpret_cast<const char*>(
                *reinterpret_cast<const std::int32_t*>(
                    *reinterpret_cast<const std::int32_t*>(
                        *reinterpret_cast<const std::int32_t*>(
                            context_1 + 0x48) +
                        ((param_2 - *_DAT_00b74494) / 0xa18) * 4) +
                    0x28 + base) +
                0x325) == '\0')
        {
            const std::int32_t context_2 = FUN_10009360();

            if (*reinterpret_cast<const char*>(
                    *reinterpret_cast<const std::int32_t*>(
                        *reinterpret_cast<const std::int32_t*>(
                            *reinterpret_cast<const std::int32_t*>(
                                context_2 + 0x48) +
                            ((param_2 - *_DAT_00b74494) / 0xa18) * 4) +
                        0x28 + base_1) +
                    0x324) == '\0' &&
                0.0f < *reinterpret_cast<const float*>(param_2 + 0x4a0) &&
                (*reinterpret_cast<const std::uint8_t*>(param_2 + 0x428) & 0x20) == 0 &&
                *reinterpret_cast<const std::int32_t*>(param_2 + 0x460) != 0)
            {
                local_8 = 200;
            }
            else
            {
                local_8 = 0x78;
            }
        }
        else
        {
            local_8 = 0x78;
        }
    }
    else
    {
        local_8 = 0x78;
    }

    using TargetFunction = void(__cdecl*)(
        std::uint32_t,
        std::int32_t,
        int,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        float,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t,
        std::uint32_t);

    reinterpret_cast<TargetFunction>(0x6fc580)(
        param_1,
        param_2,
        -(param_3 != '\0') & 100,
        param_4,
        param_5,
        local_8,
        param_7,
        param_8 * static_cast<float>(_DAT_10024ff0) +
            _DAT_00c81300 * static_cast<float>(_DAT_10024ff8),
        param_9,
        param_10,
        param_11,
        param_12,
        param_13,
        param_14,
        param_15,
        param_16,
        param_17,
        param_18,
        param_19,
        param_20,
        param_21);
}