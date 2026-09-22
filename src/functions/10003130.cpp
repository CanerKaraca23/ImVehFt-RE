#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;
extern std::uint32_t _DAT_10025000;

extern "C" std::int32_t __stdcall FUN_10009360();

extern "C" void __cdecl FUN_10003130(
    std::int32_t param_1,
    std::uint32_t param_2,
    std::uint32_t param_3,
    std::uint32_t param_4,
    std::uint32_t param_5,
    std::uint32_t param_6,
    std::uint32_t param_7,
    std::uint32_t param_8,
    std::uint32_t param_9,
    std::uint32_t param_10,
    std::uint32_t param_11,
    std::uint32_t param_12,
    std::uint32_t param_13,
    std::uint32_t param_14,
    std::uint32_t param_15)
{
    const std::int32_t local_base = DAT_1003c248;
    const std::int32_t context = FUN_10009360();

    const std::int32_t index =
        (param_1 - *_DAT_00b74494) / 0xa18;

    const std::int32_t entry_array =
        *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(context + 0x48) +
            index * 4);

    if (*reinterpret_cast<char*>(entry_array + 0x1c + local_base) != '\0') {
        param_9 = _DAT_10025000;
    }

    reinterpret_cast<void(__cdecl*)(
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
        std::uint32_t,
        std::uint32_t)>(
        0x7000e0)(
        param_2,
        param_3,
        param_4,
        param_5,
        param_6,
        param_7,
        param_8,
        param_9,
        param_10,
        param_11,
        param_12,
        param_13,
        param_14,
        param_15);
}