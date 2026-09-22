#include <windows.h>

extern "C" void __stdcall FUN_100095f0()
{
    MessageBoxA(
        static_cast<HWND>(nullptr),
        "Fatal error on ControllerBlockManager",
        "Plugin SDK",
        0x10);

    ExitProcess(0xDE);
}