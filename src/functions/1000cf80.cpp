#include <cstddef>
#include <cstdint>

extern std::uint32_t _DAT_1003c3fc;
extern std::uint8_t DAT_1003c3e8;
extern std::uint8_t* DAT_1003c3ec;

extern "C" int __cdecl _atexit(void (__cdecl* function)());
extern "C" void __stdcall thunk_FUN_10009580();
using MappingEnsureFn = std::uint32_t (__thiscall*)(void*, char);
extern "C" void __stdcall FUN_100095f0();
extern "C" void* __stdcall HeapAlloc(
    void* heap,
    std::uint32_t flags,
    std::size_t bytes);

extern "C" void __stdcall FUN_1000cf80()
{
    std::uint32_t uVar1;

    if ((_DAT_1003c3fc & 1U) == 0U)
    {
        _DAT_1003c3fc = _DAT_1003c3fc | 1U;
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

    HeapAlloc(
        *reinterpret_cast<void**>(DAT_1003c3ec + 4),
        8U,
        0x1cU);

    return;
}