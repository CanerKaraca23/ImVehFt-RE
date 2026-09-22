#include <cstdint>

extern void* PTR_vftable_100377d0;
extern void* DAT_100377f8;
extern std::uint32_t DAT_100377fc;
extern std::uint32_t DAT_10037800;
extern void* DAT_100377e8;
extern std::uint32_t DAT_100377ec;
extern std::uint32_t DAT_100377f0;

extern void*
    BasicCallbackManager_5498111_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020e50(void)
{
    PTR_vftable_100377d0 =
        BasicCallbackManager_5498111_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_100377f8 != nullptr) {
        FUN_10010756(DAT_100377f8);
    }

    DAT_100377f8 = nullptr;
    DAT_100377fc = 0;
    DAT_10037800 = 0;

    if (DAT_100377e8 != nullptr) {
        FUN_10010756(DAT_100377e8);
    }

    DAT_100377e8 = nullptr;
    DAT_100377ec = 0;
    DAT_100377f0 = 0;
}