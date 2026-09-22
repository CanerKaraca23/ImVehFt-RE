#include <cstdint>

extern "C" void __cdecl __initterm_e(std::uint32_t* param_1,
                                     std::uint32_t* param_2)
{
    int iVar1 = 0;

    while ((param_1 < param_2) && (iVar1 == 0))
    {
        if (*param_1 != 0U)
        {
            using Function = int(__cdecl*)();
            iVar1 = reinterpret_cast<Function>(
                static_cast<std::uintptr_t>(*param_1))();
        }

        ++param_1;
    }
}