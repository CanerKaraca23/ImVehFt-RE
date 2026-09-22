#include <cstdint>

std::uint32_t __stdcall FUN_1000e300()
{
    static_assert(sizeof(void*) == 4);

    using Callback = void (__cdecl*)();
    using ReturnCallback = std::uint32_t (__cdecl*)();

    struct Context
    {
        std::uint8_t reserved_00[0x10];
        ReturnCallback callback_10;
        std::uint8_t reserved_14[0x04];
        Callback* callbacks_18_begin;
        Callback* callbacks_1c_end;
        std::uint8_t reserved_20[0x08];
        Callback* callbacks_28_begin;
        Callback* callbacks_2c_end;
    };

    extern std::uint32_t DAT_1003c3a8;

    const auto context =
        reinterpret_cast<Context*>(
            static_cast<std::uintptr_t>(DAT_1003c3a8));

    auto* callbacks_1c_end = context->callbacks_1c_end;

    for (auto* callback = context->callbacks_18_begin;
         callback != callbacks_1c_end;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    const std::uint32_t result =
        context->callback_10 != nullptr
            ? context->callback_10()
            : 0U;

    auto* callbacks_2c_end = context->callbacks_2c_end;

    for (auto* callback = context->callbacks_28_begin;
         callback != callbacks_2c_end;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    return result;
}