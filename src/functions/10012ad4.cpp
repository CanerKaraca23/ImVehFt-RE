#include <cstddef>
#include <cstdint>

extern "C" void* __cdecl __recalloc(
    void* _Ptr,
    std::size_t _Count,
    std::size_t _Size);

extern "C" void __stdcall Sleep(std::uint32_t dwMilliseconds);

extern "C" std::uint32_t DAT_10039a08;

extern "C" void* __cdecl __recalloc_crt(
    void* _Ptr,
    std::size_t _Count,
    std::size_t _Size)
{
    std::uint32_t dwMilliseconds = 0;

    do
    {
        void* pvVar1 = __recalloc(_Ptr, _Count, _Size);

        if (pvVar1 != nullptr)
        {
            return pvVar1;
        }

        if (_Size == 0)
        {
            return nullptr;
        }

        if (DAT_10039a08 == 0)
        {
            return nullptr;
        }

        Sleep(dwMilliseconds);

        dwMilliseconds = dwMilliseconds + 1000;

        if (DAT_10039a08 < dwMilliseconds)
        {
            dwMilliseconds = 0xffffffffu;
        }
    }
    while (dwMilliseconds != 0xffffffffu);

    return nullptr;
}