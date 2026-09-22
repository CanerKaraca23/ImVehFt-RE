#include <cstdint>

extern "C" std::uint32_t DAT_1003a324;

extern "C" void* __stdcall DecodePointer(void* Ptr);

extern "C" void __stdcall FUN_10017ec8(void)
{
    (void)DecodePointer(
        reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(DAT_1003a324)));
}