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

ExceptionStorage* ExceptionStorage::assign(ExceptionStorage* other)
{
    if (this != other)
    {
        using TidyFn = void (__thiscall*)(void*);
        reinterpret_cast<TidyFn>(static_cast<std::uintptr_t>(0x100102a5))(this);

        if (other->do_free == 0)
        {
            this->what = other->what;
        }
        else
        {
            using CopyStrFn = void (__thiscall*)(void*, char*);
            reinterpret_cast<CopyStrFn>(static_cast<std::uintptr_t>(0x10010265))(
                this, other->what);
        }
    }

    return this;
}
