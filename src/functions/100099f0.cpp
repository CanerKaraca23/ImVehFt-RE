#include <cstdint>

using Callback = void(__cdecl*)();
using RegisterContext = std::uint32_t*;

extern std::int32_t _DAT_00b7cb4c;
extern std::uint32_t* _DAT_00c1703c;

extern "C" std::int32_t __stdcall FUN_10009360();
extern void __stdcall FUN_10009a80();

void __stdcall FUN_100099f0(void)
{
    RegisterContext in_EAX;
    __asm mov in_EAX, eax

    std::int32_t state = FUN_10009360();

    if (*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(state) + 0x10) != _DAT_00b7cb4c)
    {
        *reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(state) + 0x10) = _DAT_00b7cb4c;

        FUN_10009a80();

        reinterpret_cast<void(__cdecl*)(std::uint32_t*)>(
            0x007EE180)(_DAT_00c1703c);

        state = FUN_10009360();

        reinterpret_cast<void(__cdecl*)(std::uint32_t)>(
            0x007FB060)(
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uint8_t*>(state) + 0x0C));

        reinterpret_cast<void(__cdecl*)(std::uint32_t, std::uint32_t, std::uint32_t)>(
            0x007FAF50)(
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uint8_t*>(_DAT_00c1703c) + 0x60),
                0,
                0);

        reinterpret_cast<void(__cdecl*)()>(0x007FB110)();

        reinterpret_cast<void(__cdecl*)(std::uint32_t*)>(
            0x007EE190)(_DAT_00c1703c);
    }

    std::uint32_t* end = reinterpret_cast<std::uint32_t*>(in_EAX[1]);

    for (std::uint32_t* current =
             reinterpret_cast<std::uint32_t*>(in_EAX[0]);
         current != end;
         ++current)
    {
        auto callback = reinterpret_cast<Callback>(*current);

        reinterpret_cast<void(__cdecl*)()>(0x00700D70)();
        callback();
    }
}