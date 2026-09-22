#include <cstdint>

struct TypeInfoStorage
{
    void __thiscall destroy();
    void** vtable; // offset 0
};

void TypeInfoStorage::destroy()
{
    this->vtable = reinterpret_cast<void**>(static_cast<std::uintptr_t>(0x10022248));
    using TypeInfoDtorFn = void (__cdecl*)(void*);
    reinterpret_cast<TypeInfoDtorFn>(static_cast<std::uintptr_t>(0x10013ad2))(this);
}
