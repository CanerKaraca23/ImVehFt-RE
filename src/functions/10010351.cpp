#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>

struct ExceptionStorage
{
    ExceptionStorage* __thiscall assign(ExceptionStorage* other);
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other);
    void** vtable;                 // +0x00
    char* what;                    // +0x04
    std::uint8_t do_free;          // +0x08
};

static_assert(offsetof(ExceptionStorage, what) == 4);
static_assert(offsetof(ExceptionStorage, do_free) == 8);

ExceptionStorage* ExceptionStorage::copy_construct(ExceptionStorage* other)
{
    this->what = nullptr;
    this->vtable = reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022228));
    this->do_free = 0;

    this->assign(other);

    return this;
}
