#include <cstdint>


extern std::uint32_t _DAT_1003c400;
extern const char* _DAT_1003c3f0;
extern std::uint16_t _DAT_1003c3f4;
extern std::uint16_t _DAT_1003c3f6;

extern "C" void __stdcall FUN_10009120();

extern int* __cdecl FUN_10008fa0(
    int* param_1,
    std::uint8_t* param_2,
    int param_3
);

extern "C" extern "C" void __stdcall FUN_1000cdc0(
    int* param_1,
    int* param_2,
    int* param_3,
    int* param_4,
    int* param_5
)
{    int* in_EAX;
    __asm mov in_EAX, eax


    std::uint8_t* pbVar1;
    int* piVar2;
    int iVar3;
    int local_8;

    if (*in_EAX != 0)
    {
        iVar3 = in_EAX[1];
        pbVar1 = reinterpret_cast<std::uint8_t*>(*in_EAX);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        piVar2 = FUN_10008fa0(&local_8, pbVar1, iVar3);
        *param_1 = *piVar2;
    }

    if (*param_2 != 0)
    {
        iVar3 = param_2[1];
        pbVar1 = reinterpret_cast<std::uint8_t*>(*param_2);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        piVar2 = FUN_10008fa0(reinterpret_cast<int*>(&param_2), pbVar1, iVar3);
        param_1[1] = *piVar2;
    }

    if (*param_3 != 0)
    {
        iVar3 = param_3[1];
        pbVar1 = reinterpret_cast<std::uint8_t*>(*param_3);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        piVar2 = FUN_10008fa0(reinterpret_cast<int*>(&param_2), pbVar1, iVar3);
        param_1[2] = *piVar2;
    }

    if (*param_4 != 0)
    {
        iVar3 = param_4[1];
        pbVar1 = reinterpret_cast<std::uint8_t*>(*param_4);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        piVar2 = FUN_10008fa0(reinterpret_cast<int*>(&param_2), pbVar1, iVar3);
        param_1[3] = *piVar2;
    }

    if (*param_5 != 0)
    {
        iVar3 = param_5[1];
        pbVar1 = reinterpret_cast<std::uint8_t*>(*param_5);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        piVar2 = FUN_10008fa0(reinterpret_cast<int*>(&param_2), pbVar1, iVar3);
        param_1[4] = *piVar2;
    }
}