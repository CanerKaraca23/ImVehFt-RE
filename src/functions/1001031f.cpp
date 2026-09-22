#include <cstdint>

extern "C" void __fastcall FUN_1001031f(void* param_1)
{
    *reinterpret_cast<void***>(param_1) =
        reinterpret_cast<void**>(static_cast<std::uintptr_t>(0x10022228));

    using TidyFn = void (__thiscall*)(void*);
    reinterpret_cast<TidyFn>(static_cast<std::uintptr_t>(0x100102a5))(param_1);
}
