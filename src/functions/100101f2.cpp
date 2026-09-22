#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct FUN_100101f2_this { void* __thiscall invoke(void* param_1); };

void* FUN_100101f2_this::invoke(void* param_1)
{
    using BaseExceptionCtor = void* (__thiscall*)(void*, void*);
    reinterpret_cast<BaseExceptionCtor>(
        static_cast<std::uintptr_t>(0x10010351))(this, param_1);
    *reinterpret_cast<void***>(this) =
        reinterpret_cast<void**>(static_cast<std::uintptr_t>(0x1002221c));
    return this;
}
