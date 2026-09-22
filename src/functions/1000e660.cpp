#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
std::uint32_t __stdcall FUN_1000e660()
{
    using Callback = void (__cdecl*)();
    using ReturnCallback = std::uint32_t (__cdecl*)();

    struct Context
    {
        std::uint8_t field_00[0x0c];
        ReturnCallback callback;
        std::uint8_t field_10[0x08];
        Callback* callbacks_begin;
        Callback* callbacks_end;
        std::uint8_t field_20[0x08];
        Callback* callbacks2_begin;
        Callback* callbacks2_end;
    };

    extern std::int32_t DAT_1003c3b0;

    const auto* context = reinterpret_cast<const Context*>(
        static_cast<std::uintptr_t>(DAT_1003c3b0));

    for (auto* current = context->callbacks_begin;
         current != context->callbacks_end;
         current += 1)
    {
        if (*current != nullptr)
        {
            (*current)();
        }
    }

    std::uint32_t result;

    if (context->callback == nullptr)
    {
        result = 0U;
    }
    else
    {
        result = context->callback();
    }

    for (auto* current = context->callbacks2_begin;
         current != context->callbacks2_end;
         current += 1)
    {
        if (*current != nullptr)
        {
            (*current)();
        }
    }

    return result;
}