#include <cstdint>

extern "C" std::uint32_t DAT_10029d74;
extern "C" void* DAT_10029d70;
extern "C" std::uint8_t DAT_1003a1c8;

extern "C" int __stdcall InitializeCriticalSectionAndSpinCount(
    void* lpCriticalSection,
    std::uint32_t dwSpinCount);

extern "C" int __cdecl __mtinitlocks(void)
{
    int iVar2 = 0;
    std::uint8_t* puVar3 = &DAT_1003a1c8;

    auto* lock_flags = reinterpret_cast<std::uint32_t*>(&DAT_10029d74);
    auto* lock_slots = reinterpret_cast<void**>(&DAT_10029d70);

    do
    {
        if (lock_flags[iVar2 * 2] == 1)
        {
            lock_slots[iVar2 * 2] = puVar3;
            puVar3 = puVar3 + 0x18;

            const int BVar1 =
                InitializeCriticalSectionAndSpinCount(
                    lock_slots[iVar2 * 2],
                    4000);

            if (BVar1 == 0)
            {
                lock_slots[iVar2 * 2] = nullptr;
                return 0;
            }
        }

        iVar2 = iVar2 + 1;
    }
    while (iVar2 < 0x24);

    return 1;
}