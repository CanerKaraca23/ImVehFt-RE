#include <cstdint>

extern void* PTR_vftable_10037610;
extern void* DAT_10037638;
extern std::uint32_t DAT_1003763c;
extern std::uint32_t DAT_10037640;
extern void* DAT_10037628;
extern std::uint32_t _DAT_1003762c;
extern std::uint32_t _DAT_10037630;

extern void*
    BasicCallbackManager_6018937_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020b50(void)
{
    PTR_vftable_10037610 =
        BasicCallbackManager_6018937_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (DAT_10037638 != nullptr) {
        FUN_10010756(DAT_10037638);
    }

    DAT_10037638 = nullptr;
    DAT_1003763c = 0;
    DAT_10037640 = 0;

    if (DAT_10037628 != nullptr) {
        FUN_10010756(DAT_10037628);
    }

    DAT_10037628 = nullptr;
    _DAT_1003762c = 0;
    _DAT_10037630 = 0;
}