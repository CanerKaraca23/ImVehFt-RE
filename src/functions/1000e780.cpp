#include <cstdint>

extern std::uint32_t DAT_1003c3b4;

std::uint32_t __stdcall FUN_1000e780()
{
    using Callback = void(__cdecl*)();
    using ReturnCallback = std::uint32_t(__cdecl*)();

    struct Context
    {
        std::uint32_t field_00;
        ReturnCallback field_04;
        std::uint8_t padding_08[0x10];
        Callback* field_18;
        Callback* field_1c;
        std::uint8_t padding_20[0x08];
        Callback* field_28;
        Callback* field_2c;
    };

    Context* context =
        reinterpret_cast<Context*>(
            static_cast<std::uintptr_t>(DAT_1003c3b4));

    Callback* end_1c = context->field_1c;

    for (Callback* callback = context->field_18;
         callback != end_1c;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    std::uint32_t result;

    if (context->field_04 == nullptr)
    {
        result = 0U;
    }
    else
    {
        result = context->field_04();
    }

    Callback* end_2c = context->field_2c;

    for (Callback* callback = context->field_28;
         callback != end_2c;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    return result;
}