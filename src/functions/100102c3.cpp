#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>

struct ExceptionStorage
{
    void* __thiscall construct(char** param_1);
    void** vtable;                  // +0x00
    char* what;                     // +0x04
    std::uint8_t do_free;           // +0x08
};

struct CopyStr_this
{
    void __thiscall invoke(char* param_1);
};

static_assert(offsetof(ExceptionStorage, what) == 4);
static_assert(offsetof(ExceptionStorage, do_free) == 8);

void* ExceptionStorage::construct(char** param_1)
{
    this->what = nullptr;
    this->vtable = reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022228));
    this->do_free = 0;

    reinterpret_cast<CopyStr_this*>(this)->invoke(*param_1);

    return this;
}
