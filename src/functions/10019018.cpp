#include <Windows.h>
#include <cstdint>

extern "C" std::uint32_t DAT_1003c418;
extern "C" std::uint8_t* DAT_1003c420[];
extern "C" int DAT_10039a00;

extern "C" int* __cdecl __errno();
extern "C" unsigned long* __cdecl ___doserrno();

extern "C" __declspec(dllimport)
BOOL WINAPI SetStdHandle(DWORD nStdHandle, HANDLE hHandle);

extern "C" int __cdecl __free_osfhnd(int param_1)
{
    if ((param_1 >= 0) &&
        (static_cast<std::uint32_t>(param_1) < DAT_1003c418))
    {
        const std::uint32_t offset =
            (static_cast<std::uint32_t>(param_1) & 0x1fU) * 0x40U;

        auto* base = DAT_1003c420[param_1 >> 5];

        if (((*(base + 4U + offset) & 1U) != 0U) &&
            (*reinterpret_cast<std::int32_t*>(base + offset) != -1))
        {
            if (DAT_10039a00 == 1)
            {
                DWORD nStdHandle;

                if (param_1 == 0)
                {
                    nStdHandle = 0xfffffff6U;
                }
                else if (param_1 == 1)
                {
                    nStdHandle = 0xfffffff5U;
                }
                else
                {
                    if (param_1 != 2)
                    {
                        goto clear_handle;
                    }

                    nStdHandle = 0xfffffff4U;
                }

                SetStdHandle(nStdHandle, nullptr);
            }

        clear_handle:
            *reinterpret_cast<std::int32_t*>(base + offset) = -1;
            return 0;
        }
    }

    *__errno() = 9;
    *___doserrno() = 0;
    return -1;
}