#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
unsigned int __stdcall FUN_1000eea0()
{
    using Callback = void(__cdecl*)();
    using ReturnCallback = unsigned int(__cdecl*)();

    struct GlobalState
    {
        unsigned char reserved_00[0x14];
        ReturnCallback callback_14;
        Callback* callbacks_begin_18;
        Callback* callbacks_end_1c;
        unsigned char reserved_20[0x08];
        Callback* callbacks_begin_28;
        Callback* callbacks_end_2c;
    };

    extern int DAT_1003c3c0;

    const int iVar2 = DAT_1003c3c0;
    auto* state = reinterpret_cast<GlobalState*>(
        static_cast<unsigned int>(iVar2));

    Callback* callbacks_end_1c = state->callbacks_end_1c;

    for (Callback* callback = state->callbacks_begin_18;
         callback != callbacks_end_1c;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    unsigned int local_8;

    if (state->callback_14 == nullptr)
    {
        local_8 = 0U;
    }
    else
    {
        local_8 = state->callback_14();
    }

    Callback* callbacks_end_2c = state->callbacks_end_2c;

    for (Callback* callback = state->callbacks_begin_28;
         callback != callbacks_end_2c;
         ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)();
        }
    }

    return local_8;
}