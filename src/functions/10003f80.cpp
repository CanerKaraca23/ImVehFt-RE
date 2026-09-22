#include <cstdint>

using UnresolvedVoidStdcallFunction = void (__stdcall*)();

extern "C" void __stdcall FUN_10003f80()
{
    reinterpret_cast<UnresolvedVoidStdcallFunction>(
        static_cast<std::uintptr_t>(0x7F1200u))();

    reinterpret_cast<UnresolvedVoidStdcallFunction>(
        static_cast<std::uintptr_t>(0x7F0DC0u))();
}