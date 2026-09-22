#include <cstdint>

extern "C" using Initializer = void(__cdecl*)();
extern "C" using RuntimeFunction = void(__cdecl*)(int, int, int);
extern "C" using FpmathFunction = void(__cdecl*)(int);

extern "C" int __cdecl __IsNonwritableInCurrentImage(std::uint8_t* address);
extern "C" void __cdecl __initp_misc_cfltcvt_tab();
extern "C" int __cdecl __initterm_e(std::uint32_t* begin, std::uint32_t* end);
extern "C" int __cdecl _atexit(void(__cdecl* function)());
extern "C" void __stdcall FUN_10020870();

extern "C" FpmathFunction PTR___fpmath_10025004;
extern "C" std::uint32_t DAT_100221b8[];
extern "C" std::uint32_t DAT_100221d0[];
extern "C" std::uint32_t DAT_10022154[];
extern "C" std::uint32_t DAT_100221b4[];
extern "C" RuntimeFunction DAT_1003d554;

extern "C" int __cdecl __cinit(int param_1)
{
    if (PTR___fpmath_10025004 != nullptr &&
        __IsNonwritableInCurrentImage(
            reinterpret_cast<std::uint8_t*>(&PTR___fpmath_10025004)) != 0)
    {
        PTR___fpmath_10025004(param_1);
    }

    __initp_misc_cfltcvt_tab();

    int result = __initterm_e(DAT_100221b8, DAT_100221d0);

    if (result == 0)
    {
        _atexit(reinterpret_cast<void(__cdecl*)()>(FUN_10020870));

        std::uint32_t* initializer = DAT_10022154;
        do
        {
            if (*initializer != 0U)
            {
                reinterpret_cast<Initializer>(
                    static_cast<std::uintptr_t>(*initializer))();
            }

            ++initializer;
        }
        while (initializer < DAT_100221b4);

        if (DAT_1003d554 != nullptr &&
            __IsNonwritableInCurrentImage(
                reinterpret_cast<std::uint8_t*>(&DAT_1003d554)) != 0)
        {
            DAT_1003d554(0, 2, 0);
        }

        result = 0;
    }

    return result;
}