#include <cstddef>
#include <cstdint>

using HANDLE = void*;
using LPVOID = void*;
using SIZE_T = std::size_t;
using DWORD = std::uint32_t;

extern HANDLE DAT_10039b90;
extern int DAT_1003a1c4;

extern "C" void __cdecl __FF_MSGBANNER();
extern "C" void __cdecl __NMSG_WRITE(std::uint32_t message);
extern "C" [[noreturn]] void __cdecl ___crtExitProcess(std::uint32_t code);
extern "C" LPVOID __stdcall HeapAlloc(
    HANDLE heap,
    DWORD flags,
    SIZE_T bytes);
extern "C" int __cdecl __callnewh(std::size_t size);
extern "C" int* __cdecl __errno();

extern "C" void* __cdecl _malloc(std::size_t _Size)
{
    if (_Size < static_cast<std::size_t>(0xffffffe1u))
    {
        do
        {
            if (DAT_10039b90 == nullptr)
            {
                __FF_MSGBANNER();
                __NMSG_WRITE(0x1e);
                ___crtExitProcess(0xff);
            }

            SIZE_T dwBytes = _Size;
            if (_Size == 0)
            {
                dwBytes = 1;
            }

            LPVOID pvVar1 = HeapAlloc(DAT_10039b90, 0, dwBytes);
            if (pvVar1 != nullptr)
            {
                return pvVar1;
            }

            if (DAT_1003a1c4 == 0)
            {
                int* piVar3 = __errno();
                *piVar3 = 0xc;
                break;
            }

            const int iVar2 = __callnewh(_Size);
            if (iVar2 == 0)
            {
                break;
            }
        } while (true);

        int* piVar3 = __errno();
        *piVar3 = 0xc;
    }
    else
    {
        __callnewh(_Size);

        int* piVar3 = __errno();
        *piVar3 = 0xc;
    }

    return nullptr;
}