#include <cstdint>

extern void* PTR_vftable_10037728;
extern void* DAT_10037750;
extern std::uint32_t DAT_10037754;
extern std::uint32_t DAT_10037758;
extern void* DAT_10037740;
extern std::uint32_t DAT_10037744;
extern std::uint32_t DAT_10037748;

extern void*
    BasicCallbackManager_5810733_0_0_0_0_SimpleSuperManager_PatcherJMP1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020d30(void)
{
    PTR_vftable_10037728 =
        BasicCallbackManager_5810733_0_0_0_0_SimpleSuperManager_PatcherJMP1_vftable;

    if (DAT_10037750 != nullptr) {
        FUN_10010756(DAT_10037750);
    }

    DAT_10037750 = nullptr;
    DAT_10037754 = 0;
    DAT_10037758 = 0;

    if (DAT_10037740 != nullptr) {
        FUN_10010756(DAT_10037740);
    }

    DAT_10037740 = nullptr;
    DAT_10037744 = 0;
    DAT_10037748 = 0;
}