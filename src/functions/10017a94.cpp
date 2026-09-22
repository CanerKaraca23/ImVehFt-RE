#include <cstddef>
#include <cstdint>

extern "C" void* DAT_10039b90;
extern "C" std::uint32_t DAT_1003a1c4;

extern "C" int* __cdecl __errno(void);
extern "C" void* __stdcall HeapAlloc(
    void* hHeap,
    std::uint32_t dwFlags,
    std::uint32_t dwBytes);
extern "C" int __cdecl __callnewh(std::size_t size);

extern "C" void* __cdecl __calloc_impl(
    std::uint32_t param_1,
    std::uint32_t param_2,
    std::uint32_t* param_3)
{
    if ((param_1 != 0) && (0xffffffe0u / param_1 < param_2))
    {
        int* piVar1 = __errno();
        *piVar1 = 0x0c;
        return nullptr;
    }

    std::uint32_t dwBytes = param_1 * param_2;

    if (dwBytes == 0)
    {
        dwBytes = 1;
    }

    do
    {
        void* pvVar2 = nullptr;

        if ((dwBytes < 0xffffffe1u) &&
            ((pvVar2 = HeapAlloc(DAT_10039b90, 8, dwBytes)) != nullptr))
        {
            return pvVar2;
        }

        if (DAT_1003a1c4 == 0)
        {
            if (param_3 == nullptr)
            {
                return nullptr;
            }

            *param_3 = 0x0c;
            return nullptr;
        }

        int iVar3 = __callnewh(dwBytes);

        if (iVar3 == 0)
        {
            break;
        }
    } while (true);

    if (param_3 != nullptr)
    {
        *param_3 = 0x0c;
    }

    return nullptr;
}