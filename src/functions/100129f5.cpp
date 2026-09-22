#include <cstddef>
#include <cstdint>

extern "C" void* __cdecl _malloc(std::size_t size);
extern "C" void __stdcall Sleep(std::uint32_t milliseconds);

extern "C" std::uint32_t DAT_10039a08;

extern "C" void* __cdecl __malloc_crt(std::size_t size)
{
    std::uint32_t milliseconds = 0;

    while (true)
    {
        void* result = _malloc(size);

        if (result != nullptr)
        {
            return result;
        }

        if (DAT_10039a08 == 0)
        {
            break;
        }

        Sleep(milliseconds);
        milliseconds = milliseconds + 1000;

        if (DAT_10039a08 < milliseconds)
        {
            milliseconds = 0xffffffffu;
        }

        if (milliseconds == 0xffffffffu)
        {
            return nullptr;
        }
    }

    return nullptr;
}