#include <cstdint>

extern void* PTR_vftable_100379c8;
extern void* DAT_100379f0;
extern std::uint32_t DAT_100379f4;
extern std::uint32_t DAT_100379f8;
extern void* DAT_100379e0;
extern std::uint32_t _DAT_100379e4;
extern std::uint32_t _DAT_100379e8;

extern void*
    BasicCallbackManager_5751588_0_0_0_0_SimpleSuperManagerThiscall_PatcherJMP1_THIS_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10021210(void)
{
    PTR_vftable_100379c8 =
        BasicCallbackManager_5751588_0_0_0_0_SimpleSuperManagerThiscall_PatcherJMP1_THIS_vftable;

    if (DAT_100379f0 != nullptr) {
        FUN_10010756(DAT_100379f0);
    }

    DAT_100379f0 = nullptr;
    DAT_100379f4 = 0;
    DAT_100379f8 = 0;

    if (DAT_100379e0 != nullptr) {
        FUN_10010756(DAT_100379e0);
    }

    DAT_100379e0 = nullptr;
    _DAT_100379e4 = 0;
    _DAT_100379e8 = 0;
}