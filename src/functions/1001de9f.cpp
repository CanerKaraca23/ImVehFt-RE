#include <cstdint>

using errno_t = int;

extern "C" std::uint32_t __cdecl __control87(
    std::uint32_t newValue,
    std::uint32_t mask);

extern "C" int* __cdecl __errno();

extern "C" void __stdcall FUN_1001189f();

extern "C" errno_t __cdecl __controlfp_s(
    std::uint32_t* currentState,
    std::uint32_t newValue,
    std::uint32_t mask)
{
    std::uint32_t maskedValue = mask & 0xfff7ffffU;
    errno_t result;

    if ((newValue & maskedValue & 0xfcf0fce0U) == 0U)
    {
        if (currentState == nullptr)
        {
            __control87(newValue, maskedValue);
        }
        else
        {
            maskedValue = __control87(newValue, maskedValue);
            *currentState = maskedValue;
        }

        result = 0;
    }
    else
    {
        if (currentState != nullptr)
        {
            maskedValue = __control87(0U, 0U);
            *currentState = maskedValue;
        }

        int* errorNumber = __errno();
        result = 0x16;
        *errorNumber = 0x16;
        FUN_1001189f();
    }

    return result;
}