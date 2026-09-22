#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int __stdcall FUN_10009360();
extern "C" void __stdcall FUN_10006a50()
{
    struct Context
    {
        unsigned char padding_0000[0x48];
        unsigned int entries_48;
    };

    struct TableEntry
    {
        unsigned char padding_0000[0x28];
        unsigned char data_28[1];
    };

    struct Vehicle
    {
        unsigned char padding_0000[0x494];
        int enabled_494;
        unsigned char padding_0498[0x04];
        float value_49C;
    };

    struct EdiObject
    {
        unsigned char padding_0000[0x494];
        float value_494;
    };

    using Call_0059AFE0 = void (*)(float);

    extern int DAT_1003c248;
    extern int* _DAT_00b74494;
    extern float _DAT_10024f98;
    int unaff_EDI;
    __asm mov unaff_EDI, edi

    const int iVar1 = DAT_1003c248;

    const auto context =
        reinterpret_cast<Context*>(
            static_cast<unsigned int>(FUN_10009360()));

    const int tableIndex =
        (unaff_EDI - *_DAT_00b74494) / 0xA18;

    const auto entries =
        reinterpret_cast<int32_t*>(
            static_cast<unsigned int>(context->entries_48));

    const auto tableEntry =
        reinterpret_cast<TableEntry*>(
            static_cast<unsigned int>(entries[tableIndex]));

    const int vehicleAddress =
        *reinterpret_cast<int*>(
            tableEntry->data_28 + iVar1);

    const auto vehicle =
        reinterpret_cast<Vehicle*>(
            static_cast<unsigned int>(vehicleAddress));

    const auto ediObject =
        reinterpret_cast<EdiObject*>(
            static_cast<unsigned int>(unaff_EDI));

    if (vehicle->enabled_494 != 0)
    {
        reinterpret_cast<Call_0059AFE0>(
            static_cast<unsigned int>(0x59AFE0))(
            vehicle->value_49C *
            ediObject->value_494 *
            _DAT_10024f98);
    }
}