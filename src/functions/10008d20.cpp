#include <cstdint>

using Float10 = long double;

// The calling convention of the indirect target at 0x0053CC70 is unresolved.
using UnknownFloatFunction = Float10 (*)(std::uint32_t, std::uint32_t);

extern float _DAT_10024e70;
extern float _DAT_10024e78;
extern std::uintptr_t _PTR_10024e68;

extern "C" void __stdcall FUN_10008d20()
{
    std::uint32_t in_EAX;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm mov in_EAX, eax
#else
#error "FUN_10008d20 requires access to the incoming EAX register."
#endif

    const auto function_0053cc70 =
        reinterpret_cast<UnknownFloatFunction>(0x0053CC70u);

    float fVar1 = static_cast<float>(
        function_0053cc70(
            *reinterpret_cast<const std::uint32_t*>(
                static_cast<std::uintptr_t>(in_EAX) + 0x10u),
            *reinterpret_cast<const std::uint32_t*>(
                static_cast<std::uintptr_t>(in_EAX) + 0x14u))
        * static_cast<Float10>(_DAT_10024e78)
        - static_cast<Float10>(_DAT_10024e70));

    if (0.0f <= fVar1)
    {
        return;
    }

    do
    {
        fVar1 = fVar1 + static_cast<float>(_PTR_10024e68);
    }
    while (fVar1 < 0.0f);

    return;
}