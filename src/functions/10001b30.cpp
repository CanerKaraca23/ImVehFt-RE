#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern int DAT_1003aacc;

extern "C" int __cdecl FUN_10001b30(int param_1, int param_2)
{
    struct Entry
    {
        int field_00;
        int field_04;
        int field_08;
        union
        {
            unsigned int value;
            int* pointer;
        } field_0C;
        unsigned int field_10;
    };

    int iVar3 = DAT_1003aacc;
    Entry* destination = reinterpret_cast<Entry*>(iVar3 + param_1);
    Entry* source = reinterpret_cast<Entry*>(iVar3 + param_2);

    destination->field_00 = source->field_00;
    destination->field_04 = source->field_04;
    destination->field_08 = source->field_08;

    int* piVar2;

    if ((param_2 != 0) &&
        (piVar2 = source->field_0C.pointer, piVar2 != nullptr))
    {
        iVar3 = *piVar2;

        unsigned int uVar4 =
            reinterpret_cast<unsigned int (__cdecl *)(unsigned int, unsigned int, int, int)>(
                0x7fb230)(
                    reinterpret_cast<Entry*>(iVar3)->field_0C.value,
                    reinterpret_cast<Entry*>(iVar3)->field_10,
                    0,
                    5);

        uVar4 =
            reinterpret_cast<unsigned int (__cdecl *)(unsigned int)>(
                0x7f37c0)(uVar4);

        destination->field_0C.value = uVar4;
    }

    return param_1;
}