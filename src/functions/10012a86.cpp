#include <cstddef>
#include <cstdint>

extern "C" void* __cdecl _realloc(void* ptr, std::size_t new_size);
extern "C" void __stdcall Sleep(std::uint32_t milliseconds);

extern "C" std::uint32_t DAT_10039a08;

extern "C" void* __cdecl __realloc_crt(
    void* _Ptr,
    std::size_t _NewSize)
{
    std::uint32_t milliseconds = 0;

    do
    {
        void* result = _realloc(_Ptr, _NewSize);

        if (result != nullptr)
        {
            return result;
        }

        if (_NewSize == 0)
        {
            return nullptr;
        }

        if (DAT_10039a08 == 0)
        {
            return nullptr;
        }

        Sleep(milliseconds);
        milliseconds = milliseconds + 1000;

        if (DAT_10039a08 < milliseconds)
        {
            milliseconds = 0xFFFFFFFFu;
        }
    }
    while (milliseconds != 0xFFFFFFFFu);

    return nullptr;
}