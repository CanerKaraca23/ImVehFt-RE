#include <cstddef>
#include <cstdint>

extern "C" void __cdecl _free(void* memory);

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
        _free(this->what);
    }

    this->what = nullptr;
    this->do_free = 0;
}
