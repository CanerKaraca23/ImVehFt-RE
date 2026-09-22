#include <windows.h>

extern int* DAT_1003c3ec;

struct FUN_10009430_this {
    int __thiscall FUN_10009430(char param_1);
};
extern "C" void __stdcall FUN_100095f0();

extern "C" void __stdcall FUN_100094d0()
{
    int* state = DAT_1003c3ec;
    HANDLE mappingHandle;
    LPVOID mappedView;
    int result;

    if (*state == 0)
    {
        mappingHandle = CreateFileMappingA(
            reinterpret_cast<HANDLE>(0xFFFFFFFF),
            nullptr,
            0x8000004,
            0,
            0x400,
            "GTA_PLUGIN_SDK");

        *state = reinterpret_cast<int>(mappingHandle);

        if (mappingHandle == nullptr)
            return;
    }

    if (state[1] == 0)
    {
        mappedView = MapViewOfFile(
            reinterpret_cast<HANDLE>(*state),
            0xF001F,
            0,
            0,
            0);

        state[1] = reinterpret_cast<int>(mappedView);
    }

    HANDLE heapHandle = HeapCreate(0, 8000, 0);
    *reinterpret_cast<HANDLE*>(state[1] + 4) = heapHandle;

    if (*reinterpret_cast<int*>(state[1] + 4) != 0)
    {
        *reinterpret_cast<int*>(state[1]) = 1;
        *reinterpret_cast<int*>(state[1] + 8) = 0x800;

        result = reinterpret_cast<FUN_10009430_this*>(state)->FUN_10009430('\0');

        if (static_cast<char>(result) != '\0')
        {
            mappedView = HeapAlloc(
                *reinterpret_cast<HANDLE*>(state[1] + 4),
                8,
                0x800);

            *reinterpret_cast<LPVOID*>(state[1] + 0xC) = mappedView;
            return;
        }

        FUN_100095f0();
        return;
    }

    FUN_100095f0();
}