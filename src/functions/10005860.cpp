#include <cstdint>

extern std::int32_t DAT_1003c248;
extern char DAT_00c7c728;
extern std::uint8_t DAT_00b6f081;
extern std::int32_t* _DAT_00b74494;

using Predicate2180 = char(__thiscall*)(void*, std::uint8_t);
using Predicate2230 = char(__thiscall*)(void*, std::uint8_t);

extern "C" int __stdcall FUN_10009360();
extern "C" void __cdecl FUN_10007030(
    std::int32_t,
    std::int32_t,
    std::int32_t,
    char,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    char,
    char,
    std::uint8_t);

extern void __stdcall FUN_10005670();

extern "C" void __cdecl FUN_10006be0(
    std::int32_t,
    std::int32_t,
    std::int32_t,
    std::uint8_t,
    std::uint8_t,
    std::uint32_t,
    std::uint8_t,
    float,
    char,
    float,
    char);

extern void __stdcall FUN_100060d0();

extern "C" void __cdecl FUN_10005860(int param_1)
{
    int iVar7 = DAT_1003c248;

    if (DAT_00c7c728 == '\0') {
        int iVar8 = (unsigned int)DAT_00b6f081 * 0x238 + 0x00B6F338;
        int iVar6 = FUN_10009360();

        iVar7 = *(int *)(*(int *)(iVar6 + 0x48) +
            ((param_1 - *_DAT_00b74494) / 0xA18) * 4) + iVar7;

        iVar6 = *(int *)(iVar7 + 0x28);

        unsigned int local_18 = 0;
        int *local_14;

        if (*(int *)(iVar6 + 800) != 0) {
            unsigned char *puVar10 = (unsigned char *)(iVar6 + 5);

            do {
                local_14 = (int *)(puVar10 - 5);

                if (*(char *)(puVar10[8] + 4 + iVar7) == '\1') {
                    unsigned char bVar1;
                    unsigned char bVar2;
                    unsigned char bVar3;
                    unsigned char bVar15;
                    char cVar5;
                    char cVar13;
                    bool bVar11;
                    int iVar9;

                    if (puVar10[-1] == '\0') {
                        cVar5 = reinterpret_cast<Predicate2180>(0x006C2180)(reinterpret_cast<void*>(static_cast<std::uintptr_t>(param_1) + 0x5a0u), *puVar10);
                        bVar11 = cVar5 == '\0';

                        if (!bVar11)
                            goto LAB_100059A3;

                        bVar15 = puVar10[1];
                        cVar5 = puVar10[4];
                        bVar1 = puVar10[7];
                        bVar2 = puVar10[6];
                        bVar3 = puVar10[5];
                        cVar13 = '\1';
                        iVar9 = *local_14;
                    } else {
                        if ((unsigned char)(puVar10[-1] - 2) < 3) {
                            cVar5 = reinterpret_cast<Predicate2230>(0x006C2230)(reinterpret_cast<void*>(static_cast<std::uintptr_t>(param_1) + 0x5a0u), *puVar10);

                            if (cVar5 != '\0') {
                                cVar5 = reinterpret_cast<Predicate2230>(0x006C2230)(reinterpret_cast<void*>(static_cast<std::uintptr_t>(param_1) + 0x5a0u), *puVar10);
                                bVar11 = cVar5 == '\1';

                                if (!bVar11)
                                    goto LAB_100059A3;

                                bVar15 = puVar10[1];
                                cVar5 = puVar10[4];
                                bVar1 = puVar10[7];
                                bVar2 = puVar10[6];
                                bVar3 = puVar10[5];
                                cVar13 = '\1';
                                iVar9 = *local_14;
                            } else {
                                bVar15 = puVar10[1];
                                cVar5 = puVar10[4];
                                bVar1 = puVar10[7];
                                bVar2 = puVar10[6];
                                bVar3 = puVar10[5];
                                cVar13 = '\1';
                                iVar9 = *local_14;
                            }
                        } else {
                            bVar15 = puVar10[1];
                            cVar5 = puVar10[4];
                            bVar1 = puVar10[7];
                            bVar2 = puVar10[6];
                            cVar13 = '\0';
                            bVar3 = puVar10[5];
                            iVar9 = *local_14;
                        }
                    }

                    FUN_10007030(
                        iVar9,
                        param_1,
                        iVar8,
                        (char)local_18,
                        (unsigned int)bVar3,
                        (unsigned int)bVar2,
                        (unsigned int)bVar1,
                        cVar13,
                        cVar5,
                        bVar15);
                }

            LAB_100059A3:
                local_18 = local_18 + 1;
                puVar10 = puVar10 + 0x10;
            } while (local_18 < *(unsigned int *)(iVar6 + 800));
        }

        if (*(int *)(*(int *)(iVar7 + 0x28) + 0x350) != 0) {
            __asm {
                mov eax, param_1
                call FUN_10005670
            }

            iVar6 = *(int *)(iVar7 + 0x28);
            local_18 = 0;

            if (*(short *)(*(int *)(iVar6 + 0x350) + 4) != 0) {
                int iVar9 = 0;

                do {
                    if (*(char *)(iVar9 + 0x35D + iVar6) != '\0') {
                        char cVar5 = *(char *)(iVar9 + 0x358 + iVar6);

                        if (cVar5 == '\0') {
                            cVar5 = reinterpret_cast<Predicate2180>(0x006C2180)(reinterpret_cast<void*>(static_cast<std::uintptr_t>(param_1) + 0x5a0u), 
                                *(unsigned char *)(iVar9 + 0x359 + iVar6));

                            if (cVar5 != '\0')
                                goto LAB_10005B23;

                            int iVar4 = *(int *)(iVar9 + 0x360 + iVar6);
                            FUN_10006be0(
                                *(int *)(iVar9 + 0x354 + iVar6),
                                iVar8,
                                (char)local_18 + '\x1E',
                                *(unsigned char *)(iVar4 + 8),
                                *(unsigned char *)(iVar4 + 9),
                                (unsigned int)*(unsigned char *)(iVar4 + 10),
                                *(unsigned char *)(iVar4 + 0x0B),
                                *(float *)(iVar4 + 0x0C),
                                '\1',
                                *(float *)(iVar4 + 0x10),
                                *(char *)(iVar4 + 1));
                        } else if ((unsigned char)(cVar5 - 2U) < 3) {
                            cVar5 = reinterpret_cast<Predicate2230>(0x006C2230)(reinterpret_cast<void*>(static_cast<std::uintptr_t>(param_1) + 0x5a0u), 
                                *(unsigned char *)((char *)local_14 + 5));

                            if (cVar5 != '\0') {
                                cVar5 = reinterpret_cast<Predicate2230>(0x006C2230)(reinterpret_cast<void*>(static_cast<std::uintptr_t>(param_1) + 0x5a0u), 
                                    *(unsigned char *)((char *)local_14 + 5));

                                if (cVar5 != '\1')
                                    goto LAB_10005B23;
                            }

                            int iVar4 = *(int *)(iVar9 + 0x360 + iVar6);
                            FUN_10006be0(
                                *(int *)(iVar9 + 0x354 + iVar6),
                                iVar8,
                                (char)local_18 + '\x1E',
                                *(unsigned char *)(iVar4 + 8),
                                *(unsigned char *)(iVar4 + 9),
                                (unsigned int)*(unsigned char *)(iVar4 + 10),
                                *(unsigned char *)(iVar4 + 0x0B),
                                *(float *)(iVar4 + 0x0C),
                                '\1',
                                *(float *)(iVar4 + 0x10),
                                *(char *)(iVar4 + 1));
                        } else {
                            int iVar4 = *(int *)(iVar9 + 0x360 + iVar6);
                            FUN_10006be0(
                                *(int *)(iVar9 + 0x354 + iVar6),
                                iVar8,
                                (char)local_18 + '\x1E',
                                *(unsigned char *)(iVar4 + 8),
                                *(unsigned char *)(iVar4 + 9),
                                (unsigned int)*(unsigned char *)(iVar4 + 10),
                                *(unsigned char *)(iVar4 + 0x0B),
                                *(float *)(iVar4 + 0x0C),
                                '\0',
                                *(float *)(iVar4 + 0x10),
                                *(char *)(iVar4 + 1));
                        }
                    }

                LAB_10005B23:
                    iVar6 = *(int *)(iVar7 + 0x28);
                    local_18 = local_18 + 1;
                    iVar9 = iVar9 + 0x14;
                } while ((int)local_18 < (int)(unsigned int)
                    *(unsigned short *)(*(int *)(iVar6 + 0x350) + 4));
            }
        }

        __asm {
                mov esi, param_1
                call FUN_100060d0
        }
    }
}