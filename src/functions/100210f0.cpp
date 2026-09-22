#include <cstdint>

extern void* PTR_vftable_10037920;
extern void* DAT_10037948;
extern std::uint32_t DAT_1003794c;
extern std::uint32_t DAT_10037950;
extern void* DAT_10037938;
extern std::uint32_t _DAT_1003793c;
extern std::uint32_t _DAT_10037940;

extern void*
    BasicCallbackManager_7220533_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_100210f0(void)
{
    PTR_vftable_10037920 =
        BasicCallbackManager_7220533_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

    if (DAT_10037948 != nullptr) {
        FUN_10010756(DAT_10037948);
    }

    DAT_10037948 = nullptr;
    DAT_1003794c = 0;
    DAT_10037950 = 0;

    if (DAT_10037938 != nullptr) {
        FUN_10010756(DAT_10037938);
    }

    DAT_10037938 = nullptr;
    _DAT_1003793c = 0;
    _DAT_10037940 = 0;
}