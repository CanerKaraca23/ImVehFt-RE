#include <cstdint>

extern "C" void __cdecl FUN_10010756(void* value);

struct TypeInfoStorage
{
    TypeInfoStorage* __thiscall scalar_deleting_destructor(std::uint32_t flags);
    void __thiscall destroy();
    void** vtable; // offset 0
};

TypeInfoStorage* TypeInfoStorage::scalar_deleting_destructor(std::uint32_t flags)
{
    this->destroy();

    if ((flags & 1U) != 0)
    {
        FUN_10010756(this);
    }

    return this;
}
