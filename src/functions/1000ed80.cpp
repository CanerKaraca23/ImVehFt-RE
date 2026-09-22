#include <cstdint>

extern std::uint32_t DAT_1003c3c0;

std::uint32_t __stdcall FUN_1000ed80()
{
    using Callback = void(__cdecl*)();
    using ReturnCallback = std::uint32_t(__cdecl*)();

    struct GlobalState
    {
        std::uint8_t field_00[0x08];
        std::uint32_t field_08;
        std::uint8_t field_0C[0x0C];
        std::uint32_t* field_18;
        std::uint32_t* field_1C;
        std::uint8_t field_20[0x08];
        std::uint32_t* field_28;
        std::uint32_t* field_2C;
    };

    const std::uint32_t stateAddress = DAT_1003c3c0;
    auto* state = reinterpret_cast<GlobalState*>(
        static_cast<std::uintptr_t>(stateAddress));

    std::uint32_t* firstEnd = state->field_1C;

    for (std::uint32_t* current = state->field_18;
         current != firstEnd;
         current += 1)
    {
        if (*current != 0U)
        {
            reinterpret_cast<Callback>(*current)();
        }
    }

    std::uint32_t result;

    if (state->field_08 == 0U)
    {
        result = 0U;
    }
    else
    {
        result = reinterpret_cast<ReturnCallback>(state->field_08)();
    }

    std::uint32_t* secondEnd = state->field_2C;

    for (std::uint32_t* current = state->field_28;
         current != secondEnd;
         current += 1)
    {
        if (*current != 0U)
        {
            reinterpret_cast<Callback>(*current)();
        }
    }

    return result;
}