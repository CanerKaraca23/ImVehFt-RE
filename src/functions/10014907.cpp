#include <cstdint>
#include <windows.h>

extern "C" void __cdecl ___addlocaleref(LONG* param_1)
{
    LONG* const original = param_1;

    InterlockedIncrement(param_1);

    if (param_1[0x2C] != 0)
        InterlockedIncrement(reinterpret_cast<LONG*>(param_1[0x2C]));

    if (param_1[0x2E] != 0)
        InterlockedIncrement(reinterpret_cast<LONG*>(param_1[0x2E]));

    if (param_1[0x2D] != 0)
        InterlockedIncrement(reinterpret_cast<LONG*>(param_1[0x2D]));

    if (param_1[0x30] != 0)
        InterlockedIncrement(reinterpret_cast<LONG*>(param_1[0x30]));

    LONG* entry = param_1 + 0x14;

    for (int count = 6; count != 0; --count)
    {
        if (reinterpret_cast<void*>(entry[-2]) !=
                reinterpret_cast<void*>(0x100299C4) &&
            entry[0] != 0)
        {
            InterlockedIncrement(reinterpret_cast<LONG*>(entry[0]));
        }

        if (entry[-1] != 0 && entry[1] != 0)
            InterlockedIncrement(reinterpret_cast<LONG*>(entry[1]));

        entry += 4;
    }

    InterlockedIncrement(reinterpret_cast<LONG*>(
        static_cast<std::uintptr_t>(original[0x35]) + 0xB4));
}