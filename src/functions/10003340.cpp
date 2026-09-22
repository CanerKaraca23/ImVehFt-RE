#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;
extern float _DAT_00c81300;

extern "C" int __stdcall FUN_10009360();

using DispatchFunction = void(__cdecl*)(
    std::uint32_t, int, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, float, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t);

void __cdecl FUN_10003340(
    std::uint32_t param_1,
    int param_2,
    std::uint32_t param_3,
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
    const int iVar1 = DAT_1003c248;
    const int iVar2 = FUN_10009360();

    const int tableBase =
        *reinterpret_cast<int*>(
            static_cast<std::uintptr_t>(iVar2) + 0x48);

    const int entry =
        *reinterpret_cast<int*>(
            static_cast<std::uintptr_t>(tableBase) +
            ((param_2 - *_DAT_00b74494) / 0xa18) * 4);

    const float adjustedValue =
        _DAT_00c81300 +
        param_8 +
        static_cast<float>(
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(entry + 0x1c + iVar1)));

    reinterpret_cast<DispatchFunction>(
        static_cast<std::uintptr_t>(0x6fc580))(
        param_1,
        param_2,
        param_3,
        param_4,
        param_5,
        0x80,
        param_7,
        adjustedValue,
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