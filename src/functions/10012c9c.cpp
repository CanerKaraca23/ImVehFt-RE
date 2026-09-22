#include <cstdint>

using Callback = void(__cdecl*)();

extern "C" void __cdecl __SEH_prolog4(std::uint32_t, int);
extern "C" void __stdcall __SEH_epilog4(void);
extern "C" void __cdecl __lock(int);
extern "C" void __stdcall FUN_10012dc7(void);
extern "C" void __cdecl FUN_10017cd2(int);
extern "C" void __cdecl ___crtExitProcess(int);
extern "C" int __stdcall FUN_10014c40(void);
extern "C" void __stdcall FUN_1001b29b(void);
extern "C" void* __stdcall DecodePointer(void*);

extern "C" void* DAT_1003d54c;
extern "C" void* DAT_1003d548;
extern "C" int DAT_10039a3c;
extern "C" int DAT_10039a38;
extern "C" std::uint8_t DAT_10039a34;
extern "C" Callback DAT_100221d4[3];
extern "C" Callback DAT_100221e4[1];

extern "C" void __cdecl doexit(int param_1, int param_2, int param_3)
{
    __SEH_prolog4(0u, 0);
    __lock(8);

    if (DAT_10039a3c != 1)
    {
        DAT_10039a38 = 1;
        DAT_10039a34 = static_cast<std::uint8_t>(param_3);

        if (param_2 == 0)
        {
            int* piVar1 =
                static_cast<int*>(DecodePointer(DAT_1003d54c));

            if (piVar1 != nullptr)
            {
                int* piVar2 =
                    static_cast<int*>(DecodePointer(DAT_1003d548));

                int* local_34 = piVar1;
                int* local_2c = piVar2;
                int* local_28 = piVar1;

                while (piVar2 = piVar2 - 1, piVar1 <= piVar2)
                {
                    int iVar3 = FUN_10014c40();

                    if (*piVar2 != iVar3)
                    {
                        if (piVar2 < piVar1)
                            break;

                        Callback pcVar4 = reinterpret_cast<Callback>(
                            DecodePointer(reinterpret_cast<void*>(
                                static_cast<std::uintptr_t>(
                                    static_cast<std::uint32_t>(*piVar2)))));

                        *piVar2 = FUN_10014c40();
                        (*pcVar4)();

                        int* piVar5 =
                            static_cast<int*>(DecodePointer(DAT_1003d54c));
                        int* piVar6 =
                            static_cast<int*>(DecodePointer(DAT_1003d548));

                        if ((local_28 != piVar5) ||
                            (piVar1 = local_34, local_2c != piVar6))
                        {
                            piVar1 = piVar5;
                            piVar2 = piVar6;
                            local_34 = piVar5;
                            local_2c = piVar6;
                            local_28 = piVar5;
                        }
                    }
                }
            }

            for (Callback* local_20 = &DAT_100221d4[0];
                 local_20 < &DAT_100221d4[3];
                 local_20 = local_20 + 1)
            {
                if (*local_20 != nullptr)
                    (*local_20)();
            }
        }

        for (Callback* local_24 = &DAT_100221e4[0];
             local_24 < &DAT_100221e4[1];
             local_24 = local_24 + 1)
        {
            if (*local_24 != nullptr)
                (*local_24)();
        }

        FUN_1001b29b();
    }

    FUN_10012dc7();

    if (param_3 != 0)
    {
        __SEH_epilog4();
        return;
    }

    DAT_10039a3c = 1;
    FUN_10017cd2(8);
    __SEH_epilog4();
    ___crtExitProcess(param_1);
}