#include <cstdint>

std::uint32_t __stdcall FUN_1000e060()
{
    using Callback = void(__cdecl*)();
    using ReturnCallback = std::uint32_t(__cdecl*)();

    struct RuntimeState
    {
        std::uint32_t reserved_00[2];
        std::uint32_t return_callback; // 0x08
        std::uint32_t reserved_0c[3];
        std::uint32_t callbacks_begin; // 0x18
        std::uint32_t callbacks_end;   // 0x1c
        std::uint32_t reserved_20[2];
        std::uint32_t cleanup_begin;   // 0x28
        std::uint32_t cleanup_end;     // 0x2c
    };

    extern std::uint32_t DAT_1003c3a4;

    const std::uint32_t iVar2 = DAT_1003c3a4;
    auto* state = reinterpret_cast<RuntimeState*>(
        static_cast<std::uintptr_t>(iVar2));

    auto* puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->callbacks_end));

    for (auto* puVar3 = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(state->callbacks_begin));
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*puVar3))();
        }
    }

    std::uint32_t local_8;

    if (state->return_callback == 0U)
    {
        local_8 = 0U;
    }
    else
    {
        local_8 = reinterpret_cast<ReturnCallback>(
            static_cast<std::uintptr_t>(state->return_callback))();
    }

    puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(state->cleanup_end));

    for (auto* puVar3 = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(state->cleanup_begin));
         puVar3 != puVar1;
         puVar3 += 1)
    {
        if (*puVar3 != 0U)
        {
            reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*puVar3))();
        }
    }

    return local_8;
}