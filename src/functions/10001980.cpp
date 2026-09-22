#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int* __cdecl FUN_10001980(int* param_1, unsigned int param_2)
{
    using LookupFunction =
        int*(__cdecl*)(unsigned int, char*);
    using AllocateFunction =
        unsigned int(__cdecl*)(unsigned int, unsigned int,
                                unsigned int, unsigned int);
    using InitializeFunction =
        unsigned int(__cdecl*)(unsigned int);

    extern char* PTR_s__dirt_10037588[];
    extern unsigned int DAT_1003aacc;
    extern int __cdecl _strnicmp(char*, char*, std::size_t);
    extern int __cdecl strncpy_s(char*, std::size_t, char*, std::size_t);

    char local_28[32];
    unsigned int local_8 = 0;

    while (true)
    {
        char* pcVar3 = PTR_s__dirt_10037588[local_8];
        char* pcVar5 = pcVar3;
        char cVar2;

        do
        {
            cVar2 = *pcVar5;
            pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');

        char* piVar6 = reinterpret_cast<char*>(param_1) + 0x10;
        int iVar8;

        do
        {
            iVar8 = *reinterpret_cast<unsigned char*>(piVar6);
            piVar6 = piVar6 + 1;
        } while (static_cast<char>(iVar8) != '\0');

        char* pcVar7 = pcVar3;

        do
        {
            cVar2 = *pcVar7;
            pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');

        iVar8 = _strnicmp(
            piVar6 - 1 - (pcVar7 - (pcVar3 + 1)),
            pcVar3,
            static_cast<std::size_t>(pcVar5 - (pcVar3 + 1)));

        if (iVar8 == 0)
            break;

        local_8 = local_8 + 1;

        if (1 < local_8)
            return param_1;
    }

    char* piVar6 = reinterpret_cast<char*>(param_1) + 0x10;
    int iVar8;

    do
    {
        iVar8 = *reinterpret_cast<unsigned char*>(piVar6);
        piVar6 = piVar6 + 1;
    } while (static_cast<char>(iVar8) != '\0');

    char* pcVar5 = PTR_s__dirt_10037588[local_8];
    char* pcVar3 = pcVar5 + 1;

    char cVar2;
    do
    {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');

    strncpy_s(
        local_28,
        0x20,
        reinterpret_cast<char*>(param_1) + 0x10,
        static_cast<std::size_t>(
            (piVar6 - 1 - (reinterpret_cast<char*>(param_1) + 0x10)) -
            (pcVar5 - pcVar3)));

    int* matched =
        reinterpret_cast<LookupFunction>(0x7f39f0)(
            param_2,
            local_28);

    int iVar8_global = static_cast<int>(DAT_1003aacc);

    if (matched != nullptr)
    {
        unsigned int uVar10 =
            *reinterpret_cast<unsigned int*>(*param_1 + 0x0c);

        unsigned int uVar4 =
            *reinterpret_cast<unsigned int*>(*param_1 + 0x10);

        if (static_cast<int>(uVar10) <= static_cast<int>(uVar4))
            uVar10 = uVar4;

        uVar4 =
            *reinterpret_cast<unsigned int*>(*matched + 0x0c);

        if (uVar10 <= uVar4)
            uVar10 = uVar4;

        uVar4 =
            *reinterpret_cast<unsigned int*>(*matched + 0x10);

        if (uVar10 <= uVar4)
            uVar10 = uVar4;

        int iVar11;

        if (uVar10 < 0x401)
        {
            if (uVar10 < 0x201)
            {
                iVar11 =
                    ((0U - static_cast<unsigned int>(0x100 < uVar10)) & 0x100U) +
                    0x100U;
            }
            else
            {
                iVar11 = 0x400;
            }
        }
        else
        {
            iVar11 = 0x800;
        }

        *reinterpret_cast<int**>(
            static_cast<std::uintptr_t>(
                iVar8_global + 8 +
                reinterpret_cast<std::uintptr_t>(matched))) = param_1;

        unsigned int* puVar1 =
            reinterpret_cast<unsigned int*>(
                static_cast<std::uintptr_t>(
                    iVar8_global +
                    reinterpret_cast<std::uintptr_t>(param_1)));

        puVar1[1] =
            static_cast<unsigned int>(
                reinterpret_cast<std::uintptr_t>(matched));

        *puVar1 = 4;

        unsigned int uVar9 =
            reinterpret_cast<AllocateFunction>(0x7fb230)(
                static_cast<unsigned int>(iVar11),
                static_cast<unsigned int>(iVar11),
                0,
                5);

        uVar9 =
            reinterpret_cast<InitializeFunction>(0x7f37c0)(uVar9);

        puVar1[3] = uVar9;
    }

    return param_1;
}