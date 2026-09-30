#include <cstddef>
#include <cstdint>

struct ExceptionStorage
{
    ExceptionStorage* __thiscall assign(ExceptionStorage* other);
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other);
    void __thiscall tidy();
    void** vtable;                 // +0x00
    char* what;                    // +0x04
    std::uint8_t do_free;          // +0x08
};

struct CopyStr_this
{
    void __thiscall invoke(char* param_1);
};

static_assert(offsetof(ExceptionStorage, what) == 4);
static_assert(offsetof(ExceptionStorage, do_free) == 8);

ExceptionStorage* ExceptionStorage::assign(ExceptionStorage* other)
{
    if (this != other)
    {
        this->tidy();

        if (other->do_free == 0)
        {
            this->what = other->what;
        }
        else
        {
            reinterpret_cast<CopyStr_this*>(this)->invoke(other->what);
        }
    }

    return this;
}
