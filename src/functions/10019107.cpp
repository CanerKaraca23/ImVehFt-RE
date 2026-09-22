#include <Windows.h>
#include <cstdint>

extern "C" std::uint8_t* DAT_1003c420[];

extern "C" void __cdecl __lock(int _File);
extern "C" void __stdcall FUN_1001919d();

extern "C" int __cdecl ___lock_fhandle(int _Filehandle)
{
    std::uint8_t* iVar2 =
        DAT_1003c420[_Filehandle >> 5] +
        ((_Filehandle & 0x1fU) * 0x40U);

    std::uint32_t local_20 = 1U;

    if (*reinterpret_cast<std::int32_t*>(iVar2 + 8U) == 0)
    {
        __lock(10);

        if (*reinterpret_cast<std::int32_t*>(iVar2 + 8U) == 0)
        {
            const BOOL BVar1 =
                InitializeCriticalSectionAndSpinCount(
                    reinterpret_cast<LPCRITICAL_SECTION>(iVar2 + 0x0cU),
                    4000U);

            local_20 = static_cast<std::uint32_t>(BVar1 != 0);
            *reinterpret_cast<std::int32_t*>(iVar2 + 8U) =
                *reinterpret_cast<std::int32_t*>(iVar2 + 8U) + 1;
        }

        FUN_1001919d();
    }

    if (local_20 != 0U)
    {
        EnterCriticalSection(
            reinterpret_cast<LPCRITICAL_SECTION>(iVar2 + 0x0cU));
    }

    return static_cast<int>(local_20);
}