#include <cstdint>

using errno_t = int;

extern "C" unsigned char DAT_10028500;

extern "C" void __cdecl __SEH_prolog4();
extern "C" void __cdecl __SEH_epilog4();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

extern "C" errno_t __cdecl FUN_100182c1(
    std::uint32_t* param_1,
    char* param_2,
    std::uint32_t param_3,
    int param_4,
    std::uint8_t param_5);

extern "C" void __stdcall FUN_10018a8b();

extern "C" errno_t __cdecl FID_conflict___sopen_helper(
    char* _Filename,
    int _OFlag,
    int _ShFlag,
    int _PMode,
    int* _PFileHandle,
    int _BSecure)
{
    __SEH_prolog4();

    std::uint32_t local_20[5];
    std::uint32_t uStack_c;
    void* local_8;

    local_8 = &DAT_10028500;
    uStack_c = 0x10018a01u;
    local_20[0] = 0;

    errno_t eVar2;

    if (((_PFileHandle == nullptr) ||
         (*_PFileHandle = -1, _Filename == nullptr)) ||
        ((_BSecure != 0) && ((_PMode & 0xFFFFFE7F) != 0)))
    {
        int* piVar1 = __errno();
        eVar2 = 0x16;
        *piVar1 = 0x16;
        FUN_1001189f();
    }
    else
    {
        local_8 = nullptr;

        eVar2 = FUN_100182c1(
            local_20,
            _Filename,
            static_cast<std::uint32_t>(_OFlag),
            _ShFlag,
            static_cast<std::uint8_t>(_PMode));

        local_8 = reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(0xFFFFFFFEu));

        FUN_10018a8b();

        if (eVar2 != 0)
        {
            *_PFileHandle = -1;
        }
    }

    __SEH_epilog4();
    return eVar2;
}