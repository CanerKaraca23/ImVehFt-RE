#include <cstdint>

extern void* PTR_vftable_100378e8;
extern void* DAT_10037910;
extern std::uint32_t DAT_10037914;
extern std::uint32_t DAT_10037918;
extern void* DAT_10037900;
extern std::uint32_t _DAT_10037904;
extern std::uint32_t _DAT_10037908;

extern void*
    BasicCallbackManager_7167791_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10021090(void)
{
    PTR_vftable_100378e8 =
        BasicCallbackManager_7167791_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

    if (DAT_10037910 != nullptr) {
        FUN_10010756(DAT_10037910);
    }

    DAT_10037910 = nullptr;
    DAT_10037914 = 0;
    DAT_10037918 = 0;

    if (DAT_10037900 != nullptr) {
        FUN_10010756(DAT_10037900);
    }

    DAT_10037900 = nullptr;
    _DAT_10037904 = 0;
    _DAT_10037908 = 0;
}