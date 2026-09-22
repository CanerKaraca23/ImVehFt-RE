#include <cstdint>

extern void* PTR_vftable_1003c328;
extern void* DAT_1003c37c;
extern std::uint32_t DAT_1003c380;
extern std::uint32_t DAT_1003c384;
extern void* DAT_1003c36c;
extern std::uint32_t DAT_1003c370;
extern std::uint32_t DAT_1003c374;

extern void*
    BasicCallbackManager_0_0_0_0_0_cbResetDeviceManager_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020fd0(void)
{
    PTR_vftable_1003c328 =
        BasicCallbackManager_0_0_0_0_0_cbResetDeviceManager_vftable;

    if (DAT_1003c37c != nullptr) {
        FUN_10010756(DAT_1003c37c);
    }

    DAT_1003c37c = nullptr;
    DAT_1003c380 = 0;
    DAT_1003c384 = 0;

    if (DAT_1003c36c != nullptr) {
        FUN_10010756(DAT_1003c36c);
    }

    DAT_1003c36c = nullptr;
    DAT_1003c370 = 0;
    DAT_1003c374 = 0;
}