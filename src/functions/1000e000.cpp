#include <cstddef>
#include <cstdint>

std::uint32_t __stdcall FUN_1000e000()
{
    using VoidCallback = void (__stdcall*)();
    using ReturnCallback = std::uint32_t (__stdcall*)();

    struct State
    {
        std::uint8_t padding_00[0x04];
        ReturnCallback field_04;
        std::uint8_t padding_08[0x10];
        VoidCallback* field_18;
        VoidCallback* field_1C;
        std::uint8_t padding_20[0x08];
        VoidCallback* field_28;
        VoidCallback* field_2C;
    };

    static_assert(sizeof(void*) == 4);
    static_assert(offsetof(State, field_04) == 0x04);
    static_assert(offsetof(State, field_18) == 0x18);
    static_assert(offsetof(State, field_1C) == 0x1C);
    static_assert(offsetof(State, field_28) == 0x28);
    static_assert(offsetof(State, field_2C) == 0x2C);
    static_assert(sizeof(State) == 0x30);

    extern std::uint32_t DAT_1003c3a4;

    const auto state =
        reinterpret_cast<State*>(
            static_cast<std::uintptr_t>(DAT_1003c3a4));

    VoidCallback* end_1C = state->field_1C;

    for (VoidCallback* callback = state->field_18;
         callback != end_1C;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    std::uint32_t result;

    if (state->field_04 == nullptr)
    {
        result = 0;
    }
    else
    {
        result = state->field_04();
    }

    VoidCallback* end_2C = state->field_2C;

    for (VoidCallback* callback = state->field_28;
         callback != end_2C;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    return result;
}