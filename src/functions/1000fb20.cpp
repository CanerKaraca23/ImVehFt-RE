#include <cstdint>

extern std::int32_t DAT_1003c3d8;

std::uint32_t __stdcall FUN_1000fb20(std::uint32_t param_1)
{
    using Callback = void (__stdcall *)(std::uint32_t);
    using ReturnCallback = std::uint32_t (__stdcall *)();

    struct State
    {
        std::uint8_t field_00[0x10];
        std::uint32_t field_10;
        std::uint8_t field_14[0x04];
        std::uint32_t field_18;
        std::uint32_t field_1c;
        std::uint8_t field_20[0x08];
        std::uint32_t field_28;
        std::uint32_t field_2c;
    };

    const std::int32_t iVar2 = DAT_1003c3d8;
    auto* state = reinterpret_cast<State*>(
        static_cast<std::uintptr_t>(iVar2));

    auto* puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->field_1c));

    for (auto* puVar3 = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(state->field_18));
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*puVar3))(param_1);
        }
    }

    std::uint32_t local_8;
    const auto callback = reinterpret_cast<ReturnCallback>(
        static_cast<std::uintptr_t>(state->field_10));

    if (callback == nullptr)
    {
        local_8 = 0U;
    }
    else
    {
        local_8 = callback();
    }

    puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->field_2c));

    for (auto* puVar3 = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(state->field_28));
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*puVar3))(param_1);
        }
    }

    return local_8;
}