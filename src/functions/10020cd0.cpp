#include <cstdint>

extern void* PTR_vftable_100376f0;
extern void* DAT_10037718;
extern std::uint32_t DAT_1003771c;
extern std::uint32_t DAT_10037720;
extern void* DAT_10037708;
extern std::uint32_t _DAT_1003770c;
extern std::uint32_t _DAT_10037710;

extern void*
    BasicCallbackManager_5499265_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020cd0(void)
{
    PTR_vftable_100376f0 =
        BasicCallbackManager_5499265_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037718 != nullptr) {
        FUN_10010756(DAT_10037718);
    }

    DAT_10037718 = nullptr;
    DAT_1003771c = 0;
    DAT_10037720 = 0;

    if (DAT_10037708 != nullptr) {
        FUN_10010756(DAT_10037708);
    }

    DAT_10037708 = nullptr;
    _DAT_1003770c = 0;
    _DAT_10037710 = 0;
}