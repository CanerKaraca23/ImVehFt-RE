#include <cstdint>

extern "C" std::uint32_t __fastcall __NLG_Notify1(
    std::int32_t );

using UnresolvedCodePointer = void (*)();

extern "C" void __stdcall __CallSettingFrame_12(
    std::uint32_t ,
    std::uint32_t ,
    std::int32_t param_3)
{
    auto pcVar1 = reinterpret_cast<UnresolvedCodePointer>(
        static_cast<std::uintptr_t>(
            __NLG_Notify1(param_3)));

    (*pcVar1)();

    if (param_3 == 0x100)
    {
        param_3 = 2;
    }

    __NLG_Notify1(param_3);
}