#include <cstdint>

extern int _DAT_1003c24c;
extern int* _DAT_00b74494;

extern "C" int __stdcall FUN_10009360();

void __cdecl FUN_1000d250(int param_1)
{
    int* piVar1;
    int iVar2;
    int iVar3;
    int iVar4;

    _DAT_1003c24c = param_1;

    iVar2 = FUN_10009360();
    iVar3 = (param_1 - *_DAT_00b74494) / 0xA18;

    piVar1 = reinterpret_cast<int*>(
        *reinterpret_cast<int*>(iVar2 + 0x48) + iVar3 * 4);

    if (*reinterpret_cast<int*>(
            *reinterpret_cast<int*>(iVar2 + 0x48) + iVar3 * 4) == 0)
    {
        iVar3 = FUN_10009360();
        iVar2 = FUN_10009360();
        iVar4 = iVar3 + 0x50;

        *piVar1 =
            ((param_1 - *_DAT_00b74494) / 0xA18) *
                *reinterpret_cast<int*>(iVar2 + 0x44) +
            *reinterpret_cast<int*>(iVar2 + 0x40);

        if (*reinterpret_cast<int*>(iVar3 + 0x54) == 0)
        {
            *reinterpret_cast<int*>(iVar3 + 0x54) = iVar4;
            *reinterpret_cast<int*>(iVar4) = iVar4;
        }

        iVar2 = *reinterpret_cast<int*>(iVar3 + 0x54);

        while (true)
        {
            if (*reinterpret_cast<int*>(iVar3 + 0x54) == 0)
            {
                *reinterpret_cast<int*>(iVar3 + 0x54) = iVar4;
                *reinterpret_cast<int*>(iVar4) = iVar4;
            }

            if (iVar2 == iVar4)
                break;

            using Callback = void (__cdecl*)(int, int);

            reinterpret_cast<Callback>(
                *reinterpret_cast<int*>(iVar2 + 0x14))(
                    param_1,
                    *reinterpret_cast<int*>(iVar2 + 0x08) + *piVar1);

            iVar2 = *reinterpret_cast<int*>(iVar2 + 0x04);
        }
    }
}