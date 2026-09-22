#include <cstdint>

extern void* PTR_vftable_10037798;
extern void* DAT_100377c0;
extern std::uint32_t DAT_100377c4;
extern std::uint32_t DAT_100377c8;
extern void* DAT_100377b0;
extern std::uint32_t _DAT_100377b4;
extern std::uint32_t _DAT_100377b8;

extern void*
    BasicCallbackManager_4625275_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020df0(void)
{
    PTR_vftable_10037798 =
        BasicCallbackManager_4625275_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_100377c0 != nullptr) {
        FUN_10010756(DAT_100377c0);
    }

    DAT_100377c0 = nullptr;
    DAT_100377c4 = 0;
    DAT_100377c8 = 0;

    if (DAT_100377b0 != nullptr) {
        FUN_10010756(DAT_100377b0);
    }

    DAT_100377b0 = nullptr;
    _DAT_100377b4 = 0;
    _DAT_100377b8 = 0;
}