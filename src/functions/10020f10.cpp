#include <cstdint>

extern void* PTR_vftable_10037840;
extern void* DAT_10037868;
extern std::uint32_t _DAT_1003786c;
extern std::uint32_t _DAT_10037870;
extern void* DAT_10037858;
extern std::uint32_t _DAT_1003785c;
extern std::uint32_t _DAT_10037860;

extern void*
    BasicCallbackManager_5499603_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020f10(void)
{
    PTR_vftable_10037840 =
        BasicCallbackManager_5499603_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037868 != nullptr) {
        FUN_10010756(DAT_10037868);
    }

    DAT_10037868 = nullptr;
    _DAT_1003786c = 0;
    _DAT_10037870 = 0;

    if (DAT_10037858 != nullptr) {
        FUN_10010756(DAT_10037858);
    }

    DAT_10037858 = nullptr;
    _DAT_1003785c = 0;
    _DAT_10037860 = 0;
}