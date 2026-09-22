#include <cstdint>

extern void* PTR_vftable_10037958;
extern void* DAT_10037980;
extern std::uint32_t DAT_10037984;
extern std::uint32_t DAT_10037988;
extern void* DAT_10037970;
extern std::uint32_t _DAT_10037974;
extern std::uint32_t _DAT_10037978;

extern void*
    BasicCallbackManager_6193234_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10021150(void)
{
    PTR_vftable_10037958 =
        BasicCallbackManager_6193234_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

    if (DAT_10037980 != nullptr) {
        FUN_10010756(DAT_10037980);
    }

    DAT_10037980 = nullptr;
    DAT_10037984 = 0;
    DAT_10037988 = 0;

    if (DAT_10037970 != nullptr) {
        FUN_10010756(DAT_10037970);
    }

    DAT_10037970 = nullptr;
    _DAT_10037974 = 0;
    _DAT_10037978 = 0;
}