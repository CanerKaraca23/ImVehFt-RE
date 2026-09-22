#include <cstdint>

extern void* PTR_vftable_100375a0;
extern void* DAT_100375c8;
extern std::uint32_t DAT_100375cc;
extern std::uint32_t DAT_100375d0;
extern void* DAT_100375b8;
extern std::uint32_t DAT_100375bc;
extern std::uint32_t DAT_100375c0;

extern void* BasicCallbackManager_4459021_5487817_5488269_5488583_6393605_SimpleSuperManager_PatcherCALL1_vftable;
extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020a90(void)
{
    PTR_vftable_100375a0 =
        BasicCallbackManager_4459021_5487817_5488269_5488583_6393605_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_100375c8 != nullptr) {
        FUN_10010756(DAT_100375c8);
    }

    DAT_100375c8 = nullptr;
    DAT_100375cc = 0;
    DAT_100375d0 = 0;

    if (DAT_100375b8 != nullptr) {
        FUN_10010756(DAT_100375b8);
    }

    DAT_100375b8 = nullptr;
    DAT_100375bc = 0;
    DAT_100375c0 = 0;
}