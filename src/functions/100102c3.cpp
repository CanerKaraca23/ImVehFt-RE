#include <cstddef>
#include <cstdint>

struct ExceptionStorage
{
    void* __thiscall construct(char** param_1);
    void** vtable;                  // +0x00
    char* what;                     // +0x04
    std::uint8_t do_free;           // +0x08
};

static_assert(offsetof(ExceptionStorage, what) == 4);
static_assert(offsetof(ExceptionStorage, do_free) == 8);

void* ExceptionStorage::construct(char** param_1)
{
    this->what = nullptr;
    this->vtable = reinterpret_cast<void**>(static_cast<std::uintptr_t>(0x10022228));
    this->do_free = 0;

    using CopyStrFn = void (__thiscall*)(void*, char*);
    reinterpret_cast<CopyStrFn>(static_cast<std::uintptr_t>(0x10010265))(
        this, *param_1);

    return this;
}
