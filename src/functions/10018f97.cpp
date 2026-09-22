#include <Windows.h>
#include <cstdint>

extern "C" std::uint32_t DAT_1003c418;
extern "C" std::uint8_t* DAT_1003c420[];
extern "C" int DAT_10039a00;

extern "C" int* __cdecl __errno();
extern "C" unsigned long* __cdecl ___doserrno();

extern "C" __declspec(dllimport)
BOOL WINAPI SetStdHandle(DWORD nStdHandle, HANDLE hHandle);

extern "C" int __cdecl __set_osfhnd(int param_1, std::intptr_t param_2)
{
    if ((param_1 >= 0) &&
        (static_cast<std::uint32_t>(param_1) < DAT_1003c418))
    {
        const std::uint32_t offset =
            (static_cast<std::uint32_t>(param_1) & 0x1fU) * 0x40U;

        auto* slot = reinterpret_cast<std::intptr_t*>(
            DAT_1003c420[param_1 >> 5] + offset);

        if (*slot == -1)
        {
            if (DAT_10039a00 == 1)
            {
                DWORD nStdHandle;

                if (param_1 == 0)
                {
                    nStdHandle = 0xfffffff6UL;
                }
                else if (param_1 == 1)
                {
                    nStdHandle = 0xfffffff5UL;
                }
                else
                {
                    if (param_1 != 2)
                        goto store_handle;

                    nStdHandle = 0xfffffff4UL;
                }

                SetStdHandle(nStdHandle, reinterpret_cast<HANDLE>(param_2));
            }

        store_handle:
            *slot = param_2;
            return 0;
        }
    }

    *__errno() = 9;
    *___doserrno() = 0;
    return -1;
}