#include <cstdint>
#include <cstdlib>
#include <windows.h>

extern std::uint32_t _DAT_1003c3fc;
extern std::uint8_t* _DAT_00b74494;
extern HANDLE DAT_1003c3e8;
extern int* DAT_1003c3ec;

extern "C" int __stdcall FUN_10009360();
extern "C" __declspec(noreturn) void __stdcall FUN_100095f0();
extern "C" void __stdcall FUN_100094d0();
extern "C" void __stdcall thunk_FUN_10009580();



void __stdcall FUN_1000d030()
{
    int iVar1;
    int iVar2;
    int* piVar3;
    LPVOID pvVar4;
    HANDLE pvVar5;
    int iVar6;

    iVar2 = FUN_10009360();

    if (*reinterpret_cast<int*>(iVar2 + 0x40) != 0)
        return;

    iVar1 = *reinterpret_cast<int*>(_DAT_00b74494 + 8);
    iVar6 = *reinterpret_cast<int*>(iVar2 + 0x44) * iVar1;

    if ((_DAT_1003c3fc & 1u) == 0)
    {
        _DAT_1003c3fc |= 1u;
        DAT_1003c3e8 = nullptr;
        DAT_1003c3ec = nullptr;
        std::atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_10009580));
    }

    if (DAT_1003c3ec == nullptr)
    {
        if (DAT_1003c3e8 == nullptr)
            goto LAB_1000d09b;

LAB_1000d0be:
        if (DAT_1003c3ec != nullptr ||
            ((DAT_1003c3ec = static_cast<int*>(
                  MapViewOfFile(DAT_1003c3e8, 0xF001Fu, 0, 0, 0))),
             DAT_1003c3ec != nullptr))
        {
            piVar3 = DAT_1003c3ec;
            pvVar5 = DAT_1003c3e8;

            if (DAT_1003c3e8 != nullptr && *DAT_1003c3ec == 0)
            {
                FUN_100095f0();
            }

            goto LAB_1000d0ee;
        }
    }
    else
    {
        piVar3 = DAT_1003c3ec;
        pvVar5 = DAT_1003c3e8;

        if (DAT_1003c3e8 != nullptr)
            goto LAB_1000d10e;

LAB_1000d09b:
        DAT_1003c3e8 =
            OpenFileMappingA(0xF001Fu, FALSE, "GTA_PLUGIN_SDK");

        piVar3 = DAT_1003c3ec;
        pvVar5 = DAT_1003c3e8;

        if (DAT_1003c3e8 != nullptr)
            goto LAB_1000d0be;

LAB_1000d0ee:
        if (piVar3 != nullptr && pvVar5 != nullptr)
            goto LAB_1000d10e;
    }

    FUN_100094d0();
    piVar3 = DAT_1003c3ec;
    pvVar5 = DAT_1003c3e8;

LAB_1000d10e:
    if (piVar3 == nullptr || pvVar5 == nullptr)
        FUN_100095f0();

    pvVar4 = HeapAlloc(
        reinterpret_cast<HANDLE>(piVar3[1]),
        0,
        static_cast<SIZE_T>(iVar6 + iVar1 * 4));

    *reinterpret_cast<LPVOID*>(iVar2 + 0x40) = pvVar4;

    const std::uint32_t address =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(pvVar4));

    *reinterpret_cast<LPVOID*>(iVar2 + 0x48) =
        reinterpret_cast<LPVOID>(
            static_cast<std::uintptr_t>(
                address + static_cast<std::uint32_t>(iVar6)));
}