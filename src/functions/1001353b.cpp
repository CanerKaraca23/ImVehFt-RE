#include <Windows.h>
#include <cstdint>

extern "C" std::uint32_t DAT_1003c420[64];
extern "C" void __cdecl _free(void* memory);

void __cdecl __ioterm(void)
{
    std::uint32_t* puVar3 = DAT_1003c420;

    do
    {
        const std::uint32_t uVar1 = *puVar3;

        if (uVar1 != 0)
        {
            if (uVar1 < uVar1 + 0x800)
            {
                LPCRITICAL_SECTION lpCriticalSection =
                    reinterpret_cast<LPCRITICAL_SECTION>(
                        static_cast<std::uintptr_t>(uVar1) + 0x0c);

                LPCRITICAL_SECTION p_Var2 = nullptr;
                do
                {
                    if (lpCriticalSection[-1].SpinCount != 0)
                    {
                        DeleteCriticalSection(lpCriticalSection);
                    }

                    p_Var2 = lpCriticalSection + 2;
                    lpCriticalSection =
                        reinterpret_cast<LPCRITICAL_SECTION>(
                            &p_Var2->LockSemaphore);
                }
                while (
                    reinterpret_cast<std::uint8_t*>(
                        &p_Var2->LockCount)
                    <
                    reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(*puVar3) + 0x800));
            }

            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(*puVar3)));

            *puVar3 = 0;
        }

        ++puVar3;
    }
    while (puVar3 < DAT_1003c420 + 64);
}