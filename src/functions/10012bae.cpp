#include <cstdint>

extern "C" std::uint32_t __stdcall FUN_10014c40(void);
extern "C" std::uint32_t __cdecl FUN_10013efc(std::uint32_t param_1);
extern "C" std::uint32_t __cdecl FUN_10011715(std::uint32_t param_1);
extern "C" std::uint32_t __cdecl FUN_100172be(std::uint32_t param_1);
extern "C" std::uint32_t __cdecl FUN_10018078(std::uint32_t param_1);
extern "C" std::uint32_t __cdecl __initp_misc_winsig(std::uint32_t param_1);
extern "C" std::uint32_t __stdcall FUN_10017e62(void);

extern "C" void __cdecl __init_pointers(void)
{
    const std::uint32_t uVar1 = FUN_10014c40();

    FUN_10013efc(uVar1);
    FUN_10011715(uVar1);
    FUN_100172be(uVar1);
    FUN_10018078(uVar1);
    __initp_misc_winsig(uVar1);
    FUN_10017e62();
}