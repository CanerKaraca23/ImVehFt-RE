#include <cstdint>

extern int DAT_1003aacc;

extern "C" int __cdecl FUN_10001b00(int param_1)
{
    int iVar1;

    if ((param_1 != 0) &&
        (iVar1 = *reinterpret_cast<int*>(DAT_1003aacc + 0xc + param_1), iVar1 != 0))
    {
        reinterpret_cast<void (__cdecl *)(int)>(
            static_cast<std::uintptr_t>(0x7f3820))(iVar1);
    }

    return param_1;
}