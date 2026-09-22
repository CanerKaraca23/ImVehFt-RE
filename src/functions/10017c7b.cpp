#include <cstdint>

extern "C" void* DAT_10029d70;

extern "C" void __stdcall DeleteCriticalSection(void* lpCriticalSection);
extern "C" void __cdecl _free(void* _Memory);

extern "C" void __cdecl __mtdeletelocks(void)
{
    auto* puVar1 =
        reinterpret_cast<std::uint32_t*>(&DAT_10029d70);

    do
    {
        void* lpCriticalSection =
            reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(puVar1[0]));

        if ((lpCriticalSection != nullptr) && (puVar1[1] != 1))
        {
            DeleteCriticalSection(lpCriticalSection);
            _free(lpCriticalSection);
            puVar1[0] = 0;
        }

        puVar1 += 2;
    }
    while (reinterpret_cast<std::uintptr_t>(puVar1) < 0x10029e90u);

    puVar1 =
        reinterpret_cast<std::uint32_t*>(&DAT_10029d70);

    do
    {
        void* lpCriticalSection =
            reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(puVar1[0]));

        if ((lpCriticalSection != nullptr) && (puVar1[1] == 1))
        {
            DeleteCriticalSection(lpCriticalSection);
        }

        puVar1 += 2;
    }
    while (reinterpret_cast<std::uintptr_t>(puVar1) < 0x10029e90u);
}