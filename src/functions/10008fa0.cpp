#include <windows.h>

extern "C" int* __cdecl FUN_10008f10(int* param_1, unsigned char* param_2);

int* __cdecl FUN_10008fa0(
    int* param_1,
    unsigned char* param_2,
    int param_3
)
{
    DWORD local_14;
    DWORD local_c[2];

    FUN_10008f10(param_1, param_2);

    const BOOL protectionChanged =
        VirtualProtect(param_2, 1, PAGE_EXECUTE_READWRITE, &local_14);

    *param_2 = 0xE9;

    if (protectionChanged != FALSE)
    {
        local_c[0] = local_14;
        VirtualProtect(param_2, 1, local_14, local_c);
    }

    unsigned char* lpAddress = param_2 + 1;

    const BOOL displacementProtectionChanged =
        VirtualProtect(lpAddress, 4, PAGE_EXECUTE_READWRITE, &local_14);

    *reinterpret_cast<int*>(lpAddress) =
        param_3 - reinterpret_cast<int>(param_2 + 5);

    if (displacementProtectionChanged != FALSE)
    {
        local_c[0] = local_14;
        VirtualProtect(lpAddress, 4, local_14, local_c);
    }

    return param_1;
}