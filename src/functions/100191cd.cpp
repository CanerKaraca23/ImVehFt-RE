#include <Windows.h>
#include <cstddef>
#include <cstdint>

extern "C" std::uint8_t* DAT_1003c420[0x40];
extern "C" int DAT_1003c418;

extern "C" void __cdecl __SEH_prolog4(std::uint32_t, std::int32_t);
extern "C" void __stdcall __SEH_epilog4();

extern "C" int __cdecl __mtinitlocknum(int);
extern "C" void __cdecl __lock(int);
extern "C" void* __cdecl __calloc_crt(std::size_t, std::size_t);
extern "C" int __cdecl ___lock_fhandle(int);
extern "C" void __stdcall FUN_1001929f();
extern "C" void __stdcall FUN_1001935d();

extern "C" int __cdecl __alloc_osfhnd()
{
    __SEH_prolog4(0, 0);

    bool initialization_failed = false;
    int result = -1;
    int block_index = 0;

    int lock_result = __mtinitlocknum(0x0b);
    if (lock_result == 0)
    {
        result = -1;
    }
    else
    {
        __lock(0x0b);

        for (; block_index < 0x40; block_index = block_index + 1)
        {
            std::uint8_t* block = DAT_1003c420[block_index];

            if (block == nullptr)
            {
                block = static_cast<std::uint8_t*>(
                    __calloc_crt(0x20, 0x40));

                if (block != nullptr)
                {
                    DAT_1003c420[block_index] = block;
                    DAT_1003c418 = DAT_1003c418 + 0x20;

                    for (std::uint8_t* entry = block;
                         entry < DAT_1003c420[block_index] + 0x800;
                         entry = entry + 0x40)
                    {
                        *reinterpret_cast<std::uint8_t*>(entry + 4) = 0;
                        *reinterpret_cast<std::int32_t*>(entry) = -1;
                        *reinterpret_cast<std::uint8_t*>(entry + 5) = 10;
                        *reinterpret_cast<std::int32_t*>(entry + 8) = 0;
                    }

                    result = block_index << 5;
                    DAT_1003c420[result >> 5][4] = 1;

                    lock_result = ___lock_fhandle(result);
                    if (lock_result == 0)
                    {
                        result = -1;
                    }
                }

                break;
            }

            for (std::uint8_t* entry = block;
                 entry < DAT_1003c420[block_index] + 0x800;
                 entry = entry + 0x40)
            {
                if ((*reinterpret_cast<std::uint8_t*>(entry + 4) & 1) == 0)
                {
                    if (*reinterpret_cast<std::int32_t*>(entry + 8) == 0)
                    {
                        __lock(10);

                        if (*reinterpret_cast<std::int32_t*>(entry + 8) == 0)
                        {
                            BOOL initialized =
                                InitializeCriticalSectionAndSpinCount(
                                    reinterpret_cast<LPCRITICAL_SECTION>(
                                        entry + 0x0c),
                                    4000);

                            if (initialized == 0)
                            {
                                initialization_failed = true;
                            }
                            else
                            {
                                *reinterpret_cast<std::int32_t*>(entry + 8) =
                                    *reinterpret_cast<std::int32_t*>(entry + 8) + 1;
                            }
                        }

                        FUN_1001929f();
                    }

                    if (!initialization_failed)
                    {
                        EnterCriticalSection(
                            reinterpret_cast<LPCRITICAL_SECTION>(entry + 0x0c));

                        if ((*reinterpret_cast<std::uint8_t*>(entry + 4) & 1) == 0)
                        {
                            *reinterpret_cast<std::uint8_t*>(entry + 4) = 1;
                            *reinterpret_cast<std::int32_t*>(entry) = -1;

                            result =
                                (static_cast<std::int32_t>(
                                     reinterpret_cast<std::uintptr_t>(entry) -
                                     reinterpret_cast<std::uintptr_t>(
                                         DAT_1003c420[block_index])) >>
                                 6) +
                                block_index * 0x20;

                            break;
                        }

                        LeaveCriticalSection(
                            reinterpret_cast<LPCRITICAL_SECTION>(entry + 0x0c));
                    }
                }
            }

            if (result != -1)
            {
                break;
            }
        }

        FUN_1001935d();
    }

    __SEH_epilog4();
    return result;
}