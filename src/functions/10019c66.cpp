#include <cstddef>

extern "C" void __cdecl _free(void* _Memory);

extern "C" void __cdecl __freea(void* _Memory)
{
    if ((_Memory != nullptr) &&
        (*reinterpret_cast<int*>(
             static_cast<std::byte*>(_Memory) - 8) == 0xdddd))
    {
        _free(static_cast<std::byte*>(_Memory) - 8);
    }
}