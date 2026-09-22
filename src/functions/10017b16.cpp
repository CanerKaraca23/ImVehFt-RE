#include <cstddef>
#include <cstdint>

extern "C" void* DAT_10039b90;
extern "C" std::uint32_t DAT_1003a1c4;

extern "C" void* __cdecl _malloc(std::size_t _Size);
extern "C" void __cdecl _free(void* _Memory);
extern "C" int __cdecl __callnewh(std::size_t _Size);
extern "C" int* __cdecl __errno();
extern "C" int __cdecl __get_errno_from_oserr(std::uint32_t _OSError);

extern "C" void* __stdcall HeapReAlloc(
    void* _Heap,
    std::uint32_t _Flags,
    void* _Memory,
    std::size_t _Size);

extern "C" std::uint32_t __stdcall GetLastError();

extern "C" void* __cdecl _realloc(void* _Memory, std::size_t _NewSize)
{
    if (_Memory == nullptr)
    {
        return _malloc(_NewSize);
    }

    if (_NewSize == 0)
    {
        _free(_Memory);
    }
    else
    {
        do
        {
            if (0xffffffe0u < _NewSize)
            {
                __callnewh(_NewSize);

                int* piVar4 = __errno();
                *piVar4 = 0x0c;
                return nullptr;
            }

            if (_NewSize == 0)
            {
                _NewSize = 1;
            }

            void* pvVar2 = HeapReAlloc(
                DAT_10039b90,
                0,
                _Memory,
                _NewSize);

            if (pvVar2 != nullptr)
            {
                return pvVar2;
            }

            if (DAT_1003a1c4 == 0)
            {
                int* piVar4 = __errno();
                std::uint32_t DVar5 = GetLastError();
                int iVar3 = __get_errno_from_oserr(DVar5);
                *piVar4 = iVar3;
                return nullptr;
            }

            int iVar3 = __callnewh(_NewSize);
            if (iVar3 != 0)
            {
                continue;
            }

            int* piVar4 = __errno();
            std::uint32_t DVar5 = GetLastError();
            iVar3 = __get_errno_from_oserr(DVar5);
            *piVar4 = iVar3;
        } while (false);
    }

    return nullptr;
}