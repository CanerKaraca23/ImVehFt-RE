#include <windows.h>
#include <cstdint>
#include <cstdio>

extern char DAT_1003a8c8[0x200];
extern std::uint8_t DAT_1003a6c4;
extern std::uint8_t DAT_1003a6c5;
extern FILE* DAT_1003a6c0;

extern "C" FILE* __stdcall FUN_10001520();
extern "C" std::uint8_t __fastcall FUN_1000a560(std::int32_t param_1);

extern "C" int __cdecl fclose(FILE* file);

extern "C" std::uint32_t __stdcall FUN_10001db0(std::uint32_t, std::int32_t param_2)
{
    HMODULE hModule;
    char* pcVar1;

    if (param_2 == 1)
    {
        hModule = GetModuleHandleA("ImVehFt.asi");
        GetModuleFileNameA(hModule, DAT_1003a8c8, 0x200);

        pcVar1 = strrchr(DAT_1003a8c8, 0x5c);
        if (pcVar1 != nullptr)
        {
            pcVar1 = strrchr(DAT_1003a8c8, 0x5c);
            pcVar1[1] = '\0';
        }

        DAT_1003a6c5 = 1;
        DAT_1003a6c0 = FUN_10001520();
        DAT_1003a6c4 = 1;

        FUN_1000a560(6);
        FUN_1000a560(0xf);

        return 1;
    }

    if ((param_2 == 0) && (DAT_1003a6c4 != '\0'))
    {
        DAT_1003a6c4 = '\0';
        fclose(DAT_1003a6c0);
    }

    return 1;
}