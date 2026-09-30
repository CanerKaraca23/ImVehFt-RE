#include "imvehft_image_aliases.hpp"
#include <cstdint>

struct TypeInfoStorage
{
    void __thiscall destroy();
    void** vtable; // offset 0
};

extern "C" void __cdecl _Type_info_dtor(TypeInfoStorage* value);

void TypeInfoStorage::destroy()
{
    this->vtable = reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022248));
    _Type_info_dtor(this);
}
