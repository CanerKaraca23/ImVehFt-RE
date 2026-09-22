#include <cstdint>

extern void* PTR_vftable_100375d8;
extern void* DAT_10037600;
extern std::uint32_t DAT_10037604;
extern std::uint32_t DAT_10037608;
extern void* DAT_100375f0;
extern std::uint32_t _DAT_100375f4;
extern std::uint32_t _DAT_100375f8;

extern void* BasicCallbackManager_5499395_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;
extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020af0(void)
{
    PTR_vftable_100375d8 =
        BasicCallbackManager_5499395_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037600 != nullptr) {
        FUN_10010756(DAT_10037600);
    }

    DAT_10037600 = nullptr;
    DAT_10037604 = 0;
    DAT_10037608 = 0;

    if (DAT_100375f0 != nullptr) {
        FUN_10010756(DAT_100375f0);
    }

    DAT_100375f0 = nullptr;
    _DAT_100375f4 = 0;
    _DAT_100375f8 = 0;
}