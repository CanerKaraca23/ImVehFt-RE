#include <cstdint>

extern std::int32_t* _DAT_00b74494;

extern "C" std::int32_t __stdcall FUN_10009360();

using Callback = void(__cdecl*)(std::int32_t, std::int32_t);

void __cdecl FUN_1000d300(std::int32_t param_1)
{
    const std::int32_t state = FUN_10009360();
    const std::int32_t index = (param_1 - *_DAT_00b74494) / 0xA18;

    const std::int32_t table =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(state) + 0x48);

    std::int32_t* entry =
        reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(table) + index * 4);

    if (*entry != 0)
    {
        const std::int32_t currentState = FUN_10009360();
        const std::int32_t sentinel = currentState + 0x50;

        if (*reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(currentState) + 0x54) == 0)
        {
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(currentState) + 0x54) = sentinel;

            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(sentinel)) = sentinel;
        }

        std::int32_t current =
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(currentState) + 0x54);

        while (true)
        {
            if (*reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(currentState) + 0x54) == 0)
            {
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(currentState) + 0x54) = sentinel;

                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(sentinel)) = sentinel;
            }

            if (current == sentinel)
            {
                break;
            }

            const auto callback =
                *reinterpret_cast<Callback*>(
                    static_cast<std::uintptr_t>(current) + 0x18);

            callback(
                param_1,
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(current) + 0x08) +
                *entry);

            current =
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(current) + 0x04);
        }

        *entry = 0;
    }
}