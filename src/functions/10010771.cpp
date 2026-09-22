#include <cstdint>

struct TypeInfoStorage
{
    TypeInfoStorage* __thiscall scalar_deleting_destructor(std::uint32_t flags);
    void** vtable; // offset 0
};

TypeInfoStorage* TypeInfoStorage::scalar_deleting_destructor(std::uint32_t flags)
{
    using DestructorFn = void (__thiscall*)(void*);
    reinterpret_cast<DestructorFn>(static_cast<std::uintptr_t>(0x10010761))(this);

    if ((flags & 1U) != 0)
    {
        using FreeFn = void (__cdecl*)(void*);
        reinterpret_cast<FreeFn>(static_cast<std::uintptr_t>(0x10010756))(this);
    }

    return this;
}
