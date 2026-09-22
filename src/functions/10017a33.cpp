#include <cstdint>

extern "C" void* PTR_LAB_10029d40[10];

extern "C" void* __stdcall EncodePointer(void* Ptr);

extern "C" void __stdcall __initp_misc_cfltcvt_tab(void)
{
    std::uint32_t uVar2 = 0;

    do
    {
        void** entry = reinterpret_cast<void**>(
            reinterpret_cast<std::uintptr_t>(&PTR_LAB_10029d40) + uVar2);

        void* pvVar1 = EncodePointer(*entry);
        *entry = pvVar1;

        uVar2 = uVar2 + 4;
    } while (uVar2 < 0x28);

    return;
}