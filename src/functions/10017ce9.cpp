#include <cstdint>

#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" void* DAT_10029d70;
extern "C" int DAT_10039b90;

extern "C" void* __cdecl __malloc_crt(std::size_t _Size);
extern "C" int* __cdecl __errno(void);
extern "C" void __cdecl __lock(int _LockNum);
extern "C" int __stdcall InitializeCriticalSectionAndSpinCount(
    void* lpCriticalSection,
    std::uint32_t dwSpinCount);
extern "C" void __cdecl _free(void* _Memory);
extern "C" void __stdcall FUN_10017da2(void);
extern "C" void __cdecl __FF_MSGBANNER(void);
extern "C" void __cdecl __NMSG_WRITE(int _Message);
extern "C" [[noreturn]] void __cdecl ___crtExitProcess(
    std::uint32_t _Status);

extern "C" int __cdecl __mtinitlocknum(int _LockNum)
{
    int* piVar1;
    void* lpCriticalSection;
    int BVar2;
    int iVar3;
    int local_20;

    iVar3 = 1;
    local_20 = 1;

    if (DAT_10039b90 != 0)
    {
        piVar1 =
            reinterpret_cast<int*>(&DAT_10029d70) + _LockNum * 2;

        if (*piVar1 == 0)
        {
            lpCriticalSection = __malloc_crt(0x18);

            if (lpCriticalSection == nullptr)
            {
                piVar1 = __errno();
                *piVar1 = 0xC;
                iVar3 = 0;
            }
            else
            {
                __lock(10);

                if (*piVar1 == 0)
                {
                    BVar2 = InitializeCriticalSectionAndSpinCount(
                        lpCriticalSection,
                        4000);

                    if (BVar2 == 0)
                    {
                        _free(lpCriticalSection);
                        piVar1 = __errno();
                        *piVar1 = 0xC;
                        local_20 = 0;
                    }
                    else
                    {
                        *piVar1 = static_cast<int>(
                            reinterpret_cast<std::uintptr_t>(
                                lpCriticalSection));
                    }
                }
                else
                {
                    _free(lpCriticalSection);
                }

                FUN_10017da2();
                iVar3 = local_20;
            }
        }

        return iVar3;
    }

    __FF_MSGBANNER();
    __NMSG_WRITE(0x1E);
    ___crtExitProcess(0xFF);
}