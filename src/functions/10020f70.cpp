#include <cstdint>

extern void* PTR_vftable_10037878;
extern void* DAT_100378a0;
extern std::uint32_t DAT_100378a4;
extern std::uint32_t DAT_100378a8;
extern void* DAT_10037890;
extern std::uint32_t _DAT_10037894;
extern std::uint32_t _DAT_10037898;

extern void*
    BasicCallbackManager_5497491_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020f70(void)
{
    PTR_vftable_10037878 =
        BasicCallbackManager_5497491_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_100378a0 != nullptr) {
        FUN_10010756(DAT_100378a0);
    }

    DAT_100378a0 = nullptr;
    DAT_100378a4 = 0;
    DAT_100378a8 = 0;

    if (DAT_10037890 != nullptr) {
        FUN_10010756(DAT_10037890);
    }

    DAT_10037890 = nullptr;
    _DAT_10037894 = 0;
    _DAT_10037898 = 0;
}