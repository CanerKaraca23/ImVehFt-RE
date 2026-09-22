#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
#include <windows.h>
extern "C" void __stdcall thunk_FUN_10009580();
extern "C" void __stdcall FUN_100095f0();
#include <windows.h>
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

    using MappingEnsureFn = std::uint32_t (__thiscall*)(void*, char);

    std::uint32_t uVar1;

    if ((DAT_1003c3fc & 1u) == 0)
    {
        DAT_1003c3fc = DAT_1003c3fc | 1u;
        DAT_1003c3e8 = 0;
        DAT_1003c3ec = nullptr;
        _atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_10009580));
    }

    uVar1 = reinterpret_cast<MappingEnsureFn>(static_cast<std::uintptr_t>(0x10009430))(&DAT_1003c3e8, '\0');

    if (static_cast<char>(uVar1) == '\0')
    {
        FUN_100095f0();
        return;
    }

    HeapAlloc(DAT_1003c3ec->heap_handle, 8, 0xCu);
    return;
}