#include <exception>

struct FUN_1001d906_this { void* __thiscall invoke(std::exception* param_1); };

void* FUN_1001d906_this::invoke(std::exception* param_1)
{
    void* self = static_cast<void*>(this);
    using ExceptionCopyConstructor =
        void (__thiscall*)(void*, std::exception*);
    reinterpret_cast<ExceptionCopyConstructor>(0x10010351)(self, param_1);

    *reinterpret_cast<void***>(self) =
        reinterpret_cast<void**>(0x100261e8);

    return self;
}