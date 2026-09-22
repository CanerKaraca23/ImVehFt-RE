#include <windows.h>

extern "C" int* __cdecl FUN_10008f10(int* param_1, unsigned char* param_2);

extern "C" int* __cdecl FUN_10009060(
    int* param_1,
    unsigned char* param_2,
    int param_3
)
{
    BOOL protectionChanged;
    unsigned char* lpAddress;
    DWORD local_14;
    DWORD local_c[2];

    FUN_10008f10(param_1, param_2);

    protectionChanged =
        VirtualProtect(param_2, 1, 0x40, &local_14);

    *param_2 = 0xE8;

    if (protectionChanged != FALSE)
    {
        local_c[0] = local_14;
        VirtualProtect(param_2, 1, local_14, local_c);
    }

    lpAddress = param_2 + 1;

    protectionChanged =
        VirtualProtect(lpAddress, 4, 0x40, &local_14);

    *(int*)lpAddress =
        param_3 - (int)(param_2 + 5);

    if (protectionChanged != FALSE)
    {
        local_c[0] = local_14;
        VirtualProtect(lpAddress, 4, local_14, local_c);
    }

    return param_1;
}