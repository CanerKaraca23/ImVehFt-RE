#include <cstdint>

extern void* PTR_vftable_10037760;
extern void* DAT_10037788;
extern std::uint32_t DAT_1003778c;
extern std::uint32_t DAT_10037790;
extern void* DAT_10037778;
extern std::uint32_t _DAT_1003777c;
extern std::uint32_t _DAT_10037780;

extern void*
    BasicCallbackManager_5500065_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020d90(void)
{
    PTR_vftable_10037760 =
        BasicCallbackManager_5500065_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037788 != nullptr) {
        FUN_10010756(DAT_10037788);
    }

    DAT_10037788 = nullptr;
    DAT_1003778c = 0;
    DAT_10037790 = 0;

    if (DAT_10037778 != nullptr) {
        FUN_10010756(DAT_10037778);
    }

    DAT_10037778 = nullptr;
    _DAT_1003777c = 0;
    _DAT_10037780 = 0;
}