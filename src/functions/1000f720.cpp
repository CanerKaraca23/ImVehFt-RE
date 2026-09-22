#include <cstdint>

extern std::uint32_t DAT_1003c3d4;

std::uint32_t __stdcall FUN_1000f720(std::uint32_t param_1)
{
    using Callback = void (__cdecl*)(std::uint32_t);
    using ReturnCallback = std::uint32_t (__cdecl*)();

    struct GlobalState
    {
        std::uint8_t padding_0x00[0x04];
        ReturnCallback callback_0x04;
        std::uint8_t padding_0x08[0x10];
        Callback* callbackBegin_0x18;
        Callback* callbackEnd_0x1c;
        std::uint8_t padding_0x20[0x08];
        Callback* callbackBegin_0x28;
        Callback* callbackEnd_0x2c;
    };

    GlobalState* const state = reinterpret_cast<GlobalState*>(
        static_cast<std::uintptr_t>(DAT_1003c3d4));
    Callback* const firstEnd = state->callbackEnd_0x1c;

    for (Callback* callback = state->callbackBegin_0x18;
         callback != firstEnd;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)(param_1);
        }
    }

    std::uint32_t result = 0U;
    if (state->callback_0x04 != nullptr)
    {
        result = state->callback_0x04();
    }

    Callback* const secondEnd = state->callbackEnd_0x2c;

    for (Callback* callback = state->callbackBegin_0x28;
         callback != secondEnd;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)(param_1);
        }
    }

    return result;
}