#include <windows.h>
#include <cstdlib>

extern int _DAT_1003c3fc;
extern HANDLE DAT_1003c3e8;
extern int* DAT_1003c3ec;

extern "C" void __stdcall thunk_FUN_10009580();
extern "C" __declspec(noreturn) void __stdcall FUN_100095f0();
extern "C" void __stdcall FUN_100094d0();


extern "C" int __stdcall FUN_10009360()
{
    HANDLE mappingHandle;
    int* mappingView;

    if ((_DAT_1003c3fc & 1) == 0)
    {
        _DAT_1003c3fc |= 1;
        DAT_1003c3e8 = nullptr;
        DAT_1003c3ec = nullptr;
        std::atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_10009580));
    }

    if (DAT_1003c3ec == nullptr)
    {
        if (DAT_1003c3e8 == nullptr)
            goto LAB_100093aa;

    LAB_100093cb:
        if (DAT_1003c3ec != nullptr ||
            (DAT_1003c3ec = static_cast<int*>(
                 MapViewOfFile(DAT_1003c3e8, 0xF001F, 0, 0, 0)),
             DAT_1003c3ec != nullptr))
        {
            mappingHandle = DAT_1003c3e8;
            mappingView = DAT_1003c3ec;

            if (DAT_1003c3e8 != nullptr && *DAT_1003c3ec == 0)
            {
                FUN_100095f0();
            }

            goto LAB_100093fd;
        }
    }
    else
    {
        mappingHandle = DAT_1003c3e8;
        mappingView = DAT_1003c3ec;

        if (DAT_1003c3e8 != nullptr)
            goto LAB_1000941c;

    LAB_100093aa:
        DAT_1003c3e8 = OpenFileMappingA(0xF001F, FALSE, "GTA_PLUGIN_SDK");
        mappingHandle = DAT_1003c3e8;
        mappingView = DAT_1003c3ec;

        if (DAT_1003c3e8 != nullptr)
            goto LAB_100093cb;

    LAB_100093fd:
        if (mappingView != nullptr && mappingHandle != nullptr)
            goto LAB_1000941c;
    }

    FUN_100094d0();
    mappingHandle = DAT_1003c3e8;
    mappingView = DAT_1003c3ec;

LAB_1000941c:
    if (mappingView == nullptr || mappingHandle == nullptr)
    {
        FUN_100095f0();
    }

    return mappingView[3];
}