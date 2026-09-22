#include <cstdint>

extern std::int32_t DAT_1003c400;
extern const char* DAT_1003c3f0;
extern std::uint16_t DAT_1003c3f4;
extern std::uint16_t DAT_1003c3f6;
extern std::int32_t* DAT_00c97c28;

extern "C" std::uint32_t __stdcall FUN_10009120();
extern "C" void __cdecl FUN_100099e0(void*, void*, std::uint32_t);

std::uint32_t __stdcall FUN_100096e0(
    std::int32_t param_1,
    std::int32_t param_2)
{
    if ((DAT_1003c400 & 1) == 0)
    {
        DAT_1003c400 = DAT_1003c400 | 1;
        DAT_1003c3f0 = "Unknown Plugin Name";
        DAT_1003c3f6 = 0;
        DAT_1003c3f4 = 0;
        FUN_10009120();
    }

    std::int32_t* pluginInterface = DAT_00c97c28;

    if ((DAT_1003c400 & 1) == 0)
    {
        DAT_1003c400 = DAT_1003c400 | 1;
        DAT_1003c3f0 = "Unknown Plugin Name";
        DAT_1003c3f6 = 0;
        DAT_1003c3f4 = 0;
        FUN_10009120();
    }

    void* plugin = *reinterpret_cast<void**>(
        static_cast<std::uintptr_t>(param_1 + param_2 * 4));

    if (plugin != nullptr)
    {
        FUN_100099e0(plugin, pluginInterface, 0xC9C040);
        return 0;
    }

    using VTableFunction = std::uint32_t(__thiscall*)(
        std::int32_t*, std::uint32_t);

    auto function = reinterpret_cast<VTableFunction>(
        static_cast<std::uintptr_t>(*pluginInterface + 0x40));

    return function(pluginInterface, 0xC9C040);
}
