#include <cstdint>

extern void* PTR_vftable_100376b8;
extern void* DAT_100376e0;
extern std::uint32_t DAT_100376e4;
extern std::uint32_t DAT_100376e8;
extern void* DAT_100376d0;
extern std::uint32_t _DAT_100376d4;
extern std::uint32_t _DAT_100376d8;

extern void*
    BasicCallbackManager_7638537_7638600_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020c70(void)
{
    PTR_vftable_100376b8 =
        BasicCallbackManager_7638537_7638600_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_100376e0 != nullptr) {
        FUN_10010756(DAT_100376e0);
    }

    DAT_100376e0 = nullptr;
    DAT_100376e4 = 0;
    DAT_100376e8 = 0;

    if (DAT_100376d0 != nullptr) {
        FUN_10010756(DAT_100376d0);
    }

    DAT_100376d0 = nullptr;
    _DAT_100376d4 = 0;
    _DAT_100376d8 = 0;
}