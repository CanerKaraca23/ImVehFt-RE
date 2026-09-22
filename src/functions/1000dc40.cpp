#include <cstdint>

std::uint32_t __stdcall FUN_1000dc40()
{
    struct GlobalState
    {
        std::uint32_t reserved_00;
        std::uint32_t callback_04;
        std::uint8_t reserved_08[0x10];
        std::uint32_t callbacks_begin_18;
        std::uint32_t callbacks_end_1C;
        std::uint8_t reserved_20[0x08];
        std::uint32_t callbacks_begin_28;
        std::uint32_t callbacks_end_2C;
    };

    using VoidCallback = void (__cdecl*)();
    using ReturnCallback = std::uint32_t (__cdecl*)();

    extern std::uint32_t DAT_1003c39c;

    auto* state = reinterpret_cast<GlobalState*>(
        static_cast<std::uintptr_t>(DAT_1003c39c));

    auto* callbacks_begin_18 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->callbacks_begin_18));
    auto* callbacks_end_1C = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->callbacks_end_1C));

    for (auto* callback = callbacks_begin_18;
         callback != callbacks_end_1C;
         ++callback)
    {
        if (*callback != 0U)
        {
            reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*callback))();
        }
    }

    std::uint32_t local_8;

    if (state->callback_04 == 0U)
    {
        local_8 = 0U;
    }
    else
    {
        local_8 = reinterpret_cast<ReturnCallback>(
            static_cast<std::uintptr_t>(state->callback_04))();
    }

    auto* callbacks_begin_28 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->callbacks_begin_28));
    auto* callbacks_end_2C = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->callbacks_end_2C));

    for (auto* callback = callbacks_begin_28;
         callback != callbacks_end_2C;
         ++callback)
    {
        if (*callback != 0U)
        {
            reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*callback))();
        }
    }

    return local_8;
}