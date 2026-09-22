#include <cstdint>

extern void* PTR_vftable_10037808;
extern void* DAT_10037830;
extern std::uint32_t DAT_10037834;
extern std::uint32_t DAT_10037838;
extern void* DAT_10037820;
extern std::uint32_t DAT_10037824;
extern std::uint32_t DAT_10037828;

extern void*
    BasicCallbackManager_6027355_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020eb0(void)
{
    PTR_vftable_10037808 =
        BasicCallbackManager_6027355_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037830 != nullptr) {
        FUN_10010756(DAT_10037830);
    }

    DAT_10037830 = nullptr;
    DAT_10037834 = 0;
    DAT_10037838 = 0;

    if (DAT_10037820 != nullptr) {
        FUN_10010756(DAT_10037820);
    }

    DAT_10037820 = nullptr;
    DAT_10037824 = 0;
    DAT_10037828 = 0;
}