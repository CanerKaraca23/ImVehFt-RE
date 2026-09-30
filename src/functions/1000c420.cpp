#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
#include <windows.h>
extern "C" void __stdcall thunk_FUN_10009580();
extern "C" void __stdcall FUN_100095f0();
#include <windows.h>
struct FUN_10009430_this
{
    int __thiscall FUN_10009430(char);
};
struct StateAt1003c3ec
{
    std::uint32_t unknown_0x0;
    HANDLE heap_handle;
};

static_assert(offsetof(StateAt1003c3ec, heap_handle) == 4);
extern "C" std::uint32_t DAT_1003c3fc;
extern "C" HANDLE DAT_1003c3e8;
extern "C" StateAt1003c3ec* DAT_1003c3ec;

extern "C" void __stdcall FUN_1000c420()
{
    extern std::uint32_t DAT_1003c3fc;
    extern int __cdecl _atexit(void (__cdecl*)());

    std::uint32_t uVar1;

    if ((DAT_1003c3fc & 1u) == 0)
    {
        DAT_1003c3fc = DAT_1003c3fc | 1u;
        DAT_1003c3e8 = 0;
        DAT_1003c3ec = nullptr;
        _atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_10009580));
    }

    uVar1 = reinterpret_cast<FUN_10009430_this*>(&DAT_1003c3e8)
                ->FUN_10009430('\0');

    if (static_cast<char>(uVar1) == '\0')
    {
        FUN_100095f0();
        return;
    }

    HeapAlloc(DAT_1003c3ec->heap_handle, 8, 0xCu);
    return;
}
