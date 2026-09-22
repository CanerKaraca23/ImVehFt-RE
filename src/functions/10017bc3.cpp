#include <cstddef>
#include <cstdint>

extern "C" int* __cdecl __errno();
extern "C" std::size_t __cdecl __msize(void* memory);
extern "C" void* __cdecl _realloc(void* memory, std::size_t newSize);
extern "C" void* __cdecl _memset(void* destination, int value, std::size_t size);

extern "C" void* __cdecl __recalloc(
    void* memory,
    std::size_t count,
    std::size_t size)
{
    std::size_t oldSize = 0;
    void* result;

    if ((count == 0) || (size <= (0xffffffe0u / count)))
    {
        const std::uint32_t newSize =
            static_cast<std::uint32_t>(count * size);

        if (memory != nullptr)
        {
            oldSize = __msize(memory);
        }

        result = _realloc(memory, newSize);

        if ((result != nullptr) && (oldSize < newSize))
        {
            _memset(
                reinterpret_cast<void*>(
                    static_cast<std::uintptr_t>(oldSize) +
                    static_cast<std::uintptr_t>(
                        static_cast<std::int32_t>(
                            reinterpret_cast<std::uintptr_t>(result)))),
                0,
                newSize - oldSize);
        }
    }
    else
    {
        *(__errno()) = 0x0c;
        result = nullptr;
    }

    return result;
}