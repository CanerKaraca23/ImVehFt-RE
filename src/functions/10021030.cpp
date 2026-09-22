#include <cstdint>

extern void* PTR_vftable_100378b0;
extern void* DAT_100378d8;
extern std::uint32_t DAT_100378dc;
extern std::uint32_t DAT_100378e0;
extern void* DAT_100378c8;
extern std::uint32_t _DAT_100378cc;
extern std::uint32_t _DAT_100378d0;

extern void* BasicCallbackManager_5499603_0_0_0_0_cbPostFXManager_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10021030(void)
{
    PTR_vftable_100378b0 =
        BasicCallbackManager_5499603_0_0_0_0_cbPostFXManager_vftable;

    if (DAT_100378d8 != nullptr) {
        FUN_10010756(DAT_100378d8);
    }

    DAT_100378d8 = nullptr;
    DAT_100378dc = 0;
    DAT_100378e0 = 0;

    if (DAT_100378c8 != nullptr) {
        FUN_10010756(DAT_100378c8);
    }

    DAT_100378c8 = nullptr;
    _DAT_100378cc = 0;
    _DAT_100378d0 = 0;
}