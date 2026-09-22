#include <cstdint>

extern std::uint32_t _DAT_00c1703c;
extern "C" std::int32_t __stdcall FUN_10009360();

void __stdcall FUN_10009a80(void)
{
    const std::int32_t state = FUN_10009360();

    const auto global_base =
        static_cast<std::uintptr_t>(_DAT_00c1703c);

    const std::int32_t object =
        *reinterpret_cast<std::int32_t*>(global_base + 0x60);

    const std::int32_t value_14 =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(object) + 0x14);
    const std::int32_t value_0c =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(object) + 0x0c);
    const std::int32_t value_10 =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(object) + 0x10);

    const std::int32_t existing =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(state) + 0x0c);

    if (existing != 0)
    {
        if (*reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(existing) + 0x0c) == value_0c &&
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(existing) + 0x10) == value_10 &&
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(existing) + 0x14) == value_14)
        {
            return;
        }

        reinterpret_cast<void(__cdecl*)(std::int32_t)>(
            0x007FB020)(existing);

        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(state) + 0x0c) = 0;
    }

    *reinterpret_cast<std::int32_t*>(
        static_cast<std::uintptr_t>(state) + 0x0c) =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uint32_t(__cdecl*)(
                std::int32_t,
                std::int32_t,
                std::int32_t,
                std::int32_t)>(0x007FB230)(
                    value_0c,
                    value_10,
                    value_14,
                    5));
}