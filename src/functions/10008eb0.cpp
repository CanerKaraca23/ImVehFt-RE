#include <windows.h>

extern "C" void __cdecl FUN_10008eb0(int* param_1, int* param_2)
{
    DWORD local_10;
    const BOOL protectionChanged =
        VirtualProtect(param_2, 4, PAGE_EXECUTE_READWRITE, &local_10);

    const int iVar1 = *param_2;

    if (protectionChanged != FALSE)
    {
        DWORD local_8 = local_10;
        VirtualProtect(param_2, 4, local_10, &local_8);
    }

    *param_1 = reinterpret_cast<int>(param_2) + iVar1 + 4;
}