#include <cstddef>
#include <cstdint>

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" std::size_t __stdcall HeapSize(
    void* hHeap,
    std::uint32_t dwFlags,
    const void* lpMem);

extern "C" void* DAT_10039b90;

extern "C" std::size_t __cdecl __msize(void* _Memory)
{
    if (_Memory == nullptr)
    {
        int* piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
        return static_cast<std::size_t>(0xFFFFFFFFu);
    }

    std::size_t SVar2 = HeapSize(DAT_10039b90, 0, _Memory);
    return SVar2;
}