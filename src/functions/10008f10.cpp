#include <cstdint>
#include <windows.h>

extern "C" void __cdecl FUN_10008eb0(int* param_1, int* param_2);

extern "C" int* __cdecl FUN_10008f10(int* param_1, std::uint8_t* param_2)
{
    DWORD local_10;
    const BOOL protectionChanged =
        VirtualProtect(param_2, 1u, 0x40u, &local_10);

    const std::uint8_t byteValue = *param_2;

    if (protectionChanged != 0)
    {
        DWORD local_8 = local_10;
        VirtualProtect(param_2, 1u, local_10, &local_8);
    }

    if ((0xe7u < byteValue) && (byteValue < 0xeau))
    {
        FUN_10008eb0(param_1, reinterpret_cast<int*>(param_2 + 1));
        return param_1;
    }

    *param_1 = 0;
    return param_1;
}