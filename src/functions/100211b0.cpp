#include <cstdint>

extern void* PTR_vftable_10037990;
extern void* DAT_100379b8;
extern std::uint32_t DAT_100379bc;
extern std::uint32_t DAT_100379c0;
extern void* DAT_100379a8;
extern std::uint32_t _DAT_100379ac;
extern std::uint32_t _DAT_100379b0;

extern void*
    BasicCallbackManager_6195212_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_100211b0(void)
{
    PTR_vftable_10037990 =
        BasicCallbackManager_6195212_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

    if (DAT_100379b8 != nullptr) {
        FUN_10010756(DAT_100379b8);
    }

    DAT_100379b8 = nullptr;
    DAT_100379bc = 0;
    DAT_100379c0 = 0;

    if (DAT_100379a8 != nullptr) {
        FUN_10010756(DAT_100379a8);
    }

    DAT_100379a8 = nullptr;
    _DAT_100379ac = 0;
    _DAT_100379b0 = 0;
}