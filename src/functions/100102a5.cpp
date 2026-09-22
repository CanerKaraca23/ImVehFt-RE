#include <cstddef>
#include <cstdint>

struct ExceptionStorage
{
    void __thiscall tidy();
    void* vtable;                  // +0x00
    char* what;                    // +0x04
    std::uint8_t do_free;          // +0x08
};

static_assert(offsetof(ExceptionStorage, what) == 4);
static_assert(offsetof(ExceptionStorage, do_free) == 8);

void ExceptionStorage::tidy()
{
    if (this->do_free != 0)
    {
        using FreeFn = void (__cdecl*)(void*);
        reinterpret_cast<FreeFn>(static_cast<std::uintptr_t>(0x100116db))(this->what);
    }

    this->what = nullptr;
    this->do_free = 0;
}
