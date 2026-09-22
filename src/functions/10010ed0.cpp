#include <cstdint>

std::uint32_t* __cdecl FUN_10016846(std::uint32_t* param_1);

extern "C" std::uint32_t* __cdecl FUN_10010ed0(
    std::uint32_t* param_1,
    char* param_2)
{
    char cVar3;
    std::uint32_t* puVar4;
    std::uint32_t* puVar5;
    char* pcVar1;
    char* pcVar2;
    char* pcVar6;

    if (*param_2 == '\0')
    {
        return param_1;
    }

    if (param_2[1] == '\0')
    {
        puVar5 = FUN_10016846(param_1);
        return puVar5;
    }

    do
    {
        cVar3 = *reinterpret_cast<char*>(param_1);

        do
        {
            puVar5 = param_1;
            param_1 = reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<char*>(puVar5) + 1);

            if (cVar3 == *param_2)
            {
                break;
            }

            if (cVar3 == '\0')
            {
                return nullptr;
            }

            cVar3 = *reinterpret_cast<char*>(param_1);
        }
        while (true);

        cVar3 = *reinterpret_cast<char*>(param_1);
        pcVar6 = param_2;
        puVar4 = puVar5;

        if (cVar3 != param_2[1])
        {
            continue;
        }

        do
        {
            if (pcVar6[2] == '\0')
            {
                return puVar5;
            }

            if (*reinterpret_cast<char*>(
                    reinterpret_cast<char*>(puVar4) + 2) != pcVar6[2])
            {
                break;
            }

            pcVar1 = pcVar6 + 3;

            if (*pcVar1 == '\0')
            {
                return puVar5;
            }

            pcVar2 = reinterpret_cast<char*>(puVar4) + 3;
            pcVar6 = pcVar6 + 2;
            puVar4 = reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<char*>(puVar4) + 2);
        }
        while (*pcVar1 == *pcVar2);
    }
    while (true);
}