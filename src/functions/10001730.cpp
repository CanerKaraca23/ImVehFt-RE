#include <cstdint>

extern int DAT_1003aac8;

extern "C" void __cdecl FUN_100014c0(char* format, ...);

extern "C" void __stdcall FUN_10001730()
{
    int unaff_ESI;
    __asm mov unaff_ESI, esi

    if (unaff_ESI != 0)
    {
        if (*reinterpret_cast<int*>(unaff_ESI + 0x54) < 2)
        {
            DAT_1003aac8 = DAT_1003aac8 + -1;

            FUN_100014c0(
                const_cast<char*>("____UNLOADED_TEXTURE %s, TEXTURES_LEFT: %d"));
        }

        reinterpret_cast<void (__cdecl*)(int)>(
            static_cast<std::uintptr_t>(0x7f3820))(unaff_ESI);
    }
}