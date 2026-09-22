#include <cstdint>

std::uint32_t __stdcall FUN_1000d700()
{
    struct GlobalState
    {
        std::uint8_t field_00[0x44];
        std::uint32_t* field_44;
        std::uint32_t* field_48;
        std::uint8_t field_4c[0x08];
        std::uint32_t* field_54;
        std::uint32_t* field_58;
    };

    using Callback = void (*)();

    extern std::int32_t DAT_1003c390;
    extern std::uint32_t __stdcall FUN_100096e0(
        std::int32_t,
        std::int32_t
    );

    const std::int32_t state_address = DAT_1003c390;
    auto* state = reinterpret_cast<GlobalState*>(
        static_cast<std::uintptr_t>(state_address));

    for (std::uint32_t* callback = state->field_44;
         callback != state->field_48;
         callback += 1)
    {
        if (*callback != 0U)
        {
            reinterpret_cast<Callback>(*callback)();
        }
    }

    const std::uint32_t result = FUN_100096e0(state_address + 4, 7);

    for (std::uint32_t* callback = state->field_54;
         callback != state->field_58;
         callback += 1)
    {
        if (*callback != 0U)
        {
            reinterpret_cast<Callback>(*callback)();
        }
    }

    return result;
}