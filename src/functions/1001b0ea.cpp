#include <cstdint>

extern "C" int DAT_1003c420[];

extern "C" int __cdecl __setmode_nolock(int _FileHandle, int _Mode)
{
    int* piVar1;
    char cVar2;
    unsigned char bVar3;
    int iVar4;
    unsigned char* pbVar5;
    unsigned char bVar6;
    int iVar7;

    piVar1 = &DAT_1003c420[_FileHandle >> 5];
    iVar7 = (_FileHandle & 0x1fU) * 0x40;
    iVar4 = *piVar1 + iVar7;

    cVar2 = *reinterpret_cast<char*>(iVar4 + 0x24);
    bVar3 = *reinterpret_cast<unsigned char*>(iVar4 + 4);

    if (_Mode == 0x4000) {
        *reinterpret_cast<unsigned char*>(iVar4 + 4) |= 0x80;

        pbVar5 = reinterpret_cast<unsigned char*>(*piVar1 + 0x24 + iVar7);
        *pbVar5 &= 0x80;
    }
    else if (_Mode == 0x8000) {
        *reinterpret_cast<unsigned char*>(iVar4 + 4) &= 0x7f;
    }
    else {
        if ((_Mode == 0x10000) || (_Mode == 0x20000)) {
            *reinterpret_cast<unsigned char*>(iVar4 + 4) |= 0x80;

            pbVar5 = reinterpret_cast<unsigned char*>(*piVar1 + 0x24 + iVar7);
            bVar6 = (*pbVar5 & 0x82) | 2;
        }
        else {
            if (_Mode != 0x40000)
                goto LAB_1001b187;

            *reinterpret_cast<unsigned char*>(iVar4 + 4) |= 0x80;

            pbVar5 = reinterpret_cast<unsigned char*>(*piVar1 + 0x24 + iVar7);
            bVar6 = (*pbVar5 & 0x81) | 1;
        }

        *pbVar5 = bVar6;
    }

LAB_1001b187:
    if ((bVar3 & 0x80) == 0)
        return 0x8000;

    return ((0U - static_cast<unsigned int>(
                  (static_cast<char>(cVar2 * '\x02') >> 1) != '\0')) &
            0xc000U) +
           0x4000U;
}