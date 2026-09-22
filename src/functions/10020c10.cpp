#include <cstdint>

extern void* PTR_vftable_10037680;
extern void* DAT_100376a8;
extern std::uint32_t DAT_100376ac;
extern std::uint32_t DAT_100376b0;
extern void* DAT_10037698;
extern std::uint32_t _DAT_1003769c;
extern std::uint32_t _DAT_100376a0;

extern void*
    BasicCallbackManager_7638267_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020c10(void)
{
    PTR_vftable_10037680 =
        BasicCallbackManager_7638267_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_100376a8 != nullptr) {
        FUN_10010756(DAT_100376a8);
    }

    DAT_100376a8 = nullptr;
    DAT_100376ac = 0;
    DAT_100376b0 = 0;

    if (DAT_10037698 != nullptr) {
        FUN_10010756(DAT_10037698);
    }

    DAT_10037698 = nullptr;
    _DAT_1003769c = 0;
    _DAT_100376a0 = 0;
}