#include <cstdint>

extern void* PTR_vftable_10037648;
extern void* DAT_10037670;
extern std::uint32_t DAT_10037674;
extern std::uint32_t DAT_10037678;
extern void* DAT_10037660;
extern std::uint32_t _DAT_10037664;
extern std::uint32_t _DAT_10037668;

extern void*
    BasicCallbackManager_5487649_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020bb0(void)
{
    PTR_vftable_10037648 =
        BasicCallbackManager_5487649_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037670 != nullptr) {
        FUN_10010756(DAT_10037670);
    }

    DAT_10037670 = nullptr;
    DAT_10037674 = 0;
    DAT_10037678 = 0;

    if (DAT_10037660 != nullptr) {
        FUN_10010756(DAT_10037660);
    }

    DAT_10037660 = nullptr;
    _DAT_10037664 = 0;
    _DAT_10037668 = 0;
}