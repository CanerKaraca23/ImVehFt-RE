#include <cstdint>
#include <intrin.h>

extern "C" void __cdecl FUN_10017cd2(std::int32_t param_1);

extern "C" void __stdcall FUN_1001803c(void)
{
    // Uses the caller's EBP-relative value at offset -0x1C.
    // The exact source-level object corresponding to this value is unresolved.
    if (*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) - 0x20) != 0)
    {
        FUN_10017cd2(0);
    }
}